
void loadingAnimation()
{
    printf("\t\tLoading...");

    for (int i = 0; i < 10; i++)
    {
        printf(".");
        fflush(stdout);
        usleep(500000); // Adjust the usleep value for the desired animation speed (in microseconds)
    }

    printf("\n");
}

void displayMessage()
{
    printf("=================================================\n");
    printf("=                                               =\n");
    printf("=          Welcome to HaniFusion                =\n");
    printf("=                                               =\n");
    printf("=       Together We can change the world!       =\n");
    printf("=                                               =\n");
    printf("=================================================\n");
}

void animation()
{
    loadingAnimation();
    displayMessage();
}
