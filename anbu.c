#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void initializeVehicles();
void initializeZones();
void addIncident();
void processIncident();
void updateActiveDispatches();
void releaseVehicle();
void displayMenu();

struct Vehicle {
    char Type[5];
    char ID[4];
    int zone;
    int status;
    struct Vehicle *next;
};
struct Vehicle *VHead = NULL;

struct Incident {
    int ID;
    int sivearity;
    int zone;
    struct Vehicle *assignedVehicle;
};
struct Incident inci[5];

struct Zone{
    int ID;
    struct Zone *left;
    struct Zone *right;
    struct Vehicle *vehicles;
};

int main() {
    
    

    int Systemrunning = 1;

    while(Systemrunning)
    {
        displayMenu();
        int choice;
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addIncident();
                break;
            case 2:
                processIncident();
                break;
            case 3:
                updateActiveDispatches();
                break;
            case 4:
                releaseVehicle();
                break;
            case 5:
                initializeVehicles();
                break;
            case 6:
                initializeZones();
                break;
            case 7:
                Systemrunning = 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }


    return 0;
}
void displayMenu()
    {
        printf("1. Add Incident\n");
        printf("2. Process Incident\n");
        printf("3. Update Active Dispatches\n");
        printf("4. Release Vehicle\n");
        printf("5. Initialize Vehicles\n");
        printf("6. Initialize Zones\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
    }

void initializeVehicles()
{
    
    static int i=0,n=0;
    int x;
    char type[5]="", tempID[4];
    printf("Initializing Vehicles...\n");
    printf("Enter the number of vehicles to initialize : ");
    scanf("%d",&x);
    n=n+x;
    static struct Vehicle *newVehicle, *prev = NULL;
    for (; i < n; i++) {
        newVehicle = malloc(sizeof(struct Vehicle ));
        printf("Enter details for vehicle %d:\n", i + 1);
        printf("Type (AMB/FIR/POL): ");
        scanf("%s", newVehicle->Type);
        for (int j = 0; j < 3; j++) {
            
            type[j] = newVehicle->Type[j];
        }
        if (strcmp(type, "AMB") == 0) {
            newVehicle->ID[0] = 'A';
        } else if (strcmp(type, "FIR") == 0) {
            newVehicle->ID[0] = 'F';
        } else if (strcmp(type, "POL") == 0) {
            newVehicle->ID[0] = 'P';
        } else {
            printf("Invalid type.\n");
            initializeVehicles();
            return;
        }
        printf("ID (integer in XXX form): ");
        scanf("%s", tempID);
        for (int k = 1; k < 4; k++) {
            newVehicle->ID[k] = tempID[k-1];
        }
        newVehicle->zone= -1;
        newVehicle->status = 0;
        newVehicle->next = NULL;

        if (VHead == NULL) VHead = newVehicle;
        else prev->next = newVehicle;
        prev = newVehicle;

        
    }
    struct Vehicle *temp = VHead;
        for (; temp != NULL; temp = temp->next) {
            printf("Vehicle ID: %3s, Type: %3s, Zone: %d, Status: %d\n", temp->ID, temp->Type, temp->zone, temp->status);
        }
}
void releaseVehicle()
{
    if (VHead == NULL) {
        printf("No vehicles initialized.\n");
        return;
    }


    printf("\n--- All Vehicles ---\n");
    struct Vehicle *temp = VHead;
    while (temp != NULL) {
        printf("Vehicle ID: %s, Type: %s, Zone: %d, Status: %d (%s)\n",
               temp->ID, temp->Type, temp->zone, temp->status,
               temp->status == 1 ? "Available" : "Busy");
        temp = temp->next;
    }
    printf("--------------------\n\n");

    char id[5];
    printf("Enter Vehicle ID to release: ");
    scanf("%s", id);

    struct Vehicle *curr = VHead;
    while (curr != NULL) {
        if (strcmp(curr->ID,id)) {
            if (curr->status == 0) {
                curr->status = 1; 
                printf("Vehicle ID %s is now released and available.\n", id);
            } else {
                printf("Vehicle ID %s is already available.\n", id);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Vehicle ID %s not found.\n", id);

}
void updateActiveDispatches(){}
void processIncident(){}
void addIncident(){}
void initializeZones(){}
