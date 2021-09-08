#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>

#include "visitor.h"
#include "fairgroundRide.h"
#include "management.h"
#include "queue.h"
#include "stack.h"



void appDataInitialize(tAppData *object) 
{
	/* Set parent folder as the default path */
	strcpy(object->path, "../");

	/* Initialize the visitor table */
	visitorTableInit(&(object->visitors));

	/* Initialize the fairground ride table */
	fairgroundRideTableInit(&(object->fairgroundRides));

	/* Initialize the management rides table */
    managementTableInit(&(object->managementRides));
}



void appDataLoadFromFile(tAppData *object, tError *retVal) 
{
	char path[MAX_LINE];
	*retVal = OK;

	/* Load the table of fairground rides */
	sprintf(path,"%sfairgroundRides.txt", object->path);
	fairgroundRideTableLoadFromFile(&(object->fairgroundRides), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of fairground rides\n");
	}

	/* Load the table of visitors */
	sprintf(path,"%svisitors.txt", object->path);
	visitorTableLoadFromFile(&(object->visitors), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of visitors\n");
	}

	/* Load the table of rides management */
	sprintf(path,"%smanagements.txt", object->path);
	managementTableLoad(&(object->managementRides), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of rides management\n");
	}
}



void appDataSaveToFile(tAppData object, tError *retVal)  
{
	char path[MAX_LINE];
	*retVal = OK;

	/* Save the table of fairground rides */
	sprintf(path,"%sfairgroundRides.txt", object.path);
	fairgroundRideTableSaveToFile(object.fairgroundRides, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of fairground rides\n");
	}

	/* Save the table of visitors */
	sprintf(path,"%svisitors.txt", object.path);
	visitorTableSaveToFile(object.visitors, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of visitors\n");
	}

	/* Save the table of rides management */
	sprintf(path,"%smanagements.txt", object.path);
	managementTableSave(object.managementRides, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of rides management\n");
	}
}



