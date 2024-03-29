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
void readRestOfLine(void);
int systemInit(VendingMachineType*);
int loadData(VendingMachineType*, char*, char*);
void systemFree(VendingMachineType*);
ProductNodeType *insertNode(ProductNodeType*, ProductNodeType*);
void displayMainMenu(void);
int getUserInt(char *, int, int, int);
void getProductName(char*);
void getBrandName(char*);
ProductNodeType* getProduct(char*, VendingMachineType *);
double makePayment(double, VendingMachineType*, int*);
int getCoins(VendingMachineType*);
void printChangeCoins(double, VendingMachineType*);
#endif
