#include "data.h"

/* Get a textual representation of a ride management */
void getManagementStr(tRideManagement management, int maxSize, char *str);

/* Get a ride management object from its textual representation */
void getManagementObject(const char *str, tRideManagement *management);

/* Copy the management data in src to dst*/
void managementCopy(tRideManagement *dst, tRideManagement src);

/* Compares the management data of p1 and p2*/
int managementCompare(tRideManagement p1, tRideManagement p2);

/* Initializes the given managements table */
void managementTableInit(tRidesManagementTable *managementsTable);

/* Add a new management to the table of managements */
void managementTableAdd(tRidesManagementTable *tabManagements, tRideManagement management, tError *retVal);

/* Load the table of managements from a file */
void managementTableLoad(tRidesManagementTable *tabManagements, const char* filename, tError *retVal);

/* Save a table of managements to a file */
void managementTableSave(tRidesManagementTable tabManagements, const char* filename, tError *retVal);
