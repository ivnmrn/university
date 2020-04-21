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
void writeFairgroundRide(tFairgroundRide fRide);
void copyFairgroundRide(tFairgroundRide fRideSrc, tFairgroundRide *fRideDst);
void getFairgroundRideObject(const char *str, tFairgroundRide *fRide);
void fairgroundRidesTableAddElement(tFairgroundRidesTable *fRidesTable, tFairgroundRide fRide);
void fairgroundRidesTableLoadDataFromFile(tFairgroundRidesTable *fRidesTable,const char* filename);
void fairgroundRidesTableInitialize(tFairgroundRidesTable *tFairgroundRide);
void fairgroundRidesTableFilter(tFairgroundRidesTable *fRidesTable, char area, tFairgroundRideCategory category, tFairgroundRidesTable *myfRidesTable);
int myChoice(tFairgroundRidesTable *myfRideTable);