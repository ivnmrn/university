#include <stdio.h>

#define MAX_NAME_LEN 15
#define TIME_TO_EMPTY 60
#define TIME_TO_UP 120

typedef enum {FORBIDDEN, ALLOWED_WITH_COMPANION, ALLOWED} tFairgroundRideAccess;

typedef struct {
    tFairgroundRideAccess lessThan100;
    tFairgroundRideAccess between100_120;
    tFairgroundRideAccess between120_140;
    tFairgroundRideAccess greaterThan140;
} tFairgroundRideHeightRequirement;

typedef struct {
    char name[MAX_NAME_LEN];
    tFairgroundRideHeightRequirement accessHeight;
    int durationTrip;
    int numPersonsTrip;
} tFairgroundRide;

void readFairgroundRideAccess() {
    printf("ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN,1-ALLOWED_WITH_COMPANION, 2 -ALLOWED):\n");
    scanf("%d", (fRide1->accessHeight));
    printf("ACCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2 -ALLOWED):\n");
    scanf("%d", (fRide1->accessHeight));
    printf("ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed):\n");
    scanf("%d", (fRide1->accessHeight));
    printf("ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed):\n");
    scanf("%d", (fRide1->accessHeight));
}

void readFairgroundRide(tFairgroundRide *fRide, int people) {
    int x = 0;
    printf("ENTER THE PEOPLE IN THE QUEUE OF FAIRGROUND RIDE %d >>\n", x+1);
    scanf("%d", &people);
    printf("ENTER DATA FOR FIRST FAIRGROUND RIDE >>\n");
    printf("NAME >>\n");
    scanf("%s", (fRide[x].name));
    printf("TRIP DURATION:\n");
    scanf("%d", &(fRide[x].durationTrip));
    printf("NUMBER OF PERSONS ON A TRIP:\n");
    scanf("%d", &(fRide[x].numPersonsTrip));
}

// void writeFairgroundRide() {
//     printf("RESULTS: \n");
//     printf("NAME %s\n", name);
//     printf("ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN,1-ALLOWED_WITH_COMPANION, 2 -ALLOWED):\n");
//     printf("ACCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2 -ALLOWED):\n");
//     printf("ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed):\n");
//     printf("ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed):\n");
//     printf("TRIP DURATION:\n");
//     printf("NUMBER OF PERSONS ON A TRIP:\n");
// }

// int waitingTime(tFairgroundRide fRide, int people) {
//     int timeWaiting;
//     int timeWaitingRide = (fRide.durationTrip+TIME_TO_EMPTY+TIME_TO_UP)*(people/fRide.numPersonsTrip);
//     return timeWaiting;
// }

// int accessWithoutCompanion(tFairgroundRide fRide int *height) {
//     // height between tFairgroundRideHeightRequirement values
//     if (height => 100) {
//         if (height >= 100 && height >= 140) {
//             //conn compañia
//         }
//         else {
//             //solo
//         }
//     }
//     else {
//         // no puede entrar
//     }
//     return 0;
// }

// void selectFairgroundRide(tFairgroundRide fRide1, tFairgroundRide Ride2, int people1, int people2, int height) {

// }

// copyFairgroundRide() {

// }



int main() {


    int height, peopleInQue1, peopleInQue2;
    tFairgroundRide fRide[2];
    
    for (int x = 0; x < 2; ++x) {
        readFairgroundRide(&fRide[x], peopleInQue1);
    }

   printf("ENTER THE HEIGHT >> \n");
   scanf("%d", &height, peopleInQue1);
   //writeFairgroundRide(elganador, );

}
