#include "defs.h"

/*
  Function:  initCustArray
   Purpose:  initializes the size value in arr
       out:  list with default value for size
*/
void initCustArray(CustArrayType *arr) {
  arr->size = 0;
}

/*
  Function:  initCustomer
   Purpose:  initialize all the values of a customer
        in:  customer ID
        in:  customer name
       out:  customer type to have values initialized
*/
void initCustomer(int id, char *n, CustomerType **cust) {
  *cust = calloc(1, sizeof(CustomerType)); //*cust = calloc(MAX_ARR, sizeof(CustomerType));
  (*cust)->id = id;
  strcpy((*cust)->name, n);
  (*cust)->accounts = calloc(1, sizeof(AcctListType)); //(*cust)->accounts = calloc(MAX_ARR, sizeof(AcctListType));
  initAcctList((*cust)->accounts);
}

/*
  Function:  addCustomer
   Purpose:  adds a given customer to the back of the customer array
       out:  customer array to have added customer
        in:  customer to be added
*/
void addCustomer(CustArrayType *arr, CustomerType *c) {
  if (arr->size < MAX_ARR) {
    arr->curstomer[arr->size] = c;
    arr->size = arr->size + 1;
  } else {
    printf("Customer array capacity reached.");
  }
}

/*
  Function:  printCustomers
   Purpose:  prints all the customers and their corresonding accounts
        in:  array with customers to have information printed
*/
void printCustomers(CustArrayType *arr) {
  for (int i = 0; i < arr->size; ++i) {
    printf("%d %-10s\n", arr->curstomer[i]->id, arr->curstomer[i]->name);
    printAccounts(arr->curstomer[i]->accounts, C_FALSE);
  }
}

/*
  Function:  cleanupCustArray
   Purpose:  deallocates memory from customer array
        in:  customer array to have memory deallocated
*/
void cleanupCustArray(CustArrayType *arr) {
  for (int i = 0; i < arr->size; ++i) {
    cleanupAcctList(arr->curstomer[i]->accounts);
    free(arr->curstomer[i]->accounts);
    free(arr->curstomer[i]);
  }
}