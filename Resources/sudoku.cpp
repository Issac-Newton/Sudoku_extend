#include "stdafx.h"
#include <assert.h>
#include <time.h>
int resultC[MAX_C][CELL];
int resultN[MAX_N][CELL];
int resultS[MAX_S][CELL];

void output(int number, int mode, FILE* ans);
void help();
int main(int argc, char** argv)
{
	int COUNT = 0;
	Handler handler;
	Core core;
	try
	{
		switch (handler.CheckCmd(argc, argv))
		{
		case ERROR:
			//
			cout << "ERROR" << endl;
			break;
		case C_CMD:
			cout << "-c " << handler.GetNumberC() << endl;
			FILE* ans;
			core.generate(handler.GetNumberC(), resultC);
			freopen_s(&ans, "sudoku.txt", "w", stdout);
			assert(ans != NULL);
			output(1, handler.GetNumberC(), ans);
			fclose(stdout);
			break;
		case S_CMD:
			cout << "-s " << handler.GetPath() << endl;
			int puzzle[CELL];
			FILE* file_in;
			FILE* file_out;
			freopen_s(&file_in, argv[2], "r", stdin);

			while (true)
			{
				if (fscanf_s(file_in,"%d",&puzzle[0]) == EOF)
				{
					break;
				}
				for (int i = 1; i < CELL; i++)
				{
					fscanf_s(file_in, "%d", &puzzle[i]);
				}

				core.solve(puzzle, resultS[COUNT]);
				COUNT++;
			}
			freopen_s(&file_out,"sudoku.txt","w",stdout);
			output(3, COUNT, file_out);
			break;
		case NM_CMD:
			cout << "-n -m " << handler.GetNumberN() << " " << handler.GetMode() << endl;	
			core.generate(handler.GetNumberN(), handler.GetMode(), resultN);
			freopen_s(&ans, "sudoku.txt", "w", stdout);
			assert(ans != NULL);
			output(2, handler.GetNumberN(), ans);
			fclose(stdout);
			fclose(ans);

			break;
		case NR_CMD:
			cout << "-n -r " << handler.GetNumberN() << " " << handler.GetLower() << "~" << handler.GetUpper() << endl;

			core.generate(handler.GetNumberN(), handler.GetLower(), handler.GetUpper(), handler.GetUnique(), resultN);
			freopen_s(&ans,"sudoku.txt","w",stdout);
			output(handler.GetNumberN(),2,ans);
			break;

		case NU_CMD:
			cout << "-n -u " << handler.GetNumberN() << endl;
			core.generate(handler.GetNumberN(),20,40,true,resultN);
			freopen_s(&ans, "sudoku.txt", "w", stdout);
			assert(ans != NULL);
			output(2, handler.GetNumberN(), ans);
			fclose(stdout);
			fclose(ans);
			break;

		case NRU_CMD:
			cout << "-n -r -u " << handler.GetNumberN() << " " << handler.GetLower() << "~" << handler.GetUpper() << endl;
			core.generate(handler.GetNumberN(), handler.GetLower(), handler.GetUpper(), handler.GetUnique(), resultN);
			freopen_s(&ans, "sudoku.txt", "w", stdout);
			assert(ans != NULL);
			output(2, handler.GetNumberN(), ans);
			break;

		default:
			cout << "ERROR2" << endl;
			break;
		}
	}
	catch (ModeException& ME)
	{
		cout << ME.m_msg;
		help();
		return 1;
	}
	catch (NoSolutionException& NSE)
	{
		cout << NSE.m_msg;
		help();
		return 1;
	}
	catch (IllegalNumberException& INE)
	{
		cout << INE.m_msg;
		help();
		return 1;
	}
	catch (NumberOutOfBoundException& NOB)
	{
		cout << NOB.m_msg;
		help();
		return 1;
	}
	catch (IllegalCharException& IC)
	{
		cout << IC.m_msg;
		help();
		return 1;
	}
	catch (ParametersNumberException& PN)
	{
		cout << PN.m_msg;
		help();
		return 1;
	}
	catch (FileNotExistException& FNE)
	{
		cout << FNE.m_msg;
		help();
		return 1;
	}
	catch (RParametersException& RPE)
	{
		cout << RPE.m_msg;
		help();
		return 1;
	}
	return 0;
}


void output(int mode,int number,FILE* ans)
{
	int pointer = 0;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, sizeof(buffer));

	int* result = NULL;
	for (int i = 0; i < number; i++)
	{
		pointer = 0;
		//根据模式用不同的矩阵
		if (mode == 1)
		{
			result = resultC[i];
		}
		else if (mode == 2)
		{
			result = resultN[i];
		}
		else
		{
			result = resultS[i];
		}

		for (int j = 0; j < CELL; j++)
		{
			buffer[pointer] = result[j] + '0';
			pointer++;
			if ((j + 1) % 9 != 0)
			{
				buffer[pointer] = ' ';
				pointer++;
			}

			else
			{
				if (j != 0)
				{
					buffer[pointer] = '\n';
					pointer++;
				}
			}
		}
		buffer[pointer] = '\n';
		fputs(buffer,ans);
	}
}

void help()
{
	cout << usage << endl;
	cout << usageC << endl;
	cout << usageS << endl;
	cout << usageN << endl;
	cout << usageNM << endl;
	cout << usageNRU << endl;
	cout << commands << endl;
	cout << commandC << endl;
	cout << commandS << endl;
	cout << commandN << endl;
	cout << commandM << endl;
	cout << commandR << endl;
	cout << commandU << endl;
}