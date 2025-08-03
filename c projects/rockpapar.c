// c code to play rock paper scissors for 2 players
// Compiler: gcc
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int player1, player2;
    srand(time(NULL)); // Seed the random number generator

    printf("Player 1, enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ");
    scanf("%d", &player1);
    
    printf("Player 2, enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ");
    scanf("%d", &player2);

    if (player1 < 0 || player1 > 2 || player2 < 0 || player2 > 2) {
        printf("Invalid input! Please enter 0, 1, or 2.\n");
        return 1;
    }

    if (player1 == player2) {
        printf("It's a tie!\n");
    } else if ((player1 == 0 && player2 == 2) || (player1 == 1 && player2 == 0) || (player1 == 2 && player2 == 1)) {
        printf("Player 1 wins!\n");
    } else {
        printf("Player 2 wins!\n");
    }

    return 0;
}