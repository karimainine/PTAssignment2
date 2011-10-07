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

#include "vm.h"
#include "vm_utility.h"
#include "vm_options.h"

/****************************************************************************
* Menu option #1: Purchase Product
* Allows the user to purchase a product by specifying the product name and
* insert coins into the system in an interactive fashion. User is given any
* change necessary.
****************************************************************************/
void purchaseProduct(VendingMachineType *vm)
{
   char productName [PRODUCT_NAME_MAX + EXTRA_SPACES];
   ProductNodeType *selectedProduct = NULL;
   double change;
   int paymentComplete;
   getProductName(productName);
   if(*productName != '\n'){
      selectedProduct = getProduct(productName, vm);
      if(selectedProduct != NULL && selectedProduct->qty > 0){
         printf("\nProduct Price: %.2f\n", ((double)selectedProduct->price)/100);
         change = makePayment(selectedProduct->price, vm, &paymentComplete);
         if(paymentComplete == TRUE){
            selectedProduct->qty--;
            printf("Thank you for purchasing %s\n", selectedProduct->name);
         } else {
            printf("You selected to cancel the purchase\n");
         }
         if(change > 0){
            printf("Your change is: %.2f\n", change/100);
            printChangeCoins(change, vm);
         }
      }else if(selectedProduct != NULL && selectedProduct->qty <= 0){
         printf("\nThe selected product is out of stock.\n");
      }else{
         printf("\nProduct not found. Please try again.\n");
      }
   }
   
}

/****************************************************************************
* Menu option #2: Display Products
* Allows the user to view all products in the vending machine.
****************************************************************************/
void displayProducts(VendingMachineType *vm)
{
   ProductNodeType *current;
   current = vm->headProduct;
   printf("\nProduct                                  Brand                Price Qty");
   printf("\n---------------------------------------- -------------------- ----- ---\n");
   
   while (current != NULL)
   {
      printf("%-40.40s %-20.20s %5d %3d\n", current->name, current->brand, current->price, current->qty);
      current = current->nextProduct;
   }
   printf("\n");
}

/****************************************************************************
* Menu option #3: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(VendingMachineType *vm, char *stockFile, char *coinsFile)
{
}

/****************************************************************************
* Menu option #4: Add Product
* Allows a supplier to add a new product to the vending machine. All
* necessary information is prompted for.
****************************************************************************/
void addProduct(VendingMachineType *vm)
{
   char productName[PRODUCT_NAME_MAX];
   char productBrand[PRODUCT_BRAND_MAX];
   unsigned productPrice;
   unsigned productQuantity;
   ProductNodeType *product;
   
   printf("\nAdd Product\n");
   printf("-----------\n");
   getProductName(productName); 
   if(*productName != '\n'){
      getBrandName(productBrand);
      if(*productBrand != '\n'){
         productPrice = getUserInt("Enter the product's price in cents: ", PRODUCT_PRICE_MAX, MIN_PRODUCT_PRICE, MAX_PRODUCT_PRICE);
         if(productPrice != -1){
            productQuantity = getUserInt("Enter the products quantity: ", PRODUCT_QTY_MAX, MIN_PRODUCT_QUANTITY, MAX_PRODUCT_QUANTITY);
            if(productQuantity != -1){
               product = getProduct(productName, vm);
               if(product != NULL && product->price == productPrice){
                  product->qty += productQuantity;
               } else {
                  product = malloc(sizeof(ProductNodeType));
                  strcpy(product->name, productName);
                  strcpy(product->brand, productBrand);
                  product->price = productPrice;
                  product->qty = productQuantity;
                  
                  vm->headProduct = insertNode(vm->headProduct, product);
                  vm->totalProducts++;
               }
               printf("\n%s has been added successfully for $%.2f\n", productName, ((double)productPrice)/100);
            }
         }
      }
   }
}

/****************************************************************************
* Menu option #5: Remove Product
* Allows a supplier to remove a product from the vending machine.
****************************************************************************/
void removeProduct(VendingMachineType *vm)
{
}

/****************************************************************************
* Menu option #6: Display Coins
* Allows a supplier to view a summary of all coins in the vending machine.
****************************************************************************/
void displayCoins(VendingMachineType *vm)
{
   int i;
   double coinValue;
   double total = 0;
   printf("\nCoin  Quantity Value\n");
   printf("----- -------- --------\n");
   for(i=0; i<vm->totalCoins; i++){

      CoinType coin = vm->coins[i];
      coinValue = (((double)coin.value)/100)*coin.qty;
      
      printf("%5.2f %8d %8.2f\n", ((double)coin.value)/100, coin.qty, coinValue);
      total += coinValue;
   }
   printf("%24s","--------\n");
   printf("Total Value: %10.2f", total);
}

/****************************************************************************
* Menu option #7: Restock Products
* Allows the supplier to restock the vending machine products to the default
* level. The STOCK_DEFAULT constant from vm.h is used here.
****************************************************************************/
void restockProducts(VendingMachineType* vm)
{
}

/****************************************************************************
* Menu option #8: Restock Coins
* Allows the supplier to restock the vending machine coins to the default
* level. The COINS_DEFAULT constant from vm.h is used here.
****************************************************************************/
void restockCoins(VendingMachineType *vm)
{
}
