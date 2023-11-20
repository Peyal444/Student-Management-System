#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

// Structure to store student information
typedef struct Student
{
    char name[50];
    int id;
    char section[10];
    char department[50];
    struct Student *next;
} Student;

// Structure to store course result
typedef struct Result
{
    float dataStructure;
    float algorithm;
    float numericalMethods;
} Result;

// Function prototypes
void loadingScreen();
void adminSection();
void studentSection();
void addStudent();
void deleteStudent();
void viewAllStudents();
void addResult();
void viewResult();
void viewSelfInfo();
void saveStudentToFile(Student *student);
void saveResultToFile(Result result, int studentId);
void printLine();

// Global variables
Student *studentList = NULL;

int main()
{
    int choice;

    loadingScreen();

    do
    {
        /* Display the student menu */
        printf("\n\n\t\t\t----- MAIN MENU -----\n\n");

        /* Display menu options */
        printf("\t\t1. Admin Section\n\n");
        printf("\t\t2. Student Section\n\n");
        printf("\t\t3. About Student Management System\n\n");
        printf("\t\t4. Exit\n\n");

        /* Prompt the user for their choice */
        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            adminSection();
            break;
        case 2:

            studentSection();
            break;
        
        case 3:
            system("cls");
            printf("\n\n\n\n\n\t\t\t\tThis project is developed by\n\n\t\t\t\t1. Mst. Asrufa Anne\n\t\t\t\t2. Chayan Halder\n\t\t\t\t3. Peyal Sarker");
            sleep(2);
            system("cls");
            break;
        case 4:
            system("cls");
            printf("\n\t\tThank you for using the Student Management System!\n");
            sleep(2);
            exit(0);
        default:

            printf("\n\t\tInvalid choice! Please try again.\n");
        }
    } while (1);

    return 0;
}

void loadingScreen()
{
    system("cls");
    int progress = 0;
    printf("\n\n\t\t\tStudent Management System\n\n");

    printf("\t\t\tLoading...");

    for (progress = 0; progress <= 100; progress++)
    {
        printf("\r\t\t\tLoading: [%d%%]", progress);
        fflush(stdout);
        Sleep(20);
    }

    printf("\n\n\t\t\tLoading complete!");
    sleep(2);
    system("cls");
}

void adminSection()
{
    system("cls");
    char username[20];
    char password[20];

    printf("\n\n\t\t\t----- ADMIN SECTION -----\n\n");
    printf("\t\tEnter username: ");
    scanf("%s", username);
    printf("\t\tEnter password: ");
    scanf("%s", password);

    // Check if username and password are correct
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0)
    {
        system("cls");
        int choice;

        do
        {

            /* Display the admin menu */
            printf("\n\n\t\t\t----- ADMIN MENU -----\n\n");

            /* Display menu options */
            printf("\t\t1. Add Student\n\n");
            printf("\t\t2. Delete Student\n\n");
            printf("\t\t3. View All Students\n\n");
            printf("\t\t4. Add Result\n\n");
            printf("\t\t5. Back to Main Menu\n\n");

            /* Prompt the user for their choice */
            printf("\n\n\t\tEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:

                addStudent();
                break;
            case 2:

                deleteStudent();
                break;
            case 3:

                viewAllStudents();
                break;
            case 4:

                addResult();
                break;
            case 5:
                system("cls");
                return;
            default:

                printf("\n\t\tInvalid choice! Please try again.\n");
            }
        } while (1);
    }
    else
    {
        printf("\n\t\tInvalid username or password! Access denied.\n");
    }
}

void studentSection()
{
    system("cls");

    int choice;

    do
    {
        /* Display the student menu */
        printf("\n\n\t\t\t----- STUDENT MENU -----\n\n");

        /* Display menu options */
        printf("\t\t1. View Result\n\n");
        printf("\t\t2. View Self Info\n\n");
        printf("\t\t3. Back to Main Menu\n\n");

        /* Prompt the user for their choice */
        printf("\n\n\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            viewResult();
            break;
        case 2:

            viewSelfInfo();
            break;
        case 3:
            system("cls");
            return;
        default:

            printf("\n\t\tInvalid choice! Please try again.\n");
        }
    } while (1);
}

