#include <ncurses.h>
#include <unistd.h>  // For usleep function
#include <math.h>    // For sin, cos functions

#define DELAY 50000
#define COLOR_CYCLE 7

int main() {
    int x, y;
    int max_x, max_y;
    float radius = 1.0;
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

        // Draw expanding circles
        for (float angle = 0; angle < 360; angle += 10) {
            float rad = angle * M_PI / 180;
            x = center_x + (int)(radius * cos(rad));
            y = center_y + (int)(radius * sin(rad));

            // Set color and draw circle points
            attron(COLOR_PAIR(color_index));
            mvprintw(y, x, "#");
            attroff(COLOR_PAIR(color_index));
        }

        // Refresh the screen to show changes
        refresh();

        // Cycle through colors for each frame
        color_index = (color_index % COLOR_CYCLE) + 1;

        // Increase radius for expansion
        radius += 0.5;
        if (radius > max_x / 2) {
            radius = 1.0;  // Reset radius after a certain size
        }

        // Delay before next frame
        usleep(DELAY);
    }

    // End ncurses mode
    endwin();

    return 0;
}
