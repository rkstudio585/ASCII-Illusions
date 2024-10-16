#include <ncurses.h>
#include <unistd.h>  // For usleep function
#include <stdlib.h>  // For rand()

#define DELAY 50000
#define COLOR_CYCLE 7

int main() {
    int x, y;
    int max_x, max_y;
    int color_index = 1;

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();

    // Define color pairs
    for (int i = 1; i <= COLOR_CYCLE; i++) {
        init_pair(i, i, COLOR_BLACK);
    }

    // Get the screen size
    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();  // Clear the screen

        // Draw falling characters
        for (x = 0; x < max_x; x++) {
            for (y = 0; y < max_y; y++) {
                if (rand() % 10 < 2) {  // Randomly place characters
                    attron(COLOR_PAIR(color_index));
                    mvprintw(y, x, "%c", (rand() % 94) + 33);  // Random ASCII character
                    attroff(COLOR_PAIR(color_index));
                }
            }
        }

        // Refresh the screen to show changes
        refresh();

        // Cycle through colors for each frame
        color_index = (color_index % COLOR_CYCLE) + 1;

        // Delay before next frame
        usleep(DELAY);
    }

    // End ncurses mode
    endwin();

    return 0;
}
