// c code for online voting system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_CANDIDATES 100
#define MAX_NAME_LENGTH 50
#define MAX_VOTERS 10000000
#define MAX_VOTER_ID_LENGTH 20
#define MAX_VOTER_NAME_LENGTH 50
#define MAX_VOTER_ADDRESS_LENGTH 100
#define MAX_VOTER_PHONE_LENGTH 15
typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;
typedef struct {
    char id[MAX_VOTER_ID_LENGTH];
    char name[MAX_VOTER_NAME_LENGTH];
    char address[MAX_VOTER_ADDRESS_LENGTH];
    char phone[MAX_VOTER_PHONE_LENGTH];
    int hasVoted;
} Voter;
typedef struct {
    Candidate candidates[MAX_CANDIDATES];
    int candidateCount;
    Voter voters[MAX_VOTERS];
    int voterCount;
} VotingSystem;
void initializeVotingSystem(VotingSystem *vs) {
    vs->candidateCount = 0;
    vs->voterCount = 0;
}
void addCandidate(VotingSystem *vs, const char *name) {
    if (vs->candidateCount < MAX_CANDIDATES) {
        strncpy(vs->candidates[vs->candidateCount].name, name, MAX_NAME_LENGTH);
        vs->candidates[vs->candidateCount].votes = 0;
        vs->candidateCount++;
    } else {
        printf("Maximum candidate limit reached.\n");
    }
}
void addVoter(VotingSystem *vs, const char *id, const char *name, const char *address, const char *phone) {
    if (vs->voterCount < MAX_VOTERS) {
        strncpy(vs->voters[vs->voterCount].id, id, MAX_VOTER_ID_LENGTH);
        strncpy(vs->voters[vs->voterCount].name, name, MAX_VOTER_NAME_LENGTH);
        strncpy(vs->voters[vs->voterCount].address, address, MAX_VOTER_ADDRESS_LENGTH);
        strncpy(vs->voters[vs->voterCount].phone, phone, MAX_VOTER_PHONE_LENGTH);
        vs->voters[vs->voterCount].hasVoted = 0;
        vs->voterCount++;
    } else {
        printf("Maximum voter limit reached.\n");
    }
}
void castVote(VotingSystem *vs, const char *voterId, const char *candidateName) {
    for (int i = 0; i < vs->voterCount; i++) {
        if (strcmp(vs->voters[i].id, voterId) == 0) {
            if (vs->voters[i].hasVoted) {
                printf("Voter %s has already voted.\n", vs->voters[i].name);
                return;
            }
            for (int j = 0; j < vs->candidateCount; j++) {
                if (strcmp(vs->candidates[j].name, candidateName) == 0) {
                    vs->candidates[j].votes++;
                    vs->voters[i].hasVoted = 1;
                    printf("Vote casted successfully for %s by %s.\n", candidateName, vs->voters[i].name);
                    return;
                }
            }
            printf("Candidate %s not found.\n", candidateName);
            return;
        }
    }
    printf("Voter with ID %s not found.\n", voterId);
}
void displayResults(const VotingSystem *vs) {
    printf("Voting Results:\n");
    for (int i = 0; i < vs->candidateCount; i++) {
        printf("Candidate: %s, Votes: %d\n", vs->candidates[i].name, vs->candidates[i].votes);
    }
}
void saveDataToFile(const VotingSystem *vs, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(vs, sizeof(VotingSystem), 1, file);
    fclose(file);
    printf("Data saved to %s successfully.\n", filename);
}
void loadDataFromFile(VotingSystem *vs, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fread(vs, sizeof(VotingSystem), 1, file);
    fclose(file);
    printf("Data loaded from %s successfully.\n", filename);
}
int main() {
    VotingSystem vs;
    initializeVotingSystem(&vs);
    
    int choice;
    do {
        printf("\nVoting System Menu:\n");
        printf("1. Add Candidate\n");
        printf("2. Add Voter\n");
        printf("3. Cast Vote\n");
        printf("4. Display Results\n");
        printf("5. Save Data to File\n");
        printf("6. Load Data from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                printf("Enter candidate name: ");
                scanf("%s", name);
                addCandidate(&vs, name);
                break;
            }
            case 2: {
                char id[MAX_VOTER_ID_LENGTH], name[MAX_VOTER_NAME_LENGTH], address[MAX_VOTER_ADDRESS_LENGTH], phone[MAX_VOTER_PHONE_LENGTH];
                printf("Enter voter ID: ");
                scanf("%s", id);
                printf("Enter voter name: ");
                scanf("%s", name);
                printf("Enter voter address: ");
                scanf("%s", address);
                printf("Enter voter phone: ");
                scanf("%s", phone);
                addVoter(&vs, id, name, address, phone);
                break;
            }
            case 3: {
                char voterId[MAX_VOTER_ID_LENGTH], candidateName[MAX_NAME_LENGTH];
                printf("Enter voter ID: ");
                scanf("%s", voterId);
                printf("Enter candidate name to vote for: ");
                scanf("%s", candidateName);
                castVote(&vs, voterId, candidateName);
                break;
            }
            case 4:
                displayResults(&vs);
                break;
            case 5: {
                char filename[100];
                printf("Enter filename to save data: ");
                scanf("%s", filename);
                saveDataToFile(&vs, filename);
                break;
            }
            case 6: {
                char filename[100];
                printf("Enter filename to load data: ");
                scanf("%s", filename);
                loadDataFromFile(&vs, filename);
                break;
            }
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while
    (choice != 0);
    return 0;
}