#include "Grid.h"

Grid::Grid()
{
	init();
}

/* Init matrix with CHIP_NONE and chips_on_col with 0 */
void Grid::init()
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			grid[i][j] = CHIP_NONE;
	
	for(int i = 0; i < N; i++)
		chips_on_col[i] = 0;
}

/* Places a chip of the "player" on the "column" */
int Grid::place_chip(Chip player, int column)
{
	if (column > N - 1 || grid[0][column] != CHIP_NONE)
		return -1;
	
	int nextRow = get_next_row(column);
	grid[nextRow][column] = player;
	
	chips_on_col[column]++;
	
	return column;
}

/* Rmoves a chip from a column */
int Grid::remove_chip(int column)
{
	int lastRow = get_next_row(column) + 1;
	grid[lastRow][column] = CHIP_NONE;
	
	chips_on_col[column]--;
	return column;
}

/* Get Chip from a cell in the matrix */
Grid::Chip Grid::get_cell(int row, int column)
{
	if(row > N - 1 || column > N - 1)
		return CHIP_INVALID;
	return grid[row][column];
}

int Grid::get_next_row(int column)
{
	return N - chips_on_col[column] - 1;
}

