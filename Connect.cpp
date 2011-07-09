#include "Connect.h"

Connect::Connect(Grid::Chip colourp) 
{
	colour = colourp;
}

/* Places chip on grid on the position decided by alpha-beta */
int Connect::place_chip(Grid& Grid){
	int ret = alphaBeta(Grid, 0, colour, -INIT, INIT);
	return ret;
}

/* Alpha-Beta Prunning algorithm */
int Connect::alphaBeta(Grid& grid, int depth, Grid::Chip turn, int alpha, int beta)
{
	if (depth > 0)
		turn = (Grid::Chip)((turn + 1) % 2);
	
	if (depth >= MAX_DEPTH)
		return evaluate.eval(grid, turn);
	
	int chosen_move;
	
	for(int i = 0; i < Grid::N; i++) {
		int ret = grid.place_chip(turn, i);
		/* if placing a chip on a columns is illegal, try another column */
		if (ret == -1)
			continue;
		
		int curr_alpha = -alphaBeta(grid, depth + 1, turn, -beta, -alpha);
		if(curr_alpha > alpha) {
			alpha = curr_alpha;
			chosen_move = i;
		}
		
		grid.remove_chip(i);
		
		if (beta <= alpha)
			break;
	}
	
	if (depth == 0) {
		grid.place_chip(colour, chosen_move);
		return chosen_move;
	}

	return alpha;
}

