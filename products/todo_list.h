#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void addTodo(char todos[][100], int count, const char todo[]);
void displayTodos(const char todos[][100], int count);
void removeTodo(char todos[][100], int count, int index);
int isEmpty(int count);

void addTodo(char todos[][100], int count, const char todo[])
{
    if (count >= MAX_SIZE)
    {
        printf("\n--------------------------------------------------\n");
        printf("ERROR: Todo list is full. Cannot add more todos.\n");
        printf("--------------------------------------------------\n");

        return;
    }

    strcpy(todos[count], todo);
    printf("\n-----------------------------------------------\n");
    printf("SUCCESS: Todo '%s' added successfully.\n", todo);
    printf("-----------------------------------------------\n");
}

void displayTodos(const char todos[][100], int count)
{
    if (count == 0)
    {
        printf("\n-------------------\n");
        printf("No todos found. :(\n");
        printf("-------------------\n");
        return;
    }

    printf("+-------+-------------------------------------------------+\n");
    printf("|  ALL  |                       Task                      |\n");
    printf("+-------+-------------------------------------------------+\n");
    for (int i = 0; i < count; i++)
    {
        printf("|  %2d   |  %-45s  |\n", i + 1, todos[i]);
    }
    printf("+-------+-------------------------------------------------+\n");
}

void removeTodo(char todos[][100], int count, int index)
{
    if (isEmpty(count))
    {
        printf("\n-----------------------------------\n");
        printf("Todo list is empty. Nothing to remove.\n");
        printf("\n-----------------------------------\n");
        return;
    }

    if (index < 1 || index > count)
    {
        printf("\n------------------------------------\n");
        printf("Invalid index. Removing the last todo.\n");
        printf("\n------------------------------------\n");
        index = count;
    }

    index--; // Adjust index to zero-based array indexing
    char removedTodo[100];
    strcpy(removedTodo, todos[index]);
    memmove(todos[index], todos[index + 1], (count - index - 1) * sizeof(todos[0]));
    printf("\n----------------------------------\n");
    printf("Todo '%s' removed successfully.\n", removedTodo);
    printf("\n----------------------------------\n");
}

int isEmpty(int count)
{
    return count == 0;
}

void todoList()
{
    char todos[MAX_SIZE][100];
    int count = 0;
    int choice;

    printf("\n-----------------------------------------------------------\n");
    printf("-                    T  O  D  O    L  I  S  T                -\n");
    printf("-----------------------------------------------------------\n");

    do
    {
        printf("\n=================================\n");
        printf("       <<< TODO MENU >>>      \n");
        printf("=================================\n");
        printf("1.  Add Todo\n");
        printf("2.  Display Todos\n");
        printf("3.  Remove Todo\n");
        printf("4.  Reset Todo list\n");
        printf("5.  Quit\n");
        printf("=================================\n");
        printf("Enter your choice: ");

        while (scanf("%d", &choice) != 1)
        {
            printf("-> Invalid choice. Please enter an integer: ");
            scanf("%*s"); // Clear the input buffer
        }

        switch (choice)
        {
        case 1:
        {
            char todo[100];
            printf("- Enter the todo: ");
            scanf(" %[^\n]", todo);
            addTodo(todos, count, todo);
            count++;
            break;
        }
        case 2:
            displayTodos(todos, count);
            break;
        case 3:
        {
            if (isEmpty(count))
            {
                printf("\n------------------------------------\n");
                printf("Todo list is empty. Nothing to remove.\n");
                printf("------------------------------------\n");
                break;
            }

            int index;
            printf("* Enter the index of the todo to remove: ");
            while (scanf("%d", &index) != 1)
            {
                printf("\n-> Invalid index. Please enter an integer: ");
                scanf("%*s"); // Clear the input buffer
            }

            if (index <= 0)
            {
                printf("\n>>>>>> Index is too low then range. Removing the first todo. <<<<<<\n");
                index = 1;
            }
            else if (index > count)
            {
                printf("\n>>>>>> Index is too high then range. Removing the last todo. <<<<<<\n");
                index = count;
            }

            removeTodo(todos, count, index);
            count--;
            break;
        }
        case 4:
        {
            if (isEmpty(count))
            {
                printf("\n-------------------------------------------\n");
                printf("Todo list is already empty. No need to reset.\n");
                printf("-------------------------------------------\n");
                break;
            }

            printf("\n-> Are you sure you want to reset the Todo list? (Y/N): ");

            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 'Y' || confirm == 'y')
            {
                count = 0;
                printf("\n-------------------------\n");
                printf("Todo list has been reset.\n");
                printf("-------------------------\n");
            }
            else
            {
                printf("\n-------------------------\n");
                printf("Reset operation canceled.\n");
                printf("-------------------------\n");
            }
            break;
        }
        case 5:
            printf("\n.......................\n");
            printf("..Back To HaniFusion...\n");
            printf(".......................\n");

            break;
        default:
            printf("\n--------------------------------\n");
            printf("Invalid choice. Please try again.\n");
            printf("--------------------------------\n");

            break;
        }
    } while (choice != 5);

    printf("\n");
    printf("    Thank you for using the Todo List.    \n");
    printf("\n");
}
