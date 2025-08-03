#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TABLE_SIZE 10
#define PRIME 7

// Node structure for chaining
struct Node {
    int data;
    struct Node* next;
};

// HashTable structure for chaining
struct ChainingHashTable {
    int size;
    struct Node** table;
};

// HashTable structure for open addressing
struct OpenAddressingHashTable {
    int size;
    int* table;
    int* deleted; // To mark deleted slots
};

// Function prototypes
struct ChainingHashTable* createChainingHashTable(int size);
void freeChainingHashTable(struct ChainingHashTable* ht);
struct OpenAddressingHashTable* createOpenAddressingHashTable(int size);
void freeOpenAddressingHashTable(struct OpenAddressingHashTable* ht);

// Hash Functions
int divisionMethod(int key, int size);
int midSquareMethod(int key, int size);
int foldingMethod(int key, int size);
int multiplicationMethod(int key, int size);
int universalHashing(int key, int size);
void printHashTable(struct OpenAddressingHashTable* ht);

// Chaining methods
int insertChaining(struct ChainingHashTable* ht, int key);
int searchChaining(struct ChainingHashTable* ht, int key);
int deleteChaining(struct ChainingHashTable* ht, int key);
void printChainingHashTable(struct ChainingHashTable* ht);

// Linear Probing methods
int insertLinearProbing(struct OpenAddressingHashTable* ht, int key);
int searchLinearProbing(struct OpenAddressingHashTable* ht, int key);
int deleteLinearProbing(struct OpenAddressingHashTable* ht, int key);
void printLinearProbingHashTable(struct OpenAddressingHashTable* ht);

// Quadratic Probing methods
int insertQuadraticProbing(struct OpenAddressingHashTable* ht, int key);
int searchQuadraticProbing(struct OpenAddressingHashTable* ht, int key);
int deleteQuadraticProbing(struct OpenAddressingHashTable* ht, int key);
void printQuadraticProbingHashTable(struct OpenAddressingHashTable* ht);

// Double Hashing methods
int doubleHashFunction(int key, int size);
int insertDoubleHashing(struct OpenAddressingHashTable* ht, int key);
int searchDoubleHashing(struct OpenAddressingHashTable* ht, int key);
int deleteDoubleHashing(struct OpenAddressingHashTable* ht, int key);
void printDoubleHashingHashTable(struct OpenAddressingHashTable* ht);

// Hash Functions Implementation
int divisionMethod(int key, int size) {
    return key % size;
}

int midSquareMethod(int key, int size) {
    long long square = (long long)key * key;
    int digits = 0;
    long long temp = square;
    
    // Count digits in square
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    // Extract middle digits
    int mid_digits = digits / 2;
    if (mid_digits < 2) mid_digits = 2;
    
    temp = square;
    for (int i = 0; i < (digits - mid_digits) / 2; i++) {
        temp /= 10;
    }
    
    int result = temp % (int)pow(10, mid_digits);
    return result % size;
}

int foldingMethod(int key, int size) {
    int sum = 0;
    int temp = key;
    
    // Simple folding - sum digits in groups
    while (temp > 0) {
        sum += temp % 1000; // Take 3 digits at a time
        temp /= 1000;
    }
    
    return sum % size;
}

int multiplicationMethod(int key, int size) {
    const double A = 0.6180339887; // Golden ratio - 1
    double val = key * A;
    val = val - floor(val); // Get fractional part
    return (int)(val * size);
}

int universalHashing(int key, int size) {
    // Simple universal hashing using randomization
    static int a = 0, b = 0;
    if (a == 0) {
        srand(time(NULL));
        a = rand() % size + 1;
        b = rand() % size;
    }
    return ((a * key + b) % PRIME) % size;
}


// Chaining Implementation
struct ChainingHashTable* createChainingHashTable(int size) {
    struct ChainingHashTable* ht = (struct ChainingHashTable*)malloc(sizeof(struct ChainingHashTable));
    ht->size = size;
    ht->table = (struct Node**)malloc(size * sizeof(struct Node*));
    
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    
    return ht;
}

