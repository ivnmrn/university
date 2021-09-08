#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "management.h"
#include "stack.h"
#include "queue.h"
#include "visitor.h"

void getManagementStr(tRideManagement management, int maxSize, char *str) 
{
    int length;
 
    /* write the ride management identification */
    length= snprintf(str, maxSize-1, "%d", management.fairgroundId);
 	if (length>0) 
		str[length]='\0';    
}

void getManagementObject(const char *str, tRideManagement *management) 
{
    char tempStr[MAX_LINE];   
    int i;
    
    /* read the ride management identification */
    sscanf(str, "%d %[^\n]s", &management->fairgroundId, tempStr); 

    /* initialize the visitors queue: main, single and fast-pass */
    visitorQueueCreate( &management->fastPassQueue );
    visitorQueueCreate( &management->singleQueue );
    visitorQueueCreate( &management->mainQueue );
    
    /* initialize row queues */
    management->rowQueues.nRows= 0;
    for (i= 0; i< MAX_ROW_NUMBER; i++)
        visitorQueueCreate( &management->rowQueues.rowQueue[i] );

    /* initialize wagon rows */
    management->wagons.nRows= 0;
    for (i= 0; i< MAX_ROW_NUMBER; i++)
        visitorStackCreate( &management->wagons.wagonRow[i] );
}

void managementCopy(tRideManagement *dst, tRideManagement src) 
{
    int i;
    
    /* copy the fairground ride id */
    dst->fairgroundId= src.fairgroundId;
    
    /* copy queues */
    visitorQueueCopy(&dst->fastPassQueue, src.fastPassQueue);
    visitorQueueCopy(&dst->singleQueue, src.singleQueue);
    visitorQueueCopy(&dst->mainQueue, src.mainQueue);
    
    /* copy row queues */
    dst->rowQueues.nRows= src.rowQueues.nRows;
    for (i= 0; i< src.rowQueues.nRows; i++)
        visitorQueueCopy( &dst->rowQueues.rowQueue[i], 
                           src.rowQueues.rowQueue[i] );

    /* copy wagon rows */
    dst->wagons.nRows= src.wagons.nRows;
    for (i= 0; i< src.wagons.nRows; i++)
        visitorStackCopy( &dst->wagons.wagonRow[i], 
                           src.wagons.wagonRow[i] );
}

int managementCompare(tRideManagement d1, tRideManagement d2)
{
    int i, result = 0;

    if (d1.fairgroundId > d2.fairgroundId)
        result= 1;
    else if (d1.fairgroundId < d2.fairgroundId)
        result= -1;
    else {
        result= visitorQueueCompare(d1.fastPassQueue,d2.fastPassQueue);
        if (result==0) {
            result= visitorQueueCompare(d1.mainQueue,d2.mainQueue);
            if (result == 0) {
                result= visitorQueueCompare(d1.singleQueue,d2.singleQueue);
                
                if (d1.rowQueues.nRows > d2.rowQueues.nRows)
                    result= 1;
                else if (d1.rowQueues.nRows < d2.rowQueues.nRows)
                    result= -1;
                i= 0;
                while (result == 0 && i < d1.rowQueues.nRows) {
                    result= visitorQueueCompare( d1.rowQueues.rowQueue[i], 
                                              d2.rowQueues.rowQueue[i]);
                }
                
                if (d1.wagons.nRows > d2.wagons.nRows)
                    result= 1;
                else if (d1.wagons.nRows < d2.wagons.nRows)
                    result= -1;
                i= 0;
                while (result == 0 && i < d1.rowQueues.nRows) {
                    result= visitorStackCompare( d1.wagons.wagonRow[i], 
                                              d2.wagons.wagonRow[i]);
                }
            }
        }                                        
    }

    return result;
}

void managementTableInit(tRidesManagementTable *managementsTable) {
	
	managementsTable->nRidesManagement= 0;
}

void managementTableAdd(tRidesManagementTable *tabManagements, tRideManagement management, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new management */
	if(tabManagements->nRidesManagement>=MAX_RIDES_MANAGEMENT)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new management to the end of the table */
		managementCopy(&tabManagements->table[tabManagements->nRidesManagement],management);
		tabManagements->nRidesManagement++;
	}
}

void managementTableSave(tRidesManagementTable tabManagements, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} 
    else 
    {
        /* Save general management data to the file */
        for(i=0;i<tabManagements.nRidesManagement;i++) 
        {
            getManagementStr(tabManagements.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            
            getVisitorQueueStr(tabManagements.table[i].fastPassQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);

            getVisitorQueueStr(tabManagements.table[i].singleQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);

            getVisitorQueueStr(tabManagements.table[i].mainQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            
            fprintf(fout, "%d\n", tabManagements.table[i].rowQueues.nRows);
            for (i= 0; i< tabManagements.table[i].rowQueues.nRows; i++) {
                getVisitorQueueStr(tabManagements.table[i].rowQueues.rowQueue[i], MAX_LINE, str);
                fprintf(fout, "%s\n", str);
            }

            fprintf(fout, "%d\n", tabManagements.table[i].wagons.nRows);
            for (i= 0; i< tabManagements.table[i].wagons.nRows; i++) {
                getVisitorStackStr(tabManagements.table[i].wagons.wagonRow[i], MAX_LINE, str);
                fprintf(fout, "%s\n", str);
            }
        }
                    
        /* Close the file */
        fclose(fout);
	}
}

void managementTableLoad(tRidesManagementTable *tabManagements, const char* filename, tError *retVal) 
{	
	char line[MAX_LINE];
	tRideManagement newManagement;
    int i, managementLines;
	FILE *fin=0;
	*retVal = OK;
	
	/* Initialize the output table */
	managementTableInit(tabManagements);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the managements */
		while(!feof(fin) && tabManagements->nRidesManagement<MAX_RIDES_MANAGEMENT) 
        {
			/* Read the management object */
            managementLines= 0;
			line[0] = '\0';
			fgets(line, MAX_LINE-1, fin);
			line[MAX_LINE-1]='\0';
			if (strlen(line)>0) {
               getManagementObject(line, &newManagement);
               managementLines++;
            }
    
			/* Read the fastpass queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getVisitorQueueObject(line,&newManagement.fastPassQueue);
                    managementLines++;
                }
            }
                
			/* Read the single queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getVisitorQueueObject(line,&newManagement.singleQueue);
                    managementLines++;
                }
            }
            
			/* Read the main queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getVisitorQueueObject(line,&newManagement.mainQueue);
                    managementLines++;
                }
            }
            
			/* Read the queue rows object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    sscanf(line, "%d", &newManagement.rowQueues.nRows); 
                    managementLines++;
                }
            }
            i= 0;
            while (!feof(fin) && i < newManagement.rowQueues.nRows) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getVisitorQueueObject(line,&newManagement.rowQueues.rowQueue[i]);
                    i++;
                }
            }

			/* Read the wagon rows object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    sscanf(line, "%d", &newManagement.wagons.nRows); 
                    managementLines++;
                }
            }
            i= 0;
            while (!feof(fin) && i < newManagement.wagons.nRows) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getVisitorStackObject(line,&newManagement.wagons.wagonRow[i]);
                    i++;
                }
            }
            
            /* Add the new management to the output table */
            if (managementLines == 6) 
                managementTableAdd(tabManagements, newManagement, retVal);		
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
