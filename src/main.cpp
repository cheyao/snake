#include <deque>
#include <ncurses.h>
#include <random>
#include <utility>

#define HEAD 'A'  // '🐍'
#define BODY 'o'  // '🟩'
#define APPLE '+' // '🍎'

int y, x;

std::deque<std::pair<int, int>> snake;
std::pair<int, int> apple;
int yv = 0, xv = 1;

void input(char c) {
	switch (c) {
		case 'w':
			yv = -1;
			xv = 0;
			break;
		case 's':
			yv = 1;
			xv = 0;
			break;
		case 'd':
			yv = 0;
			xv = 1;
			break;
		case 'a':
			yv = 0;
			xv = -1;
			break;
	}
}

bool dead() {
	const auto& head = snake.front();
	const auto& cx = head.first;
	const auto& cy = head.second;

	if (cx == 0 || cy == 0) {
		return true;
	}

	if (cx == x || cy == y) {
		return true;
	}

	return false;
}

void genApple(std::mt19937 rng, std::uniform_int_distribution<std::mt19937::result_type> xr, std::uniform_int_distribution<std::mt19937::result_type> yr) {
	// New apple
	int nx = xr(rng);
	int ny = yr(rng);

	apple = std::make_pair(nx, ny);
}

int main() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	halfdelay(2);
	getmaxyx(stdscr, y, x);
	curs_set(0);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6x(1, x - 1);
	std::uniform_int_distribution<std::mt19937::result_type> dist6y(1, y - 1);

	snake.emplace_front(3, y / 2);
	snake.emplace_front(4, y / 2);
	snake.emplace_front(5, y / 2);
	snake.emplace_front(6, y / 2);

	for (const auto& c : snake) {
		mvaddch(c.second, c.first, 'o');
	}
	mvaddch(snake.front().second, snake.front().first, HEAD);

	wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');

	genApple(rng, dist6x, dist6y);
	mvaddch(apple.second, apple.first, APPLE);

	char ch;
	while ((ch = getch()) != 'q') {
		input(ch);

		mvaddch(snake.back().second, snake.back().first, ' ');
		snake.pop_back();

		const auto last = snake.begin() + 1;
		mvaddch(last->second, last->first, BODY);

		mvaddch(snake.front().second, snake.front().first, HEAD);
		snake.emplace_front(snake.front().first + xv, snake.front().second + yv);

		if (dead()) {
			break;
		}

		refresh();
	}

	endwin();

	return 0;
}
