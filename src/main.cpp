#include <deque>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <utility>

#define HEAD 'A'  // '🐍'
#define BODY 'o'  // '🟩'
#define APPLE '+' // '🍎'

std::deque<std::pair<int, int>> snake;
std::vector<std::pair<int, int>> apples;
int yv = 0, xv = 1;

void input(int c) {
	switch (c) {
		case KEY_UP:
		case 'w':
			yv = -1;
			xv = 0;
			break;
		case KEY_DOWN:
		case 's':
			yv = 1;
			xv = 0;
			break;
		case KEY_RIGHT:
		case 'd':
			yv = 0;
			xv = 1;
			break;
		case KEY_LEFT:
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

	if (cx >= COLS || cy >= LINES) {
		return true;
	}

	for (auto p = snake.begin() + 1; p != snake.end(); ++p) {
		if (p->first == head.first && p->second == head.second) {
			return true;
		}
	}

	return false;
}

std::random_device dev;
std::mt19937 rng(dev());

void genApple() {
	std::uniform_int_distribution<std::mt19937::result_type> dist6x(1, COLS - 1);
	std::uniform_int_distribution<std::mt19937::result_type> dist6y(1, LINES - 1);

	// New apple
start:
	int nx = dist6x(rng);
	int ny = dist6y(rng);

	for (const auto& p : snake) {
		if (nx == p.first && ny == p.second) {
			goto start;
		}
	}

	apples.emplace_back(nx, ny);
}

int score = 0;

int main() {
begin:
	std::cout << "Which type of snake do you want to play?\n";
	std::cout << "1) Normal\n";
	std::cout << "2) Multifruit" << std::endl;
	int option = 0;
	std::cin >> option;
	if (!(option == 1 || option == 2)) {
		std::cout << "Invalid option, please retry.";
		goto begin;
	}
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	halfdelay(2);
	getmaxyx(stdscr, LINES, COLS);
	curs_set(0);

	// Add 4, one gets eaten at the begining
	snake.emplace_front(3, LINES / 2);
	snake.emplace_front(4, LINES / 2);
	snake.emplace_front(5, LINES / 2);
	snake.emplace_front(6, LINES / 2);

	for (const auto& c : snake) {
		mvaddch(c.second, c.first, 'o');
	}
	mvaddch(snake.front().second, snake.front().first, HEAD);

	genApple();

	for (const auto& apple : apples) {
		mvaddch(apple.second, apple.first, APPLE);
	}

	int ch;
	while ((ch = getch()) != 'q') {
		wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');

		input(ch);

		mvaddch(snake.back().second, snake.back().first, ' '); // Remove last seg

		const auto& last = snake.begin() + 1;
		mvaddch(last->second, last->first, BODY); // Change last one to body

		const auto& head = snake.front();

		mvaddch(head.second, head.first, HEAD); // Add head

		for (const auto& apple : apples) {
			if (head.first == apple.first && head.second == apple.second) { // Head on apple
				if (option == 2) {
					genApple();
					genApple();
				} else {
					genApple();
				}
				for (const auto& a : apples) {
					mvaddch(a.second, a.first, APPLE);
				}
				score++;
				snake.emplace_back(snake.back());
			}
		}

		if (dead()) { // Dead RIP
			break;
		}

		refresh();

		snake.pop_back();
		snake.emplace_front(snake.front().first + xv, snake.front().second + yv);
	}

	endwin();

	std::cout << "Your score is: " << score << std::endl;

	return 0;
}