void addStudent()
{
    system("cls");
    Student *newStudent = (Student *)malloc(sizeof(Student));

    printf("\n\n\t\t\t----- ADD STUDENT -----\n\n");
    printf("\t\tEnter student name: ");
    scanf(" %[^\n]s", newStudent->name);
    printf("\t\tEnter student ID: ");
    scanf("%d", &(newStudent->id));
    printf("\t\tEnter student section: ");
    scanf(" %[^\n]s", newStudent->section);
    printf("\t\tEnter student department: ");
    scanf(" %[^\n]s", newStudent->department);

    newStudent->next = NULL;

    if (studentList == NULL)
    {
        studentList = newStudent;
    }
    else
    {
        Student *current = studentList;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newStudent;
    }

    saveStudentToFile(newStudent);

    printf("\n\t\tStudent added successfully!\n");
    sleep(2);
    system("cls");
}

void deleteStudent()
{
    system("cls");
    int studentId;
    char confirm;

    printf("\n\n\t\t\t----- DELETE STUDENT -----\n\n");
    printf("\t\tEnter student ID to delete: ");
    scanf("%d", &studentId);

    Student *current = studentList;
    Student *previous = NULL;

    while (current != NULL && current->id != studentId)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("\n\t\tStudent not found!\n");
        return;
    }

    printf("\n\t\tAre you sure you want to delete this student? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y')
    {
        if (previous == NULL)
        {
            studentList = current->next;
        }
        else
        {
            previous->next = current->next;
        }

        FILE *file = fopen("students.txt", "w");

 
        Student *temp = studentList;
        while (temp != NULL)
        {
            fprintf(file, "%s,%d,%s,%s\n", temp->name, temp->id, temp->section, temp->department);
            temp = temp->next;
        }

        fclose(file);

        free(current);
        printf("\n\t\tStudent deleted successfully!\n");
    }
    else
    {
        printf("\n\t\tDeletion canceled.\n");
    }

    sleep(2);
    system("cls");
}

void viewAllStudents()
{
    system("cls");
    printf("\n\n\t\t\t----- ALL STUDENTS -----\n\n");

    FILE *file = fopen("students.txt", "r");
    if (file == NULL)
    {
        printf("\n\t\tNo students found!\n");
        return;
    }

    Student *current = studentList;

    // Clear the existing linked list
    while (current != NULL)
    {
        Student *temp = current;
        current = current->next;
        free(temp);
    }
    studentList = NULL;

    // Read student information from the file and populate the linked list
    while (1)
    {
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if (fscanf(file, "%[^,],%d,%[^,],%[^\n]\n", newStudent->name, &newStudent->id, newStudent->section, newStudent->department) == 4)
        {
            newStudent->next = NULL;

            if (studentList == NULL)
            {
                studentList = newStudent;
            }
            else
            {
                current = studentList;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newStudent;
            }
        }
        else
        {
            free(newStudent);
            break;
        }
    }

    fclose(file);

    // Display the student information in a table
    printf("\n\t\t+-----------------+-----------------+-----------------+-----------------+\n");
    printf("\t\t|      Name       |        ID       |     Section     |    Department   |\n");
    printf("\t\t+-----------------+-----------------+-----------------+-----------------+\n");

    current = studentList;
    while (current != NULL)
    {
        printf("\t\t| %-15s | %-15d | %-15s | %-15s |\n", current->name, current->id, current->section, current->department);
        current = current->next;
    }

    printf("\t\t+-----------------+-----------------+-----------------+-----------------+\n\n\n");
    printf("Press any key to continue...\n");
    system("pause");
    getchar();
    system("cls");
}

