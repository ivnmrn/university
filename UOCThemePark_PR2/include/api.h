#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appDataInitialize(tAppData *object);

/* Load the application data from file */
void appDataLoadFromFile(tAppData *object, tError *error);

/* Save the application data to a file */
void appDataSaveToFile(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appDataSetPathApp(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the visitors */
void getVisitors(tAppData object, tVisitorTable *result);

/* Get the visitor information */
void getVisitor(tAppData object, tVisitorId visitorId, tVisitor *visitor, tError *retVal);

/* Add a new visitor */
void addVisitor(tAppData *object, tVisitor visitor, tError *retVal);

/* Remove a certain visitor */
void removeVisitor(tAppData *object, tVisitor visitor);

/* Return the table of fairground rides */
void getFairgroundRides(tAppData object, tFairgroundRideTable *result);

/* Get the fairground ride information */
void getFairgroundRide(tAppData object, tFairgroundRideId fairgroundRideId, tFairgroundRide *fairgroundride, tError *retVal);

/* Add a new fairground ride */
void addFairgroundRide(tAppData *object, tFairgroundRide fairgroundRide, tError *retVal);

/* Checks a ride management structure */
bool checkRide( tRideManagement ride,
                    tFairgroundRideTable fairgroundRides );

/* Checks if a group size fits in the row queues */
bool checkGroup( tRowQueues rowQueues, unsigned int groupSize );
            
/* Checks visitors height is suitable to ride according to current 
 * requirements and the presence of an adult in the group */
bool checkHeight( float height, 
                      tFairgroundRideHeightRequirement access, 
                      bool adultInGroup );

/* Checks if a visitor can ride according to height requirements,  
 * type of pass purchased and type of queue where he/she is placed */
bool checkVisitor( tVisitorGroup group,
                       tFairgroundRide fairgroundRide,
                       tVisitorTable visitors,
                       bool adultInGroup,
                       tQueueType queueType );

/* Process a group of visitors of a given size moving the people
   allowed to ride to the row queues of the wagons */
void processGroup( tVisitorQueue *queue, 
                   tRowQueues *rowQueues, 
                   unsigned int groupSize,
                   tFairgroundRide fairgroundRide,
                   tVisitorTable visitors,
                   unsigned int *freeSeats,
                   tQueueType queueType );

/* Process the given queue of visitors */
void processQueue( tVisitorQueue *queue, 
                   tRowQueues *rowQueues, 
                   tFairgroundRide fairgroundRide,
                   tVisitorTable visitors,
                   unsigned int *freeSeats,
                   tQueueType queueType );

/* Process the queues of visitors:
   fast-pass queue, main queue and single queue */
void processQueues( tRideManagement *rideManagement, 
                    tFairgroundRide fairgroundRide,
                    tVisitorTable visitors, 
                    unsigned int freeSeats );

/* Fills the wagons before the ride */
void fillWagons( tRideManagement *rideManagement );

/* Clears the wagons after the ride */
void clearWagons( tRideManagement *rideManagement );

/* Processes the given ride */
void processRide( tRideManagement *rideManagement,
                  tFairgroundRideTable fairgroundRides,
                  tVisitorTable visitors );

/* Processes all rides */
void processAllRides(tAppData *object);
