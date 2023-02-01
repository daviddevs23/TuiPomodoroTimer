#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

int one[5][3] =     {{0,1,0},
                     {0,1,0},
                     {0,1,0},
                     {0,1,0},
                     {0,1,0}};

int two[5][3] =     {{1,1,1},
                     {0,0,1},
                     {1,1,1},
                     {1,0,0},
                     {1,1,1}};

int three[5][3] =   {{1,1,1},
                     {0,0,1},
                     {1,1,1},
                     {0,0,1},
                     {1,1,1}};

int four[5][3] =    {{1,0,1},
                     {1,0,1},
                     {1,1,1},
                     {0,0,1},
                     {0,0,1}};

int five[5][3] =    {{1,1,1},
                     {1,0,0},
                     {1,1,1},
                     {0,0,1},
                     {1,1,1}};

int six[5][3] =     {{1,1,1},
                     {1,0,0},
                     {1,1,1},
                     {1,0,1},
                     {1,1,1}};

int seven[5][3] =   {{1,1,1},
                     {0,0,1},
                     {0,0,1},
                     {0,0,1},
                     {0,0,1}};

int eight[5][3] =   {{1,1,1},
                     {1,0,1},
                     {1,1,1},
                     {1,0,1},
                     {1,1,1}};

int nine[5][3] =    {{1,1,1},
                     {1,0,1},
                     {1,1,1},
                     {0,0,1},
                     {0,0,1}};

int colon[5][3] =   {{0,0,0},
                     {0,1,0},
                     {0,0,0},
                     {0,1,0},
                     {0,0,0}};

// Utility function to pretty print
void prettyPrint(int time, int sleepSeconds) {
    int minutes = (int)(time / 60);
    int seconds = time % 60;
    std::string printChar = "#";

    // Screen dimensions
    int row, col{};
    getmaxyx(stdscr, row, col);

    // Print Stuff
    refresh();
    sleep(sleepSeconds);
    clear();
}

int main(int argc, char *argv[]) {
    // Provide help menu
    if (argc == 2 && !strcmp(argv[1], "-h")) {
        std::cout
            << "Usage: pomo-tui <work> <short-break> <long-break> <sessions>"
            << std::endl
            << std::endl;
        std::cout << "  work        - focused work time in minutes"
                  << std::endl;
        std::cout << "  short-break - short breaks time in minutes"
                  << std::endl;
        std::cout << "  long-break  - long break time in minute" << std::endl;
        std::cout << "  sessions    - number of sessions before a break"
                  << std::endl;
        return 0;

        // Provide default usage
    } else if (argc < 5) {
        std::cout
            << "Usage: pomo-tui <work> <short-break> <long-break> <sessions>"
            << std::endl;
        return 1;
    }

    int workTime = atoi(argv[1]) * 60;
    int shortBreak = atoi(argv[2]) * 60;
    int longBreak = atoi(argv[3]) * 60;
    int sessions = atoi(argv[4]);

    initscr();
    // Run through the number of sessions
    for (int session = 0; session < sessions; session++) {
        // Work Time
        for (int work = workTime; work >= 0; work--) {
            printw("Work: %02d:%02d", (int)(work / 60), work % 60);

            refresh();
            sleep(1);
            clear();
        }

        // Short Break
        for (int relax = shortBreak; relax >= 0; relax--) {
            printw("Relax: %02d:%02d", (int)(relax / 60), relax % 60);

            refresh();
            sleep(1);
            clear();
        }
    }
    // Long Break
    for (int longRelax = longBreak; longRelax >= 0; longRelax--) {
        printw("Long Relax: %02d:%02d", (int)(longRelax / 60), longRelax % 60);

        refresh();
        sleep(1);
        clear();
    }
    // Close the ncurse tui
    endwin();

    return 0;
}
