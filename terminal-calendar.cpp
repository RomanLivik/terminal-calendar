#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <termios.h>
#include <unistd.h>

using namespace std;

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

void print_calendar(int year, int month) {
    
    cout << "\033[H\033[2J\033[3J";

    struct tm first_day_tm = {0};
    first_day_tm.tm_year = year - 1900;
    first_day_tm.tm_mon = month - 1;
    first_day_tm.tm_mday = 1;
    mktime(&first_day_tm);

    int first_day = (first_day_tm.tm_wday + 6) % 7;
    int days_in_month = getDaysInMonth(month, year);

    time_t t = time(0);
    struct tm* now = localtime(&t);
    int real_day = now->tm_mday;
    int real_month = now->tm_mon + 1;
    int real_year = now->tm_year + 1900;

    vector<string> months = {"", "January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};

    string RED = "\033[31m";
    string RESET = "\033[0m";
    string BG_WHITE = "\033[47m\033[30m"; 

    cout << RED << "╭──────────────────────────────────╮" << endl;
    cout << "│             Calendar             │" << endl;
    cout << "│                                  │" << endl;

    string title = months[month] + " " + to_string(year);
    int total_width = 34;
    int padding = (total_width - title.length()) / 2;
    cout << "│" << string(padding, ' ') << title << string(total_width - padding - title.length(), ' ') << "│" << endl;

    cout << "├──────────────────────────────────┤" << endl;
    cout << "║Mon ║Tue ║Wed ║Thu ║Fri ║Sat ║Sun ║" << endl;
    cout << "├╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┤" << endl;

    int day = 1;
    for (int week = 0; week < 6; ++week) {
        cout << "║";
        for (int col = 0; col < 7; ++col) {
            int pos_day = week * 7 + col - first_day + 1;

            if (pos_day >= 1 && pos_day <= days_in_month) {
                if (pos_day == real_day && month == real_month && year == real_year) {
                    printf(" %s%2d%s %s║", BG_WHITE.c_str(), pos_day, RESET.c_str(), RED.c_str());
                } else {
                    printf("%s %2d %s║", RESET.c_str(), pos_day, RED.c_str());
                }
                day++;
            } else {
                cout << "    ║";
            }
        }
        cout << endl;
        cout << "├╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┤" << endl;
        if (day > days_in_month && week >= 4) break;
    }
    cout << "╰──────────────────────────────────╯" << RESET << endl;
    cout << "  Arrows: Navigate | Q: Exit" << endl;
}

int main() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    int current_year = now->tm_year + 1900;
    int current_month = now->tm_mon + 1;

    while (true) {
        print_calendar(current_year, current_month);

        int c = getch();

        if (c == 'q' || c == 'Q') break;

        if (c == 27) { 
            getch(); 
            switch (getch()) {
                case 'A': 
                    current_year++;
                    break;
                case 'B': 
                    current_year--;
                    break;
                case 'C': 
                    current_month++;
                    if (current_month > 12) {
                        current_month = 1;
                        current_year++;
                    }
                    break;
                case 'D': 
                    current_month--;
                    if (current_month < 1) {
                        current_month = 12;
                        current_year--;
                    }
                    break;
            }
        }
    }

    return 0;
}
