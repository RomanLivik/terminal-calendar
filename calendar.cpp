#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

const string RED = "\033[31m";
const string RESET = "\033[0m";
const string BG_WHITE = "\033[47m"; 
const string BLACK_TEXT = "\033[30m"; 

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

void print_calendar(int year, int month) {
    struct tm first_day_tm = {0};
    first_day_tm.tm_year = year - 1900;
    first_day_tm.tm_mon = month - 1;
    first_day_tm.tm_mday = 1;
    mktime(&first_day_tm);

    int first_day = (first_day_tm.tm_wday + 6) % 7;
    int days_in_month = getDaysInMonth(month, year);

    time_t t = time(0);
    struct tm* now = localtime(&t);
    int current_day = (now->tm_mday && (now->tm_mon + 1 == month) && (now->tm_year + 1900 == year)) ? now->tm_mday : -1;

    vector<string> months = {"", "January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};

    cout << RED << "╭──────────────────────────────────╮" << endl;
    cout << "│             Calendar             │" << endl;
    cout << "│                                  │" << endl;

    string title = months[month] + " " + to_string(year);
    int padding = (34 - title.length()) / 2;
    cout << "│" << string(padding, ' ') << title << string(34 - padding - title.length(), ' ') << "│" << endl;

    cout << "├──────────────────────────────────┤" << endl;
    
    cout << "║Mon ║Tue ║Wed ║Thu ║Fri ║Sat ║Sun ║" << endl;
    cout << "├╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌┤" << endl;

    int day = 1;
    for (int week = 0; week < 6; ++week) {
        cout << "║";
        for (int col = 0; col < 7; ++col) {
            int pos_day = week * 7 + col - first_day + 1;

            if (pos_day >= 1 && pos_day <= days_in_month) {
                if (pos_day == current_day) {
                    cout << " " << BG_WHITE << BLACK_TEXT << (pos_day < 10 ? " " : "") << pos_day << RESET << RED << " ║";
                } else {
                    cout << RESET << " " << (pos_day < 10 ? " " : "") << pos_day << " " << RED << "║";
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
}

int main() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    
    print_calendar(now->tm_year + 1900, now->tm_mon + 1);
    
    return 0;
}
