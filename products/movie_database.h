// Structure to store movie information
typedef struct
{
    char title[100];
    char genre[50];
    float rating;
} Movie;

// Genre database
char *genres[7] = {
    "Action",
    "Horror",
    "Sci-Fi",
    "Comedy",
    "Drama",
    "Romantic",
    "Thriller"};

// Function to perform linear search
int linearSearch(Movie movies[], int n, char key[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(movies[i].title, key) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Function to perform insertion sort
void insertionSort(Movie movies[], int n)
{
    for (int i = 1; i < n; i++)
    {
        Movie key = movies[i];
        int j = i - 1;
        while (j >= 0 && movies[j].rating < key.rating)
        {
            movies[j + 1] = movies[j];
            j--;
        }
        movies[j + 1] = key;
    }
}

void movieDatabase()
{
    printf("\n--------------------------------------------------------------------\n");
    printf("-                           M  O  V  I  E                           -\n");
    printf("-                        D  A  T  A  B  A  S  E                     -\n");
    printf("---------------------------------------------------------------------\n");

    int numMovies = 0;
    Movie movies[100]; // Assuming a maximum of 100 movies in the database

    int choice;
    do
    {
        printf("\n====================================\n");
        printf("       <<< MOVIE DATABASE MENU >>>      \n");
        printf("====================================\n");
        printf("1. Add a movie\n");
        printf("2. Show movie list\n");
        printf("3. Search for a movie\n");
        printf("4. Sort by rating\n");
        printf("5. Wipe out database\n");
        printf("6. Exit\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Clear the input buffer

        switch (choice)
        {
        case 1:
        {
            if (numMovies >= 100)
            {
                printf("\n=== Movie database is full. Cannot add more movies. ===\n\n");
            }
            else
            {
                Movie newMovie;
                printf("> Enter the title of the movie: ");
                fgets(newMovie.title, sizeof(newMovie.title), stdin);
                newMovie.title[strcspn(newMovie.title, "\n")] = '\0';

                int validGenre = 0;
                while (!validGenre)
                {
                    printf("> Select a genre:\n");
                    printf("--------------------\n");
                    for (int i = 0; i < 7; i++)
                    {
                        printf("%d. %s\n", i + 1, genres[i]);
                    }
                    printf("--------------------\n");

                    printf("> Enter the genre index: ");
                    int genreIndex;
                    scanf("%d", &genreIndex);
                    while (getchar() != '\n')
                        ; // Clear the input buffer

                    if (genreIndex < 1 || genreIndex > 7)
                    {
                        printf("\n=== Invalid genre index. Please try again. ===\n\n");
                    }
                    else
                    {
                        strcpy(newMovie.genre, genres[genreIndex - 1]);
                        validGenre = 1;
                    }
                }

                while (1)
                {
                    printf("> Enter the rating of the movie: ");
                    char ratingInput[10];
                    fgets(ratingInput, sizeof(ratingInput), stdin);
                    sscanf(ratingInput, "%f", &newMovie.rating);

                    if (newMovie.rating <= 0 || newMovie.rating > 10.0)
                    {
                        printf("\n=== Invalid rating. Rating should be greater than 0 and not greater than 10.0. Please insert again. ===\n\n");
                    }
                    else
                    {
                        break;
                    }
                }

                movies[numMovies++] = newMovie;
                printf("\n=== Movie added successfully. ===\n\n");
            }
            break;
        }
        case 2:
        {
            if (numMovies == 0)
            {
                printf("\n=== No movies in the database. ===\n\n");
            }
            else
            {
                printf("\nMovie List:\n");
                printf("--------------------------------------------\n");
                printf("|   Title        |   Genre       |  Rating |\n");
                printf("--------------------------------------------\n");
                for (int i = 0; i < numMovies; i++)
                {
                    printf("| %-14s | %-13s |  %.1f    |\n", movies[i].title, movies[i].genre, movies[i].rating);
                    printf("--------------------------------------------\n");
                }
            }
            break;
        }
        case 3:
        {
            if (numMovies == 0)
            {
                printf("\n=== No movies in the database. ===\n\n");
            }
            else
            {
                char searchTitle[100];
                printf(">> Enter the title of the movie to search: ");
                fgets(searchTitle, sizeof(searchTitle), stdin);
                searchTitle[strcspn(searchTitle, "\n")] = '\0';

                int linearResult = linearSearch(movies, numMovies, searchTitle);
                if (linearResult != -1)
                {
                    printf("\nMovie found using linear search:\n");
                    printf("---------------------------------\n");
                    printf("Title:  %s\n", movies[linearResult].title);
                    printf("Genre:  %s\n", movies[linearResult].genre);
                    printf("Rating: %.1f\n", movies[linearResult].rating);
                    printf("---------------------------------\n");
                }
                else
                {
                    printf("\n=== Movie not found using linear search. ===\n\n");
                }
            }
            break;
        }
        case 4:
        {
            if (numMovies == 0)
            {
                printf("\n=== No movies in the database. ===\n\n");
            }
            else
            {
                insertionSort(movies, numMovies);
                printf("\nBest movies sorted by rating:\n");
                printf("--------------------------------------------\n");
                printf("|   Title        |   Genre       |  Rating |\n");
                printf("--------------------------------------------\n");
                for (int i = 0; i < numMovies; i++)
                {
                    printf("| %-14s | %-13s |  %.1f    |\n", movies[i].title, movies[i].genre, movies[i].rating);
                    printf("--------------------------------------------\n");
                }
            }
            break;
        }
        case 5:
        {
            if (numMovies == 0)
            {
                printf("\n=== No movies in the database. ===\n\n");
                break;
            }

            printf("\n> Are you sure you want to wipe out the database? (y/n): ");
            char confirm;
            scanf(" %c", &confirm);
            while (getchar() != '\n')
                ; // Clear the input buffer

            if (confirm == 'y' || confirm == 'Y')
            {
                numMovies = 0;
                printf("\n=== Database wiped out successfully. ===\n\n");
            }
            else
            {
                printf("\n=== Database wipe out cancelled. ===\n\n");
            }
            break;
        }
        case 6:
        {
            printf("\n=== Back To HaniFusion. ===\n\n");
            break;
        }
        default:
        {
            printf("\n=== Invalid choice. Please try again. ===\n\n");
            break;
        }
        }
        printf("\n");
    } while (choice != 6);
}
