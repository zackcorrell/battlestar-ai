#ifndef BOARD2_H
#define BOARD2_H

class Board12
{
	int b[10][10];
public:
	Board12()
	{
		for(int i = 0; i < 10; i++)
			for(int j = 0; j < 10; j++)
				b[i][j] = 0;
	}
	int at(int x, int y)
	{
		return b[x][y];
	}
	void set(int x, int y, int s)
	{
		b[x][y] = s;
	}
	void print()
	{
		for(int i = 0; i < 10; i++)
			printf("%d%d%d%d%d%d%d%d%d%d\n", b[i][0], b[i][1], b[i][2], b[i][3], b[i][4], b[i][5], b[i][6], b[i][7], b[i][8], b[i][9]);
	}
};

#endif