void freeChainingHashTable(struct ChainingHashTable* ht) {
    if (ht) {
        for (int i = 0; i < ht->size; i++) {
            struct Node* current = ht->table[i];
            while (current) {
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(ht->table);
        free(ht);
    }
}

int insertChaining(struct ChainingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    
    return 1; // Insertion successful
}

int searchChaining(struct ChainingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    struct Node* current = ht->table[index];
    
    while (current) {
        if (current->data == key) {
            return index; // Key found
        }
        current = current->next;
    }
    
    return -1; // Key not found
}

int deleteChaining(struct ChainingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    struct Node* current = ht->table[index];
    struct Node* prev = NULL;
    
    while (current) {
        if (current->data == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht->table[index] = current->next;
            }
            free(current);
            return 1; // Deletion successful
        }
        prev = current;
        current = current->next;
    }
    
    return 0; // Key not found
}

void printChainingHashTable(struct ChainingHashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("Index %d: ", i);
        struct Node* current = ht->table[i];
        if (current == NULL) {
            printf("Empty");
        } else {
            while (current) {
                printf("%d", current->data);
                current = current->next;
                if (current) printf(" -> ");
            }
        }
        printf("\n");
    }
}

// Open Addressing Implementation
struct OpenAddressingHashTable* createOpenAddressingHashTable(int size) {
    struct OpenAddressingHashTable* ht = (struct OpenAddressingHashTable*)malloc(sizeof(struct OpenAddressingHashTable));
    ht->size = size;
    ht->table = (int*)malloc(size * sizeof(int));
    ht->deleted = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        ht->table[i] = -1; // -1 indicates empty slot
        ht->deleted[i] = 0; // 0 indicates not deleted
    }
    
    return ht;
}

void freeOpenAddressingHashTable(struct OpenAddressingHashTable* ht) {
    if (ht) {
        free(ht->table);
        free(ht->deleted);
        free(ht);
    }
}

// Linear Probing Implementation
int insertLinearProbing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    
    while (ht->table[index] != -1 && !ht->deleted[index]) {
        if (ht->table[index] == key) {
            return 0; // Key already exists
        }
        index = (index + 1) % ht->size;
        if (index == originalIndex) {
            return 0; // Table is full
        }
    }
    
    ht->table[index] = key;
    ht->deleted[index] = 0;
    return 1; // Insertion successful
}

int searchLinearProbing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    
    while (ht->table[index] != -1 || ht->deleted[index]) {
        if (ht->table[index] == key && !ht->deleted[index]) {
            return index; // Key found
        }
        index = (index + 1) % ht->size;
        if (index == originalIndex) {
            break; // Table is full, key not found
        }
    }
    
    return -1; // Key not found
}

int deleteLinearProbing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    
    while (ht->table[index] != -1 || ht->deleted[index]) {
        if (ht->table[index] == key && !ht->deleted[index]) {
            ht->deleted[index] = 1; // Mark as deleted
            return 1; // Deletion successful
        }
        index = (index + 1) % ht->size;
        if (index == originalIndex) {
            break; // Table is full, key not found
        }
    }
    
    return 0; // Key not found
}

void printLinearProbingHashTable(struct OpenAddressingHashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != -1 && !ht->deleted[i]) {
            printf("Index %d: %d\n", i, ht->table[i]);
        } else if (ht->deleted[i]) {
            printf("Index %d: Deleted\n", i);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

// Quadratic Probing Implementation
int insertQuadraticProbing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index] != -1 && !ht->deleted[index]) {
        if (ht->table[index] == key) {
            return 0; // Key already exists
        }
        i++;
        index = (originalIndex + i * i) % ht->size;
        if (i >= ht->size) {
            return 0; // Table is full
        }
    }
    
    ht->table[index] = key;
    ht->deleted[index] = 0;
    return 1; // Insertion successful
}

