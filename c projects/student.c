// c project for student grading system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 10000
#define NAME_LENGTH 50
#define SUBJECTS 5
typedef struct {
    char name[NAME_LENGTH];
    int roll_no;
    float marks[SUBJECTS];
    float average;
} Student;
int main()
{
    Student students[MAX_STUDENTS];
    int student_count = 0, i, j;
    char choice;
    printf("Welcome to the Student Grading System\n");
    printf("Do you want to enter another student? (y/n): ");
    scanf(" %c", &choice);
    while (choice == 'y' || choice == 'Y') {
        if (student_count >= MAX_STUDENTS) {
            printf("Maximum number of students reached.\n");
            break;
        }
        // Clear input buffer before fgets
        while (getchar() != '\n');

        printf("Enter student name: ");
        fgets(students[student_count].name, NAME_LENGTH, stdin);
        // Remove trailing newline from name
        size_t len = strlen(students[student_count].name);
        if (len > 0 && students[student_count].name[len - 1] == '\n') {
            students[student_count].name[len - 1] = '\0';
        }
        printf("Enter roll number: ");
        scanf("%d", &students[student_count].roll_no);

        for (j = 0; j < SUBJECTS; j++) {
            printf("Enter marks for subject %d: ", j + 1);
            scanf("%f", &students[student_count].marks[j]);
        }

        // Calculate average
        float total = 0;
        for (j = 0; j < SUBJECTS; j++) {
            total += students[student_count].marks[j];
        }
        students[student_count].average = total / SUBJECTS;

        student_count++;

        // Prompt for next student
        printf("Do you want to enter another student? (y/n): ");
        scanf(" %c", &choice);
    }

    // Display all students
    printf("\nStudent Records:\n");
    for (i = 0; i < student_count; i++) {
        printf("Name: %s, Roll No: %d, Average Marks: %.2f\n",
               students[i].name, students[i].roll_no, students[i].average);
    }

    return 0;
}
