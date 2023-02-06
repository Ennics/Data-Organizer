#include "defs.h"

int main()
{
  BankType bank;
  initBank(&bank);
  loadBankData(&bank);
  int choice;

  do {
    printMenu(&choice);
    if (choice == 1) {
      printCustomers(&bank.customers);
    } else if (choice == 2) {
      printAccounts(&bank.accounts, C_TRUE);
    } else if (choice == 3) {
      printByBalance(&bank.accounts, C_TRUE);
    } else {
      if (choice == 0) {
        break;
      }
      printf("Invalid choice... try again\n\n");
    }
  } while (choice != 0);

  cleanupCustArray(&bank.customers);
  cleanupAcctData(&bank.accounts);
  cleanupAcctList(&bank.accounts);

  return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print customers\n");
  printf("  (2) Print accounts\n");
  printf("  (3) Print accounts by balance\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