int searchQuadraticProbing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index] != -1 || ht->deleted[index]) {
        if (ht->table[index] == key && !ht->deleted[index]) {
            return index; // Key found
        }
        i++;
        index = (originalIndex + i * i) % ht->size;
        if (i >= ht->size || index == originalIndex) {
            return -1; // Key not found or table full
        }
    }
    
    return -1; // Key not found
}

int deleteQuadraticProbing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index] != -1 || ht->deleted[index]) {
        if (ht->table[index] == key && !ht->deleted[index]) {
            ht->deleted[index] = 1; // Mark as deleted
            return 1; // Deletion successful
        }
        i++;
        index = (originalIndex + i * i) % ht->size;
        if (i >= ht->size || index == originalIndex) {
            return 0; // Key not found or table full
        }
    }
    
    return 0; // Key not found
}

void printQuadraticProbingHashTable(struct OpenAddressingHashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != -1 && !ht->deleted[i]) {
            printf("Index %d: %d\n", i, ht->table[i]);
        } else if (ht->deleted[i]) {
            printf("Index %d: Deleted\n", i);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

// Double Hashing Implementation
int doubleHashFunction(int key, int size) {
    return PRIME - (key % PRIME);
}

int insertDoubleHashing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index] != -1 && !ht->deleted[index]) {
        if (ht->table[index] == key) {
            return 0; // Key already exists
        }
        i++;
        index = (originalIndex + i * doubleHashFunction(key, ht->size)) % ht->size;
        if (i >= ht->size) {
            return 0; // Table is full
        }
    }
    
    ht->table[index] = key;
    ht->deleted[index] = 0;
    return 1; // Insertion successful
}

int searchDoubleHashing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index] != -1 || ht->deleted[index]) {
        if (ht->table[index] == key && !ht->deleted[index]) {
            return index; // Key found
        }
        i++;
        index = (originalIndex + i * doubleHashFunction(key, ht->size)) % ht->size;
        if (i >= ht->size || index == originalIndex) {
            return -1; // Key not found or table full
        }
    }
    
    return -1; // Key not found
}

int deleteDoubleHashing(struct OpenAddressingHashTable* ht, int key) {
    int index = divisionMethod(key, ht->size);
    int originalIndex = index;
    int i = 0;
    
    while (ht->table[index] != -1 || ht->deleted[index]) {
        if (ht->table[index] == key && !ht->deleted[index]) {
            ht->deleted[index] = 1; // Mark as deleted
            return 1; // Deletion successful
        }
        i++;
        index = (originalIndex + i * doubleHashFunction(key, ht->size)) % ht->size;
        if (i >= ht->size || index == originalIndex) {
            return 0; // Key not found or table full
        }
    }
    
    return 0; // Key not found
}

