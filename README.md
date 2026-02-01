<img width="273" height="283" alt="Снимок экрана 2026-01-13 в 18 52 04" src="https://github.com/user-attachments/assets/70da0899-a9d8-44ea-ab41-928c437fdc52" />

This is simple and lightweight for MacOS or Linux terminal. It is ideal for customizing your terminal or like a desktop widget. You can custom this calendar very easy. In this repository you can find 2 versions of calendar - static and interactive (with the up and down arrows for the year and the left and right arrows for the months). If you want to stop interactive calendar you should tap Ctrl+C.

### Attention:
Performance was tested on macos 26 tahoe and arch linux. Performance on other distributions is not guaranteed.

## You need this packages to run this script:

**Arch:** base-devel

**Debian:** build-essential

**Fedora:** gcc-c++

### Installation of static calendar:

```
git clone https://github.com/RomanLivik/terminal-calendar.git
cd terminal-calendar
g++ calendar.cpp -o calendar
./calendar
```

### Installation of interactive calendar:

```
git clone https://github.com/RomanLivik/terminal-calendar.git
cd terminal-calendar
g++ terminal-calendar.cpp -o interactive-calendar
./interactive-calendar
```
