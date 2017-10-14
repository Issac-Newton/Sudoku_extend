#include "stdafx.h"
#include "../sudoku/stdafx.h"
#include "../sudoku/InputHandler.h"
#include "../sudoku/Core.cpp"
#include "../sudoku/InputHandler.cpp"
#include "../sudoku/sudoku.cpp"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModeTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		bool valid(int sudoku[][GRIDSIZE]) {
			for (int i = 0; i < GRIDSIZE; i++) {
				bool line_exist[10];
				memset(line_exist, 0, sizeof(line_exist));
				for (int j = 0; j < GRIDSIZE; j++) {
					if ((i == 0 && (j == 0 || j == 3 || j == 6)) || (i == 3 && (j == 0 || j == 3 || j == 6))
						|| (i == 6 && (j == 0 || j == 3 || j == 6))) {
						bool exist[10];
						memset(exist, 0, sizeof(exist));
						for (int cell_i = 0; cell_i < 3; cell_i++) {
							for (int cell_j = 0; cell_j < 3; cell_j++) {
								exist[sudoku[cell_i + i][cell_j + j]] = true;
							}
						}

						for (int exist_i = 1; exist_i < 10; exist_i++) {
							if (!exist[exist_i])
								return false;
						}
					}

					line_exist[sudoku[i][j]] = true;
				}

				for (int j = 1; j <= GRIDSIZE; j++) {
					if (!line_exist[j]) {
						return false;
					}
				}
			}

			for (int i = 0; i < GRIDSIZE; i++) {
				bool col_exist[10];
				memset(col_exist, 0, sizeof(col_exist));
				for (int j = 0; j < GRIDSIZE; j++) {
					col_exist[sudoku[j][i]] = true;
				}
				for (int j = 1; j <= GRIDSIZE; j++) {
					if (!col_exist[j]) {
						return false;
					}
				}
			}

			return true;
		}

		bool IsValid(int pos, int grid[GRIDSIZE][GRIDSIZE])
		{
			int x = pos / GRIDSIZE;
			int y = pos % GRIDSIZE;
			int z = x / SQRTSIZE * SQRTSIZE + y / SQRTSIZE;
			int leftTop = z / SQRTSIZE * GRIDSIZE * SQRTSIZE + (z % SQRTSIZE) * SQRTSIZE;
			int rightDown = leftTop + (2 * GRIDSIZE + SQRTSIZE - 1);
			// check row
			for (int i = 0; i < GRIDSIZE; i++)
			{
				if (i == y)
				{
					continue;
				}
				if (grid[x][i] == grid[x][y])
				{
					return false;
				}
			}
			// check column
			for (int i = 0; i < GRIDSIZE; i++)
			{
				if (i == x)
				{
					continue;
				}
				if (grid[i][y] == grid[x][y])
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
						continue;
					}
					if (grid[i][j] == grid[x][y])
					{
						return false;
					}
				}
			}
			return true;
		}

		bool MultiSolution(int tot, int& ans, int grid[GRIDSIZE][GRIDSIZE])
		{
			if (tot == GRIDSIZE * GRIDSIZE) {
				ans++;
				return true;
			}
			else {
				int x = tot / GRIDSIZE;
				int y = tot % GRIDSIZE;

				if (grid[x][y] == 0) {
					for (int i = 1; i <= 9; i++) {
						grid[x][y] = i;
						if (IsValid(tot, grid)) {
							if (MultiSolution(tot + 1, ans, grid)) {
								if (ans > 1)
								{
									return true;
								}
								continue;
							}
						}
					}
					grid[x][y] = 0;
				}
				else {
					return MultiSolution(tot + 1, ans, grid);
				}
			}
			return false;
		}


		//-c 测试(回归测试)
		TEST_METHOD(TestMethod4)
		{
			int result[100][CELL];
			int grid[GRIDSIZE][GRIDSIZE];

			set<string> container;
			string inserted;

			Core core;
			core.generate(100, result);
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < GRIDSIZE; j++)
				{
					for (int k = 0; k < GRIDSIZE; k++)
					{
						grid[j][k] = result[i][j * GRIDSIZE + k];
						assert(!(grid[j][k] <= 9 && grid[j][k] >= 1));
						inserted.push_back(grid[j][k] + '0');
					}
				}
				Assert::IsTrue(valid(grid));
				container.insert(inserted);
				inserted.clear();
			}
			assert(container.size() == 100);
		}

		//-n -m 2 测试
		TEST_METHOD(TestMethod1)
		{
			int modeUpper = 32;
			int modeLower = 25;
			int result[200][CELL];
			Core core;
			core.generate(100,2,result);

			bool flag = true;

			for (int i = 0; i < 100; i++)
			{
				int count = 0;
				for (int j = 0; j < GRIDSIZE; j++)
				{
					for (int k = 0; k < GRIDSIZE; k++)
					{
						
						if (result[i][j * GRIDSIZE + k] > 0)
						{
							count++;
						}
					}
				}
				if (count < modeLower || count > modeUpper)
				{
					flag = false;
				}
			}

			Assert::IsTrue(flag);
		}
		//-n -m 1
		TEST_METHOD(TestMethod2)
		{
			int modeUpper = 40;
			int modeLower = 33;
			int result[200][CELL];
			Core core;
			core.generate(100, 1, result);

			bool flag = true;

			for (int i = 0; i < 100; i++)
			{
				int count = 0;
				for (int j = 0; j < GRIDSIZE; j++)
				{
					for (int k = 0; k < GRIDSIZE; k++)
					{

						if (result[i][j * GRIDSIZE + k] > 0)
						{
							count++;
						}
					}
				}
				if (count < modeLower || count > modeUpper)
				{
					flag = false;
				}
			}

			Assert::IsTrue(flag);
		}
		// -n -m 3
		TEST_METHOD(TestMethod3)
		{
			int modeUpper = 24;
			int modeLower = 17;
			int result[200][CELL];
			Core core;
			core.generate(100, 3, result);

			bool flag = true;

			for (int i = 0; i < 100; i++)
			{
				int count = 0;
				for (int j = 0; j < GRIDSIZE; j++)
				{
					for (int k = 0; k < GRIDSIZE; k++)
					{

						if (result[i][j * GRIDSIZE + k] > 0)
						{
							count++;
						}
					}
				}
				if (count < modeLower || count > modeUpper)
				{
					flag = false;
				}
			}

			Assert::IsTrue(flag);
		}
		
		//-n -r -u true
		TEST_METHOD(TestMethod5)
		{
			int result[1000][CELL];

			Core core;
			core.generate(2, 55, 55, true, result);
			
			bool flag = true;

			for (int i = 0; i < 2; i++)
			{
				int grid[GRIDSIZE][GRIDSIZE];
				for (int j = 0; j < CELL; j++)
				{
					grid[j / GRIDSIZE][j % GRIDSIZE] = result[i][j];
				}
				int ans = 0;
				if (MultiSolution(0, ans, grid))
				{
					flag = false;
				}
			}

			Assert::IsTrue(flag);
		}

		//-n -r -u false
		TEST_METHOD(TestMethod6)
		{
			int result[1000][CELL];

			Core core;
			core.generate(100,55,55,false,result);

			bool flag = true;

			for (int i = 0; i < 2; i++)
			{
				int count = 0;
				for (int j = 0; j < CELL; j++)
				{
					if(result[i][j] == UNKNOWN)
					{
						count++;
					}
				}
				if (count != 55)
				{
					flag = false;
				}
			}

			Assert::IsTrue(flag);
		}

		//-s(回归测试)
		TEST_METHOD(TestMethod7)
		{
			int puzzle[CELL];
			int solution[CELL];
			Core core;

			bool flag = true;

			FILE* file_in;
			freopen_s(&file_in, "C:\\Users\\dell\\Source\\sudoku\\ModeTest\\sudoku.txt", "r", stdin);
			assert(file_in != NULL);
			while (true)
			{
				if (fscanf(file_in, "%d", &puzzle[0]) == EOF)
				{
					break;
				}
				for (int i = 1; i < CELL; i++)
				{
					fscanf(file_in, "%d", &puzzle[i]);
				}
				assert(core.solve(puzzle,solution));
				int grid[GRIDSIZE][GRIDSIZE];
				for (int j = 0; j < CELL; j++)
				{
					grid[j / GRIDSIZE][j % GRIDSIZE] = solution[j];
				}
				assert(valid(grid));
			}
		}



		//以下是关于异常的测试
		//参数个数异常
		TEST_METHOD(TestMethod8)
		{
			char* command[8] = {"sudoku.exe","-n","100","-n","-r","-s","-m","-d"};
			try {
				main(9,(char**)command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(ParametersNumberException));
			}
		}

		//文件不存在异常
		TEST_METHOD(TestMethod9)
		{
			char* command[3] = { "sudoku.exe","-s","NotExist.txt" };
			try
			{
				main(3,command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(FileNotExistException));
			}
		}

		//数字超出范围
		TEST_METHOD(TestMethod10)
		{
			//-c
			char* command[3] = { "sudoku.exe","-c","100000000" };
			try
			{
				main(3, (char**)command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(NumberOutOfBoundException));
			}



			//-n
			char* command1[5] = {"sudoku.txt","-n","10001","-m","1"};
			try
			{
				main(5, (char**)command1);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(NumberOutOfBoundException));
			}

			//-m（模式错误）
			char* command2[5] = { "sudoku.txt","-n","1000","-m","4" };
			try
			{
				main(5, (char**)command2);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(ModeException));
			}

			//-r
			char* command3[20] = {"sudoku.exe","-n","10","-r","50~56"};
			try
			{
				main(3, (char**)command3);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(NumberOutOfBoundException));
			}
		}

		//关于R的参数存在异常
		TEST_METHOD(TestMethod11)
		{
			//中间连接符不是~
			char* command[5] = { "sudoku.exe","-n","10","-r","20-55"};
			try
			{
				main(5, command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(RParametersException));
			}

			//大小颠倒
			char* command1[20] = { "sudoku.exe","-n","10","-r","30~25" };
			try
			{
				main(5, command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(NumberOutOfBoundException));
			}
		}

		//命令中存在不合法的字符
		TEST_METHOD(TestMethod12)
		{
			char* command[20] = { "sudoku.exe","-nn","10","-r","20~55" };
			try
			{
				main(5, (char**)command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(IllegalCharException));
			}
		}

		
		//数独无解
		TEST_METHOD(TestMethod13)
		{
			char* command[20] = { "sudoku.exe","-s","puzzle.txt"};
			try
			{
				main(3,command);
			}
			catch (exception& e)
			{
				Assert::IsTrue(typeid(e) == typeid(NoSolutionException));
			}
		}
	};
}