#include <ncurses.h>
#include <unistd.h>  // For usleep function
#include <math.h>    // For sin, cos functions

#define DELAY 50000  // Delay between frame updates (in microseconds)
#define COLOR_CYCLE 7

int main() {
    int x, y;
    int max_x, max_y;
    float angle = 0.0;
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
    int center_x = max_x / 2;
    int center_y = max_y / 2;

    while (1) {
        clear();  // Clear the screen

        // Draw rotating lines
        for (int i = 0; i < 360; i += 15) {
            float rad = (i + angle) * M_PI / 180;
            int line_x = center_x + (int)(10 * cos(rad));
            int line_y = center_y + (int)(5 * sin(rad));

            // Set color and draw lines
            attron(COLOR_PAIR(color_index));
            mvprintw(line_y, line_x, "#");
            attroff(COLOR_PAIR(color_index));
        }

        // Refresh the screen to show changes
        refresh();

        // Cycle through colors for each frame
        color_index = (color_index % COLOR_CYCLE) + 1;

        // Increase the angle for rotation
        angle += 2.0;
        if (angle >= 360.0) {
            angle = 0.0;
        }

        // Delay before next frame
        usleep(DELAY);
    }

    // End ncurses mode
    endwin();

    return 0;
}
