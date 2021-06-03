#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Target {
	Target (int h = 0, int w = 0) : h(h), w(w) {}
	
	int h;
	int w;
};

int main()
{
	srand(time(NULL));
	
	char space[40][40], wall_ch = '#', way_ch = ' ';
    	int size_h = sizeof(space) / sizeof(space[0]) - 1,
    	size_w = sizeof(space[0]) / sizeof(space[0][0]) - 1,
	target_h = 1, target_w = 1, rand_way = 10,
	up = 1, left = 2, down = 3, right = 4;

	list<Target> target;
	target.push_back(Target(target_h, target_w));

	for(int i = 0; i < size_h; i++)
		for(int j = 0; j < size_w; j++)
			space[i][j] = wall_ch;

	space[1][0] = way_ch;
	space[size_h - 2][size_w - 1] = way_ch;
	
	while(1)
	{
		if(space[target_h - 2][target_w] == way_ch || target_h - 2 < 1)
			if(space[target_h + 2][target_w] == way_ch || target_h + 2 > size_h - 1)
				if(space[target_h][target_w - 2] == way_ch || target_w - 2 < 1) 
					if(space[target_h][target_w + 2] == way_ch || target_w + 2 > size_w - 1)
					{
						target.pop_back();
						if(target.empty()) break;
						target_h = target.back().h;
						target_w = target.back().w;
					}
	
		rand_way = rand() % 4 + 1;
		if(rand_way == up && target_h - 2 > 0 && space[target_h - 2][target_w] != way_ch)
			{
				space[target_h][target_w] = way_ch;
				space[target_h - 1][target_w] = way_ch;
				space[target_h - 2][target_w] = way_ch;
				target_h -= 2;
				target.push_back(Target(target_h, target_w));
			}

		if(rand_way == left && target_w - 2 > 0 && space[target_h][target_w - 2] != way_ch)
			{
				space[target_h][target_w] = way_ch;
				space[target_h][target_w - 1] = way_ch;
				space[target_h][target_w - 2] = way_ch;
				target_w -= 2;
				target.push_back(Target(target_h, target_w));
			}

		if(rand_way == down && target_h + 2 < size_h - 1 && space[target_h + 2][target_w] != way_ch)
			{
				space[target_h][target_w] = way_ch;
				space[target_h + 1][target_w] = way_ch;
				space[target_h + 2][target_w] = way_ch;
				target_h += 2;
				target.push_back(Target(target_h, target_w));
			}

		if(rand_way == right && target_w + 2 < size_w - 1 && space[target_h][target_w + 2] != way_ch)
			{
				space[target_h][target_w] = way_ch;
				space[target_h][target_w + 1] = way_ch;
				space[target_h][target_w + 2] = way_ch;
				target_w += 2;
				target.push_back(Target(target_h, target_w));
			}
	}

	for(int i = 0; i < size_h; i++)
	{
		for(int j = 0; j < size_w; j++)
			cout << space[i][j];
		cout << endl;
	}

	return 0;
}
