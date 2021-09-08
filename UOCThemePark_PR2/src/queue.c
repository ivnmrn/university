#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "visitor.h"
#include "queue.h"

void visitorQueueCreate( tVisitorQueue *queue ) {
	queue->nElem=0;
}

tVisitorGroup visitorQueueHead(tVisitorQueue queue) {
	tVisitorGroup head;
    visitorGroupCopy( &head, queue.table[0]);
	return head;
}

bool visitorQueueEmpty(tVisitorQueue queue) {	
	bool empty = true;
	empty = (queue.nElem==0);
	return empty;
}

bool visitorQueueFull(tVisitorQueue queue) {	
	bool full = false;
	full = (queue.nElem==MAX_VISITORS);
	return full;
}

int visitorQueueLength(tVisitorQueue queue)
{
    return queue.nElem;
}

void visitorQueueEnqueue(tVisitorQueue *queue, tVisitorGroup newElement) 
{
    visitorGroupCopy( &queue->table[queue->nElem], newElement);
    queue->nElem++;
}

void visitorQueueDequeue (tVisitorQueue *queue) 
{	
	unsigned int i=0;
	for (i=0; i<queue->nElem-1; i++) {
        visitorGroupCopy( &queue->table[i], queue->table[i+1]);
	}
	queue->nElem--;
}

void visitorQueueCopy(tVisitorQueue *dst, tVisitorQueue src)
{    
    visitorQueueCreate(dst);
    while (!visitorQueueEmpty(src)) {
            visitorQueueEnqueue(dst, visitorQueueHead(src));
            visitorQueueDequeue(&src);
    }
}

int visitorQueueCompare(tVisitorQueue q1, tVisitorQueue q2)
{
    int result;
    
    result= 0;
    
    if (visitorQueueLength(q1) < visitorQueueLength(q2))
        result= -1;
    else if (visitorQueueLength(q1) > visitorQueueLength(q2))
        result= 1;
    else {
        while (!visitorQueueEmpty(q1) && result==0) {
                result= visitorGroupCompare(visitorQueueHead(q1),visitorQueueHead(q2));
                visitorQueueDequeue(&q1);
                visitorQueueDequeue(&q2);
        }            
    }
    
    return result;
}

void getVisitorGroupStr( tVisitorGroup group, int maxSize, char *str )
{
    int length;

    length= snprintf(str, maxSize-1, "%d %d", group.visitor, group.groupSize);
            
    if (length>0) 
        str[length]='\0';
} 

void getVisitorGroupObject(const char *str, tVisitorGroup *group) 
{
	int aux_visitor_id, aux_visitor_group_size;
    sscanf(str, "%d %d", &aux_visitor_id, &aux_visitor_group_size); 
    group->visitor= (tVisitorId)aux_visitor_id;
    group->groupSize= aux_visitor_group_size;
}

/* The content of the fields of the queue structure is written into the string str */
void getVisitorQueueStr( tVisitorQueue queue, int maxSize, char *str) 
{
    int length;
	tVisitorGroup visitorGroup;
    char tempStr[MAX_LINE];    

    /* write the size of the queue */
    length= snprintf(str, maxSize-1, "%d", visitorQueueLength(queue));
 	if (length>0) 
		str[length]='\0';

    while(!visitorQueueEmpty(queue))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        visitorGroupCopy( &visitorGroup, visitorQueueHead(queue) );

        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d %d", tempStr, 
                visitorGroup.visitor, visitorGroup.groupSize);
        if (length>0) 
            str[length]='\0';

        /* dequeue the head element to allow writting of next element */
        visitorQueueDequeue(&queue);
    }

 	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the queue structure */
void getVisitorQueueObject(const char *str, tVisitorQueue *queue) 
{
	int i, size, aux_visitor_id, aux_visitor_group_size;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tVisitorGroup newVisitor;

    /* read queue size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the queue */
    visitorQueueCreate(queue);

    for (i= 0; i< size; i++)
    {
        /* read the loaded data as a string*/
        sscanf(tempStr, "%d %d %[^\n]s", &aux_visitor_id, &aux_visitor_group_size, nextStr); 
        newVisitor.visitor= (tVisitorId)(aux_visitor_id);
        newVisitor.groupSize= (tVisitorId)(aux_visitor_group_size);

        /* enqueue it on the queue */
        visitorQueueEnqueue( queue, newVisitor );

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

void visitorQueueSave(tVisitorQueue queue, const char* filename, tError *retVal) {

	*retVal = OK;
	FILE *fout=0;
	char str[MAX_LINE];
	tVisitorGroup req;
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {

		/* Save all visitors to the file */
		while(!visitorQueueEmpty(queue))
        {
            visitorGroupCopy(&req, visitorQueueHead(queue));
            getVisitorGroupStr(req, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            visitorQueueDequeue(&queue);
		}
           
        /* Close the file */
		fclose(fout);
	} 
}

void visitorQueueLoad(tVisitorQueue *queue, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=0;
	char line[MAX_LINE];
	tVisitorGroup newVisitor;
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

	    /* Initialize the queue */
		visitorQueueCreate(queue);

		/* Read all the lines (visitors) */
		while(!feof(fin) && !visitorQueueFull(*queue)) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getVisitorGroupObject(line, &newVisitor);
				/* Add the new visitor to the queue */
				visitorQueueEnqueue(queue, newVisitor);		
			}
		}

		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void visitorGroupCopy( tVisitorGroup *target, tVisitorGroup source )
{
    target->visitor  = source.visitor;
    target->groupSize= source.groupSize;    
}

int visitorGroupCompare( tVisitorGroup group1, tVisitorGroup group2 )
{
    int result= 0;
    
    if (group1.groupSize < group2.groupSize)
        result= -1;
    else if (group1.groupSize > group2.groupSize)
        result= 1;
    else {
        if (group1.visitor < group2.visitor)
            result= -1;
        else if (group1.visitor > group2.visitor)
            result= 1;
    }
    
    return result;
}
