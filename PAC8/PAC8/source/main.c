#include <stdio.h>
#include <string.h>
#include "fairgroundRide.h"

//main algorithm
int main(int argc, char **argv){

    char fileName[MAX_NAME];
    char areaMap;
    int category;

    tFairgroundRidesTable fRideTableIn, fRideTableOut;

    fRideTableIn.nFairgroundRides = 0;
    fRideTableIn.nFairgroundRides = 0;

    printf("LOAD DATA FROM FILE. ENTER THE NAME OF THE FILE >>\n");
    scanf("%s", fileName);
	getchar();
    fairgroundRidesTableLoadDataFromFile(&fRideTableIn, fileName);
    printf("ENTER THE AREA OF THE MAP (A CHARACTER) >>\n");
    scanf("%c", &areaMap);
	getchar();
    printf("%c\n", areaMap);
    printf("ENTER THE CATEGORY (0-STRONG, 1-MODERATE, 2-CHILDISH) >>\n");
    scanf("%d", &category);
    fairgroundRidesTableFilter(&fRideTableIn, areaMap, category);
}
