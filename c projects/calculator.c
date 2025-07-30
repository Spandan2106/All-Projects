// c project to create calculator
#include<stdio.h>
#include<math.h>
int sum(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 0; // Return 0 or handle error as needed
    }
    return a / b;
}
int modulus(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 0; // Return 0 or handle error as needed
    }
    return a % b;
}
int power(int base, int exp) {
    return (int)pow(base, exp);
}
int main()
{
    int a, b, choice;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    
    printf("Choose an operation:\n");
    printf("1. Sum\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Result: %d\n", sum(a, b));
            break;
        case 2:
            printf("Result: %d\n", subtract(a, b));
            break;
        case 3:
            printf("Result: %d\n", multiply(a, b));
            break;
        case 4:
            printf("Result: %d\n", divide(a, b));
            break;
        case 5:
            printf("Result: %d\n", modulus(a, b));
            break;
        case 6:
            printf("Result: %d\n", power(a, b));
            break;
        default:
            printf("Invalid choice.\n");
    }
    
    return 0;
}
