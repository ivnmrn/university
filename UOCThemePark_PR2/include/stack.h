#include "data.h"

/* Creates the stack */
void visitorStackCreate( tVisitorStack * );

/* Push an element on the top of the stack */
void visitorStackPush(tVisitorStack *s, tVisitorId e);

/* Pops an element from the top of the stack */
void visitorStackPop(tVisitorStack *s);

/* Returns the element on top of the stack */
tVisitorId visitorStackTop(tVisitorStack s);

/* Says if the stack is empty */
bool visitorStackEmpty(tVisitorStack s);

/* Says if the stack is full */
bool visitorStackFull(tVisitorStack s);

/* Inverts a stack (puts bottom on top and top on bottom) */
void visitorStackInvert(tVisitorStack *s);

/* Cleans a stack (pops all elements) */
void visitorStackClean(tVisitorStack *s);

/* Returns the size (i.e. the number of elements) of the stack */
int visitorStackSize(tVisitorStack s);

/* Says if the given visitor is in the stack (on top or in any other position) */
bool visitorStackContains(tVisitorStack s, tVisitorId e);

/* Saves the stack on file */
void visitorStackSave(tVisitorStack  stack, const char* filename, tError *retVal);

/* Loads the stack from file */
void visitorStackLoad(tVisitorStack *stack, const char* filename, tError *retVal);

/* Copies an stack onto another stack */
void visitorStackCopy(tVisitorStack *dst, tVisitorStack src);

/* Compares two stacks */
int visitorStackCompare(tVisitorStack s1, tVisitorStack s2);

/* Gets the stack as a textual representation (string) */
void getVisitorStackStr( tVisitorStack stack, int maxSize, char *str);

/* Gets the stack object out of its textual representation (string) */
void getVisitorStackObject(const char *str, tVisitorStack *stack);
