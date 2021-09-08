#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fairgroundRide.h"
#include "util.h"

void getFairgroundRideStr(tFairgroundRide fairgroundRide, int maxSize, char *str) {

	int length= 0;
	
    // Build the string	(the content of the fields of the fairground ride structure is written into the string str)
	length = snprintf(str,maxSize-1,"%d %s %d %d %c %d %d %d %d %d %d %d %d %d %.2f %d",
             (int)fairgroundRide.id, 
			 fairgroundRide.name,
			 (int)fairgroundRide.type,
			 (int)fairgroundRide.category,
			 fairgroundRide.areaMap,
			 (int)fairgroundRide.state,
			 (int)fairgroundRide.accessHeight.lessThan100,
			 (int)fairgroundRide.accessHeight.between100_120,
			 (int)fairgroundRide.accessHeight.between120_140,
			 (int)fairgroundRide.accessHeight.greaterThan140,
			 fairgroundRide.averageWaitingTime,
			 fairgroundRide.durationTrip,
			 fairgroundRide.numPersonsTrip,
			 (int)fairgroundRide.allowsPayTicket,
			 fairgroundRide.ticketPrice,
			 (int)fairgroundRide.allowsFastPass);
	
	if (length>0) {
		str[length]='\0';
	}
}


void getFairgroundRideObject(const char *str, tFairgroundRide *fairgroundRide) {
	
	int aux_id, aux_type, aux_category, aux_state, 
			aux_accessLess100, aux_accessBetween100_120, aux_accessBetween120_140, aux_accessGreater140,
			aux_allowsPayTicket, aux_allowsFastPass;

	/* The content of the string str is parsed into the fields of the fairground ride structure */
	sscanf(str, "%d %s %d %d %c %d %d %d %d %d %d %d %d %d %f %d",
			&aux_id, 
			fairgroundRide->name,
			&aux_type,
			&aux_category,
			&(fairgroundRide->areaMap),
			&aux_state,
			&aux_accessLess100,
			&aux_accessBetween100_120,
			&aux_accessBetween120_140,
			&aux_accessGreater140,
			&(fairgroundRide->averageWaitingTime),
			&(fairgroundRide->durationTrip),
			&(fairgroundRide->numPersonsTrip),
			&aux_allowsPayTicket,
			&(fairgroundRide->ticketPrice),
			&aux_allowsFastPass);

	fairgroundRide->id = (tFairgroundRideId)aux_id;
	fairgroundRide->type = (tFairgroundRideType)aux_type;
	fairgroundRide->category = (tFairgroundRideCategory)aux_category;
	fairgroundRide->state = (tFairgroundRideState)aux_state;
	fairgroundRide->accessHeight.lessThan100 = (tFairgroundRideAccess)aux_accessLess100;
	fairgroundRide->accessHeight.between100_120 = (tFairgroundRideAccess)aux_accessBetween100_120;
	fairgroundRide->accessHeight.between120_140 = (tFairgroundRideAccess)aux_accessBetween120_140;
	fairgroundRide->accessHeight.greaterThan140 = (tFairgroundRideAccess)aux_accessGreater140;
	fairgroundRide->allowsPayTicket = (bool)aux_allowsPayTicket;
	fairgroundRide->allowsFastPass = (bool)aux_allowsFastPass;
}

void fairgroundRideAccessCopy(tFairgroundRideHeightRequirement *dst, tFairgroundRideHeightRequirement src)
{
	dst->lessThan100 = src.lessThan100;
	dst-> between100_120= src.between100_120;
	dst->between120_140 = src.between120_140;
	dst->greaterThan140 = src.greaterThan140;
}

void fairgroundRideCopy(tFairgroundRide *dst, tFairgroundRide src) 
{    
	dst->id = src.id;
	strcpy(dst->name, src.name);
	dst->type = src.type;
	dst->category = src.category;
	dst->areaMap = src.areaMap;
	dst->state = src.state;
	fairgroundRideAccessCopy(&(dst->accessHeight), src.accessHeight);
	dst->averageWaitingTime = src.averageWaitingTime;
	dst->durationTrip = src.durationTrip;
	dst->numPersonsTrip = src.numPersonsTrip;
	dst->allowsPayTicket = src.allowsPayTicket;
	dst->ticketPrice = src.ticketPrice;
	dst->allowsFastPass = src.allowsFastPass;
}


