#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "visitor.h"

void visitorStackCreate(tVisitorStack *stack ) {
	stack->nElem=0;
}

void visitorStackPush(tVisitorStack *s, tVisitorId t)
{
    if (s->nElem == MAX_VISITORS_IN_STACK) {
        printf("\n Full stack \n");
    } else {
        s->table[s->nElem]= t;
        s->nElem++;
    }
}

tVisitorId visitorStackTop(tVisitorStack s)
{
    tVisitorId t;

    if (s.nElem == 0) {
        printf("\n Empty stack \n");
        t= NO_VISITOR;
    } else {
        t= s.table[s.nElem-1];
    }
    return t;
}

void visitorStackPop(tVisitorStack *s)
{
    if (s->nElem == 0) {
        printf("\n Empty stack\n");
    } else {
        s->nElem--;
    }    
}

bool visitorStackEmpty(tVisitorStack s)
{
    return (s.nElem == 0);
}

bool visitorStackFull(tVisitorStack s)
{
    return (s.nElem == MAX_VISITORS_IN_STACK);
}

void visitorStackInvert(tVisitorStack *stack)
{
    tVisitorStack tmpStack;
    tVisitorId e;

    /* move all elements to an auxiliar stack */
    visitorStackCreate(&tmpStack);
    while (!visitorStackEmpty(*stack)) 
    {
        e= visitorStackTop(*stack);
        visitorStackPush(&tmpStack,e);
        visitorStackPop(stack);
    }
    
    /* assign inverted stack */
    *stack= tmpStack;
}

void visitorStackClean(tVisitorStack *s)
{
    s->nElem= 0;
}

int visitorStackSize(tVisitorStack s)
{
    return s.nElem;
}

bool visitorStackContains(tVisitorStack s, tVisitorId e)
{
    bool found;
    int i;

    i= 0;
    found= false;
    while (i < s.nElem && !found) {
        found= (s.table[i] == e);
        i++;
    }
    
    return found;
}

void visitorStackSave(tVisitorStack stack, const char* filename, tError *retVal)
{
	*retVal = OK;

	FILE *fout=0;
	tVisitorId visitor;

	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;

	} else {

        /* invert to ensure correct order when loading */
        visitorStackInvert(&stack);
        
		while(!visitorStackEmpty(stack))
        {
			visitor = visitorStackTop(stack);
			fprintf(fout, "%d\n",visitor);
			visitorStackPop(&stack);
		}

        /* Close the file */
		fclose(fout);
	}
}

void visitorStackLoad(tVisitorStack *stack, const char* filename, tError *retVal)
{
	*retVal = OK;
	FILE *fin=0;
	char line[MAX_LINE];
	tVisitorId newVisitor;
    int aux_id;

	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) 
    {
        /* Initialize the stack */
		visitorStackCreate(stack);

		/* Read all the lines (requests) */
		while(!feof(fin) && !visitorStackFull(*stack)) {

			/* Remove any content from the line */
			line[0] = '\0';

			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);

			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
                sscanf(line, "%d", &aux_id);
                newVisitor= (tVisitorId)(aux_id);
                
				/* Add the new request to the queue */
				visitorStackPush(stack, newVisitor);		
			}
		}
		/* Close the file */
		fclose(fin);
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void visitorStackCopy(tVisitorStack *dst, tVisitorStack src)
{    
    visitorStackCreate(dst);
    while (!visitorStackEmpty(src)) {
            visitorStackPush(dst, visitorStackTop(src));
            visitorStackPop(&src);
    }
    
    visitorStackInvert(dst);
}

int visitorStackCompare(tVisitorStack s1, tVisitorStack s2)
{
    int result;
    
    result= 0;
    
    if (visitorStackSize(s1) < visitorStackSize(s2))
        result= -1;
    else if (visitorStackSize(s1) > visitorStackSize(s2))
        result= 1;
    else {
        while (!visitorStackEmpty(s1) && result==0) {
			// @@ no faltaria l'assignació de result = 0 quan siguin iguals?
				if (visitorStackTop(s1) > visitorStackTop(s2))
                    result= 1;
                else if (visitorStackTop(s1) < visitorStackTop(s2))
                    result= -1;
                visitorStackPop(&s1);
                visitorStackPop(&s2);
        }
    }
    
    return result;
}

/* The content of the fields of the stack structure is written into the string str */
void getVisitorStackStr( tVisitorStack stack, int maxSize, char *str) {

    int length;
	tVisitorId visitor;
    char tempStr[MAX_LINE];    
    
    /* invert to allow writting from bottom to top */
    visitorStackInvert(&stack);

    /* write the size of the stack */
    length= snprintf(str, maxSize-1, "%d", visitorStackSize(stack));
 	if (length>0) 
		str[length]='\0';
    
    while(!visitorStackEmpty(stack))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        visitor = visitorStackTop(stack);
        
        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d", tempStr, visitor);
        if (length>0) 
            str[length]='\0';
            
        /* pop the top element to allow writting of next element */
        visitorStackPop(&stack);
    }

 	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the stack structure */
void getVisitorStackObject(const char *str, tVisitorStack *stack) {

	int i, size, aux_visitor_id;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tVisitorId newVisitor;

    /* read stack size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 
    
    /* Initialize the stack */
    visitorStackCreate(stack);
        
    for (i= 0; i< size; i++)
    {
        /* read the loaded visitor as a string*/
        sscanf(tempStr, "%d %[^\n]s", &aux_visitor_id, nextStr); 
        newVisitor= (tVisitorId)(aux_visitor_id);
        
        /* push it on the top of the stack */
        visitorStackPush( stack, newVisitor );
     
        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}
