#ifndef EVALUATE_H_
#define EVALUATE_H_

#include "Grid.h"

class Evaluate
{
    public:
	    Evaluate();
    	int eval              (Grid&, Grid::Chip);
    private:
	    int get_points        (Grid&, Grid::Chip, int&, int&, Grid::Chip, Grid::Chip);
	    int assign_points     (Grid::Chip, Grid::Chip, int, int);
	    void eval_line_or_col (Grid&, Grid::Chip, int&, bool);
  	    void eval_line        (Grid&, Grid::Chip, int&);
   	    void eval_col         (Grid&, Grid::Chip, int&);
   	    void eval_firts_diag  (Grid&, Grid::Chip, int&);
   	    void eval_second_diag (Grid&, Grid::Chip, int&);
   	    void eval_third_diag  (Grid&, Grid::Chip, int&);
   	    void eval_forth_diag  (Grid&, Grid::Chip, int&);
};

#endif /*EVALUATE_H_*/
