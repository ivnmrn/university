#include <stdio.h>
#include <stdbool.h>
#include "fairgroundRide.h"

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
	
	/* input height */
    printf("ENTER THE HEIGHT >> \n");
    scanf("%d", &height);
	/* call to selectFairgroundRide */
    selectFairgroundRide(fRide[0], fRide[1], peopleInQue[0], peopleInQue[1], height);
}