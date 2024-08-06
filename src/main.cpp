#include <deque>
#include <ncurses.h>
#include <utility>

#define HEAD 'o' // '🐍'
#define BODY 'A' // '🟩'
#define FRUIT '+' // '🍎'

int y, x;

std::deque<std::pair<int, int>> snake;

int main() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	halfdelay(2);
	getmaxyx(stdscr, y, x);

	snake.emplace_back(3, y / 2);

	char ch;
	while ((ch = getch()) != 'q') {
		wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');

		for (const auto& part : snake) {
			mvaddch(part.second, part.first, BODY);
		}

		refresh();
	}

	endwin();

	return 0;
}
