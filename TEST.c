#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define THEATER_COUNT 10
#define SEATS_PER_MOVIE 20

/*
 * Our movie list and count
 */
typedef struct {
    int id;
    const char name[64];
} Movie;

static const Movie movies[] = {
    {0,  "Inception"},
    {1,  "Pulp Fiction"},
    {2,  "The Matrix"},
    {3,  "Jurassic Park"},
    {4,  "The Shawshank Redemption"},
    {5,  "Parasite"},
    {6,  "Mad Max: Fury Road"},
    {7,  "The Dark Knight"},
    {8,  "Forrest Gump"},
    {9,  "The Godfather"},
    {10, "Interstellar"},
    {11, "Fight Club"},
    {12, "Back to the Future"},
    {13, "Star Wars: A New Hope"}
};
#define MOVIE_COUNT (sizeof (movies)/ sizeof(Movie))
/*
 * 
 */

/*
 * Our theater list
 */
typedef struct {
    int id;
    char name[64];
    int avail_movies; // bitmask, 1 -> the movie is on the playlist
    unsigned int avail_seats[MOVIE_COUNT]; // bitmask, for each movie, 1 -> the seat is booked
} Theater;

// static initialization ensures playlist and seats are empty at startup
static Theater theaters[THEATER_COUNT] = {
    {0, "Starlight Cinema"},
    {1, "Galaxy Screenplex"},
    {2, "The Velvet Reel"},
    {3, "CineNova"},
    {4, "Majestic Motion Theater"},
    {5, "The Neon Flick"},
    {6, "Silver Screen Sanctum"},
    {7, "Aurora Cineplex"},
    {8, "The Flicker House"},
    {9, "Midnight Marquee"}
};
/*
 *
 */

// set the playlist randomly via a bitfield (0x0 -> 0x3fff)
static void fillTheaters() 
{
    for (int i = 0; i < THEATER_COUNT; i++) 
        theaters[i].avail_movies = rand() % (1 << MOVIE_COUNT);
}

// Iterate over movies array to show all movies
static void showMovies()
{
    printf("\nAvailable Movies:\n");
    for (int i = 0; i < MOVIE_COUNT; i++) {
        printf("%d: %s\n", i, movies[i].name);
    }
}

// Iterate over movies array to check bit setting on the theater array
static void showTheatersForMovie(int movie_id)
{
    printf("\nTheaters showing \"%s\":\n", movies[movie_id].name);
    for (int i = 0; i < THEATER_COUNT; i++) {
        if (theaters[i].avail_movies & (1 << movie_id)) {
            printf("%d: %s\n", i, theaters[i].name);
        }
    }
}

// Check bit is set on a given theater seat
static void showAvailableSeats(int theater_id, int movie_id) {
    printf("Available seats for \"%s\" in \"%s\":\n", movies[movie_id].name, theaters[theater_id].name);
    unsigned int mask = theaters[theater_id].avail_seats[movie_id];
    int is_found = 0;
    for (int s = 0; s < SEATS_PER_MOVIE; s++) {
        if ((mask & (1 << s)) == 0) {
            printf("%d ", s + 1);
            is_found = 1;
        }
    }
    if (!is_found) {
        printf("No available seats.");
    }
    printf("\n");
}

// Set bit on the given theater seat
static void reserveSeat(int theater_id, int movie_id) {
    showAvailableSeats(theater_id, movie_id);

    printf("Enter a seat number (1-%d) to book: ", SEATS_PER_MOVIE);
    int seat_num;
    int res = scanf("%d", &seat_num);

    seat_num = seat_num - 1;
    if (seat_num < 0 || seat_num >= SEATS_PER_MOVIE) 
    {
        printf("Invalid seat number.\n");
        return;
    }

    unsigned int mask = theaters[theater_id].avail_seats[movie_id];
    if (mask & (1 << seat_num)) 
    {
        printf("Seat %d already booked.\n", seat_num + 1);
    }
    else 
    {
        theaters[theater_id].avail_seats[movie_id] = mask | (1 << seat_num);
        printf("Seat %d booked.\n", seat_num + 1);
    }
}

int main() {
    srand((unsigned)time(NULL));
    fillTheaters();

    // Main loop for user interface
    for (;;) {
        printf("\n\nMenu :\n");
        printf("1 - View all movies\n");
        printf("2 - See theaters showing the movie\n");
        printf("3 - See available seats in a theater for a movie\n");
        printf("4 - Book a seat\n");
        printf("Choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            break;
        }
        // MENU 1 -- View all playing movies
        if (choice == 1)
        {
            showMovies();
        }
        // MENU 2 -- See all theaters showing the movie
        else if (choice == 2)
        {
            showMovies();
            printf("Select the movie : ");
            int selectedMovie ;
            if (scanf("%d", &selectedMovie) == 1 && selectedMovie >= 0 && selectedMovie < MOVIE_COUNT) {
                showTheatersForMovie(selectedMovie);
            }
        }
        // MENU 3 -- See available seats (e.g., a1, a2, a3) for the selected theater and movie. 
        else if (choice == 3)
        {
            showMovies(); 
            printf("Select the movie : ");
            int selectedMovie;
            if (scanf("%d", &selectedMovie) == 1 && selectedMovie >= 0 && selectedMovie < MOVIE_COUNT) {
                showTheatersForMovie(selectedMovie);
                printf("Select a theater ID: ");
                int selectedTheater;
                if (scanf("%d", &selectedTheater) == 1 && selectedTheater >= 0 && selectedTheater < THEATER_COUNT) {
                    if (theaters[selectedTheater].avail_movies & (1 << selectedMovie)) {
                        showAvailableSeats(selectedTheater, selectedMovie);
                    }
                    else {
                        printf("This theater does not show the selected movie.\n");
                    }
                }
            }
        }


        // MENU 4 -- Book one or more of the available seats.
        else if (choice == 4)
        {
            showMovies();
            printf("Select the movie : ");
            int selectedMovie;
            if (scanf("%d", &selectedMovie) == 1) 
            {
                showTheatersForMovie(selectedMovie);
                printf("Select a theater ID: ");
                int selectedTheater;
                if (scanf("%d", &selectedTheater) == 1) 
                {
                    if (theaters[selectedTheater].avail_movies & (1 << selectedMovie)) 
                    {
                        reserveSeat(selectedTheater, selectedMovie);
                    }
                    else 
                        printf("This theater does not show the selected movie.\n");
                }
            }
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
