#include "Core.h"
#include "stdafx.h"


Core::Core()
{
	memset(m_grid,0,sizeof(m_grid));
}

int Core::TraceBack(int pos, int number, int& count, int result[][CELL],bool isSolve)
{
	if (pos == CELL)
	{
		CopySudoku(result[count],m_grid);
		count++;
		if (count == number)
		{
			return 1;
		}
	}
	else
	{
		int x = pos / GRIDSIZE;
		int y = pos % GRIDSIZE;

		int base = x / 3 * 3;
		for (int i = 0; i < GRIDSIZE; i++)         // try to fill the pos from 1-9
		{
			m_grid[x][y] = (i + base) % GRIDSIZE + 1;
			if (IsValid(pos,isSolve))               // if the number is valid
			{
				if (TraceBack(pos + 1, number, count, result, isSolve) == 1)       // try to fill next pos
				{
					return 1;
				}
			}
			m_grid[x][y] = UNKNOWN;
		}
	}
	return 0;
}

bool Core::TraceBackSolve(int pos) throw (IllegalNumberException)
{
	if (pos == CELL)
	{
		return true;
	}
	int x = pos / GRIDSIZE;
	int y = pos % GRIDSIZE;

	if (m_grid[x][y] == UNKNOWN)
	{
		for (int i = 1; i <= GRIDSIZE; i++)
		{
			m_grid[x][y] = i;
			if (IsValid(pos, true))
			{
				if (TraceBackSolve(pos + 1))
				{
					return true;
				}
			}
			m_grid[x][y] = UNKNOWN;
		}
	}
	else if (m_grid[x][y] > GRIDSIZE || m_grid[x][y] < UNKNOWN)
	{
		throw IllegalNumberException("The sudoku has illegal number or the file type is wrong.\n\n");
	}
	else
	{
		if (TraceBackSolve(pos + 1))
		{
			return true;
		}
	}

	return false;
}

bool Core::solve(int puzzle[CELL], int solution[CELL]) throw (NoSolutionException,IllegalNumberException)
{
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
		{
			m_grid[i][j] = puzzle[i*GRIDSIZE + j];
		}
	}

if (TraceBackSolve(0))
{
	CopySudoku(solution, m_grid);
	return true;
}
throw NoSolutionException("The sudoku has no solution.\n\n");
}

bool Core::IsValid(int pos, bool isSolve)
{
	int x = pos / GRIDSIZE;
	int y = pos % GRIDSIZE;
	int z = x / SQRTSIZE * SQRTSIZE + y / SQRTSIZE;
	int leftTop = z / SQRTSIZE * GRIDSIZE * SQRTSIZE + (z % SQRTSIZE) * SQRTSIZE;
	int rightDown = leftTop + (2 * GRIDSIZE + SQRTSIZE - 1);
	int bound = isSolve ? GRIDSIZE : y;
	// check row
	for (int i = 0; i < bound; i++)
	{
		if (i == y)
		{
			continue;
		}
		if (m_grid[x][i] == m_grid[x][y])
		{
			return false;
		}
	}
	// check column
	bound = isSolve ? GRIDSIZE : x;
	for (int i = 0; i < bound; i++)
	{
		if (i == x)
		{
			continue;
		}
		if (m_grid[i][y] == m_grid[x][y])
		{
			return false;
		}
	}
	// check box
	int bound_x = leftTop / GRIDSIZE;
	int bound_y = leftTop % GRIDSIZE;
	if (bound_x % 3 != 0 || bound_y % 3 != 0 || bound_x > GRIDSIZE - 3 || bound_y > GRIDSIZE - 3)
	{
		cout << "error" << endl;
		exit(0);
	}
	for (int i = bound_x; i < (bound_x + 3); i++)
	{
		for (int j = bound_y; j < (bound_y + 3); j++)
		{
			if (i == x && j == y)
			{
				if (isSolve)
				{
					continue;
				}
				else
				{
					return true;
				}
			}
			if (m_grid[i][j] == m_grid[x][y])
			{
				return false;
			}
		}
	}
	return true;
}

void Core::generate(int number, int result[][CELL]) throw (NumberOutOfBoundException)
{
	if (number < 1 || number > MAX_C)
	{
		throw NumberOutOfBoundException("The number after -c is not in the range.\n\n");
	}
	int count = 0;
	TraceBack(0, number, count, result, false);
}

