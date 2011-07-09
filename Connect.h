#ifndef CONNECT_H_
#define CONNECT_H_

#include "Grid.h"
#include "Evaluate.h"

#define INIT 999999999
#define MAX_DEPTH 5

class Connect
{
    private:
    	Evaluate    evaluate;
    	Grid::Chip  colour;
    public:
    	Connect         (Grid::Chip);
    	int place_chip  (Grid&);
    	int alphaBeta   (Grid&, int, Grid::Chip, int, int);
};

#endif /*CONNECT_H_*/
