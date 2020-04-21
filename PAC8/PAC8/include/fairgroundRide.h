// define constants
#define MAX_NAME 15+1
#define MAX_LINE 514
#define MAX_FRIDES 150
#define FIRST 1
#define SECOND 2


//type declarations
typedef enum {STRONG, MODERATE, CHILDISH} tFairgroundRideCategory;

typedef struct {
	char name[MAX_NAME];
	tFairgroundRideCategory category;
	char areaMap;
	int durationTrip; 	
	int averageWaitingTime; 
} tFairgroundRide;

typedef struct {
	tFairgroundRide fairgroundRides[MAX_FRIDES];
	int nFairgroundRides;
}tFairgroundRidesTable;

//define function headers
/* output of fairground ride */
void writeFairgroundRide(tFairgroundRide fRide);
/* copy from one fairground ride to other */
void copyFairgroundRide(tFairgroundRide fRideSrc, tFairgroundRide *fRideDst);
/* Read fairground data */
void getFairgroundRideObject(const char *str, tFairgroundRide *fRide);
/* Add the new fairground ride at the end of the table */
void fairgroundRidesTableAddElement(tFairgroundRidesTable *fRidesTable, tFairgroundRide fRide);
/* Open the input file and load on it the information */
void fairgroundRidesTableLoadDataFromFile(tFairgroundRidesTable *fRidesTable, const char* filename);
/* Initialize table */
void fairgroundRidesTableInitialize(tFairgroundRidesTable *tFairgroundRide);
/* Find in the table the correct values for area and category */
void fairgroundRidesTableFilter(tFairgroundRidesTable *fRidesTable, char area, tFairgroundRideCategory category, tFairgroundRidesTable *myfRidesTable);
/* Select best option */
int myChoice(tFairgroundRidesTable *myfRideTable);