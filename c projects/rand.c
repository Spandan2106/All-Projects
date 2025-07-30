// c project for number gussing system by using rand()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    int number, guess, guess_count = 0;
    srand(time(0)); // Seed the random number generator
    number = rand() % 100 + 1; // Generate a random number between 1 and 100
    printf("Welcome to the Number Guessing Game!\n");
    printf("I have selected a number between 1 and 100. Try to guess it!\n");
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        guess_count++;
        
        if (guess < number) {
            printf("Too low! Try again.\n");
        } else if (guess > number) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations! You've guessed the number %d in %d attempts.\n", number, guess_count);
        }
    } while (guess != number);
    return 0;

}