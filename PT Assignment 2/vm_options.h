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
