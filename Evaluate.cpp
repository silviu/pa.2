#include "Evaluate.h"

Evaluate::Evaluate(){}

/* "eval" is called in the alpha beta algorithm*/
int Evaluate::eval(Grid& grid, Grid::Chip player)
{
	int points = 0;
	
	eval_line(grid, player, points);
	eval_col (grid, player, points);
	
	eval_firts_diag	 (grid, player, points);
	eval_second_diag (grid, player, points);
	
	eval_third_diag  (grid, player, points);
	eval_forth_diag  (grid, player, points);

	return points;
}

/* Calculates points for chips on line and column*/
void Evaluate::eval_line_or_col(Grid& grid, Grid::Chip player, int &points, bool line)
{
	for(int i = 0; i < Grid::N; i++) {
		Grid::Chip last_chip = Grid::CHIP_INVALID;
		int connected_chips = 0;
		int connected_empty = 0;
		for(int j = 0; j <= Grid::N; j++) {
			Grid::Chip curr_chip = Grid::CHIP_INVALID;
			if (line)
				curr_chip = grid.get_cell(i, j);
			else 
				curr_chip = grid.get_cell(j, i);
			points += get_points(grid, curr_chip, connected_chips, connected_empty, last_chip, player);
			last_chip = curr_chip;
		}
	}
}

void Evaluate::eval_line(Grid& grid, Grid::Chip player, int &points)
{
	eval_line_or_col(grid, player, points, true);
}

void Evaluate::eval_col(Grid& grid, Grid::Chip player, int &points)
{
	eval_line_or_col(grid, player, points, false);
}


/*Calculates points for the upper left half of the first diagonal*/
void Evaluate::eval_firts_diag(Grid& grid, Grid::Chip player, int &points)
{
	for(int i = 0; i < Grid::N; i++) {
		Grid::Chip last_chip = Grid::CHIP_INVALID;
		int connected_chips = 0;
		int connected_empty = 0;
		for(int j = i, k = 0; j <= Grid::N && k <= Grid::N; j++, k++) {
			Grid::Chip curr_chip = grid.get_cell(j, k);
			points += get_points(grid, curr_chip, connected_chips, connected_empty, last_chip, player);
			last_chip = curr_chip;
		}
	}
}

/*Calculates points for the lower half of the first diagonal*/
void Evaluate::eval_second_diag(Grid& grid, Grid::Chip player, int &points) 
{
	for(int i = 1; i < Grid::N; i++) {
		Grid::Chip last_chip = Grid::CHIP_INVALID;
		int connected_chips = 0;
		int connected_empty = 0;
		for(int j = 0, k = i; j <= Grid::N && k <= Grid::N; j++, k++) {
			Grid::Chip curr_chip = grid.get_cell(j, k);
			points += get_points(grid, curr_chip, connected_chips, connected_empty, last_chip, player);
			last_chip = curr_chip;
		}
	}	
}

/*Calculates points for the upper half of the second diagonal*/
void Evaluate::eval_third_diag(Grid& grid, Grid::Chip player, int &points)
{
	for(int i = Grid::N-1; i > 0; i--) {
		Grid::Chip last_chip = Grid::CHIP_INVALID;
		int connected_chips = 0;
		int connected_empty = 0;
		for(int j = i, k = 0; j >= 0 && k <= Grid::N; j--, k++) {
			Grid::Chip curr_chip = grid.get_cell(j, k);
			points += get_points(grid, curr_chip, connected_chips, connected_empty, last_chip, player);
			last_chip = curr_chip;
		}
	}
}

/*Calculates points for the lower half of the second diagonal*/
void Evaluate::eval_forth_diag(Grid& grid, Grid::Chip player, int &points) 
{
	for(int i = 1; i < Grid::N; i++) {
		Grid::Chip last_chip = Grid::CHIP_INVALID;
		int connected_chips = 0;
		int	connected_empty = 0;
		for(int j = Grid::N-1, k = i; j >= 0 && k <= Grid::N; j--, k++) {
			Grid::Chip curr_chip = grid.get_cell(j, k);
			points += get_points(grid, curr_chip, connected_chips, connected_empty, last_chip, player);
			last_chip = curr_chip;
		}
	}
}

int Evaluate::get_points(Grid& grid, Grid::Chip curr_chip, int& connected_chips, int& connected_empty, Grid::Chip last_chip, Grid::Chip player)
{
	int points = 0;
	
	/* If current chip is a valid chip from a player*/
	if (curr_chip == Grid::CHIP_RED || curr_chip == Grid::CHIP_GREEN) {
		Grid::Chip oponent = (Grid::Chip)((curr_chip + 1) % 2);
		if (last_chip == oponent) {
			/* Ended a counting for same chip color*/
			points += assign_points(oponent, player, connected_chips, connected_empty);
			connected_chips = 1;
			connected_empty = 0;
		}
		else if (last_chip == curr_chip) {
			/* Continue counting for same chip color */
			connected_chips++;
		}
		else if (last_chip == Grid::CHIP_NONE) {
			/* Starting to count for same chip color */
			connected_chips = 1;
			connected_empty = 1;
		}
		else if (last_chip == Grid::CHIP_INVALID) {
			connected_chips = 1;
			connected_empty = 0;
		}
	}
	/* If current place is an empty Chip place */
	else if (curr_chip == Grid::CHIP_NONE) {
		if(last_chip == Grid::CHIP_RED || last_chip == Grid::CHIP_GREEN) {
			/* End for counting for same chip color */
			connected_empty++;
			points += assign_points(last_chip, player, connected_chips, connected_empty);
			connected_chips = 0;
		}
		else if(last_chip == Grid::CHIP_NONE || Grid::CHIP_INVALID) {
			/* There were no repeating chips */
			connected_chips = 0;
			connected_empty = 1;
		}
	}
	/* If chip is not on grid */
	else if(curr_chip == Grid::CHIP_INVALID) {
		if(last_chip == Grid::CHIP_RED || last_chip == Grid::CHIP_GREEN) {
			/* End for counting for same chip color */
			points += assign_points(last_chip, player, connected_chips, connected_empty);
			connected_chips = 0;
		}
		else if(last_chip == Grid::CHIP_NONE || Grid::CHIP_INVALID) {
			/* There were no repeating chips */
			connected_chips = 0;
			connected_empty = 0;
		}
	}
	
	return points;
}

/* Decides how many points to return on number of connected chips */
int Evaluate::assign_points(Grid::Chip curr_turn, Grid::Chip player, int connected_chips, int connected_empty)
{
	int points;
	if (connected_chips < 2)
		points = 0;
	else if (connected_chips == 2)
		points = 10 * connected_empty; 
	else if (connected_chips == 3)
		points = 100 * connected_empty;
	else
		points = 1000;
	
	if (curr_turn == player)
		return points;
	else
		return -points;
}