void appDataSetPathApp(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 

 *        API

 **********************/



void getFairgroundRides(tAppData object, tFairgroundRideTable *result) {
	*result = object.fairgroundRides;
}

void getFairgroundRide(tAppData object, tFairgroundRideId fairgroundRideId, tFairgroundRide *fairgroundRide, tError *retVal)
{
	int i;
	*retVal = OK;

	/* Check if there is a fairground ride with this id */
	i = fairgroundRideTableFindById(object.fairgroundRides, fairgroundRideId);
	if (i!=NO_FAIRGROUNDRIDE) {
		fairgroundRideCopy(fairgroundRide, object.fairgroundRides.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addFairgroundRide(tAppData *object, tFairgroundRide fairgroundRide, tError *retVal) 
{
	*retVal = OK;
	tFairgroundRide tmp;

	/* Check if there is another fairground ride with the same id */
	getFairgroundRide(*object, fairgroundRide.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new fairground ride using the fairground ride table method */
		fairgroundRideTableAddElement(&(object->fairgroundRides), fairgroundRide, retVal);
	}
}

void getVisitors(tAppData object, tVisitorTable *result)
{
	*result = object.visitors;	
}

void getVisitor(tAppData object, tVisitorId id, tVisitor *visitor, tError *retVal)
{
	int i;
	*retVal = OK;

	/* Check if there is a visitor with this id */
	i = visitorTableFindById(object.visitors, id);
	if (i!=NO_VISITOR) {
		visitorCopy(visitor, object.visitors.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}



void addVisitor(tAppData *object, tVisitor visitor, tError *retVal) 
{
	*retVal = OK;
	tVisitor tmpVisitor;

	/* Check if there is another visitor with the same id */
	getVisitor(*object, visitor.id, &tmpVisitor, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new visitor using the visitor table method */
		visitorTableAddElement(&(object->visitors), visitor, retVal);
	}
}


void removeVisitor(tAppData *object, tVisitor visitor) 
{	
	/* Call the method from the visitors table*/
	visitorTableRemoveElement(&(object->visitors), visitor);
}

bool checkRide( tRideManagement ride,
                tFairgroundRideTable fairgroundRides )
{
    /*********** PR2 - EX 1A **********/
	int pos, total;
    bool result= false;

	pos = fairgroundRideTableFindById(fairgroundRides, ride.fairgroundId);
	total = ride.rowQueues.nRows * MAX_VISITORS_IN_ROW;

	if (fairgroundRides.table[pos].id == ride.fairgroundId &&
	 	fairgroundRides.table[pos].state == 0 && 
		fairgroundRides.table[pos].numPersonsTrip == total && 
		ride.rowQueues.rowQueue[pos].nElem == 0 && 
		ride.wagons.wagonRow[pos].nElem == 0) {
 			result = true;
	}
    /**********************************/
    return result;
}



bool checkGroup( tRowQueues rowQueues, unsigned int groupSize )
{
    /*********** PR2 - EX 1B **********/
    bool groupFits= false;
	int total = 0;

	for (int b = 0; b < rowQueues.nRows; b++) {
		total = total + (MAX_VISITORS_IN_ROW-visitorQueueLength(rowQueues.rowQueue[b]));
	}

	if (total >= groupSize) {
		groupFits = true;
	}
    /**********************************/
    return groupFits;
}

            

bool checkHeight( float height, tFairgroundRideHeightRequirement access, bool adultInGroup )
{
    bool result= false;

    /*********** PR2 - EX 1C **********/
	if (height < 1.00 && access.lessThan100 != 0 && access.lessThan100 == adultInGroup) { 
		result = true;
	}
	else if (height >= 1.00 && height < 1.20 && access.between100_120 != 0 && access.between100_120 == adultInGroup) {
		result = true;
	}
	else if (height >= 1.20 && height < 1.40 && access.between120_140 != 0 && access.between120_140 == adultInGroup) {
		result = true;
	}
	else {
		if (height >= 1.40 && access.greaterThan140 == 2) {
				result = true;
		}
	}
    /**********************************/
    return result;
}



bool checkVisitor( tVisitorGroup group,
                       tFairgroundRide fairgroundRide,
                       tVisitorTable visitors,
                       bool adultInGroup,
                       tQueueType queueType )
{
    /*********** PR2 - EX 1D **********/
	bool result= false;
    int pos, ticketType, accessHeigh;

	pos = visitorTableFindById(visitors, group.visitor);
	if (pos >= 0) {
		ticketType = visitors.table[pos].purchasedTicket;
		accessHeigh = checkHeight(visitors.table[pos].height*0.01, fairgroundRide.accessHeight, adultInGroup);
		if (ticketType > 0 && accessHeigh && 
			((ticketType == 2 && queueType <= 1) || (ticketType == 1 && queueType > 0)) &&
			((group.groupSize >= 1 && queueType != 2) || (group.groupSize == 1 && queueType == 2))) {
			result = true;
		}
	}
    /**********************************/
    return result;
}

void processGroup( tVisitorQueue *queue, 
                   tRowQueues *rowQueues, 
                   unsigned int groupSize,
                   tFairgroundRide fairgroundRide,
                   tVisitorTable visitors,
                   unsigned int *freeSeats, 
                   tQueueType queueType )
{
    /*********** PR2 - EX 2 **********/
	bool hasAdult = false;
	bool canEnter = false;
	int delete = 0;
	int queuePos = 0;
	int visitorsInQueue  = 0;

	tVisitorQueue temporaryQueue;
	tVisitorGroup head;

 	visitorQueueCreate(&temporaryQueue); 
	if (!visitorQueueEmpty(*queue)) { 
		for (int x = 0; x < groupSize; x++) { 
			head = visitorQueueHead(*queue); 
			visitorQueueEnqueue(&temporaryQueue, head); 
			visitorQueueDequeue(queue); 
			if (isAdultVisitor(head.visitor, visitors)){ 
				hasAdult = true; 
			} 
		} 
	} 


	for (int z = 0; z < groupSize; z++) {
		head = visitorQueueHead(temporaryQueue);
		canEnter = checkVisitor(head, fairgroundRide, visitors, hasAdult, queueType);
		if(canEnter) {
			visitorsInQueue = visitorQueueLength(rowQueues->rowQueue[queuePos]);
			if(visitorsInQueue >= MAX_VISITORS_IN_ROW) {
				queuePos += 1;
			}
			visitorQueueEnqueue(&rowQueues->rowQueue[queuePos], head);
			delete += 1;
		}
		visitorQueueDequeue(&temporaryQueue);
	}
	*freeSeats = *freeSeats-delete;
    /**********************************/
}

void processQueue( tVisitorQueue *queue, 
                   tRowQueues *rowQueues, 
                   tFairgroundRide fairgroundRide,
                   tVisitorTable visitors,
                   unsigned int *freeSeats,
                   tQueueType queueType )
{
  	tVisitorGroup group;
  	bool check= true;

	while (check && !visitorQueueEmpty(*queue)){
    	group= visitorQueueHead(*queue);
    	check= checkGroup( *rowQueues, group.groupSize );
    	if (check) {
        	processGroup( queue, rowQueues, group.groupSize, 
                    fairgroundRide, visitors, freeSeats, queueType );
        	visitorQueueDequeue(queue);
    	} 
	}
}



void processQueues( tRideManagement *rideManagement, 
                    tFairgroundRide fairgroundRide,
                    tVisitorTable visitors, 
                    unsigned int freeSeats )
{
    processQueue(&rideManagement->fastPassQueue,
                 &rideManagement->rowQueues, 
                  fairgroundRide, visitors, 
                 &freeSeats, FAST_PASS_QUEUE );

    processQueue(&rideManagement->mainQueue,
                 &rideManagement->rowQueues, 
                  fairgroundRide, visitors, 
                 &freeSeats, MAIN_QUEUE );

    processQueue(&rideManagement->singleQueue,
                 &rideManagement->rowQueues, 
                  fairgroundRide, visitors,
                 &freeSeats, SINGLE_QUEUE );
}



void fillWagons( tRideManagement *rideManagement )
{
    /*********** PR2 - EX 3A **********/
	int x, b, numVisitors;
	tVisitorGroup head;

	if (!visitorQueueEmpty(rideManagement->rowQueues.rowQueue[0])) {
		for (x = 0; x < rideManagement->rowQueues.nRows; x++) {
			if (!visitorQueueEmpty(rideManagement->rowQueues.rowQueue[x])) {
				numVisitors = visitorQueueLength(rideManagement->rowQueues.rowQueue[x]);
				for (b = 0; b < numVisitors; b++) {
					head = visitorQueueHead(rideManagement->rowQueues.rowQueue[x]);
					visitorStackPush(&rideManagement->wagons.wagonRow[x], head.visitor); 
					visitorQueueDequeue(&rideManagement->rowQueues.rowQueue[x]);
				}
			}
		}
	}
    /**********************************/
}


void clearWagons( tRideManagement *rideManagement )
{
    /*********** PR2 - EX 3B **********/
	int x, b, numVisitors;

	if (!visitorStackEmpty(*rideManagement->wagons.wagonRow)) {
		for (x = 0; x < rideManagement->rowQueues.nRows; x++) {
			if (!visitorStackEmpty(rideManagement->wagons.wagonRow[x])) {
				numVisitors = visitorStackSize(rideManagement->wagons.wagonRow[x]);
				for (b = 0; b < numVisitors; b++) {
					visitorStackPop(&rideManagement->wagons.wagonRow[x]);
				}
			}
		}	
	}
    /**********************************/
}



void processRide( tRideManagement *rideManagement,
                  tFairgroundRideTable fairgroundRides,
                  tVisitorTable visitors )
{
    int freeSeats, idx;
    tFairgroundRide fairgroundRide;
 
    if (checkRide( *rideManagement, fairgroundRides ))
    {
        idx= fairgroundRideTableFindById(fairgroundRides, rideManagement->fairgroundId);
        fairgroundRideCopy(&fairgroundRide,fairgroundRides.table[idx]);
        freeSeats= fairgroundRide.numPersonsTrip;

        /* process visitors in the fairground queues and put them into the row queues */
        processQueues( rideManagement, fairgroundRide, visitors, freeSeats );

        /* move people from the row queues to corresponding row wagon */
        fillWagons( rideManagement );

        /* here is where visitors have fun */
        /* :-) */

        /* move people out from the all row wagons (let place to other visitors waiting their turn) */
        clearWagons( rideManagement );
    }
}

void processAllRides(tAppData *object)
{
    int i;

    for (i= 0; i< object->managementRides.nRidesManagement; i++)
        processRide( &(object->managementRides.table[i]),
                       object->fairgroundRides, 
                       object->visitors ); 
}

