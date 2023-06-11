#define MAX_COURSES 100
#define MAX_STUDENTS 100

struct Student
{
    char name[100];
};

struct Course
{
    char code[10];
    char name[100];
    int totalSeats;
    int bookedSeats;
    struct Student *students[MAX_STUDENTS];
};

struct CourseCatalog
{
    struct Course *courses[MAX_COURSES];
    int numCourses;
};

struct Course *createCourse(const char *code, const char *name, int totalSeats)
{
    struct Course *newCourse = (struct Course *)malloc(sizeof(struct Course));
    strcpy(newCourse->code, code);
    strcpy(newCourse->name, name);
    newCourse->totalSeats = totalSeats;
    newCourse->bookedSeats = 0;
    return newCourse;
}

void addStudentToCourse(struct Course *course, struct Student *student)
{
    course->students[course->bookedSeats] = student;
    course->bookedSeats++;
}

struct Student *createStudent(const char *name)
{
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    return newStudent;
}

void displayCourseCatalog(struct CourseCatalog *catalog)
{
    if (catalog->numCourses == 0)
    {
        printf("\n=== Sorry, no courses are available. ===\n\n");
        return;
    }

    printf("\n==========================================================================================================\n");
    printf("\n\t\t\t\t\tCourse Catalog.\n");
    printf("==========================================================================================================\n");
    printf("%-15s %-30s %-15s %-15s %-15s\n", "Course Code", "Course Name", "Total Seats", "Booked Seats", "Available Seats");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < catalog->numCourses; i++)
    {
        struct Course *course = catalog->courses[i];
        printf("%-15s %-30s %-15d %-15d %-15d\n", course->code, course->name, course->totalSeats, course->bookedSeats, course->totalSeats - course->bookedSeats);

        if (course->bookedSeats > 0)
        {
            printf("\nRegistered Students:\n\n");
            printf("%-30s %-15s\n", "Student Name", "Seat Number");
            printf("---------------------------------------------------------------------------------------------------------\n");

            for (int j = 0; j < course->bookedSeats; j++)
            {
                printf("%-30s %-15d\n", course->students[j]->name, j + 1);
            }
        }

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }

    printf("==========================================================================================================\n");
}

void courseRegistration()
{

    printf("\n------------------------------------------------------------------------------\n");
    printf("-                 S  T  U  D  E  N  T    C  O  U  R  S  E                    -\n");
    printf("-                    R  E  G  I  S  T  R  A  T  I  O  N                      -\n");
    printf("------------------------------------------------------------------------------\n");

    struct CourseCatalog catalog;
    catalog.numCourses = 0;

    int choice;
    char code[10];
    char name[100];
    int totalSeats;
    char studentName[100];

    do
    {
        printf("\n========================================\n");
        printf("    <<< COURSE REGISTRATION MENU >>>    \n");
        printf("========================================\n");
        printf("1. Display Course Catalog\n");
        printf("2. Register for a Course\n");
        printf("3. Create a Course\n");
        printf("4. Exit\n");
        printf(">> Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n");
            displayCourseCatalog(&catalog);
            break;
        case 2:
            if (catalog.numCourses == 0)
            {
                printf("\n=== No courses available. ===\n");
                printf("You cannot register as there are no courses.\n\n");
                break;
            }

            printf("\n> Enter the course code you wish to register for: ");
            scanf("%s", code);

            struct Course *selectedCourse = NULL;
            for (int i = 0; i < catalog.numCourses; i++)
            {
                if (strcmp(code, catalog.courses[i]->code) == 0)
                {
                    selectedCourse = catalog.courses[i];
                    break;
                }
            }

            if (selectedCourse == NULL)
            {
                printf("\n=== Oops! The course you entered could not be found. Please double-check the course code and try again. ===\n");

                break;
            }

            printf("> Enter your name: ");
            scanf("%s", studentName);

            if (selectedCourse->bookedSeats >= selectedCourse->totalSeats)
            {
                printf("\n=== Sorry, the course is fully booked. Registration failed. ===\n");
            }
            else
            {
                struct Student *newStudent = createStudent(studentName);
                addStudentToCourse(selectedCourse, newStudent);
                printf("\n======================================================\n");
                printf("               Registration Successful!\n");
                printf("======================================================\n");
                printf("| %-15s | %-30s   |\n", "Course Code", "Course Name");
                printf("|-----------------|----------------------------------|\n");
                printf("| %-15s | %-30s   |\n", selectedCourse->code, selectedCourse->name);
                printf("======================================================\n");
            }

            break;

        case 3:
            printf("\n> Enter the course code: ");
            scanf("%s", code);
            printf("> Enter the course name: ");
            scanf(" %[^\n]s", name);
            printf("> Enter the total number of seats: ");
            scanf("%d", &totalSeats);

            struct Course *newCourse = createCourse(code, name, totalSeats);
            catalog.courses[catalog.numCourses++] = newCourse;
            printf("\n=== Course created successfully. ===\n\n");
            break;
        case 4:
            printf("\n=== Back To HaniFusion... ===\n\n");
            break;
        default:
            printf("\n=== Invalid choice. Please try again. ===\n\n");
        }
    } while (choice != 4);
}
