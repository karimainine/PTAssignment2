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

#ifndef _VM_H
#define _VM_H

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>

/* Constants. */
#define COIN_DEFAULT 5
#define STOCK_DEFAULT 5
#define PRODUCT_NAME_MAX 40
#define PRODUCT_BRAND_MAX 20
#define DISTINCT_COINS 6
#define PRODUCT_PRICE_MAX 3
#define PRODUCT_QTY_MAX 3
#define ADMIN_OPTIONS_NUM 6
#define USER_OPTIONS_NUM 3
#define TRUE 1
#define FALSE 0
#define EXTRA_SPACES 2
#define STRING_MIN_CHARS 1
#define MAX_PRODUCT_PRICE 995
#define MIN_PRODUCT_PRICE 5
#define MAX_PRODUCT_QUANTITY 999
#define MIN_PRODUCT_QUANTITY 0
#define MAX_MONETARY_STRINGS 20
#define MAX_COIN_VALUE 999

/* Max and Min values for a user input from the menu selection*/
#define MAX_OPTION_RANGE 9
#define MIN_OPTION_RANGE 1
#define MAX_OPTION_INPUT 1

#define SUCCESS 1
#define FAILURE 0

/* Structure definitions. */
typedef struct coin
{
   unsigned qty;
   unsigned value;  /* Stored in cents (not dollars). */
} CoinType;

typedef struct productNode
{
   char name[PRODUCT_NAME_MAX + 1];
   char brand[PRODUCT_BRAND_MAX + 1];
   unsigned price;  /* Stored in cents (not dollars). */
   unsigned qty;
   struct productNode *nextProduct;
} ProductNodeType;

typedef struct vendingMachine
{
   CoinType coins[DISTINCT_COINS];
   unsigned totalCoins;
   ProductNodeType *headProduct;
   unsigned totalProducts;
} VendingMachineType;

#endif
