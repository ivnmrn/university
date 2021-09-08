#include "data.h"

void visitorQueueCreate( tVisitorQueue *queue );
tVisitorGroup visitorQueueHead(tVisitorQueue queue);
bool visitorQueueEmpty(tVisitorQueue queue);
bool visitorQueueFull(tVisitorQueue queue);
int  visitorQueueLength(tVisitorQueue queue);
void visitorQueueEnqueue(tVisitorQueue *queue, tVisitorGroup newElement);
void visitorQueueDequeue(tVisitorQueue *queue);
void visitorQueueCopy(tVisitorQueue *dst, tVisitorQueue src);
int  visitorQueueCompare(tVisitorQueue q1, tVisitorQueue q2);
void visitorQueueSave(tVisitorQueue tabVisitors, const char* filename, tError *retVal);
void visitorQueueLoad(tVisitorQueue *tabVisitors, const char* filename, tError *retVal);
void getVisitorQueueStr( tVisitorQueue queue, int maxSize, char *str);
void getVisitorQueueObject(const char *str, tVisitorQueue *queue);
void visitorGroupCopy( tVisitorGroup *target, tVisitorGroup source );
int  visitorGroupCompare( tVisitorGroup group1, tVisitorGroup group2 );
