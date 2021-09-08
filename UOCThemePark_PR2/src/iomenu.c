#include <stdio.h>
#include <string.h>
#include "iomenu.h"
#include "fairgroundRide.h"
#include "visitor.h"
#include "util.h"

void readVisitor(tVisitor *visitor, tError *retVal)
{
	*retVal = OK;

	char buffer[MAX_LINE];
	int length;
	
	int number, typeTicket, satisfaction;
	tTime timeEnter, timeExit;
	
	/* Request visitor information */
	printf("Visitor id (integer greater or equal 1 and less or equal than %d):\n>> ", MAX_VISITORS);
	scanf("%d", &number);
	if (number < 1 || number > MAX_VISITORS) {
		*retVal = ERROR;
	} else {
		visitor->id = (tVisitorId)number;
	}
	
	if (*retVal != ERROR) {		
		printf("Name (%d char max, no spaces):\n>> ", MAX_NAME-1);
		scanf("%s", buffer);
		length = strlen(buffer);
		if (length < MAX_NAME) {
			strncpy(visitor->name, buffer, MAX_NAME);
		} else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Surname (%d char max, no spaces):\n>> ", MAX_SURNAME-1);
		scanf("%s", buffer);
		length = strlen(buffer);
		if (length < MAX_SURNAME) {
			strncpy(visitor->surname, buffer, MAX_SURNAME);
		} else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Document number (%d char max, no spaces):\n>> ", MAX_DOC_NUMBER-1);
		scanf("%s", buffer);
		length = strlen(buffer);
		if (length < MAX_DOC_NUMBER) {
			strncpy(visitor->docNumber, buffer, MAX_DOC_NUMBER);
		} else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Birthdate (format dd/mm/yyyy, and year greater than 1900 and less than %d):\n>> ", YEAR_ACTUAL);
		scanf("%s", buffer);
		if (length < MAX_DATE_STRING) {
			sscanf(buffer, "%d/%d/%d", &(visitor->birthDate.day), &(visitor->birthDate.month), &(visitor->birthDate.year));
			if (!validateDate(visitor->birthDate)) {
				*retVal = ERROR;
			}
		}
		else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("City (%d char max, no spaces):\n>> ", MAX_CITY-1);
		scanf("%s", buffer);
		length = strlen(buffer);
		if (length < MAX_CITY) {
			strncpy(visitor->city, buffer, MAX_CITY);
		} else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Height (real value in centimeters, greater than 0.00 and less than %.2f):\n>> ", MAX_HEIGHT);
		scanf("%f", &(visitor->height));
		if (visitor->height <= 0 || visitor->height >= MAX_HEIGHT) {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Is premium? (YES/NO):\n>> ");
		scanf("%s", buffer);
		if (isStringYes(buffer)) {
			visitor->isPremium = true;
		} else if (isStringNo(buffer)) {
			visitor->isPremium = false;
		}
		else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Has any disability? (YES/NO):\n>> ");
		scanf("%s", buffer);
		if (isStringYes(buffer)) {
			visitor->hasAnyDisability = true;
		} else if (isStringNo(buffer)) {
			visitor->hasAnyDisability = false;
		}
		else {
			*retVal = ERROR;
		}
	}
	
	if (*retVal != ERROR) {		
		printf("Is a large family? (YES/NO):\n>> ");
		scanf("%s", buffer);
		if (isStringYes(buffer)) {
			visitor->isLargeFamily = true;
		} else if (isStringNo(buffer)) {
			visitor->isLargeFamily = false;
		}
		else {
			*retVal = ERROR;
		}
	}	
	
	if (*retVal != ERROR) {		
		printf("Has any discount? (YES/NO):\n>> ");
		scanf("%s", buffer);
		if (isStringYes(buffer)) {
			visitor->hasDiscount = true;
			
			printf("Discount percentatge (real value between 0.00 and 100.00 (both included)):\n>> ");
			scanf("%f", &(visitor->discount));
			if (visitor->discount < 0 || visitor->discount > 100) {
				*retVal = ERROR;
			}
		} else if (isStringNo(buffer)) {
			visitor->hasDiscount = false;
			visitor->discount = 0.0;
		}
		else {
			*retVal = ERROR;
		}
	}
	
	if (*retVal != ERROR) {		
		printf("Purchased ticket type (1 digit being 0=FOR_A_WALK 1=GENERAL 2=GENERAL_FAST_PASS):\n>> ");
		scanf("%d", &typeTicket);
		if (typeTicket >=0 && typeTicket <= 2) {
			visitor->purchasedTicket = (tTicketType)typeTicket;
		} else {
			*retVal = ERROR;
		}
	}	

	if (*retVal != ERROR) {		
		printf("Entrance time to the park (hh:mm) (hour in 24 hours format):\n>> ");
		scanf("%s", buffer);
		sscanf(buffer, "%d:%d", &(timeEnter.hour), &(timeEnter.minutes));

		printf("Departure time to the park (hh:mm) (hour in 24 hours format):\n>> ");
		scanf("%s", buffer);
		sscanf(buffer, "%d:%d", &(timeExit.hour), &(timeExit.minutes));
		
		if (validateTime(timeEnter) && validateTime(timeExit)) {
			if (timeCompare(timeExit, timeEnter) > 0) {
				timeCopy(&(visitor->timeInPark.timeEnter), timeEnter);
				timeCopy(&(visitor->timeInPark.timeExit), timeExit);
			}
			else {
				*retVal = ERROR;
			}
		} else {
			*retVal = ERROR;
		}
	}	
	
	if (*retVal != ERROR) {		
		printf("Satisfaction (integer between 0 and 10 (both included)):\n>> ");
		scanf("%d", &(satisfaction));
		if (satisfaction >=0 && satisfaction <= 10) {
			visitor->satisfaction = satisfaction;
		} else {
			*retVal = ERROR;
		}
	}		
}

void printVisitor(tVisitor visitor, int index) 
{    
	char visitorStr[MAX_LINE];
    getVisitorStr(visitor, MAX_LINE, visitorStr);
    printf("[%u] - %s\n", index, visitorStr);
}



void printVisitorTable(tVisitorTable table) 
{
	int i;	
	
	if(table.nVisitors == 0) {
		printf("No visitors.\n");
	} else {
		for(i=0;i<table.nVisitors;i++) {
            printVisitor(table.table[i], i+1);
		}		
	}
}


void readFairgroundRide(tFairgroundRide *fairgroundRide, tError *retVal)
{
	*retVal = OK;
	
	char buffer[MAX_LINE];
	int number, type, category, state, length;
	char area;
	int accessLess100, accessBetween100_120, accessBetween120_140, accessGreater140;
	
	printf("Fairground ride id (integer greater or equal 1 and less or equal than %d):\n>> ", MAX_FAIRGROUNDRIDES);
	scanf("%d", &number);
	if (number < 1 || number > MAX_FAIRGROUNDRIDES) {
		*retVal = ERROR;
	} else {
		fairgroundRide->id = (tFairgroundRideId)number;
	}
	
	
	if (*retVal != ERROR) {
		printf("Fairground ride name (max %d char, no spaces):\n>> ", MAX_NAME-1);
		scanf("%s",buffer);
		length = strlen(buffer);
		if (length < MAX_NAME) {
			strncpy(fairgroundRide->name, buffer, MAX_NAME);
		} else {
			*retVal = ERROR;
		}
	}
	
	if (*retVal != ERROR) {
		printf("Fairground ride type (1 digit being 0=ROLLER_COASTER 1=VIRTUAL_SIMULATOR 2=CAR_TRACK 3=BABY_CIRCUITS 4=MAT 5=SHOW_CINEMA 6=TERROR_PASSAGE):\n>> ");
		scanf("%d", &type);
		if (type >=0 && type <= 6) {
			fairgroundRide->type = (tFairgroundRideType)type;
		}
		else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {
		printf("Fairground ride category (1 digit being 0=STRONG 1=MODERATE 2=CHILDISH):\n>> ");
		scanf("%d", &category);
		if (category >=0 && category <= 2) {
			fairgroundRide->category = (tFairgroundRideCategory)category;
		}
		else {
			*retVal = ERROR;
		}
	}
	
	if (*retVal != ERROR) {
		printf("Fairground ride area inside map (1 character, an upper letter):\n>> ");
		getchar();	
		scanf("%c", &area);
		if (area >= 'A' && area <= 'Z') {
			fairgroundRide->areaMap = area;
		}
		else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {
		printf("Fairground ride state (1 digit being 0=WORKING 1=OUT_OF_ORDER):\n>> ");
		scanf("%d", &state);
		if (state >=0 && state <= 1) {
			fairgroundRide->state = (tFairgroundRideState)state;
		}
		else {
			*retVal = ERROR;
		}
	}
	
	if (*retVal != ERROR) {
		printf("Fairground ride access according to age:\n");
		printf("Access if the height is <= 1 meter (1 digit being 0=FORBIDDEN 1=ALLOWED_WITH_COMPANION 2=ALLOWED):\n>> ");
		scanf("%d", &accessLess100);
		printf("Access if the height is > 1 meter and <= 1.20 meters (1 digit being 0=FORBIDDEN 1=ALLOWED_WITH_COMPANION 2=ALLOWED):\n>> ");
		scanf("%d", &accessBetween100_120);
		printf("Access if the height is > 1.20 meters and <= 1.40 meters (1 digit being 0=FORBIDDEN 1=ALLOWED_WITH_COMPANION 2=ALLOWED):\n>> ");
		scanf("%d", &accessBetween120_140);
		printf("Access if the height is > 1.40 meters (1 digit being 0=FORBIDDEN 1=ALLOWED_WITH_COMPANION 2=ALLOWED):\n>> ");
		scanf("%d", &accessGreater140);

		if ( (accessLess100 >=0 && accessLess100 <= 2) && (accessBetween100_120 >= 0 && accessBetween100_120 <=2) &&
			(accessBetween120_140 >= 0 && accessBetween120_140 <=2) && (accessGreater140 >= 0 && accessGreater140 <= 2) ) {
			fairgroundRide->accessHeight.lessThan100 = (tFairgroundRideAccess)accessLess100;
			fairgroundRide->accessHeight.between100_120 = (tFairgroundRideAccess)accessBetween100_120;
			fairgroundRide->accessHeight.between120_140 = (tFairgroundRideAccess)accessBetween120_140;
			fairgroundRide->accessHeight.greaterThan140 = (tFairgroundRideAccess)accessGreater140;
		}
		else {
			*retVal = ERROR;
		}
	}
	if (*retVal != ERROR) {
		printf("Average waiting time (integer value in minutes):\n>> ");	
		scanf("%d", &(fairgroundRide->averageWaitingTime));
		if (fairgroundRide->averageWaitingTime < 0) {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {
		printf("Duration trip (integer value in seconds):\n>> ");
		scanf("%d", &(fairgroundRide->durationTrip));
		if (fairgroundRide->durationTrip < 0) {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {
		printf("Number of persons per trip (integer value):\n>> ");
		scanf("%d", &(fairgroundRide->numPersonsTrip));
		if (fairgroundRide->numPersonsTrip <= 0) {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {		
		printf("Can you pay fairground ride ticket? (YES/NO):\n>> ");
		scanf("%s", buffer);
		if (isStringYes(buffer)) {
			fairgroundRide->allowsPayTicket = true;
			
			printf("Ticket price (real value in euros):\n>> ");
			scanf("%f", &(fairgroundRide->ticketPrice));
			if (fairgroundRide->ticketPrice < 0) {
				*retVal = ERROR;
			}

		} else if (isStringNo(buffer)) {
			fairgroundRide->allowsPayTicket = false;
			fairgroundRide->ticketPrice = 0;
		}
		else {
			*retVal = ERROR;
		}
	}

	if (*retVal != ERROR) {
		printf("Has a queueu for fast pass? (YES/NO):\n>> ");
		scanf("%s", buffer);
		if (isStringYes(buffer)) {
			fairgroundRide->allowsFastPass = true;
		} else if (isStringNo(buffer)) {
			fairgroundRide->allowsFastPass = false;
		}
		else {
			*retVal = ERROR;
		}
	}
	
}

void printFairgroundRide(tFairgroundRide fairgroundRide, int index) 
{    
	char fairgroundRideStr[MAX_LINE];
    getFairgroundRideStr(fairgroundRide, MAX_LINE, fairgroundRideStr);
    printf("[%u] - %s\n", index, fairgroundRideStr);
}

void printFairgroundRideTable(tFairgroundRideTable table) 
{
	int i;	
	
	if(table.nFairgroundRides ==0) {
		printf("No fairground rides.\n");
	} else {
		for(i=0;i<table.nFairgroundRides;i++) {
            printFairgroundRide(table.table[i], i+1);
		}		
	}
}


void printVisitorRecommendationsByHeight(tAppData appData, char areaMap)
{
	int i;
    tVisitorTable visitors;
	tFairgroundRideTable fairgroundRides, result;
	
	getVisitors(appData, &visitors);
	if (visitors.nVisitors == 0) 
	{
		printf("No visitors\n"); 
	}
	else {
		getFairgroundRides(appData, &fairgroundRides);
		
		for (i = 0; i < visitors.nVisitors; i++) 
		{
			visitorRecommendationByHeight(visitors.table[i], fairgroundRides, areaMap, &result);
			if (result.nFairgroundRides > 0) 
			{
				printf("Visitor:\n");
				printVisitor(visitors.table[i], i+1);
				printf("Fairgrounds ride recommendation:\n");
				printFairgroundRideTable(result);
				printf("\n");
			}
			else {
				printf("No fairground ride recommendation.\n"); 
			}
		}
	}
}
