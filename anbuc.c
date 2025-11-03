#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Vehicle {
    char Type[5];
    char ID[5];
    int zone;
    int status; 
    struct Vehicle *next;
};

struct Vehicle *AmbHead = NULL;
struct Vehicle *FireHead = NULL;
struct Vehicle *PolHead = NULL;

struct Incident {
    int ID;
    int severity;
    int zone;
    char requiredType[5];  
    struct Vehicle *assignedVehicle;
};
struct Incident inci[10];
int incidentCount = 0;

struct Zone {
    int ID;
    char name[30];
    struct Zone *left;
    struct Zone *right;
};

struct Zone *zoneRoot = NULL;

#define MAX_INCIDENTS 10

struct IncidentQueue {
    struct Incident inci[MAX_INCIDENTS];
    int front;
    int rear;
};

struct IncidentQueue highQ = { .front = -1, .rear = -1 };
struct IncidentQueue medQ = { .front = -1, .rear = -1 };
struct IncidentQueue lowQ = { .front = -1, .rear = -1 };

int isEmpty(struct IncidentQueue *q) {
    return (q->front == -1);
}

int isFull(struct IncidentQueue *q) {
    return (q->rear == MAX_INCIDENTS - 1);
}

void enqueue(struct IncidentQueue *q, struct Incident inc) {
    if (isFull(q)) {
        printf("Queue full! Cannot add more incidents.\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->inci[q->rear] = inc;
}

struct Incident dequeue(struct IncidentQueue *q) {
    struct Incident temp = q->inci[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return temp;
}



void displayMenu();
void initializeVehicles();
void initializeZones();
void displayZones(struct Zone *root);
void addIncident();
void processIncident();
void releaseVehicle();
struct Zone* insertZone(struct Zone *root, int ID, char name[]);
struct Zone* findZoneByName(struct Zone *root, char name[]);
void displayAllVehicles();

void displayMenu() {
    printf("\n------ Emergency Dispatch System ------\n");
    printf("1. Initialize Zones\n");
    printf("2. Display Zones\n");
    printf("3. Initialize Vehicles\n");
    printf("4. Release Vehicle\n");
    printf("5. Display All Vehicles\n");
    printf("6. Add Incident\n");
    printf("7. Process Incident\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}


struct Vehicle* createVehicle(char type[5], char idNum[4]) {
    struct Vehicle *newV = malloc(sizeof(struct Vehicle));
    strcpy(newV->Type, type);

    if (strcmp(type, "AMB") == 0) newV->ID[0] = 'A';
    else if (strcmp(type, "FIR") == 0) newV->ID[0] = 'F';
    else if (strcmp(type, "POL") == 0) newV->ID[0] = 'P';

    strcpy(newV->ID + 1, idNum);
    newV->zone = -1;
    newV->status = 1;
    newV->next = NULL;
    return newV;
}

void initializeVehicles() {
    int n;
    char type[5], idNum[4];
    printf("Enter number of vehicles to initialize: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for vehicle %d:\n", i + 1);
        printf("Type (AMB/FIR/POL): ");
        scanf("%s", type);
        printf("ID (3 digits): ");
        scanf("%s", idNum);

        struct Vehicle *newV = createVehicle(type, idNum);

        if (strcmp(type, "AMB") == 0) {
            newV->next = AmbHead;
            AmbHead = newV;
        } else if (strcmp(type, "FIR") == 0) {
            newV->next = FireHead;
            FireHead = newV;
        } else if (strcmp(type, "POL") == 0) {
            newV->next = PolHead;
            PolHead = newV;
        } else {
            printf("Invalid vehicle type, skipping.\n");
            free(newV);
        }
    }

    printf("\nVehicles initialized successfully.\n");
    displayAllVehicles();
}

void displayVehicleList(struct Vehicle *head, char type[5]) {
    printf("\n--- %s Vehicles ---\n", type);
    struct Vehicle *temp = head;
    if (!temp) {
        printf("No %s vehicles.\n", type);
        return;
    }
    while (temp) {
        printf("ID: %s | Zone: %d | Status: %s\n",
               temp->ID, temp->zone,
               temp->status == 1 ? "Available" : "Busy");
        temp = temp->next;
    }
}

void displayAllVehicles() {
    displayVehicleList(AmbHead, "AMB");
    displayVehicleList(FireHead, "FIR");
    displayVehicleList(PolHead, "POL");
}

struct Zone* createZone(int ID, char name[]) {
    struct Zone *newZone = malloc(sizeof(struct Zone));
    newZone->ID = ID;
    strcpy(newZone->name, name);
    newZone->left = newZone->right = NULL;
    return newZone;
}

struct Zone* insertZone(struct Zone *root, int ID, char name[]) {
    if (root == NULL)
        return createZone(ID, name);

    if (ID < root->ID)
        root->left = insertZone(root->left, ID, name);
    else if (ID > root->ID)
        root->right = insertZone(root->right, ID, name);
    
    return root;
}


void displayZones(struct Zone *root) {
    if (root == NULL) return;
    displayZones(root->left);
    printf("Zone ID: %d | Name: %s\n", root->ID, root->name);
    displayZones(root->right);
}


void initializeZones() {
    int n, id;
    char name[30];

    printf("\n=== INITIALIZE ZONES ===\n");
    printf("Enter number of zones to create: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Zone %d:\n", i + 1);
        printf("Zone ID: ");
        scanf("%d", &id);
        printf("Zone Name: ");
        scanf("%s", name);
        zoneRoot = insertZone(zoneRoot, id, name);
    }

    printf("\nZones initialized successfully!\n");
}

struct Zone* findZoneByName(struct Zone *root, char name[]) {
    if (root == NULL) return NULL;
    if (strcmp(root->name, name) == 0)
        return root;
    struct Zone *leftSearch = findZoneByName(root->left, name);
    if (leftSearch) return leftSearch;
    return findZoneByName(root->right, name);
}


void addIncident() {
    struct Incident newInc;

    printf("\nEnter Incident Details:\n");
    newInc.ID = incidentCount + 1;
    printf("Enter Severity (1 - Low, 2 - Medium, 3 - High): ");
    scanf("%d", &newInc.severity);
    printf("Required Vehicle Type (AMB/FIR/POL): ");
    scanf("%s", newInc.requiredType);

    displayZones(zoneRoot);

    printf("Enter Zone Name: ");
    char zoneName[30];
    scanf("%s", zoneName);

    struct Zone *foundZone = findZoneByName(zoneRoot, zoneName);
    if (!foundZone) {
        printf("Zone not found! Please check spelling.\n");
        return;
    }

    newInc.zone = foundZone->ID;
    newInc.assignedVehicle = NULL;

    if (newInc.severity == 3)
        enqueue(&highQ, newInc);
    else if (newInc.severity == 2)
        enqueue(&medQ, newInc);
    else
        enqueue(&lowQ, newInc);

    incidentCount++;
    printf("Incident %d recorded and added to severity queue.\n", newInc.ID);
}



struct Vehicle* getAvailableVehicle(char type[5]) {
    struct Vehicle *temp = NULL;
    if (strcmp(type, "AMB") == 0) temp = AmbHead;
    else if (strcmp(type, "FIR") == 0) temp = FireHead;
    else if (strcmp(type, "POL") == 0) temp = PolHead;

    while (temp) {
        if (temp->status == 1) return temp;
        temp = temp->next;
    }
    return NULL;
}

void processIncident() {
    struct Incident current;
    int found = 0;

    if (!isEmpty(&highQ)) {
        current = dequeue(&highQ);
        found = 1;
    } else if (!isEmpty(&medQ)) {
        current = dequeue(&medQ);
        found = 1;
    } else if (!isEmpty(&lowQ)) {
        current = dequeue(&lowQ);
        found = 1;
    }

    if (!found) {
        printf("No incidents to process.\n");
        return;
    }

    struct Vehicle *available = getAvailableVehicle(current.requiredType);
    if (available) {
        available->status = 0;
        available->zone = current.zone;
        current.assignedVehicle = available;
        printf("Processed Incident %d -> Vehicle %s (%s) assigned [Severity %d]\n",
               current.ID, available->ID, available->Type, current.severity);
    } else {
        printf("No available %s vehicles for Incident %d\n",
               current.requiredType, current.ID);
    }
}



void releaseVehicle() {
    displayAllVehicles();
    char id[5];
    printf("Enter Vehicle ID to release: ");
    scanf("%s", id);

    struct Vehicle *lists[3] = {AmbHead, FireHead, PolHead};
    for (int l = 0; l < 3; l++) {
        struct Vehicle *curr = lists[l];
        while (curr) {
            if (strcmp(curr->ID, id) == 0) {
                if (curr->status == 0) {
                    curr->status = 1;
                    curr->zone = -1;
                    printf("Vehicle %s is now released and available.\n", id);
                } else {
                    printf("Vehicle %s is already available.\n", id);
                }
                return;
            }
            curr = curr->next;
        }
    }
    printf("Vehicle %s not found.\n", id);
}


int main() {
    int SystemRunning = 1, choice;
    while (SystemRunning) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 6: addIncident(); break;
            case 7: processIncident(); break;
            case 4: releaseVehicle(); break;
            case 3: initializeVehicles(); break;
            case 1: initializeZones(); break;
            case 2: displayZones(zoneRoot); break;
            case 5: displayAllVehicles(); break;
            case 8: SystemRunning = 0; break;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
