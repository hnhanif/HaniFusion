#ifdef _WIN32
#include <windows.h>
#define MY_SLEEP(ms) Sleep(ms)
#elif __linux__
#include <unistd.h>
#define MY_SLEEP(ms) usleep((ms)*1000)
#else
#error "Unsupported operating system"
#endif

void loadingAnimation()
{
    printf("\t\tLoading...");

    for (int i = 0; i < 10; i++)
    {
        printf(".");
        fflush(stdout);

#ifdef _WIN32
        MY_SLEEP(500); // Sleep for 500 milliseconds on Windows
#elif __linux__
        MY_SLEEP(500000); // Sleep for 500,000 microseconds (0.5 seconds) on Linux
#endif
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
