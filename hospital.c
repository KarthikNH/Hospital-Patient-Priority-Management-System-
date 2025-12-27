#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct Patient {
    int id;
    char name[30];
    int priority;   // 1 = Low, 5 = Critical
};

struct Patient pq[MAX];
int size = 0;

/* ---------- File Handling ---------- */
void loadFromFile() {
    FILE *fp = fopen("patients.txt", "r");
    if (fp == NULL)
        return;

    while (fscanf(fp, "%d %s %d",
                  &pq[size].id,
                  pq[size].name,
                  &pq[size].priority) != EOF) {
        size++;
    }
    fclose(fp);
}

void saveToFile() {
    FILE *fp = fopen("patients.txt", "w");
    if (fp == NULL)
        return;

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d %s %d\n",
                pq[i].id,
                pq[i].name,
                pq[i].priority);
    }
    fclose(fp);
}

/* ---------- Core Functions ---------- */
void addPatient(int id, char name[], int priority) {
    if (size == MAX) {
        printf("Patient queue is full!\n");
        return;
    }

    pq[size].id = id;
    strcpy(pq[size].name, name);
    pq[size].priority = priority;
    size++;

    saveToFile();
    printf("Patient added successfully.\n");
}

void treatPatient() {
    if (size == 0) {
        printf("No patients to treat.\n");
        return;
    }

    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (pq[i].priority > pq[maxIndex].priority)
            maxIndex = i;
    }

    printf("\nTreating Patient:\n");
    printf("ID       : %d\n", pq[maxIndex].id);
    printf("Name     : %s\n", pq[maxIndex].name);
    printf("Priority : %d\n", pq[maxIndex].priority);

    for (int i = maxIndex; i < size - 1; i++) {
        pq[i] = pq[i + 1];
    }
    size--;

    saveToFile();
}

void displayPatients() {
    if (size == 0) {
        printf("No patients in the queue.\n");
        return;
    }

    printf("\nPatient Queue:\n");
    printf("ID\tName\t\tPriority\n");
    printf("---------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%d\t%s\t\t%d\n",
               pq[i].id,
               pq[i].name,
               pq[i].priority);
    }
}

/* ---------- Main ---------- */
int main() {
    int choice, id, priority;
    char name[30];

    loadFromFile();   // Load saved patients

    while (1) {
        printf("\n--- Hospital Patient Priority System ---\n");
        printf("1. Add Patient\n");
        printf("2. Treat Patient\n");
        printf("3. Display Patients\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                printf("Enter Patient Name: ");
                scanf("%s", name);
                printf("Enter Priority (1-Low to 5-Critical): ");
                scanf("%d", &priority);
                addPatient(id, name, priority);
                break;

            case 2:
                treatPatient();
                break;

            case 3:
                displayPatients();
                break;

            case 4:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}