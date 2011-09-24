/*****************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 2 2011 Assignment #2 - Vending Machine
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Yallara Username : EDIT HERE
* Course Code      : EDIT HERE
* Program Code     : EDIT HERE
* Start up code provided by Christopher Hoobin and Xiaodong Li
******************************************************************************/

#ifndef _VM_UTILITY_H
#define _VM_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
void systemInit(VendingMachineType* vm);
void loadData(VendingMachineType* vm, char* stockfile, char* coinsFile);
void systemFree(VendingMachineType* vm);

#endif
