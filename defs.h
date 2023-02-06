#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define C_TRUE     1
#define C_FALSE    0

#define MAX_ARR  128
#define MAX_STR   32

#define NEXT_CUST_ID    4001
#define NEXT_ACCT_ID  700210

typedef enum { CHEQUING, SAVINGS, OTHER } AcctEnumType;

struct AcctList;

typedef struct {
  int  id;
  char name[MAX_STR];
  struct AcctList *accounts;
} CustomerType;

typedef struct {
  int          acctNum;
  AcctEnumType acctType;
  CustomerType *cust;
  float        balance;
} AccountType;

/*** Define the CustArrayType here ***/
typedef struct {
  CustomerType *curstomer[MAX_ARR];
  int size;
} CustArrayType;

/*** Define the NodeType here ***/
typedef struct Node{
  AccountType *data;
  struct Node *next;
} NodeType;

/*** Complete the AcctListType here ***/
typedef struct AcctList {
  NodeType *head;
  NodeType *tail;
} AcctListType;

/*** Define the BankType here ***/
typedef struct {
  AcctListType accounts;
  CustArrayType customers;
} BankType;


void initAcctList(AcctListType*);
void initAccount(int, AcctEnumType, CustomerType*, float, AccountType**);
void initCustArray(CustArrayType *);
void initCustomer(int, char*, CustomerType**);
void initBank(BankType*);

void addAccount(AcctListType*, AccountType*);
void addAccountByBalance(AcctListType*, AccountType*);
void addCustomer(CustArrayType*, CustomerType*);

void printMenu(int*);
void printAccount(AccountType*);
void printAccounts(AcctListType*, int);
void printByBalance(AcctListType *, int);
void printCustomers(CustArrayType*);

void cleanupAcctData(AcctListType*);
void cleanupAcctList(AcctListType*);
void cleanupCustArray(CustArrayType*);
void cleanupBank(BankType*);

void loadBankData(BankType*);

void assignType(int, char*);


