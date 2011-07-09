#ifndef Grid_H_
#define Grid_H_

class Grid
{
    public:
	    static const int N = 9;
	    enum Chip {CHIP_RED, CHIP_GREEN, CHIP_NONE, CHIP_INVALID};
	
    private:
	    Chip grid[N][N];
	    int chips_on_col[N];
	
    public:
	    Grid();
	    int place_chip   (Chip, int);
	    int remove_chip  (int);
	    Chip get_cell    (int, int);
	    int get_next_row (int);
	    void init        ();
};

#endif /*Grid_H_*/
