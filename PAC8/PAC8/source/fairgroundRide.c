#include <stdio.h>
#include <string.h>
#include "fairgroundRide.h"


void writeFairgroundRide(tFairgroundRide fRide){
	printf("NAME: %s\n", fRide.name);
	printf("CATEGORY: %d\n", fRide.category);
	printf("AREA OF THE MAP: %c\n", fRide.areaMap);
	printf("DURATION OF THE TRIP: %d\n", fRide.durationTrip);
	printf("AVERAGE WAITING TIME: %d\n", fRide.averageWaitingTime);
}

void copyFairgroundRide(tFairgroundRide fRideSrc, tFairgroundRide *fRideDst){
	strcpy(fRideDst->name,fRideSrc.name);
	fRideDst->category = fRideSrc.category;
	fRideDst->areaMap = fRideSrc.areaMap;
	fRideDst->durationTrip = fRideSrc.durationTrip;
	fRideDst->averageWaitingTime = fRideSrc.averageWaitingTime;
}

void getFairgroundRideObject(const char *str, tFairgroundRide *fRide){

	int aux_category;

	/* read fairground data */

	sscanf(str, "%s %d %c %d %d",
	fRide->name,
	&aux_category,
	&fRide->areaMap,
	&fRide->durationTrip,
	&fRide->averageWaitingTime);
	
	fRide->category=(tFairgroundRideCategory)aux_category;
}

void fairgroundRidesTableLoadDataFromFile(tFairgroundRidesTable *fRidesTable,const char* filename) {

	FILE *fin=0;
	char line[MAX_LINE];
	tFairgroundRide newfRide;

	/* Initialize the output table */
	fairgroundRidesTableInitialize(fRidesTable);

	/* Open the input file */
	if((fin=fopen(filename,"r"))!=NULL) {
		/* Read all the fairground rides */
		while(!feof(fin) && fRidesTable->nFairgroundRides<MAX_FRIDES) {
			/* Remove any content from the line */
			line[0]='\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line,MAX_LINE-1,fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getFairgroundRideObject(line,&newfRide);
				/* Add the new fairground ride to the output table */
				fairgroundRidesTableAddElement(fRidesTable,newfRide);
			}
		}
		/* Close the file */
		fclose(fin);
		printf("FAIRGROUND RIDES SUCCESSFULLY LOADED!\n");
	}
}

void fairgroundRidesTableAddElement(tFairgroundRidesTable *fRidesTable, tFairgroundRide fRide) {

	/* Check if there is space enough for the new fairground ride */
	if(fRidesTable->nFairgroundRides>=MAX_FRIDES) {
		printf("ERROR ADDING A FAIRGROUND RIDE INTO TABLE\n");
	}
	else {
		/* Add the new fairground ride at the end of the table */
		copyFairgroundRide(fRide,&fRidesTable->fairgroundRides[fRidesTable->nFairgroundRides]);
		fRidesTable->nFairgroundRides++;
	}
}

void fairgroundRidesTableInitialize(tFairgroundRidesTable *tFairgroundRide) {
    tFairgroundRide->nFairgroundRides = 0;
}

void fairgroundRidesTableFilter(tFairgroundRidesTable *fRidesTable, char area, tFairgroundRideCategory category, tFairgroundRidesTable *myfRidesTable) {

	int positionMyTable = 0;

	fairgroundRidesTableInitialize(myfRidesTable);

	for (int x = 0; x < fRidesTable->nFairgroundRides; ++x) {
		if (fRidesTable->fairgroundRides[x].areaMap == area && fRidesTable->fairgroundRides[x].category == category ) {
			/* Add the matchs in a new table */
			copyFairgroundRide(fRidesTable->fairgroundRides[x], &myfRidesTable->fairgroundRides[positionMyTable]);
			positionMyTable += 1;
			myfRidesTable->nFairgroundRides++;
		}
	}
}

int myChoice(tFairgroundRidesTable myfRideTable) {

	int postionTable = 0;
	
	for (int x = 1; x<myfRideTable.nFairgroundRides; ++x) {
		if ((myfRideTable.fairgroundRides[x].durationTrip > myfRideTable.fairgroundRides[postionTable].durationTrip) ||
		(myfRideTable.fairgroundRides[x].durationTrip == myfRideTable.fairgroundRides[postionTable].durationTrip && 
		myfRideTable.fairgroundRides[x].averageWaitingTime < myfRideTable.fairgroundRides[postionTable].averageWaitingTime)) {
			postionTable += 1;
		}
	}
	return postionTable;
}
