#define MAX_ORDERS 100

// Struct to represent an order
typedef struct
{
    int orderId;
    char customerName[50];
    char orderItems[100];
    int prepTime;
} Order;

// Queue structure
typedef struct
{
    Order orders[MAX_ORDERS];
    int front;
    int rear;
    int count;
} Queue;

// Function to create an empty queue
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->count = 0;
    return queue;
}

// Function to check if the queue is empty
int isEmptyOrder(Queue *queue)
{
    return (queue->count == 0);
}

// Function to check if the queue is full
int isFull(Queue *queue)
{
    return (queue->count == MAX_ORDERS);
}

// Function to generate a new order ID
int generateOrderId(Queue *queue)
{
    return queue->count + 1;
}

// Function to add an order to the queue
void enqueue(Queue *queue, Order order)
{
    if (isFull(queue))
    {
        printf("\n----------------------------------------------------------------------------\n");
        printf("Due to high demand, we have temporarily reached our capacity for new orders.\n");
        printf("----------------------------------------------------------------------------\n");
        return;
    }

    if (isEmptyOrder(queue))
        queue->front = 0;

    queue->rear = (queue->rear + 1) % MAX_ORDERS;
    order.orderId = generateOrderId(queue);
    queue->orders[queue->rear] = order;
    queue->count++;

    printf("\n---------------------------\n");
    printf("Order added successfully!\n");
    printf("---------------------------\n");
}

// Function to remove an order from the queue and mark it as processed
void processOrder(Queue *queue)
{
    if (isEmptyOrder(queue))
    {
        printf("\n--------------------------------------\n");
        printf("Currently, there are no pending orders.\n");
        printf("--------------------------------------\n");
        return;
    }

    printf("+------------------------------- +\n");
    printf("|  Order processed successfully  |\n");
    printf("+------------------------------ -+\n");
    printf("| Order ID: %d                    |\n", queue->orders[queue->front].orderId);
    printf("| Customer Name: %-15s |\n", queue->orders[queue->front].customerName);
    printf("| Order Items: %-17s |\n", queue->orders[queue->front].orderItems);
    printf("| Preparation Time: %2d minutes   |\n", queue->orders[queue->front].prepTime);
    printf("+--------------------------------+\n");

    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % MAX_ORDERS;

    queue->count--;
}

// Function to mark all orders as completed
void completeAllOrders(Queue *queue)
{
    if (isEmptyOrder(queue))
    {
        printf("\n+---------------------------------------+\n");
        printf("|  We currently have no pending orders. |\n");
        printf("+---------------------------------------+\n");

        return;
    }

    printf("\n=== Completing all orders ===\n");

    while (!isEmptyOrder(queue))
    {
        printf("+----------------------------------------------+\n");
        printf("|  Order ID: %d\n", queue->orders[queue->front].orderId);
        printf("|  Customer Name: %s\n", queue->orders[queue->front].customerName);
        printf("|  Order Items: %s\n", queue->orders[queue->front].orderItems);
        printf("|  Estimated Preparation Time: %d minutes\n", queue->orders[queue->front].prepTime);
        printf("+----------------------------------------------+\n");

        if (queue->front == queue->rear)
            queue->front = queue->rear = -1;
        else
            queue->front = (queue->front + 1) % MAX_ORDERS;

        queue->count--;
        printf("\n");
    }

    printf("+-------------------------------------+\n");
    printf("|  All orders completed successfully  |\n");
    printf("+-------------------------------------+\n");
}

// Function to display the orders in the queue
void displayOrders(Queue *queue)
{
    if (isEmptyOrder(queue))
    {
        printf("\n+-------------------------------+\n");
        printf("|  Sorry :( no orders found!    |\n");
        printf("+-------------------------------+\n");

        return;
    }

    printf("\n+------------------------------------------------+\n");
    printf("|  We have %d orders in progress at the moment.  |\n", queue->count);
    printf("+------------------------------------------------+\n");
    printf("\n\n== Pending Orders ==\n");

    printf("+--------+-----------------+------------------+-----------------------------+-----------------------------+-------------------------------+\n");
    printf("|  Order |     Status      |    Order ID      |        Customer Name        |        Order Items          |   Estimated Preparation Time  |\n");
    printf("| Number |                 |                  |                             |                             |          (in minutes)         |\n");
    printf("+--------+-----------------+------------------+-----------------------------+-----------------------------+-------------------------------+\n");

    int i = queue->front;
    int count = 1;
    while (i != queue->rear)
    {
        printf("|   %2d   | %-15s | %16d | %-27s | %-27s | %-29d |\n",
               count++,
               (i == queue->front) ? "(*working)" : "(*waiting)",
               queue->orders[i].orderId,
               queue->orders[i].customerName,
               queue->orders[i].orderItems,
               queue->orders[i].prepTime);
        printf("+--------+-----------------+------------------+-----------------------------+-----------------------------+-------------------------------+\n");

        i = (i + 1) % MAX_ORDERS;
    }

    // Print the last order
    printf("|   %2d   | %-15s | %16d | %-27s | %-27s | %-29d |\n",
           count,
           (i == queue->front) ? "(*working)" : "(*waiting)",
           queue->orders[i].orderId,
           queue->orders[i].customerName,
           queue->orders[i].orderItems,
           queue->orders[i].prepTime);
    printf("+--------+-----------------+------------------+-----------------------------+-----------------------------+-------------------------------+\n");
}

int restaurantOrder()
{
    printf("\n----------------------------------------------------------------\n");
    printf("-             R  E  S  T  A  U  R  A  N  T                     -\n");
    printf("-            O  R  D  E  R     M  A  N  A  G  E  M  E  N  T    -\n");
    printf("----------------------------------------------------------------\n");
    Queue *orderQueue = createQueue();
    int choice;
    Order newOrder;

    while (1)
    {

        printf("\n=================================\n");
        printf("         <<< ORDER MENU >>>       \n");
        printf("=================================\n");
        printf("1. Add Order\n");
        printf("2. Process Order\n");
        printf("3. View Orders\n");
        printf("4. Complete All Orders\n");
        printf("5. Exit\n");
        printf("=================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf(">> Enter Customer Name: ");
            scanf(" %[^\n]", newOrder.customerName);

            printf(">> Enter Order Items: ");
            scanf(" %[^\n]", newOrder.orderItems);

            printf(">> Enter Estimated Preparation Time (in minutes): ");

            scanf("%d", &newOrder.prepTime);
            enqueue(orderQueue, newOrder);
            break;

        case 2:
            processOrder(orderQueue);
            break;

        case 3:
            displayOrders(orderQueue);
            break;

        case 4:
            completeAllOrders(orderQueue);
            break;

        case 5:
            printf("\n+-----------------------------+\n");
            printf("|  Back To HaniFusion.        |\n");
            printf("+-----------------------------+\n");
            return 0;

        default:
            printf("\n-> Oops! Invalid choice. Please try again.\n");
        }
    }
}
