#include <ncurses.h>
#include <unistd.h>   // For usleep function
#include <math.h>     // For sin function

#define DELAY 30000  // Delay between frame updates (in microseconds)
#define COLOR_CYCLE 7

int main() {
    int x, y;
    int max_x, max_y;
    float offset = 0.0;
    int color_index = 1;

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();

    // Define color pairs
    for (int i = 1; i <= COLOR_CYCLE; i++) {
        init_pair(i, i, COLOR_BLACK);  // Text color on black background
    }

    // Get the screen size
    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();  // Clear the screen

        // Draw zig-zag pattern
        for (y = 0; y < max_y; y++) {
            for (x = 0; x < max_x; x++) {
                if ((x + (int)offset) % 10 == 0) {
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

        // Shift pattern horizontally
        offset += 0.3;
        if (offset >= 10.0) {
            offset = 0.0;
        }

        // Delay before next frame
        usleep(DELAY);
    }

    // End ncurses mode
    endwin();

    return 0;
}
