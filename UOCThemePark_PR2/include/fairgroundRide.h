#include "data.h"

/* Get a textual representation of a fairground ride */
void getFairgroundRideStr(tFairgroundRide fairgroundRide, int maxSize, char *str);

/* Get a fairground ride object from its textual representation */
void getFairgroundRideObject(const char *str, tFairgroundRide *fairgroundRide);

/* Copy the fairground ride access requirement in src to dst */
void fairgroundRideAccessCopy(tFairgroundRideHeightRequirement *dst, tFairgroundRideHeightRequirement src);

/* Copy the fairground ride data in src to dst*/
void fairgroundRideCopy(tFairgroundRide *dst, tFairgroundRide src);

/* Compares two fairground ride access requirement objects. Return:
 * 1 	 	obj1 > obj2  | 	-1		obj1 < obj2  |  	0		obj1 = obj2 */
int fairgroundRideAccessCompare(tFairgroundRideHeightRequirement obj1, tFairgroundRideHeightRequirement obj2);

/* Compares two fairground rides. Return:
 * 1 	 	obj1 > obj2  | 	-1		obj1 < obj2  |  	0		obj1 = obj2 */
int fairgroundRideCompare(tFairgroundRide obj1, tFairgroundRide obj2);

/* Initializes the given fairground rides table */
void fairgroundRideTableInit(tFairgroundRideTable *table);

/* Add a new fairground ride to the table of fairground rides */
void fairgroundRideTableAddElement(tFairgroundRideTable *table, tFairgroundRide fairgroundRide, tError *retVal);

/* Find a fairground ride in the table by id fairground ride*/
int fairgroundRideTableFindById(tFairgroundRideTable table, tFairgroundRideId id);

/* Load the table of fairground rides from a file */
void fairgroundRideTableLoadFromFile(tFairgroundRideTable *table, const char* filename, tError *retVal);

/* Save a table of fairground rides to a file */
void fairgroundRideTableSaveToFile(tFairgroundRideTable table, const char* filename, tError *retVal);

/* Get access to a fairground ride according to height */
tFairgroundRideAccess fairgroundRideGetAccessByHeight(tFairgroundRide fairgroundRide, float height);

/* Get table of fairground ride recommendation (in an area of the park) to a visitor according his height */
void visitorRecommendationByHeight(tVisitor visitor, 
                            tFairgroundRideTable fairgroundRides,
							char areaMap,
                            tFairgroundRideTable *result);


/* Return the ratio of waiting time and the duration trip */
float fairgroundGetRideRatio(tFairgroundRide fairgroundRide);

/* Return the real waiting time according the persons before me and the time to down and up to the fairground ride */
int fairgroundRideGetWaitingTime(tFairgroundRide fairgroundRide, int nVisitantsBefore, int minutesDownUp, int percentEmptySeats);

/* Return total cost of the trip assuming the maximum number of people and all pay the ticket for the fairground ride */
float fairgroundRideGetCostTrip(tFairgroundRide fairgroundRide, int percentatgeEmptySeats);

/* Validate according a height if fairground ride allows access */
bool fairgroundRideIsAccessAllowed(tFairgroundRide fairgroundRide, int height);

/* Validate if fairground ride is in one of the areaMap and is out of order */
bool fairgroundRideIsOutOfOrderByArea(tFairgroundRide fairgroundRide, char areaMap[2]);

/* Return a selection of fairground rides */
void fairgroundRideTableSelect(tFairgroundRideTable fairgroundRideTable, 
								tFairgroundRideType type, tFairgroundRideCategory category, char areaMap,
								tFairgroundRideTable *result);

/* Return a selection of out of order fairground rides */
void fairgroundRideTableOutOfOrder(tFairgroundRideTable fairgroundRideTable, 
								char areaMap[2],
								tFairgroundRideTable *result);
								
/* Return the best ratio time (the smalledst value) of a table of fairground rides */
float fairgroundRideTableGetBestRatio(tFairgroundRideTable fairgroundRideTable);

/* Return the min cost trip */
float fairgroundRideGetSmallestCostTrip(tFairgroundRideTable fairgroundRideTable, int percentatgeEmptySeats);

/* Update waiting time of a fairground rides table */
void fairgroundRideTableUpdateWaitingTime(tFairgroundRideTable *fairgroundRideTable,
											int nVisitantsBefore, int minutesDownUp, int percentEmptySeats);

/* Return the average waiting time */
float fairgroundRideTableGetAverageWaitingTimePark(tFairgroundRideTable fairgroundRideTable);

