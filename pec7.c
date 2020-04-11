#include <stdio.h>

#define MAX_NAME_LEN 15
#define TIME_TO_EMPTY 60
#define TIME_TO_UP 120

typedef enum {FORBIDDEN, ALLOWED_WITH_COMPANION, ALLOWED} tFairgroundRideAccess;

/* atraction access requirement */
typedef struct {
    tFairgroundRideAccess lessThan100;
    tFairgroundRideAccess between100_120;
    tFairgroundRideAccess between120_140;
    tFairgroundRideAccess greaterThan140;
} tFairgroundRideHeightRequirement;

/* atraction requeriments */
typedef struct {
    char name[MAX_NAME_LEN];
    tFairgroundRideHeightRequirement accessHeight;
    int durationTrip;
    int numPersonsTrip;
} tFairgroundRide;

void readFairgroundRideAccess(tFairgroundRideHeightRequirement *fRide) {
    int x = 0;
    printf("ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN,1-ALLOWED_WITH_COMPANION, 2 -ALLOWED):\n");
    scanf("%d", &(fRide[x].lessThan100));
    printf("ACCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2 -ALLOWED):\n");
    scanf("%d", &(fRide[x].between100_120));
    printf("ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED):\n");
    scanf("%d", &(fRide[x].between120_140));
    printf("ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-alloALLOWEDwed):\n");
    scanf("%d", &(fRide[x].greaterThan140));
}

void readFairgroundRide(tFairgroundRide *fRide, tFairgroundRideHeightRequirement *fRideAccess, int *people) {
    int x = 0;
    printf("ENTER THE PEOPLE IN THE QUEUE OF FAIRGROUND RIDE %d >>\n", x+1);
    scanf("%d", &people[x]);
    printf("ENTER DATA FOR FIRST FAIRGROUND RIDE >>\n");
    printf("NAME >>\n");
    scanf("%s", (fRide[x].name));
    readFairgroundRideAccess(fRideAccess);
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
//     printf("ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED):\n");
//     printf("ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED):\n");
//     printf("TRIP DURATION:\n");
//     printf("NUMBER OF PERSONS ON A TRIP:\n");
// }

int waitingTime(tFairgroundRide fRide, int people) {
    int timeWaiting;
    int timeWaitingRide = (fRide.durationTrip+TIME_TO_EMPTY+TIME_TO_UP)*(people/fRide.numPersonsTrip);
    return timeWaiting;
}

int accessWithoutCompanion(tFairgroundRide fRide, int height) {
    int value = 0;

    if (height > 100) {
        if (height > 140) {
            if (fRide.accessHeight.greaterThan140 == 2) {
                value = 1;
            }
            else {
                value = 0;
            }
        }
        else if (height > 100 && height <120) {

        }
        else {

        }
    }
    else {
        if (fRide.accessHeight.lessThan100 == 2) {
            value = 1;
        }
        else {
            value = 0;
        }
    }

    return value;
}

void selectFairgroundRide(tFairgroundRide fRide1, tFairgroundRide Ride2, int people1, int people2, int height) {

}

int main() {
    /* variables */
    int height;
    int peopleInQue[2];
    tFairgroundRide fRide[2];
    tFairgroundRideHeightRequirement fRideAccess[2];

    /* input and creation dataStructs */
    for (int x = 0; x < 2; ++x) {
        readFairgroundRide(&fRide[x], &fRideAccess[x], &peopleInQue[x]);
    }

    printf("ENTER THE HEIGHT >> \n");
    scanf("%d", &height);
    accessWithoutCompanion(fRide[0], height);
    // selectFairgroundRide(fRide[0], fRide[1], peopleInQue[0], peopleInQue[1], height);
}
