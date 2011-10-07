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

#ifndef _VM_OPTIONS_H
#define _VM_OPTIONS_H

void purchaseProduct(VendingMachineType*);
void displayProducts(VendingMachineType*);
void saveData(VendingMachineType*, char*, char*);
void addProduct(VendingMachineType*);
void removeProduct(VendingMachineType*);
void displayCoins(VendingMachineType*);
void restockProducts(VendingMachineType*);
void restockCoins(VendingMachineType*);

#endif