void addResult()
{
    system("cls");
    int studentId;
    Result result;

    printf("\n\n\t\t\t----- ADD RESULT -----\n\n");
    printf("\t\tEnter student ID: ");
    scanf("%d", &studentId);
    printf("\t\tEnter Data Structure result: ");
    scanf("%f", &result.dataStructure);
    printf("\t\tEnter Algorithm result: ");
    scanf("%f", &result.algorithm);
    printf("\t\tEnter Numerical Methods result: ");
    scanf("%f", &result.numericalMethods);

    saveResultToFile(result, studentId);

    printf("\n\t\tResult added successfully!\n");
    sleep(2);
    system("cls");
}

void viewResult()
{
    system("cls");
    int studentId;

    printf("\n\n\t\t\t----- VIEW RESULT -----\n\n");
    printf("\t\tEnter student ID: ");
    scanf("%d", &studentId);

    FILE *file = fopen("results.txt", "r");
    if (file == NULL)
    {
        printf("\n\t\tNo results found!\n");
        return;
    }

    int found = 0;
    float dataStructure, algorithm, numericalMethods;
    int id;

    printf("\n\t\t+-----------------+-----------------+-----------------+------------------+\n");
    printf("\t\t|   Student ID    | Data Structure  |    Algorithm    | Numerical Methods|\n");
    printf("\t\t+-----------------+-----------------+-----------------+------------------+\n");

    while (fscanf(file, "%d,%f,%f,%f", &id, &dataStructure, &algorithm, &numericalMethods) == 4)
    {
        if (id == studentId)
        {
            found = 1;
            printf("\t\t|   %-14d|   %-14.2f|   %-14.2f|   %-15.2f|\n", id, dataStructure, algorithm, numericalMethods);
            break;
        }
    }

    printf("\t\t+-----------------+-----------------+-----------------+------------------+\n");

    fclose(file);

    if (!found)
    {
        printf("\n\t\tNo results found for student ID: %d\n", studentId);
    }

    printf("Press any key to continue...\n");
    system("pause");
    getchar();
    system("cls");
}

void viewSelfInfo()
{
    system("cls");
    int studentId;

    printf("\n\n\t\t\t----- VIEW SELF INFO -----\n\n");
    printf("\t\tEnter your student ID: ");
    scanf("%d", &studentId);

    FILE *file = fopen("students.txt", "r");
    if (file == NULL)
    {
        printf("\n\t\tNo student information found!\n");
        return;
    }

    int found = 0;
    char name[50], section[20], department[50];
    int id;

    printf("\n\t\t+-----------------+-------------------+-----------------+-----------------+\n");
    printf("\t\t|   Student ID    |       Name        |     Section     |    Department   |\n");
    printf("\t\t+-----------------+-------------------+-----------------+-----------------+\n");

    while (fscanf(file, "%[^,],%d,%[^,],%[^\n]\n", name, &id, section, department) == 4)
    {
        if (id == studentId)
        {
            found = 1;
            printf("\t\t|   %-14d|   %-16s|   %-14s|   %-14s|\n", id, name, section, department);
            break;
        }
    }

    printf("\t\t+-----------------+-------------------+-----------------+-----------------+\n");

    fclose(file);

    if (!found)
    {
        printf("\n\t\tNo information found for student ID: %d\n", studentId);
    }

    printf("Press any key to continue...\n");
    system("pause");
    getchar();
    system("cls");
}

void saveStudentToFile(Student *student)
{
    FILE *file = fopen("students.txt", "a");

    if (file != NULL)
    {
        fprintf(file, "%s,%d,%s,%s\n\n", student->name, student->id, student->section, student->department);
        fclose(file);
    }
}

void saveResultToFile(Result result, int studentId)
{
    FILE *file = fopen("results.txt", "a");

    if (file != NULL)
    {
        fprintf(file, "%d,%.2f,%.2f,%.2f\n", studentId, result.dataStructure, result.algorithm, result.numericalMethods);
        fclose(file);
    }
}

void printLine()
{
    printf("\n--------------------------------------------------\n");
}
