// code for hangman game where the given words are stored in an array and the words are gfg,elephant,lion,pizza,spandan,beach and there hins are respictively are coding ,animal with trunk, animal king, food, name of a person, place near water
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_WORDS 6
#define MAX_LENGTH 20
#define MAX_TRIES 6
void display_hangman(int tries) {
    switch (tries) {
        case 0:
            printf("  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n");
            break;
        case 1:
            printf("  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n");
            break;
        case 2:
            printf("  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n");
            break;
        case 3:
            printf("  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n");
            break;
        case 4:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n");
            break;
        case 5:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n");
            break;
        case 6:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n");
            break;
    }
}
void play_hangman() {
    char *words[MAX_WORDS] = {"gfg", "elephant", "lion", "pizza", "spandan", "beach"};
    char *hints[MAX_WORDS] = {"coding", "animal with trunk", "animal king", "food", "name of a person", "place near water"};
    int word_index = rand() % MAX_WORDS;
    char *word = words[word_index];
    char hint[MAX_LENGTH];
    strcpy(hint, hints[word_index]);
    
    int word_length = strlen(word);
    char guessed[word_length + 1];
    for (int i = 0; i < word_length; i++) {
        guessed[i] = '_';
    }
    guessed[word_length] = '\0';

    int tries = 0;
    int correct_guesses = 0;
    char guess;

    printf("Welcome to Hangman!\n");
    printf("Hint: %s\n", hint);

    while (tries < MAX_TRIES && correct_guesses < word_length) {
        display_hangman(tries);
        printf("Word: %s\n", guessed);
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Please enter a valid letter.\n");
            continue;
        }

        int found = 0;
        for (int i = 0; i < word_length; i++) {
            if (word[i] == guess && guessed[i] == '_') {
                guessed[i] = guess;
                found = 1;
                correct_guesses++;
            }
        }

        if (!found) {
            tries++;
            printf("Incorrect guess! You have %d tries left.\n", MAX_TRIES - tries);
        }
    }

    if (correct_guesses == word_length) {
        printf("Congratulations! You've guessed the word: %s\n", word);
    } else {
        display_hangman(tries);
        printf("Game over! The word was: %s\n", word);
    }
}
int main() {
    srand(time(NULL)); // Seed the random number generator
    play_hangman();
    return 0;
}