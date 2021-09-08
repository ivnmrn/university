/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */
#include <stdbool.h>

#define MAX_PATHNAME 500
#define MAX_LINE 520				

#define MAX_FAIRGROUNDRIDES 10
#define MAX_VISITORS 100

#define MAX_NAME 15+1
#define MAX_SURNAME 15+1
#define MAX_CITY 25+1
#define MAX_DOC_NUMBER 9+1
#define MAX_DATE_STRING 10+1

#define MIN_ADULT_AGE 18

#define NO_FAIRGROUNDRIDE -1
#define NO_VISITOR -1

#define MAX_ROW_NUMBER 6
#define MAX_RIDES_MANAGEMENT 10

#define YEAR_ACTUAL 2020

#define HEIGHT_100 100.0
#define HEIGHT_120 120.0
#define HEIGHT_140 140.0
#define MAX_HEIGHT	220.0

#define MAX_VISITORS_IN_STACK 4
#define MAX_VISITORS_IN_ROW 4

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_VISITOR=-7,ERR_NO_FAIRGROUNDRIDE=-8,ERR_NO_FREE_GAP=-9} tError; 

typedef int tFairgroundRideId; 

typedef int tVisitorId;

typedef enum { FORBIDDEN, ALLOWED_WITH_COMPANION, ALLOWED } tFairgroundRideAccess;
typedef enum { WORKING, OUT_OF_ORDER } tFairgroundRideState; 
typedef enum { ROLLER_COASTER, VIRTUAL_SIMULATOR, CAR_TRACK, BABY_CIRCUITS, MAT, SHOW_CINEMA, TERROR_PASSAGE } tFairgroundRideType;
typedef enum { STRONG, MODERATE, CHILDISH } tFairgroundRideCategory;

typedef struct {
  int day, month, year;
} tDate;

typedef struct {
  int hour, minutes;
} tTime;

typedef struct {
	tFairgroundRideAccess lessThan100;
	tFairgroundRideAccess between100_120;
	tFairgroundRideAccess between120_140;
	tFairgroundRideAccess greaterThan140;
} tFairgroundRideHeightRequirement;

typedef struct {
	tFairgroundRideId id;
	char name[MAX_NAME];
	tFairgroundRideType type; 
	tFairgroundRideCategory category;
	char areaMap;  
	tFairgroundRideState state;
	tFairgroundRideHeightRequirement accessHeight; 
	int durationTrip; 
	int numPersonsTrip;
	bool allowsPayTicket;
	float ticketPrice;
	bool allowsFastPass;
	int averageWaitingTime; 
} tFairgroundRide;

typedef struct {
	tFairgroundRide table[MAX_FAIRGROUNDRIDES];
	int nFairgroundRides;
} tFairgroundRideTable;

typedef enum { FOR_A_WALK, GENERAL, GENERAL_FAST_PASS } tTicketType;

typedef enum { FAST_PASS_QUEUE, MAIN_QUEUE, SINGLE_QUEUE, TEMP_QUEUE } tQueueType;

typedef struct {
	tTime timeEnter, timeExit;
} tTimeInPark;

typedef struct {
    tVisitorId id;
    char name[MAX_NAME];
    char surname[MAX_SURNAME];	
    char docNumber[MAX_DOC_NUMBER];	
    tDate birthDate;
    char city[MAX_CITY];
    float height;
    bool isPremium;
    bool hasAnyDisability;		
    bool isLargeFamily; 
    bool hasDiscount;		
    float discount;  
    tTicketType purchasedTicket;  
    tTimeInPark timeInPark;
    int satisfaction; 
} tVisitor;

typedef struct {
	tVisitor table[MAX_VISITORS];
	int nVisitors;
} tVisitorTable;

typedef struct {
	tVisitorId visitor;
    unsigned int groupSize;
} tVisitorGroup;

typedef struct {
	tVisitorGroup table[MAX_VISITORS];
	unsigned int nElem;
} tVisitorQueue;

typedef struct {
	tVisitorId table[MAX_VISITORS_IN_STACK];
	unsigned int nElem;
} tVisitorStack;

typedef struct {
  tVisitorQueue rowQueue[MAX_ROW_NUMBER];
  unsigned int nRows;
} tRowQueues;

typedef struct {
  tVisitorStack wagonRow[MAX_ROW_NUMBER];
  unsigned int nRows;
} tWagons;

typedef struct {
    tFairgroundRideId fairgroundId;
    tVisitorQueue fastPassQueue;
    tVisitorQueue singleQueue;
    tVisitorQueue mainQueue;
    tRowQueues rowQueues;
    tWagons wagons;
} tRideManagement;

typedef struct {
	tRideManagement table[MAX_RIDES_MANAGEMENT];
	int nRidesManagement;
} tRidesManagementTable;

/* Definition of the application data structure */
typedef struct 
{
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Fairground ride table */
	tFairgroundRideTable fairgroundRides;
	
	/* Visitors table */
	tVisitorTable visitors;
    
	/* Rides management table */
    tRidesManagementTable managementRides;
	
} tAppData;

#endif /*__DATA_H*/