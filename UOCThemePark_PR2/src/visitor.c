#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "visitor.h"
#include "util.h"

void getVisitorStr(tVisitor visitor, int maxSize, char *str) 
{
	int length = 0;
	length = snprintf(str,maxSize-1, "%d %s %s %s %d/%d/%d %s %.2f %d %d %d %d %.2f %d %d:%d %d:%d %d",
						visitor.id, 
						visitor.name,
						visitor.surname,
						visitor.docNumber,
						visitor.birthDate.day, visitor.birthDate.month, visitor.birthDate.year,
						visitor.city,
						visitor.height,
						visitor.isPremium,
						visitor.hasAnyDisability,
						visitor.isLargeFamily,
						visitor.hasDiscount,
						visitor.discount,
						visitor.purchasedTicket,
						visitor.timeInPark.timeEnter.hour, visitor.timeInPark.timeEnter.minutes,
						visitor.timeInPark.timeExit.hour, visitor.timeInPark.timeExit.minutes, 
						visitor.satisfaction);
	
	if (length>0) 
		str[length]='\0';
}

void getVisitorObject(const char *str, tVisitor *visitor) 
{	
	int aux_id, aux_isPremium, aux_hasAnyDisability, aux_isLargeFamily, aux_hasDiscount, aux_purchasedTicket;
	sscanf(str, "%d %s %s %s %d/%d/%d %s %f %d %d %d %d %f %d %d:%d %d:%d %d", 
			&aux_id, 
			visitor->name, 
			visitor->surname, 
			visitor->docNumber, 
			&(visitor->birthDate.day), &(visitor->birthDate.month), &(visitor->birthDate.year),
			visitor->city, 
			&(visitor->height),
			&aux_isPremium,
			&aux_hasAnyDisability,
			&aux_isLargeFamily,
			&aux_hasDiscount,
			&(visitor->discount),
			&aux_purchasedTicket,
			&(visitor->timeInPark.timeEnter.hour), &(visitor->timeInPark.timeEnter.minutes), 
			&(visitor->timeInPark.timeExit.hour), &(visitor->timeInPark.timeExit.minutes),
			&(visitor->satisfaction));
	
	visitor->id = (tVisitorId)aux_id;
	visitor->isPremium = (bool)aux_isPremium;
	visitor->hasAnyDisability = (bool)aux_hasAnyDisability;
	visitor->isLargeFamily = (bool)aux_isLargeFamily;
	visitor->hasDiscount = (bool)aux_hasDiscount;
	visitor->purchasedTicket = (tTicketType)aux_purchasedTicket;
}

void visitorCopy(tVisitor *dst, tVisitor src) 
{    
/*************** PR1 EX3A *****************/	
	dst->id = src.id;
	strcpy(dst->name, src.name);
	strcpy(dst->surname, src.surname);
	strcpy(dst->docNumber, src.docNumber);
	dateCopy(&(dst->birthDate), src.birthDate);
	strcpy(dst->city, src.city);
	dst->height = src.height;
	dst->isPremium = src.isPremium;
	dst->hasAnyDisability = src.hasAnyDisability;
	dst->isLargeFamily = src.isLargeFamily;
	dst->hasDiscount = src.hasDiscount;
	dst->discount = src.discount;
	dst->purchasedTicket = src.purchasedTicket;
	timeInParkCopy(&(dst->timeInPark), src.timeInPark);
	dst->satisfaction = src.satisfaction;
/******************************************/	
}


