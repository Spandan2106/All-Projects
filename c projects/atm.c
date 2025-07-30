#include <stdio.h>

typedef struct {
    double balance;
} Account;

void showMenu() {
    printf("ATM Menu:\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void checkBalance(Account *acc) {
    printf("Your current balance is: $%.2f\n", acc->balance);
}

void deposit(Account *acc) {
    double amount;
    printf("Enter amount to deposit: $");
    scanf("%lf", &amount);
    if (amount > 0) {
        acc->balance += amount;
        printf("Deposit successful. New balance: $%.2f\n", acc->balance);
    } else {
        printf("Invalid deposit amount. Please enter a positive value.\n");
    }
}

void withdraw(Account *acc) {
    double amount;
    printf("Enter amount to withdraw: $");
    scanf("%lf", &amount);
    if (amount > 0) {
        if (amount <= acc->balance) {
            acc->balance -= amount;
            printf("Withdrawal successful. New balance: $%.2f\n", acc->balance);
        } else {
            printf("Insufficient balance. Withdrawal failed.\n");
        }
    } else {
        printf("Invalid withdrawal amount. Please enter a positive value.\n");
    }
}

int main() {
    Account userAccount = {0.0};
    int choice;

    printf("Welcome to the ATM System!\n");

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(&userAccount);
                break;
            case 2:
                deposit(&userAccount);
                break;
            case 3:
                withdraw(&userAccount);
                break;
            case 4:
                printf("Thank you for using the ATM. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
