/*****************************************************************************
 * COSC1283/1284 - Programming Techniques
 * Semester 2 2011 Assignment #2
 * Full Name        : Karim Mohamed Gamal Abulainine
 * Student Number   : 3314713
 * Yallara Username : s3314713@yallara.cs.rmit.edu.au
 * Course Code      : COSC1283
 * Program Code     : MC060
 * Start up code provided by Christopher Hoobin and Xiaodong Li
 ******************************************************************************/

#ifndef _VM_UTILITY_H
#define _VM_UTILITY_H

/* Function prototypes. */
void readRestOfLine(void);
int systemInit(VendingMachineType*);
int loadData(VendingMachineType*, char*, char*);
void systemFree(VendingMachineType*);
void insertNode(VendingMachineType*, ProductNodeType*);
void displayMainMenu(void);
int getUserInt(char *, int, int, int);
void getProductName(char*);
void getBrandName(char*);
ProductNodeType* getProduct(char*, VendingMachineType *);
double makePayment(double, VendingMachineType*, int*);
int getCoins(VendingMachineType*);
void printChangeCoins(double, VendingMachineType*);
void deleteNode(VendingMachineType*, char*);
#endif