int visitorCompare(tVisitor obj1, tVisitor obj2) {
	
	int result = 0;

/*************** PR1 EX3B *****************/	
	result = stringCompareUpper(obj1.name, obj2.name);
	if (result == 0) {
		result = stringCompareUpper(obj1.surname, obj2.surname);
		if (result == 0) {
			result = stringCompareUpper(obj1.docNumber, obj2.docNumber);
			if (result == 0) {
				result = dateCompare(obj1.birthDate, obj2.birthDate);
				if (result == 0) {
					result = stringCompareUpper(obj1.city, obj2.city);
					if (result == 0) {
						result = heightCompare(obj1.height, obj2.height);
						if (result == 0) {
							result = booleanCompare(obj1.isPremium, obj2.isPremium);
							if (result == 0) {
								result = booleanCompare(obj1.hasAnyDisability, obj2.hasAnyDisability);
								if (result == 0) {
									result = booleanCompare(obj1.isLargeFamily, obj2.isLargeFamily);
									if (result == 0) {
										result = discountCompare(obj1.hasDiscount, obj1.discount, obj2.hasDiscount, obj2.discount);
										if (result == 0) {
											if (obj1.purchasedTicket > obj2.purchasedTicket) 			
												result = 1;
											else if(obj1.purchasedTicket < obj2.purchasedTicket) 		
												result = -1;
											else {
												result = timeInParkCompare(obj1.timeInPark, obj2.timeInPark);
												if (result == 0) {
													if (obj1.satisfaction > obj2.satisfaction) 		
														result = 1;
													else if(obj1.satisfaction < obj2.satisfaction)	
														result = -1;
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
	}
/******************************************/	
	return result;
}

bool isAdultVisitor( tVisitorId id,
                         tVisitorTable visitors )
{
    int idx;
    tVisitor visitor;
    bool result= false;
    
    idx= visitorTableFindById(visitors,id);
    if (idx != NO_VISITOR)
    {
        visitor= visitors.table[idx];
        result= (calculateAge(visitor.birthDate) >= MIN_ADULT_AGE);
    }
    return result;
}

void visitorTableInit(tVisitorTable *visitorTable) {
	
	visitorTable->nVisitors = 0;
}


void visitorTableAddElement(tVisitorTable *visitorTable, tVisitor visitor, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new visitor */
	if(visitorTable->nVisitors >= MAX_VISITORS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new visitor to the end of the table */
		visitorCopy(&visitorTable->table[visitorTable->nVisitors], visitor);
		visitorTable->nVisitors++;
	}
}

int visitorTableFindById(tVisitorTable visitorTable, tVisitorId id) {

	int idx = NO_VISITOR;
	
	int i=0;
	while(i< visitorTable.nVisitors && idx==NO_VISITOR) {
		/* Check if the id is the same */
		if(visitorTable.table[i].id==id) {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void visitorTableRemoveElement(tVisitorTable *visitorTable, tVisitor visitor) 
{	
    int i;
    int pos;

    pos = visitorTableFindById(*visitorTable, visitor.id);
    if (pos!=NO_VISITOR)
    {
        for(i=pos; i<visitorTable->nVisitors-1; i++) {		
            visitorCopy(&visitorTable->table[i], visitorTable->table[i+1]);
        }
        visitorTable->nVisitors = visitorTable->nVisitors-1;		
    }
}

void visitorTableSaveToFile(tVisitorTable visitorTable, const char* filename, tError *retVal) {

	*retVal = OK;
	
	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all visitors to the file */
        for(i=0;i<visitorTable.nVisitors;i++) {
            getVisitorStr(visitorTable.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void visitorTableLoadFromFile(tVisitorTable *visitorTable, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=0;
	char line[MAX_LINE];
	tVisitor newVisitor;
	
	/* Initialize the output table */
	visitorTableInit(visitorTable);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the lines */
		while(!feof(fin) && visitorTable->nVisitors<MAX_VISITORS && *retVal == OK) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getVisitorObject(line, &newVisitor);
				/* Add the new visitor to the output table */
				visitorTableAddElement(visitorTable, newVisitor, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}



void visitorTableSelect(tVisitorTable visitorTable, int selectedAge, tVisitorTable *result)
{
	tError retVal;
	
/*************** PR1 EX4A *****************/	
	int i, age;
	bool isLargeFamily, isPremium;
	tTicketType ticket;
	
	visitorTableInit(result);
	
	retVal = OK;
	i = 0;
	
	while (i < visitorTable.nVisitors && retVal == OK)
	{
		age = calculateAge(visitorTable.table[i].birthDate);
		isLargeFamily = visitorTable.table[i].isLargeFamily;
		isPremium = visitorTable.table[i].isPremium;
		ticket = visitorTable.table[i].purchasedTicket;

		if (age > selectedAge && isLargeFamily && isPremium && (ticket == GENERAL || ticket == GENERAL_FAST_PASS)) {
			visitorTableAddElement(result, visitorTable.table[i], &retVal);
		}
		i++;
	} 
/******************************************/	
}


void visitorTableApplyDiscounts(tVisitorTable visitorTable, tVisitorTable *result)
{
/*************** PR1 EX4B *****************/	
	int i;
	visitorTableSelect(visitorTable, 35, result);
	
	for (i = 0; i < result->nVisitors; i++) {
		result->table[i].hasDiscount = true;
		result->table[i].discount = 15.0; 
	}  
/******************************************/	
}


float visitorTableGetAverageTimeInPark(tVisitorTable visitorTable) 
{
	float average = 0.0;

/*************** PR1 EX6A *****************/			
	int totalTime = 0;
	int i;
	
	for (i = 0; i < visitorTable.nVisitors; i++)
	{
		totalTime += diffTime(visitorTable.table[i].timeInPark.timeExit, visitorTable.table[i].timeInPark.timeEnter);
	}

	if (visitorTable.nVisitors > 0)
	{
		average = ((float)totalTime/(float)visitorTable.nVisitors)/60.0;  
	}
/******************************************/		
	return average;
}

void visitorTableGetMinMaxAgeVisitor(tVisitorTable visitorTable, int *minAge, int *maxAge)
{
/*************** PR1 EX6B *****************/
	int i, auxAge;
	
	if (visitorTable.nVisitors > 0) {
		auxAge = calculateAge(visitorTable.table[0].birthDate);
		
		*minAge = auxAge;
		*maxAge = auxAge;
		
		for (i = 1; i < visitorTable.nVisitors; i++)
		{
			auxAge = calculateAge(visitorTable.table[i].birthDate);
			if (auxAge < *minAge)			
				*minAge = auxAge;
			if (auxAge > *maxAge)			
				*maxAge = auxAge;
		}
	}
	else {
		*minAge = -1;
		*maxAge = -1;
	}
/******************************************/
}


void visitorTableSort(tVisitorTable *visitorTable)
{
/*************** PR1 EX7 *****************/
	int i, j, posMax;
	tVisitor auxVisitor;
	
	i = 0;
	while (i < visitorTable->nVisitors - 1) 
	{
		posMax = i;
		j = i + 1;
		while (j < visitorTable->nVisitors)
		{
			if (visitorCompare(visitorTable->table[j], visitorTable->table[posMax]) > 0)
			{
				posMax = j;
			}
			j = j + 1;
		}
		
		visitorCopy(&auxVisitor, visitorTable->table[posMax]);
		visitorCopy(&(visitorTable->table[posMax]), visitorTable->table[i]);
		visitorCopy(&(visitorTable->table[i]), auxVisitor);
		i = i + 1;
	}
/******************************************/	
}