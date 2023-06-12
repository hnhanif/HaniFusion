#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities/animation.h"
#include "products/todo_list.h"
#include "products/version_control.h"
#include "products/restaurant.h"
#include "products/personal_finance.h"
#include "products/movie_database.h"
#include "products/course_registration.h"
#include "blog/about_us.h"

void displayMenu()
{
    printf("\n=================================\n");
    printf("       <<< FUSION MENU >>>      \n");
    printf("=================================\n");
    printf("1.  Todo List\n");
    printf("2.  Document Version Control\n");
    printf("3.  Restaurant Order Management\n");
    printf("4.  Personal Finanace\n");
    printf("5.  Movie DataBase\n");
    printf("6.  Course Registration\n");
    printf("7.  About Us\n");
    printf("0.  Exit\n");
    printf("=================================\n");
}

int main()
{
    animation();
    int choice;

    do
    {
        displayMenu();
        printf("\n>> Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            todoList();
            break;
        case 2:
            docVersionControl();
            break;
        case 3:
            restaurantOrder();
            break;
        case 4:
            personalFinance();
            break;
        case 5:
            movieDatabase();
            break;
        case 6:
            courseRegistration();
            break;
        case 7:
            aboutUs();
            break;
        case 0:
            printf("\n=== Thank You So Much! for spending time on HaniFusion. Stay with us :) ===\n\n");
            break;
        default:
            printf("\n");
            printf("\n=== Invalid choice! Please try again. ===\n\n");
            break;
        }
    } while (choice != 0);

    return 0;
}