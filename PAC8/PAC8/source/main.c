#include <stdio.h>
#include <string.h>
#include "fairgroundRide.h"

//main algorithm
int main(int argc, char **argv){

    char fileName[MAX_NAME];
    char areaMap;
    int category;

    tFairgroundRidesTable fRideTableIn, fRideTableOut;

    /* initialize  tables */
    fairgroundRidesTableInitialize(&fRideTableIn);
    fairgroundRidesTableInitialize(&fRideTableOut);

    /* load the parameters from file to table */
    printf("LOAD DATA FROM FILE. ENTER THE NAME OF THE FILE >>\n");
    scanf("%s", fileName);
	getchar();
    fairgroundRidesTableLoadDataFromFile(&fRideTableIn, fileName);

    /* filter the requires parameters */ 
    printf("ENTER THE AREA OF THE MAP (A CHARACTER) >>\n");
    scanf("%c", &areaMap);
	getchar();
    printf("ENTER THE CATEGORY (0-STRONG, 1-MODERATE, 2-CHILDISH) >>\n");
    scanf("%d", &category);
    fairgroundRidesTableFilter(&fRideTableIn, areaMap, category, &fRideTableOut);
    
    /* select and write the best option */
    int position = myChoice(&fRideTableOut);
    writeFairgroundRide(fRideTableOut.fairgroundRides[position]);
}
