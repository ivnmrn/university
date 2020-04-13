#include <stdio.h>
#include <stdbool.h>

#define MAX_NAME_LEN 15
#define TIME_TO_EMPTY 60
#define TIME_TO_UP 120
#define NUMBER_OF_STRING 2
#define MAX_STRING_SIZE 7

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

/* read tFairgroundRide */
void readFairgroundRide(tFairgroundRide *fRide, int *people, char orderRide[NUMBER_OF_STRING]) {
    int x = 0;
    printf("ENTER DATA FOR %s FAIRGROUND RIDE >>\n", orderRide);
    printf("NAME >>\n");
    scanf("%s", (fRide[x].name));
    printf("ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >>\n");
    scanf("%d", &(fRide[x].accessHeight.lessThan100));
    printf("ACCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >>\n");
    scanf("%d", &(fRide[x].accessHeight.between100_120));
    printf("ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >>\n");
    scanf("%d", &(fRide[x].accessHeight.between120_140));
    printf("ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >>\n");
    scanf("%d", &(fRide[x].accessHeight.greaterThan140));
    printf("TRIP DURATION >>\n");
    scanf("%d", &(fRide[x].durationTrip));
    printf("NUMBER OF PERSONS ON A TRIP >> \n");
    scanf("%d", &(fRide[x].numPersonsTrip));
    printf("ENTER THE PEOPLE IN THE QUEUE OF FAIRGROUND RIDE 1  >>\n");
    scanf("%d", &people[x]);
}

/* write best option */
void writeFairgroundRide(tFairgroundRide fRide) {
    printf("RESULTS: \n");
    printf("NAME: %s\n", fRide.name);
    printf("ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >> %d\n", fRide.accessHeight.lessThan100);
    printf("ACCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >> %d\n", fRide.accessHeight.between100_120);
    printf("ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >> %d\n", fRide.accessHeight.between120_140);
    printf("ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-ALLOWED) >> %d\n", fRide.accessHeight.greaterThan140);
    printf("TRIP DURATION: %d\n", fRide.durationTrip);
    printf("NUMBER OF PERSONS ON A TRIP: %d\n", fRide.numPersonsTrip);
}


int waitingTime(tFairgroundRide fRide, int people) {
    int waiting = (fRide.durationTrip+TIME_TO_EMPTY+TIME_TO_UP)*(people/fRide.numPersonsTrip);
    return waiting;
}

int accessWithoutCompanion(tFairgroundRide fRide, int height) {
    tFairgroundRideAccess *result=NULL;
    if (height >= 100) {
        if (height >= 100 && height <= 120) {
            result = &(fRide.accessHeight.between100_120);
        }
        else if (height > 120 && height <= 140) {
            result = &(fRide.accessHeight.between120_140);
        }
        else {
            result = &(fRide.accessHeight.greaterThan140);
        }
    }
    else {
        result = &(fRide.accessHeight.lessThan100);
    }
    if (*result == 2) {
        *result = true;
    }
    else {
        *result = false;
    }
    return *result;
}

void selectFairgroundRide(tFairgroundRide fRide1, tFairgroundRide fRide2, int people1, int people2, int height) {
    int accessRide1, accessRide2, timeWitingRide1, timeWitingRide2;

    accessRide1 = accessWithoutCompanion(fRide1, height);
    accessRide2 = accessWithoutCompanion(fRide2, height);
    timeWitingRide1 = waitingTime(fRide1, people1);
    timeWitingRide2 = waitingTime(fRide2, people2);

    if (accessRide1 == accessRide2) {
        if (timeWitingRide1 > timeWitingRide2) {
            writeFairgroundRide(fRide2);
        }
        else {
            writeFairgroundRide(fRide1);
        }
    }
    else {
        if (accessRide1 < accessRide2) {
            writeFairgroundRide(fRide2);
        }
        else {
            writeFairgroundRide(fRide1);
        }
    }
}

int main() {
    /* variables */
    int height, x;
    int peopleInQue[2];
    tFairgroundRide fRide[2];
    char orderRide[NUMBER_OF_STRING][MAX_STRING_SIZE] = {"FIRST", "SECOND"};

    /* input and creation dataStructs */
    for (int x = 0; x < 2; ++x) {
        readFairgroundRide(&fRide[x], &peopleInQue[x], orderRide[x]);
    }

    printf("ENTER THE HEIGHT >> \n");
    scanf("%d", &height);
    selectFairgroundRide(fRide[0], fRide[1], peopleInQue[0], peopleInQue[1], height);
}