void printDoubleHashingHashTable(struct OpenAddressingHashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != -1 && !ht->deleted[i]) {
            printf("Index %d: %d\n", i, ht->table[i]);
        } else if (ht->deleted[i]) {
            printf("Index %d: Deleted\n", i);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

// Main function with user interface
int main() {
    int choice, subChoice, key, result;
    struct ChainingHashTable* chainingHT = createChainingHashTable(TABLE_SIZE);
    struct OpenAddressingHashTable* linearHT = createOpenAddressingHashTable(TABLE_SIZE);
    struct OpenAddressingHashTable* quadraticHT = createOpenAddressingHashTable(TABLE_SIZE);
    struct OpenAddressingHashTable* doubleHT = createOpenAddressingHashTable(TABLE_SIZE);
    
    do {
        printf("\n===== HASH TABLE IMPLEMENTATION =====\n");
        printf("1. Hash Functions\n");
        printf("2. Collision Resolution Methods\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\n===== HASH FUNCTIONS =====\n");
                printf("1. Division Method\n");
                printf("2. Mid-Square Method\n");
                printf("3. Folding Method\n");
                printf("4. Multiplication Method\n");
                printf("5. Universal Hashing\n");
                printf("Enter your choice: ");
                scanf("%d", &subChoice);
                
                printf("Enter key: ");
                scanf("%d", &key);
                
                switch (subChoice) {
                    case 1:
                        printf("Hash Index: %d\n", divisionMethod(key, TABLE_SIZE));
                        break;
                    case 2:
                        printf("Hash Index: %d\n", midSquareMethod(key, TABLE_SIZE));
                        break;
                    case 3:
                        printf("Hash Index: %d\n", foldingMethod(key, TABLE_SIZE));
                        break;
                    case 4:
                        printf("Hash Index: %d\n", multiplicationMethod(key, TABLE_SIZE));
                        break;
                    case 5:
                        printf("Hash Index: %d\n", universalHashing(key, TABLE_SIZE));
                        break;
                    default:
                        printf("Invalid choice!\n");
                }
                break;

            case 2:
                printf("\n===== COLLISION RESOLUTION METHODS =====\n");
                printf("1. Chaining\n");
                printf("2. Linear Probing\n");
                printf("3. Quadratic Probing\n");
                printf("4. Double Hashing\n");
                printf("Enter your choice: ");
                scanf("%d", &subChoice);
                
                switch (subChoice) {
                    case 1:
                        do {
                            printf("\n===== CHAINING =====\n");
                            printf("1. Insert\n");
                            printf("2. Search\n");
                            printf("3. Delete\n");
                            printf("4. Print Table\n");
                            printf("5. Back to Main Menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &subChoice);
                            
                            switch (subChoice) {
                                case 1:
                                    printf("Enter key to insert: ");
                                    scanf("%d", &key);
                                    insertChaining(chainingHT, key);
                                    break;
                                case 2:
                                    printf("Enter key to search: ");
                                    scanf("%d", &key);
                                    result = searchChaining(chainingHT, key);
                                    if (result != -1) {
                                        printf("Key %d found at index %d\n", key, result);
                                    } else {
                                        printf("Key %d not found\n", key);
                                    }
                                    break;
                                case 3:
                                    printf("Enter key to delete: ");
                                    scanf("%d", &key);
                                    result = deleteChaining(chainingHT, key);
                                    if (result) {
                                        printf("Key %d deleted successfully\n", key);
                                    } else {
                                        printf("Key %d not found\n", key);
                                    }
                                    break;
                                case 4:
                                    printf("Chaining Hash Table:\n");
                                    printChainingHashTable(chainingHT);
                                    break;
                                case 5:
                                    break;
                                default:
                                    printf("Invalid choice!\n");
                            }
                        } while (subChoice != 5);
                        break;
                    case 2:
                    do {
                        printf("\n===== LINEAR PROBING =====\n");
                        printf("1. Insert\n");
                        printf("2. Search\n");
                        printf("3. Delete\n");
                        printf("4. Print Table\n");
                        printf("5. Back to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &subChoice);
                        
                        switch (subChoice) {
                            case 1:
                                printf("Enter key to insert: ");
                                scanf("%d", &key);
                                result = insertLinearProbing(linearHT, key);
                                if (result) {
                                    printf("Key %d inserted successfully\n", key);
                                } else {
                                    printf("Insertion failed, table might be full or key already exists\n");
                                }
                                break;
                            case 2:
                                printf("Enter key to search: ");
                                scanf("%d", &key);
                                result = searchLinearProbing(linearHT, key);
                                if (result != -1) {
                                    printf("Key %d found at index %d\n", key, result);
                                } else {
                                    printf("Key %d not found\n", key);
                                }
                                break;
                            case 3:
                                printf("Enter key to delete: ");
                                scanf("%d", &key);
                                result = deleteLinearProbing(linearHT, key);
                                if (result) {
                                    printf("Key %d deleted successfully\n", key);
                                } else {
                                    printf("Key %d not found\n", key);
                                }
                                break;
                            case 4:
                                printf("Linear Probing Hash Table:\n");
                                printLinearProbingHashTable(linearHT);
                                break;
                            case 5:
                                break;
                            default:
                                printf("Invalid choice!\n");
                        }
                    } while (subChoice != 5);
                    break;
                    case 3:
                        do {
                            printf("\n===== QUADRATIC PROBING =====\n");
                            printf("1. Insert\n");
                            printf("2. Search\n");
                            printf("3. Delete\n");
                            printf("4. Print Table\n");
                            printf("5. Back to Main Menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &subChoice);
                            
                            switch (subChoice) {
                                case 1:
                                    printf("Enter key to insert: ");
                                    scanf("%d", &key);
                                    result = insertQuadraticProbing(quadraticHT, key);
                                    if (result) {
                                        printf("Key %d inserted successfully\n", key);
                                    } else {
                                        printf("Insertion failed, table might be full or key already exists\n");
                                    }
                                    break;
                                case 2:
                                    printf("Enter key to search: ");
                                    scanf("%d", &key);
                                    result = searchQuadraticProbing(quadraticHT, key);
                                    if (result != -1) {
                                        printf("Key %d found at index %d\n", key, result);
                                    } else {
                                        printf("Key %d not found\n", key);
                                    }
                                    break;
                                case 3:
                                    printf("Enter key to delete: ");
                                    scanf("%d", &key);
                                    result = deleteQuadraticProbing(quadraticHT, key);
                                    if (result) {
                                        printf("Key %d deleted successfully\n", key);
                                    } else {
                                        printf("Key %d not found\n", key);
                                    }
                                    break;
                                case 4:
                                    printf("Quadratic Probing Hash Table:\n");
                                    printQuadraticProbingHashTable(quadraticHT);
                                    break;
                                case 5:
                                    break;
                                default:
                                    printf("Invalid choice!\n");
                            }
                        } while (subChoice != 5);
                        break;
                    case 4:
                        do {
                            printf("\n===== DOUBLE HASHING =====\n");
                            printf("1. Insert\n");
                            printf("2. Search\n");
                            printf("3. Delete\n");
                            printf("4. Print Table\n");
                            printf("5. Back to Main Menu\n");
                            printf("Enter your choice: ");
                            scanf("%d", &subChoice);
                            
                            switch (subChoice) {
                                case 1:
                                    printf("Enter key to insert: ");
                                    scanf("%d", &key);
                                    result = insertDoubleHashing(doubleHT, key);
                                    if (result) {
                                        printf("Key %d inserted successfully\n", key);
                                    } else {
                                        printf("Insertion failed, table might be full or key already exists\n");
                                    }
                                    break;
                                case 2:
                                    printf("Enter key to search: ");
                                    scanf("%d", &key);
                                    result = searchDoubleHashing(doubleHT, key);
                                    if (result != -1) {
                                        printf("Key %d found at index %d\n", key, result);
                                    } else {
                                        printf("Key %d not found\n", key);
                                    }
                                    break;
                                case 3:
                                    printf("Enter key to delete: ");
                                    scanf("%d", &key);
                                    result = deleteDoubleHashing(doubleHT, key);
                                    if (result) {
                                        printf("Key %d deleted successfully\n", key);
                                    } else {
                                        printf("Key %d not found\n", key);
                                    }
                                    break;
                                case 4:
                                    printf("Double Hashing Hash Table:\n");
                                    printDoubleHashingHashTable(doubleHT);
                                    break;
                                case 5:
                                    break;
                                default:
                                    printf("Invalid choice!\n");
                            }
                        } while (subChoice != 5);
                        break;
                    default:
                        printf("Invalid choice!\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;  
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
    // Free allocated memory
    freeChainingHashTable(chainingHT);
    freeOpenAddressingHashTable(linearHT);
    freeOpenAddressingHashTable(quadraticHT);
    freeOpenAddressingHashTable(doubleHT);
    return 0;
}
        
        