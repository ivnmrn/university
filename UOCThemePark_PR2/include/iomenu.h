#include "data.h"
#include "api.h"

/* Read visitor data from the input */
void readVisitor(tVisitor *visitor, tError *retVal);

/* Print visitor data to the output */
void printVisitor(tVisitor visitor, int index); 

/* Print table of visitors data to the output */
void printVisitorTable(tVisitorTable table);

/* Read fairground ride data from the input */
void readFairgroundRide(tFairgroundRide *fairgroundRide, tError *retVal);

/* Print fairground ride data to the output */
void printFairgroundRide(tFairgroundRide fairgroundRide, int index);

/* Print table of fairgrounds ride data to the output */
void printFairgroundRideTable(tFairgroundRideTable table);

/* Print visitor recommendations by height to the output */
void printVisitorRecommendationsByHeight(tAppData appData, char areaMap);