int fairgroundRideAccessCompare(tFairgroundRideHeightRequirement obj1, tFairgroundRideHeightRequirement obj2) 
{
	int result = 0;
	
	if (obj1.lessThan100 > obj2.lessThan100) {
		result = 1;
	}
	else if (obj1.lessThan100 < obj2.lessThan100) {
		result = -1;
	}
	else {
		if (obj1.between100_120 > obj2.between100_120) {
			result = 1;
		}
		else if (obj1.between100_120 < obj2.between100_120) {
			result = -1;
		}
		else {
			if (obj1.between120_140 > obj2.between120_140) {
				result = 1;
			}
			else if (obj1.between120_140 < obj2.between120_140) {
				result = -1;
			}
			else {
				if (obj1.greaterThan140 > obj2.greaterThan140) {
					result = 1;
				} 
				else if (obj1.greaterThan140 < obj2.greaterThan140) {
					result = -1;
				}
			}
		}
	}
		
	return result;
}

int fairgroundRideCompare(tFairgroundRide obj1, tFairgroundRide obj2)
{
    int result = 0;
	
	result = stringCompareUpper(obj1.name, obj2.name);
	if (result == 0) 
	{
		if (obj1.type > obj2.type) 			result = 1;
		else if (obj1.type < obj2.type)		result = -1;
		else {
			if (obj1.category > obj2.category)		result = 1;
			else if (obj1.category < obj2.category)	result = -1;
			else {
				if (obj1.areaMap > obj2.areaMap)		result = 1;
				else if (obj1.areaMap < obj2.areaMap)	result = -1;
				else {
					if (obj1.state > obj2.state)			result = 1;
					else if (obj1.state < obj2.state)		result = -1;
					else {
						result = fairgroundRideAccessCompare(obj1.accessHeight, obj2.accessHeight);
						if (result == 0) {
							if (obj1.averageWaitingTime > obj2.averageWaitingTime)			result = 1;
							else if (obj1.averageWaitingTime < obj2.averageWaitingTime)		result = -1;
							else {
								if (obj1.durationTrip > obj2.durationTrip)			result = 1;
								else if (obj1.durationTrip < obj2.durationTrip)		result = -1;
								else {
									if (obj1.numPersonsTrip > obj2.numPersonsTrip)			result = 1;
									else if (obj1.numPersonsTrip < obj2.numPersonsTrip)		result = -1;
									else {
										result = booleanCompare(obj1.allowsPayTicket, obj2.allowsPayTicket);
										if (result == 0) {
											if (obj1.ticketPrice > obj2.ticketPrice)			result = 1;
											else if (obj1.ticketPrice < obj2.ticketPrice)		result = -1;
											else {
												result = booleanCompare(obj1.allowsFastPass, obj2.allowsFastPass);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
 
	return result;
}


void fairgroundRideTableInit(tFairgroundRideTable *fairgroundRideTable) {
	
	fairgroundRideTable->nFairgroundRides = 0;
}

void fairgroundRideTableAddElement(tFairgroundRideTable *fairgroundRideTable, tFairgroundRide fairgroundRide, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new fairground ride */
	if(fairgroundRideTable->nFairgroundRides>=MAX_FAIRGROUNDRIDES)
		*retVal = ERR_MEMORY;
		
	if (*retVal == OK) {
		/* Add the new fairground ride to the end of the table */
		fairgroundRideCopy(&fairgroundRideTable->table[fairgroundRideTable->nFairgroundRides], fairgroundRide);
		fairgroundRideTable->nFairgroundRides++;
	}
	
}

int fairgroundRideTableFindById(tFairgroundRideTable fairgroundRideTable, tFairgroundRideId id) {

	int idx = NO_FAIRGROUNDRIDE;
	
	int i=0;
	while(i< fairgroundRideTable.nFairgroundRides && idx==NO_FAIRGROUNDRIDE) {
		/* Check if the id is the same */
		if(id==fairgroundRideTable.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void fairgroundRideTableSaveToFile(tFairgroundRideTable fairgroundRideTable, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all fairground rides to the file */
        for(i=0;i<fairgroundRideTable.nFairgroundRides;i++) {
            getFairgroundRideStr(fairgroundRideTable.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void fairgroundRideTableLoadFromFile(tFairgroundRideTable *fairgroundRideTable, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
	tFairgroundRide newFairgroundRide;
	
	/* Initialize the output table */
	fairgroundRideTableInit(fairgroundRideTable);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the fairground rides */
		while(!feof(fin) && fairgroundRideTable->nFairgroundRides<MAX_FAIRGROUNDRIDES) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getFairgroundRideObject(line, &newFairgroundRide);
				/* Add the new fairground ride to the output table */
				fairgroundRideTableAddElement(fairgroundRideTable, newFairgroundRide, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

tFairgroundRideAccess fairgroundRideGetAccessByHeight(tFairgroundRide fairgroundRide, float height) 
{
	tFairgroundRideAccess access;
	if (height < HEIGHT_100) { 
		access = fairgroundRide.accessHeight.lessThan100;
	}
	else if (height >= HEIGHT_100 && height < HEIGHT_120) {
		access = fairgroundRide.accessHeight.between100_120;
	}
	else if (height >= HEIGHT_120 && height < HEIGHT_140) {
		access = fairgroundRide.accessHeight.between120_140;
	}
	else {
		access = fairgroundRide.accessHeight.greaterThan140;
	}
		
	return access;
} 

void visitorRecommendationByHeight(tVisitor visitor, 
                            tFairgroundRideTable fairgroundRides,
							char areaMap,
                            tFairgroundRideTable *result) 
{
    tError retVal; 
/*************** PR1 EX5A *****************/		
	int i;

	fairgroundRideTableInit(result);
	
	retVal = OK;
	i = 0;
	
	while (i < fairgroundRides.nFairgroundRides && retVal == OK) {
		if (fairgroundRides.table[i].areaMap == areaMap && fairgroundRides.table[i].state == WORKING && 
			fairgroundRideGetAccessByHeight(fairgroundRides.table[i], visitor.height) != FORBIDDEN)  {
				fairgroundRideTableAddElement(result, fairgroundRides.table[i], &retVal);
		}
		i++;
	}
/******************************************/	
}


float fairgroundRideGetRatio(tFairgroundRide fairgroundRide)
{
	return (fairgroundRide.averageWaitingTime * 60.0 / fairgroundRide.durationTrip);
}


int fairgroundRideGetWaitingTime(tFairgroundRide fairgroundRide, 
									int nVisitantsBefore, int minutesUpDown, int percentEmptySeats)
{
	int waitingTime = 0;
	int tripsBefore;
	int personsTrip = fairgroundRide.numPersonsTrip - (int)((fairgroundRide.numPersonsTrip * percentEmptySeats)/100);
	if (personsTrip > 0) {
		tripsBefore = (nVisitantsBefore/personsTrip);
		waitingTime = (tripsBefore * fairgroundRide.durationTrip/60) + (tripsBefore + 1) * minutesUpDown;
	}
	return waitingTime;

}

float fairgroundRideGetCostTrip(tFairgroundRide fairgroundRide, int percentatgeEmptySeats)
{
	int emptySeats = (int)(percentatgeEmptySeats * fairgroundRide.numPersonsTrip/100);
	return ((float)(fairgroundRide.numPersonsTrip - emptySeats) * fairgroundRide.ticketPrice);
}


bool fairgroundRideIsAccessAllowed(tFairgroundRide fairgroundRide, int height)
{
	return (fairgroundRide.state == WORKING && 
			( 
				( (height < HEIGHT_100) && fairgroundRide.accessHeight.lessThan100 != FORBIDDEN) ||
				( (height >= HEIGHT_100 && height < HEIGHT_120) && fairgroundRide.accessHeight.between100_120 != FORBIDDEN) ||
				( (height >= HEIGHT_120 && height < HEIGHT_140) && fairgroundRide.accessHeight.between120_140 != FORBIDDEN) ||
				( (height > HEIGHT_140) && fairgroundRide.accessHeight.greaterThan140 != FORBIDDEN) 
			));
}

bool fairgroundRideIsOutOfOrderByArea(tFairgroundRide fairgroundRide, char areaMap[2])
{
	return (fairgroundRide.state == OUT_OF_ORDER &&
			(fairgroundRide.areaMap == areaMap[0] || fairgroundRide.areaMap == areaMap[1]));
}

void fairgroundRideTableSelect(tFairgroundRideTable fairgroundRideTable, 
								tFairgroundRideType type, tFairgroundRideCategory category, char areaMap,
								tFairgroundRideTable *result)
{
	tError retVal; 
	int i;
	
	fairgroundRideTableInit(result);
	
	for (i = 0; i < fairgroundRideTable.nFairgroundRides; i++) {
		if (fairgroundRideTable.table[i].type == type &&
			fairgroundRideTable.table[i].category == category && 
			fairgroundRideTable.table[i].areaMap == areaMap)
		{
			fairgroundRideTableAddElement(result, fairgroundRideTable.table[i], &retVal);
		}
	} 
}



void fairgroundRideTableOutOfOrder(tFairgroundRideTable fairgroundRideTable, 
								char areaMap[2],
								tFairgroundRideTable *result)
{
	tError retVal; 
	int i;
	
	fairgroundRideTableInit(result);
	
	for (i = 0; i < fairgroundRideTable.nFairgroundRides; i++) {
		if (fairgroundRideIsOutOfOrderByArea(fairgroundRideTable.table[i], areaMap))
		{
			fairgroundRideTableAddElement(result, fairgroundRideTable.table[i], &retVal);
		}
	} 
}

float fairgroundRideTableGetBestRatio(tFairgroundRideTable fairgroundRideTable)
{
	int i;
	float minRatio, ratio;
	if (fairgroundRideTable.nFairgroundRides > 0) {
		minRatio = fairgroundRideGetRatio(fairgroundRideTable.table[0]);
		for (i = 1; i < fairgroundRideTable.nFairgroundRides; i++) 
		{
			ratio = fairgroundRideGetRatio(fairgroundRideTable.table[i]);
			if (ratio < minRatio)
			{
				minRatio = ratio;
			}
		}
	}
	else {
		minRatio = -1;
	}
	return minRatio;
}


float fairgroundRideGetSmallestCostTrip(tFairgroundRideTable fairgroundRideTable, int percentatgeEmptySeats)
{
	int i;
	float minCostTrip, costTrip;
	if (fairgroundRideTable.nFairgroundRides > 0) {
		minCostTrip = fairgroundRideGetCostTrip(fairgroundRideTable.table[0], percentatgeEmptySeats);
		for (i = 1; i < fairgroundRideTable.nFairgroundRides; i++) 
		{
			costTrip = fairgroundRideGetCostTrip(fairgroundRideTable.table[i], percentatgeEmptySeats);
			if (costTrip < minCostTrip)
			{
				minCostTrip = costTrip;
			}
		}
	}
	else {
		minCostTrip = -1;
	}
	return minCostTrip;
}

void fairgroundRideTableUpdateWaitingTime(tFairgroundRideTable *fairgroundRideTable,
											int nVisitantsBefore, int minutesDownUp, int percentEmptySeats)
{
	int i, awaitingTime;
	for (i = 0; i < fairgroundRideTable->nFairgroundRides; i++) {
		awaitingTime = fairgroundRideGetWaitingTime(fairgroundRideTable->table[i], nVisitantsBefore, minutesDownUp, percentEmptySeats);
		fairgroundRideTable->table[i].averageWaitingTime = awaitingTime;
	}
}


float fairgroundRideTableGetAverageWaitingTimePark(tFairgroundRideTable fairgroundrideTable) 
{
	int i;
	float averageWaitingTimePark = 0.0;
	
	if (fairgroundrideTable.nFairgroundRides > 0)
	{
		for (i = 0; i < fairgroundrideTable.nFairgroundRides; i++)
		{
			averageWaitingTimePark += fairgroundrideTable.table[i].averageWaitingTime;
		}
		averageWaitingTimePark = averageWaitingTimePark / (float)fairgroundrideTable.nFairgroundRides;
	}
	
	return averageWaitingTimePark;
}