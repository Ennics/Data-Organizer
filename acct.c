#include "defs.h"

/*
  Function:  initAcctList
   Purpose:  initializes the account list to default values
       out:  list with default values
*/
void initAcctList(AcctListType *list) {
  list->head = NULL;
  list->tail = NULL;
}

/*
  Function:  initAccount
   Purpose:  initialize all variables in account type to default values
        in:  input param for account number
        in:  input param for account type
        in:  input param for customer type
        in:  input param for account balance 
       out:  new account with fields set to initial values
*/
void initAccount(int n, AcctEnumType at, CustomerType *c, float b, AccountType **acct) {
  *acct = calloc(1, sizeof(AccountType)); //*acct = calloc(MAX_ARR, sizeof(AccountType));
  (*acct)->acctNum = n;
  (*acct)->acctType = at;
  (*acct)->cust = c;
  (*acct)->balance = b;
}

/*
  Function:  addAccount
   Purpose:  function to add a new account to linked list off acounts
       out:  list head and tail will be adjusted 
        in:  account information to be added to linked list
*/
void addAccount(AcctListType *list, AccountType *acct) {
  NodeType *newNode;
  newNode = malloc(sizeof(NodeType));
  newNode->data = acct;
  newNode->next = NULL;

  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    list->tail->next = newNode;
    list->tail = newNode;
  }  
}

/*
  Function:  addAccountByBalance
   Purpose:  adds accounts to list in decreasing order by balance
       out:  list to have accounts added to it
        in:  account being added to the list
*/
void addAccountByBalance(AcctListType *list, AccountType *acct) {
  NodeType *newNode, *curNode, *prevNode;
  int currentPos;

  newNode = malloc(sizeof(NodeType));
  newNode->data = acct;
  newNode->next = NULL;

  curNode = list->head;
  prevNode = NULL;

  if (list->head == NULL) {
      list->head = newNode;
      list->tail = newNode;
  } else {
    while(1) {
      if (curNode == NULL) {
        prevNode->next = newNode;
        list->tail = newNode;
        break;
      } else if (newNode->data->balance < curNode->data->balance) {
        prevNode = curNode;
        curNode = curNode->next;
      } else {
        if (prevNode == NULL) {
          newNode->next = curNode;
          list->head = newNode;
          break;
        } else {
          prevNode->next = newNode;
          newNode->next = curNode;
          break;
        }
      }
    }
  }
}

/*
  Function:  printAccount
   Purpose:  prints all field in a given account
        in:  give account to be printed out
*/
void printAccount(AccountType *acct) {
  char accountType[MAX_STR], accountOwner[MAX_STR];
  assignType(acct->acctType, accountType);

  if (acct->cust == NULL) {
    strcpy(accountOwner, "UNKNOWN");
  } else {
    strcpy(accountOwner, acct->cust->name);
  }

  printf("Acct Num: %-9d Type: %-10s Owner: %-9s Balance: $ %-10.2f \n", acct->acctNum, accountType, accountOwner, acct->balance);
}

/*
  Function:  assignType
   Purpose:  passes in a string variable by reference and changes it to proper account type with given account type number
        in:  account number
       out:  corresponding account type string
*/
void assignType(int accountNum, char *accountString) {
  if (accountNum == 0) {
    strcpy(accountString, "CHECKING");
  } else if (accountNum == 1) {
    strcpy(accountString, "SAVINGS");
  } else if (accountNum == 2){
    strcpy(accountString, "OTHER");
  } else {
    strcpy(accountString, "UNKNOWN");
  }
}

/*
  Function:  printAccounts
   Purpose:  prints all accounts in linked list and prints head and tail if ends is equal to C_TRUE
        in:  linked list with all account to be printed
        in:  ends variable to see if head and tail will be printed
*/
void printAccounts(AcctListType *list, int ends) {
    if (list->head == NULL) {
        printf("NO ACCOUNTS\n");
    } else {
      NodeType *curNode;
      curNode = list->head;
      while(1) {
        if (curNode == NULL) {
            break;
        }
        printAccount(curNode->data);
        curNode = curNode->next;
      }
      if (ends == C_TRUE) {
        printf("--HEAD-- ");
        printAccount(list->head->data);
        printf("--TAIL-- ");
        printAccount(list->tail->data);
      }
    }
}

/*
  Function:  cleanupAcctData
   Purpose:  deallocates data in given linked list
        in:  list with data 
*/
void cleanupAcctData(AcctListType *list) { 
  NodeType *curNode;
  curNode = list->head;
  while(1) {
    if (curNode == NULL) {
        break;
    }
    free(curNode->data);
    curNode = curNode->next;
  }
}

/*
  Function:  cleanupAcctList
   Purpose:  deallocates nodes in given linked list
        in:  list with nodes 
*/
void cleanupAcctList(AcctListType *list) {
  NodeType *curNode;
  NodeType *nextNode;
  curNode = list->head;
  nextNode = list->head;
  while(1) {
    if (curNode == NULL) {
        break;
    }
    nextNode = curNode->next;
    free(curNode);
    curNode = nextNode;
  }
}

/*
  Function:  printByBalance
   Purpose:  prints a given list in decreasing order by balance
        in:  list to be "sorted" in decreasing order and the printed
        in:  ends variable to print or not print the head and tail of the sorted list
*/
void printByBalance(AcctListType *orgList, int ends) {
  AcctListType decreasingList;
  initAcctList(&decreasingList);

  NodeType *curNode;
  curNode = orgList->head;
  while(1) {
    if (curNode == NULL) {
        break;
    }
    addAccountByBalance(&decreasingList, curNode->data);
    curNode = curNode->next;
  }
  printAccounts(&decreasingList, ends);
  cleanupAcctList(&decreasingList);
}
