#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;


struct Target {
	Target(int h = 0, int w = 0) : h(h), w(w) {}

	int h;
	int w;
};

char space[20][20], space_fog[20][20];
const char wall_ch = '#', way_ch = ' ', fog_ch = '+', player_ch = '*';
const int size_h = sizeof(space) / sizeof(space[0]) - 1,
size_w = sizeof(space[0]) / sizeof(space[0][0]) - 1;
int key = 0, player_x = 1, player_y = 0, entrance_x, entrance_y = 0, exit_x, exit_y = 0;
bool game = true;

enum Control { STOP = 0, UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ESC = 27 };
Control ctr = STOP;


void generate_maze()
{
	srand(time(NULL));
	int target_h = 1, target_w = 1, rand_way = 10,
		up = 1, left = 2, down = 3, right = 4;
	list<Target> target;
	target.push_back(Target(target_h, target_w));

	for (int i = 0; i < size_h; i++)
		for (int j = 0; j < size_w; j++)
			space[i][j] = wall_ch;

	while (1)
	{
		if (space[target_h - 2][target_w] == way_ch || target_h - 2 < 1)
			if (space[target_h + 2][target_w] == way_ch || target_h + 2 > size_h - 1)
				if (space[target_h][target_w - 2] == way_ch || target_w - 2 < 1)
					if (space[target_h][target_w + 2] == way_ch || target_w + 2 > size_w - 1)
					{
						target.pop_back();
						if (target.empty()) break;
						target_h = target.back().h;
						target_w = target.back().w;
					}

		rand_way = rand() % 4 + 1;
		if (rand_way == up && target_h - 2 > 0 && space[target_h - 2][target_w] != way_ch)
		{
			space[target_h][target_w] = way_ch;
			space[target_h - 1][target_w] = way_ch;
			space[target_h - 2][target_w] = way_ch;
			target_h -= 2;
			target.push_back(Target(target_h, target_w));
		}

		if (rand_way == left && target_w - 2 > 0 && space[target_h][target_w - 2] != way_ch)
		{
			space[target_h][target_w] = way_ch;
			space[target_h][target_w - 1] = way_ch;
			space[target_h][target_w - 2] = way_ch;
			target_w -= 2;
			target.push_back(Target(target_h, target_w));
		}

		if (rand_way == down && target_h + 2 < size_h - 1 && space[target_h + 2][target_w] != way_ch)
		{
			space[target_h][target_w] = way_ch;
			space[target_h + 1][target_w] = way_ch;
			space[target_h + 2][target_w] = way_ch;
			target_h += 2;
			target.push_back(Target(target_h, target_w));
		}

		if (rand_way == right && target_w + 2 < size_w - 1 && space[target_h][target_w + 2] != way_ch)
		{
			space[target_h][target_w] = way_ch;
			space[target_h][target_w + 1] = way_ch;
			space[target_h][target_w + 2] = way_ch;
			target_w += 2;
			target.push_back(Target(target_h, target_w));
		}
	}

	int tmp;
	while (true) {
		tmp = rand() % (size_h - 2) + 1;
		if (space[tmp][1] == way_ch) {
			player_x = tmp;
			space[tmp][entrance_y] = way_ch;
			break;
		}
	}
	while (true) {
		tmp = rand() % (size_h - 2) + 1;
		if (space[tmp][size_w - 2] == way_ch) {
			space[tmp][size_w - 1] = way_ch;
			break;
		}
	}

}

void draw()
{
	system("cls");
	for (int i = 0; i < size_h; i++)
	{
		for (int j = 0; j < size_w; j++)
			cout << space[i][j];
		cout << endl;
	}

}

void input()
{
	if (_kbhit)
	{
		key = _getch();
		switch (key)
		{
		case UP:
			ctr = UP;
			break;
		case DOWN:
			ctr = DOWN;
			break;
		case LEFT:
			ctr = LEFT;
			break;
		case RIGHT:
			ctr = RIGHT;
			break;
		case ESC:
			game = false;

		}
	}
}

void logic()
{
	if (ctr == UP && space[player_x - 1][player_y] != wall_ch && player_x > 1) { player_x--; ctr = STOP; }
	if (ctr == DOWN && space[player_x + 1][player_y] != wall_ch && player_x < size_h) { player_x++; ctr = STOP; }
	if (ctr == LEFT && space[player_x][player_y - 1] != wall_ch && player_y > 1) { player_y--; ctr = STOP; }
	if (ctr == RIGHT && space[player_x][player_y + 1] != wall_ch && player_y < size_w) { player_y++; ctr = STOP; }

	if (player_x - 1 > 0 && player_y > 0)
		space_fog[player_x - 1][player_y - 1] = space[player_x - 1][player_y - 1];
	if (player_x - 1 > 0)
		space_fog[player_x - 1][player_y] = space[player_x - 1][player_y];
	if (player_x - 1 > 0 && player_y < size_w - 1)
		space_fog[player_x - 1][player_y + 1] = space[player_x - 1][player_y + 1];
	if (player_y > 0)
		space_fog[player_x][player_y - 1] = space[player_x][player_y - 1];
	if (player_y < size_w - 1)
		space_fog[player_x][player_y + 1] = space[player_x][player_y + 1];
	if (player_x - 1 < size_h - 1 && player_y > 0)
		space_fog[player_x + 1][player_y - 1] = space[player_x + 1][player_y - 1];
	if (player_x - 1 < size_h - 1)
		space_fog[player_x + 1][player_y] = space[player_x + 1][player_y];
	if (player_x - 1 < size_h - 1 && player_y < size_w - 1)
		space_fog[player_x + 1][player_y + 1] = space[player_x + 1][player_y + 1];

	space_fog[player_x][player_y] = player_ch;
}

int main()
{

	generate_maze();

	for (int i = 0; i < size_h; i++)
		for (int j = 0; j < size_w; j++)
		{
			if (i == 0 || j == 0 || i == size_h - 1 || j == size_w - 1) space_fog[i][j] = wall_ch;
			else space_fog[i][j] = fog_ch;
		}

	while (game)
	{
		logic();
		draw();
		input();
	}

	return 0;
}

