#include "Grid.h"
#include "Connect.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

enum {OPONENT = 0, ME = 1};

void check_terminal_state(int n)
{
	switch(n) {
		case 10:
			exit(EXIT_SUCCESS);
			break;
		case 11:
			exit(EXIT_FAILURE);
			break;
		case 12:
			exit(EXIT_SUCCESS);
			break;
		default:
			return;
			break;
	}
}

int main(int argc, char** argv)
{
	Connect* me = new Connect(Grid::CHIP_GREEN);

	Grid grid;
	int player = OPONENT;
	
	int magic_number;
	cin >> magic_number;
	int oponent_move;
	
	while (1) 
	{
		if (player == OPONENT) {
			cin >> oponent_move;
			check_terminal_state(oponent_move);
			grid.place_chip(Grid::CHIP_RED, oponent_move);
		}
		else {
			cout << me->place_chip(grid) << endl;
			cout.flush();
		}
		player = (player + 1) % 2;
	}
	
	return 0;
}

