
typedef struct Transaction
{
    char description[100];
    float amount;
    struct Transaction *next;
} Transaction;

Transaction *createTransaction(char *description, float amount)
{
    Transaction *newTransaction = (Transaction *)malloc(sizeof(Transaction));
    strcpy(newTransaction->description, description);
    newTransaction->amount = amount;
    newTransaction->next = NULL;
    return newTransaction;
}

void addTransaction(Transaction **head, char *description, float amount)
{
    Transaction *newTransaction = createTransaction(description, amount);
    if (*head == NULL)
    {
        *head = newTransaction;
    }
    else
    {
        Transaction *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newTransaction;
    }
    printf("\n=== Transaction added successfully ===\n\n");
}
void displayTransactions(Transaction *head)
{
    if (head == NULL)
    {
        printf("\n=== No transactions found ===\n\n");
        return;
    }
    printf("=================================================\n");
    printf("%-4s%-30s%-10s\n", "No.", "Description", "Amount");
    printf("-------------------------------------------------\n");
    int count = 1;
    while (head != NULL)
    {
        printf("%-4d%-30s$%.2f\n", count, head->description, head->amount);
        head = head->next;
        count++;
    }
    printf("=================================================\n");
}

float calculateTotal(Transaction *head)
{
    float total = 0;
    while (head != NULL)
    {
        total += head->amount;
        head = head->next;
    }
    return total;
}

void freeTransactions(Transaction **head)
{
    Transaction *current = *head;
    while (current != NULL)
    {
        Transaction *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("\n=== All transactions freed ===\n\n");
}

int personalFinance()
{
    printf("\n------------------------------------------------------------------------\n");
    printf("-                       P  E  R  S  O  N  A  L                         -\n");
    printf("-                       F  I  N  A  N  C  E                            -\n");
    printf("------------------------------------------------------------------------\n");

    Transaction *transactions = NULL;

    while (1)
    {
        printf("\n==================================\n");
        printf("    <<< PERSONAL FINANCE MENU >>>    \n");
        printf("==================================\n");
        printf("1.  Add Transaction\n");
        printf("2.  Display Transactions\n");
        printf("3.  Calculate Total\n");
        printf("4.  Clear All Transactions\n");
        printf("5.  Quit\n");
        printf("=================================\n");

        printf(">> Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("> Enter description: ");
            char description[100];
            scanf("%s", description);

            printf("> Enter amount: ");
            float amount;
            scanf("%f", &amount);

            addTransaction(&transactions, description, amount);
            break;
        }
        case 2:
            displayTransactions(transactions);
            break;
        case 3:
        {
            if (transactions == NULL)
            {
                printf("\n=== Sorry, in order to calculate data, you need to first add a transaction ===\n\n");
            }
            else
            {
                printf("\n=====================================\n");
                printf("Total Amount: $%.2f\n", calculateTotal(transactions));
                printf("=====================================\n");
            }
            break;
        }

        case 4:
        {
            if (transactions == NULL)
            {
                printf("\n=== No transactions found ===\n\n");
            }
            else
            {
                char confirmation;
                do
                {
                    printf("> Are you sure you want to clear all transactions? (y/n): ");

                    scanf(" %c", &confirmation);

                    if (confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N')
                    {
                        printf("\n=== Invalid input. Please enter 'y' or 'n'. ===\n\n");
                    }
                } while (confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'y' || confirmation == 'Y')
                {
                    freeTransactions(&transactions);
                }
                else
                {
                    printf("\n=== Clear all transactions operation canceled ===\n\n");
                }
            }
            break;
        }

        case 5:
            printf("\n=== Back To HaniFusion ===\n\n");
            return 0;
        default:
            printf("\n=== Invalid choice. Please try again. ===\n\n");

            break;
        }
    }
}
