/*
    conway.c
    Date: Wednesday 9th July 2025
    Author: Brendan Gasparin <brendan.gasparin@gmail.com>
    Conway's Game of Life.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include <windows.h> on Windows, otherwise <unistd.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define HEIGHT 20   // Height of the grid
#define WIDTH 60   // Width of the grid
#define FALSE 0 // False
#define TRUE 1  // True

void clear_screen();
void copy_board(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH]);
void evolve(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH]);
void print_screen(int board[HEIGHT][WIDTH]);
void tick();

int main() {
    int board[HEIGHT][WIDTH];
    int newboard[HEIGHT][WIDTH];
    int random;
    int r, c;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Randomly populate the initial board
    for (r = 0; r < HEIGHT; r++)
        for (c = 0; c < WIDTH; c++)
            board[r][c] = rand() % 2;

    // Game loop
    while (TRUE) {
        print_screen(board);
        evolve(newboard, board);
        copy_board(board, newboard);
        tick();
    }
}

// Clears the terminal.
void clear_screen() {
    // ANSI escape codes to clear screen and move cursor to top-left
    printf("\033[2J\033[H");
    fflush(stdout);
}

// Copy one board to another.
void copy_board(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH]) {
    int r, c;

    for (r = 0; r < HEIGHT; r++)
        for (c = 0; c < WIDTH; c++)
            dest[r][c] = src[r][c];
}

// Apply the rules of Conway's Game of Life to create a destination board
// from the source board.
void evolve(int dest[HEIGHT][WIDTH], int src[HEIGHT][WIDTH]) {
    int count;
    int up, down, left, right;
    int r, c;

    for (r = 0; r < HEIGHT; r++)
        for (c = 0; c < WIDTH; c++) {
            count = 0;

            up = (r - 1) % HEIGHT;
            down = (r + 1) % HEIGHT;
            left = (c - 1) % WIDTH;
            right = (c + 1) % WIDTH;

            // Count neighboring cells.
            if (src[up][left] == TRUE)
                count++;
            if (src[up][c] == TRUE)
                count++;
            if (src[up][right] == TRUE)
                count++;
            if (src[r][left] == TRUE)
                count++;
            if (src[r][right] == TRUE)
                count++;
            if (src[down][left] == TRUE)
                count++;
            if (src[down][c] == TRUE)
                count++;
            if (src[down][right] == TRUE)
                count++;
            
            // Apply the game rules to the cell on the next grid.
            if (src[r][c] == TRUE && (count == 2 || count == 3))
                dest[r][c] = TRUE;
            else if (src[r][c] == FALSE && count == 3)
                dest[r][c] = TRUE;
            else
                dest[r][c] = FALSE;
        }
}

// Print the board to the terminal.
void print_screen(int board[HEIGHT][WIDTH]) {
    int r, c;

    clear_screen();

    for (r = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++) {
            if (board[r][c] == TRUE)
                putchar('#');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    printf("\nControl-C to quit...");
    fflush(stdout);  // Force immediate display
}

// Wait for one second.
void tick() {
    #ifdef _WIN32
        Sleep(1000);
    #else
        sleep(1);
    #endif
}
