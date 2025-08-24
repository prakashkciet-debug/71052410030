#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for attendance record
typedef struct Attendance {
    int studentID;
    char date[20];
    char status[10];  // "Present" or "Absent"
    struct Attendance *next;
} Attendance;

// Function prototypes
Attendance* createRecord(int id, char *date, char *status);
void addRecord(Attendance **head, int id, char *date, char *status);
void deleteRecord(Attendance **head, int id, char *date);
void searchRecord(Attendance *head, int id, char *date);
void displayRecords(Attendance *head, char *date);
void displayReverse(Attendance *head);
Attendance* cloneList(Attendance *head);
void freeList(Attendance *head);

int main() {
    Attendance *head = NULL;
    int choice, id;
    char date[20], status[10];

    while (1) {
        printf("\n--- Student Attendance Monitoring System ---\n");
        printf("1. Add Attendance Record\n");
        printf("2. Delete Attendance Record\n");
        printf("3. Search Attendance\n");
        printf("4. Display Attendance for a Date\n");
        printf("5. Reverse Attendance Display\n");
        printf("6. Clone Attendance List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Student ID: ");
            scanf("%d", &id);
            printf("Enter Date (DD-MM-YYYY): ");
            scanf("%s", date);
            printf("Enter Status (Present/Absent): ");
            scanf("%s", status);
            addRecord(&head, id, date, status);
            break;
        case 2:
            printf("Enter Student ID to delete: ");
            scanf("%d", &id);
            printf("Enter Date (DD-MM-YYYY): ");
            scanf("%s", date);
            deleteRecord(&head, id, date);
            break;
        case 3:
            printf("Enter Student ID to search: ");
            scanf("%d", &id);
            printf("Enter Date (DD-MM-YYYY): ");
            scanf("%s", date);
            searchRecord(head, id, date);
            break;
        case 4:
            printf("Enter Date (DD-MM-YYYY): ");
            scanf("%s", date);
            displayRecords(head, date);
            break;
        case 5:
            printf("\nAttendance Records in Reverse Order:\n");
            displayReverse(head);
            break;
        case 6: {
            Attendance *clonedList = cloneList(head);
            printf("\nCloned Attendance List:\n");
            displayRecords(clonedList, date); // just display all
            freeList(clonedList);
            break;
        }
        case 7:
            freeList(head);
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Create a new record
Attendance* createRecord(int id, char *date, char *status) {
    Attendance *newNode = (Attendance*)malloc(sizeof(Attendance));
    newNode->studentID = id;
    strcpy(newNode->date, date);
    strcpy(newNode->status, status);
    newNode->next = NULL;
    return newNode;
}

// Add record at the end
void addRecord(Attendance **head, int id, char *date, char *status) {
    Attendance *newNode = createRecord(id, date, status);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Attendance *temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

// Delete record
void deleteRecord(Attendance **head, int id, char *date) {
    Attendance *temp = *head, *prev = NULL;
    while (temp) {
        if (temp->studentID == id && strcmp(temp->date, date) == 0) {
            if (prev == NULL) *head = temp->next;
            else prev->next = temp->next;
            free(temp);
            printf("Record deleted.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Record not found.\n");
}

// Search record
void searchRecord(Attendance *head, int id, char *date) {
    while (head) {
        if (head->studentID == id && strcmp(head->date, date) == 0) {
            printf("Found: ID=%d, Date=%s, Status=%s\n", head->studentID, head->date, head->status);
            return;
        }
        head = head->next;
    }
    printf("Record not found.\n");
}

// Display all records for a given date
void displayRecords(Attendance *head, char *date) {
    int found = 0;
    while (head) {
        if (strcmp(head->date, date) == 0) {
            printf("ID=%d, Date=%s, Status=%s\n", head->studentID, head->date, head->status);
            found = 1;
        }
        head = head->next;
    }
    if (!found) printf("No records found for %s.\n", date);
}

// Recursive reverse display
void displayReverse(Attendance *head) {
    if (head == NULL) return;
    displayReverse(head->next);
    printf("ID=%d, Date=%s, Status=%s\n", head->studentID, head->date, head->status);
}

// Clone the linked list
Attendance* cloneList(Attendance *head) {
    if (!head) return NULL;
    Attendance *newHead = createRecord(head->studentID, head->date, head->status);
    Attendance *curr = newHead;
    head = head->next;
    while (head) {
        curr->next = createRecord(head->studentID, head->date, head->status);
        curr = curr->next;
        head = head->next;
    }
    return newHead;
}

// Free memory
void freeList(Attendance *head) {
    Attendance *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
