import datetime
import sys

def print_calendar(year, month):
    first_day = datetime.date(year, month, 1).weekday()
    days_in_month = (datetime.date(year, month+1, 1) - datetime.date(year, month, 1)).days
    today = datetime.datetime.now()
    current_day = today.day if today.month == month and today.year == year else None
    
    months = ['', 'January', 'February', 'March', 'April', 'Мay', 'June',
              'July', 'Аugust', 'September', 'Оctober', 'November', 'December']
    #menu
    print("\033[31m╭\033[31m" + "─\033[31m"*34 + "╮\033[31m")
    print("│             Calendar             │\033[31m")
    print("│\033[31m" + " "*34 + "│\033[31m")
    print(f"│          {months[month]} {year}            │\033[31m")
    print("├\033[31m" + "─\033[31m"*34 + "┤\033[31m")
    #days
    sys.stdout.write("\033[31m")
    print("║Mon ║Tue ║Wed ║Thu ║Fri ║Sat ║Sun ║")
    print("├\033[31m" + "╌\033[31m"*34 + "┤\033[31m")
    sys.stdout.write("\033[31m")
    
    day = 1
    for week in range(6):
        line = "\033[31m║\33[31m"
        
        for col in range(7):
            pos_day = week * 7 + col - first_day + 1
            
            if 1 <= pos_day <= days_in_month:
                if pos_day == current_day:
                    line += f" \033[47m{day:2d}\033[0m \033[31m║\033[31m"
                else:
                    sys.stdout.write("\033[0m")
                    line += f" {day:2d} ║\033[31m"
                    sys.stdout.write("\033[0m")
                day += 1
            else:
                line += "    ║\033[31m"
        
        print(line)
        print("├\033[31m" + "╌\033[31m"*34 + "┤\033[31m")
    
    print("╰\033[31m" + "─\033[31m"*34 + "╯\033[31m")

today = datetime.datetime.now()
print_calendar(today.year, today.month)
