#include <stdio.h>
#include <stdlib.h> // Для использования динамического выделения памяти

// Define the "Student" structure
struct Student {
    char firstName[50];
    char lastName[50];
    int age;
    float averageGrade;
};

// Function for inputting student data
void inputStudentData(struct Student *student) {
    printf("Enter the student's first name: ");
    scanf("%s", student->firstName);

    printf("Enter the student's last name: ");
    scanf("%s", student->lastName);

    printf("Enter the student's age: ");
    scanf("%d", &student->age);

    printf("Enter the student's average grade: ");
    scanf("%f", &student->averageGrade);
}

// Function for printing student data
void printStudentData(const struct Student *student) {
    printf("\nStudent Data:\n");
    printf("First Name: %s\n", student->firstName);
    printf("Last Name: %s\n", student->lastName);
    printf("Age: %d\n", student->age);
    printf("Average Grade: %.2f\n", student->averageGrade);
}

int main() {
    // Create an array of type "Student" to store multiple students
    struct Student *students = NULL;
    int studentCount = 0; // Number of students entered
    int capacity = 1;     // Initial capacity of the array

    while (1) {
        // Dynamically allocate memory for a new student
        struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));

        // Call the function to input data for the new student
        inputStudentData(newStudent);

        // Add the new student to the array
        if (students == NULL) {
            students = newStudent;
        } else {
            // Increase the array capacity if necessary
            if (studentCount == capacity) {
                capacity *= 2;
                students = (struct Student *)realloc(students, capacity * sizeof(struct Student));
            }

            students[studentCount] = *newStudent;
        }

        studentCount++;

        printf("Do you want to enter another student (y/n)? ");
        char choice;
        scanf(" %c", &choice); // Note the space before %c to consume the newline character

        if (choice != 'y' && choice != 'Y') {
            break; // Exit the loop if the user doesn't want to enter another student
        }
    }

    // Print the list of student names and last names
    printf("\nList of Student Names:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%s %s\n", students[i].firstName, students[i].lastName);
    }


    free(students);

    return 0;
}
