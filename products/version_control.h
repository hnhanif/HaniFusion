
#define MAX_VERSION_SIZE 5

// Structure to represent a document version
typedef struct
{
    char versionNumber[100];
    char content[1000];
} DocumentVersion;

// Structure to represent the document version stack
typedef struct
{
    DocumentVersion versions[MAX_VERSION_SIZE];
    int top;
} DocumentStack;

// Function to initialize the document version stack
void initializeStack(DocumentStack *stack)
{
    stack->top = -1;
}

// Function to check if the stack is empty
int isStackEmpty(DocumentStack *stack)
{
    return stack->top == -1;
}

// Function to check if the stack is full
int isStackFull(DocumentStack *stack)
{
    return stack->top == MAX_VERSION_SIZE - 1;
}

// Function to push a new version onto the stack
void push(DocumentStack *stack, DocumentVersion version)
{
    if (isStackFull(stack))
    {
        printf("\n###Sorry, you cannot add more versions. The document version stack is full.###\n");
        return;
    }

    stack->versions[++(stack->top)] = version;
    printf("\n[+] Version %s added successfully.\n", version.versionNumber);
}

// Function to pop the most recent version from the stack
DocumentVersion pop(DocumentStack *stack)
{
    DocumentVersion emptyVersion;
    strcpy(emptyVersion.versionNumber, "-1"); // Assigned "-1" for empty version

    if (isStackEmpty(stack))
    {
        printf("\n-------------------------------------\n");
        printf("-  Warning: Stack is empty!          -\n");
        printf("-  No versions to remove.            -\n");
        printf("-------------------------------------\n");

        return emptyVersion;
    }

    // Check if there is only one version in the stack
    if (stack->top == 0)
    {

        printf("\n----------------------------------------------\n");
        printf("-  Error: Cannot revert to previous version  -\n");
        printf("-  No versions exist.                        -\n");
        printf("----------------------------------------------\n");

        return emptyVersion;
    }

    DocumentVersion revertedVersion = stack->versions[stack->top--];

    return stack->versions[stack->top]; // Return the updated top stack
}

// Function to delete a document
void deleteDocument(DocumentStack *stack)
{
    if (isStackEmpty(stack))
    {
        printf("\n-------------------------------------------------------\n");
        printf("-  Warning: Stack is empty!                             -\n");
        printf("-  No documents to delete.                              -\n");
        printf("-------------------------------------------------------\n");
        return;
    }

    printf("\n---------------------------------------\n");
    printf("-       +++ DELETE DOCUMENT +++         -\n");
    printf("---------------------------------------\n");
    printf("Are you sure you want to delete the document? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N')
    {
        printf("\n== Invalid choice. Please try again. 'y' or 'n' ==  ");
        scanf(" %c", &confirm);
    }

    if (confirm == 'y' || confirm == 'Y')
    {
        printf("\n[+] Document deleted successfully.\n");
        initializeStack(stack);
    }
    else if (confirm == 'n' || confirm == 'N')
    {
        printf("\n---------------------------------------\n");
        printf("-    >>> DELETE OPERATION CANCELLED <<<   -\n");
        printf("---------------------------------------\n");
        printf("Current Version: %s\n", stack->versions[stack->top].versionNumber);
        printf("---------------------------------------\n");
        printf("    >>> CURRENT DOCUMENT CONTENT <<<      -\n");
        printf("---------------------------------------\n");
        printf("%s\n", stack->versions[stack->top].content);
        printf("---------------------------------------\n");
    }
}

// Function to display all versions in the stack
void displayAllVersions(DocumentStack *stack)
{
    if (isStackEmpty(stack))
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("    ~ DOCUMENT VERSION STACK IS EMPTY ~     \n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("No versions to display.\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        return;
    }

    printf("\n=================================\n");
    printf("          <<< ALL VERSIONS >>>            \n");
    printf("=================================\n");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("Version: %s\n", stack->versions[i].versionNumber);
        printf("---------------------------------\n");
        if (i == stack->top)
        {
            printf("-> *** (*Current) ***\n");
            printf("---------------------------------\n");
        }
        printf("Content: \n%s\n\n", stack->versions[i].content);
        printf("---------------------------------\n");
    }
    printf("=================================\n");
}

void docVersionControl()
{
    DocumentStack stack;
    initializeStack(&stack);

    int choice;
    DocumentVersion version;
    char content[1000];

    printf("\n-----------------------------------------------------------\n");
    printf("-     D  O  C  U  M  E  N  T     V  E  R  S  I  O  N     -\n");
    printf("-                 C  O  N  T  R  O  L                    -\n");
    printf("-----------------------------------------------------------\n");

    do
    {
        printf("\n=================================\n");
        printf("       <<< DOCUMENT MENU >>>      \n");
        printf("=================================\n");
        printf("1.  Create New Version\n");
        printf("2.  Revert to Previous Version\n");
        printf("3.  Display All Versions\n");
        printf("4.  Delete Document\n");
        printf("0.  Exit\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter Version Number: ");
            scanf("%s", version.versionNumber);
            printf("\nEnter Document Content: ");
            scanf(" %[^\n]s", content);
            strncpy(version.content, content, sizeof(version.content) - 1);
            push(&stack, version);
            break;
        case 2:
            if (!isStackEmpty(&stack))
            {
                printf("\n==========================================\n");
                printf("     +++ REVERT TO PREVIOUS VERSION +++     \n");
                printf("==========================================\n");
                printf("Are you sure you want to revert to the previous version? (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N')
                {
                    printf("\n== Invalid choice. Please try again. 'y' or 'n' ==  ");
                    scanf(" %c", &confirm);
                }

                if (confirm == 'y' || confirm == 'Y')
                {
                    if (!isStackEmpty(&stack))
                    {
                        DocumentVersion currentTopVersion = stack.versions[stack.top]; // Store the current top version

                        version = pop(&stack);
                        if (strcmp(version.versionNumber, "-1") == 0)
                        {
                            printf("\n<<<In order to go back to the previous version, create at least 2 versions!>>>>\n");
                            break;
                        }

                        printf("\n[+] Version %s successfully reverted.\n", version.versionNumber);
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                        printf(">>> CURRENT DOCUMENT CONTENT <<<\n");
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                        printf("%s\n", stack.versions[stack.top].content);
                        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    }
                }
                else if (confirm == 'n' || confirm == 'N')
                {
                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("   >>> REVERT OPERATION CANCELLED <<<   \n");
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("Current Version: %s\n", stack.versions[stack.top].versionNumber);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("     >>> CURRENT DOCUMENT CONTENT <<<     \n");
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("%s\n", stack.versions[stack.top].content);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
            }
            else
            {
                printf("\n=====================================\n");
                printf("      No previous versions available     \n");
                printf("               to revert.               \n");
                printf("=====================================\n");
            }
            break;

        case 3:
            displayAllVersions(&stack);
            break;

        case 4:
            deleteDocument(&stack);
            break;

        case 0:
            printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("~~~~ Exiting Document Version Control ~~~~\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("~~~~~ Stay With HaniFusion ~~~~~\n");
            printf("~~~~~ Thank You!  :) ~~~~~\n");
            printf("~~~~~ Back To HaniFusion-> ~~~~~\n");
            break;

        default:
            printf("\n== Invalid choice. Please try again. ==\n");
            break;
        }
    } while (choice != 0);
}