void Core::generate(int number, int mode, int result[][CELL]) throw(NumberOutOfBoundException,ModeException)   //-n -m
{
	if (number < 1 || number > MAX_N)
	{
		throw NumberOutOfBoundException("The number after -n is not in the range.\n\n");
	}

	if ((mode != 1) && (mode != 2) && (mode != 3))
	{
		throw ModeException("The mode is not correct.\n\n");	
	}

	int reduce;
	int empty;
	switch(mode)
	{
	case EASY:
		reduce = 33 + rand() % 8;
		break;
	case MIDDLE:
		reduce = 25 + rand() % 8;
		break;
	case HARD:
		reduce = 17 + rand() % 8;
		break;
	default:
		break;
	}
	empty = CELL - reduce;
	cout << empty << " " << reduce << endl;
	generate(number,result);

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < empty; j++)
		{
			int dig = rand() % CELL;
			while (result[i][dig] == UNKNOWN)
			{
				dig = rand() % CELL;
			}
			result[i][dig] = 0;
		}
	}
}

void Core::generate(int number, int lower, int upper, bool unique, int result[][CELL]) throw (NumberOutOfBoundException)  //-n -r (-u)
{
	if ((number < 1) || (number > MAX_N))
	{
		throw NumberOutOfBoundException("The number after -n is not in the range.\n\n");
	}

	if (((upper > EMPTY_UPPER) || (upper < EMPTY_LOWER))
		|| ((lower > EMPTY_UPPER) || (lower < EMPTY_LOWER)))
	{
		throw NumberOutOfBoundException("The number after -r is not in the range.\n\n");
	}
	if((lower > upper))
	{
		throw NumberOutOfBoundException("The range after -r is not correct.\n\n");
	}
	int empty;
	empty = (upper == lower) ? upper : (rand() % (upper - lower + 1) + lower);
	generate(number,result);

	stack<int> posi;
//	int grid[GRIDSIZE][GRIDSIZE];
	for (int i = 0; i < number; i++)
	{
		//int count = 0;
		/*if (unique)
		{
			for (int col = 0; col < GRIDSIZE; col++)
			{
				for (int row = 0; row < GRIDSIZE; row++)
				{
					m_grid[col][row] = result[i][col*GRIDSIZE + row];
					grid[col][row] = result[i][col*GRIDSIZE + row];	
				}
			}

			DigPos(empty, count, result[i],posi,-1,grid);
			CopySudoku(result[i], grid);
			while (posi.size())
			{
				posi.pop();
			}
		}*/
		if (unique)
		{
			while (true)
			{
				for (int col = 0; col < GRIDSIZE; col++)
				{
					for (int row = 0; row < GRIDSIZE; row++)
					{
						m_grid[col][row] = result[i][col*GRIDSIZE + row];
					}
				}

				int temp;
				for (int j = 0; j < empty; j++)
				{
					temp = rand() % CELL;
					while (m_grid[temp / GRIDSIZE][temp % GRIDSIZE] == 0)
					{
						temp = (temp + 10) % CELL;
					}
					m_grid[temp / GRIDSIZE][temp % GRIDSIZE] = 0;
				}
				int tot = 0;
				int ans = 0;
				if (!IsSingleSolution(tot, ans))
				{
					CopySudoku(result[i], m_grid);
					break;
				}
			}
		}

		else
		{
			for (int j = 0; j < empty; j++)
			{
				int dig = rand() % CELL;
				while (result[i][dig] == 0)
				{
					dig = (dig + 19) % CELL;
				}
				result[i][dig] = 0;
			}
		}
		
	}
}

bool Core::IsSingleSolution(int tot, int& ans)
{
	if (tot == GRIDSIZE * GRIDSIZE) {
		ans++;
		return true;
	}
	else {
		int x = tot / GRIDSIZE;
		int y = tot % GRIDSIZE;

		if (m_grid[x][y] == UNKNOWN) {
			for (int i = 1; i <= 9; i++) {
				m_grid[x][y] = i;
				if (IsValid(tot,true)) {
					if (IsSingleSolution(tot + 1, ans)) {
						if (ans > 1)
						{
							return true;
						}
						continue;
					}
				}
			}
			m_grid[x][y] = UNKNOWN;
		}
		else {
			return IsSingleSolution(tot + 1, ans);
		}
	}
	return false;
}

void Core::CopySudoku(int result[CELL], int temp[GRIDSIZE][GRIDSIZE])
{
	for (int i = 0; i < CELL; i++)
	{
		result[i] = temp[i / GRIDSIZE][i%GRIDSIZE];
	}
}