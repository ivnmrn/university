/* const */
#define MAX_NAME_LEN 15
#define TIME_TO_EMPTY 60
#define TIME_TO_UP 120
#define NUMBER_OF_STRING 2
#define MAX_STRING_SIZE 7

/* read tFairgroundRide */
void readFairgroundRide();
/* write best option */
void writeFairgroundRide();
/* select the best fairground ride */
void selectFairgroundRide();
/* return the waiting time for fairground ride */
int waitingTime();
/* return true if access without companion is allowed if not return false */
int accessWithoutCompanion();

/* type access */
typedef enum {FORBIDDEN, ALLOWED_WITH_COMPANION, ALLOWED} tFairgroundRideAccess;

/* atraction access requirement */
typedef struct{
    tFairgroundRideAccess lessThan100;
    tFairgroundRideAccess between100_120;
    tFairgroundRideAccess between120_140;
    tFairgroundRideAccess greaterThan140;
}tFairgroundRideHeightRequirement;

/* atraction requeriments */
typedef struct{
    char name[MAX_NAME_LEN];
    tFairgroundRideHeightRequirement accessHeight;
    int durationTrip;
    int numPersonsTrip;
}tFairgroundRide; 
