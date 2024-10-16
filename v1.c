#include <ncurses.h>
#include <unistd.h>   // For usleep function
#include <math.h>     // For sin function

#define DELAY 30000  // Delay between frame updates (in microseconds)
#define COLOR_CYCLE 7  // Number of colors to cycle through

int main() {
    int x, y;
    int max_x, max_y;
    float offset = 0.0;
    int color_index = 1;

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();  // Start color functionality

    // Define color pairs
    for (int i = 1; i <= COLOR_CYCLE; i++) {
        init_pair(i, i, COLOR_BLACK);  // Text color on black background
    }

    // Get the screen size
    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();  // Clear the screen

        // Draw the wave illusion with colors
        for (y = 0; y < max_y; y++) {
            for (x = 0; x < max_x; x++) {
                // Create a wave-like pattern using sine function
                if (y == (int)(max_y / 2 + 5 * sin((x + offset) / 5.0))) {
                    // Set color and print character
                    attron(COLOR_PAIR(color_index));
                    mvprintw(y, x, "#");
                    attroff(COLOR_PAIR(color_index));
                }
            }
        }

        // Refresh the screen to show changes
        refresh();

        // Cycle through colors for each frame
        color_index = (color_index % COLOR_CYCLE) + 1;

        // Offset to create the animation illusion
        offset += 0.2;

        // Delay before next frame
        usleep(DELAY);
    }

    // End ncurses mode
    endwin();

    return 0;
}
