#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int balance = 1000;
    int bet, length, win = 0;
    int seven_count = 0;
    int symbols[100];

    printf("Welcome to the Slot Machine Game!\n");
    printf("Starting balance: $%d\n", balance);

    while (balance > 0) {
        printf("\nEnter your bet (0 to quit): ");
        scanf("%d", &bet);

        if (bet == 0) {
            break;
        }

        if (bet > balance) {
            printf("Insufficient balance. Your current balance is $%d.\n", balance);
            continue;
        }

        printf("Enter the length of the sequence: ");
        scanf("%d", &length);

        for (int i = 0; i < length; i++) {
            symbols[i] = rand() % 10;
            printf("%d ", symbols[i]);

            if (symbols[i] == 7) {
                seven_count++;
            }
        }

        win = 0;

        int count = 1;
        for (int i = 0; i < length; i++) {
            for (int j = i + 1; j < length; j++) {
                if (symbols[i] == symbols[j]) {
                    count++;
                }
            }
        }

        if (count >= length / 3) {
            win = 1;
        } else if (count == length) {
            win = 2;
        }

        if (seven_count > 0) {
            if (win == 1) {
                printf("\nYou win $%d!\n", bet);
                balance += bet;
            } else if (win == 2) {
                printf("\nYou win $%d! (All numbers are the same)\n", bet * 2);
                balance += (bet * 2);
            } else {
                printf("\nYou lose $%d.\n", bet);
                balance -= bet;
            }
        } else {
            printf("\nYou lose $%d. Try again.\n", bet);
            balance -= bet;
        }

        // Check for jackpot (all sevens)
        if (seven_count == length) {
            printf("JACKPOT! You win $1000!\n");
            balance += 1000;
        }

        printf("Your balance: $%d\n", balance);
    }

    printf("Game over. Your final balance is $%d. Thanks for playing!\n", balance);

    return 0;
}
