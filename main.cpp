#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <unordered_map>

struct Numbers {
    std::string first{};
    std::string second{};
    std::string third{};
    std::string fourth{};
    std::string fifth{};
};

// Utility function to pretty print
void prettyPrint(int time, int sleepSeconds, std::string session) {
    Numbers zero;
    zero.first = "###";
    zero.second = "# #";
    zero.third = "# #";
    zero.fourth = "# #";
    zero.fifth = "###";

    Numbers one;
    one.first = "#";
    one.second = "#";
    one.third = "#";
    one.fourth = "#";
    one.fifth = "#";

    Numbers two;
    two.first = "###";
    two.second = "  #";
    two.third = "###";
    two.fourth = "#  ";
    two.fifth = "###";

    Numbers three;
    three.first = "###";
    three.second = "  #";
    three.third = "###";
    three.fourth = "  #";
    three.fifth = "###";

    Numbers four;
    four.first = "# #";
    four.second = "# #";
    four.third = "###";
    four.fourth = "  #";
    four.fifth = "  #";

    Numbers five;
    five.first = "###";
    five.second = "#  ";
    five.third = "###";
    five.fourth = "  #";
    five.fifth = "###";

    Numbers six;
    six.first = "###";
    six.second = "#  ";
    six.third = "###";
    six.fourth = "# #";
    six.fifth = "###";

    Numbers seven;
    seven.first = "###";
    seven.second = "  #";
    seven.third = "  #";
    seven.fourth = "  #";
    seven.fifth = "  #";

    Numbers eight;
    eight.first = "###";
    eight.second = "# #";
    eight.third = "###";
    eight.fourth = "# #";
    eight.fifth = "###";

    Numbers nine;
    nine.first = "###";
    nine.second = "# #";
    nine.third = "###";
    nine.fourth = "  #";
    nine.fifth = "  #";

    std::unordered_map<int, Numbers> numbers;
    numbers[0] = zero;
    numbers[1] = one;
    numbers[2] = two;
    numbers[3] = three;
    numbers[4] = four;
    numbers[5] = five;
    numbers[6] = six;
    numbers[7] = seven;
    numbers[8] = eight;
    numbers[9] = nine;

    int minutes = (int)(time / 60);
    int seconds = time % 60;

    // Screen dimensions
    int row, col{};
    getmaxyx(stdscr, row, col);

    // Unholy garbage
    int values[4] = {(minutes / 10), (minutes % 10), (seconds / 10),
                     (seconds % 10)};
    std::string message[5]{};

    message[0] = numbers[values[0]].first + " " + numbers[values[1]].first +
                 "   " + numbers[values[2]].first + " " +
                 numbers[values[3]].first;
    message[1] = numbers[values[0]].second + " " + numbers[values[1]].second +
                 " # " + numbers[values[2]].second + " " +
                 numbers[values[3]].second;
    message[2] = numbers[values[0]].third + " " + numbers[values[1]].third +
                 "   " + numbers[values[2]].third + " " +
                 numbers[values[3]].third;
    message[3] = numbers[values[0]].fourth + " " + numbers[values[1]].fourth +
                 " # " + numbers[values[2]].fourth + " " +
                 numbers[values[3]].fourth;
    message[4] = numbers[values[0]].fifth + " " + numbers[values[1]].fifth +
                 "   " + numbers[values[2]].fifth + " " +
                 numbers[values[3]].fifth;

    int xOffset = (col - message[0].length()) / 2;
    int yOffset = (row - 5) / 2;

    mvprintw(0 + yOffset, xOffset, "%s", message[0].c_str());
    mvprintw(1 + yOffset, xOffset, "%s", message[1].c_str());
    mvprintw(2 + yOffset, xOffset, "%s", message[2].c_str());
    mvprintw(3 + yOffset, xOffset, "%s", message[3].c_str());
    mvprintw(4 + yOffset, xOffset, "%s", message[4].c_str());

    mvprintw(5 + yOffset, (col - session.size())/2, "%s", session.c_str());

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

    // Start ncurse
    initscr();
    curs_set(0);
    setlocale(LC_ALL, "");

    // Run through the number of sessions
    for (int session = 0; session < sessions; session++) {
        // Work Time
        for (int work = workTime; work >= 0; work--) {
            prettyPrint(work, 1, "Focused Work");
        }

        // Short Break
        if (session + 1 != sessions) {
            for (int relax = shortBreak; relax >= 0; relax--) {
                prettyPrint(relax, 1, "Short Break");
            }
        }
    }
    // Long Break
    for (int longRelax = longBreak; longRelax >= 0; longRelax--) {
        prettyPrint(longRelax, 1, "Long Break");
    }
    // Close the ncurse tui
    endwin();

    return 0;
}
