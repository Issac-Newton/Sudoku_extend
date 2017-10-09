#pragma warning(disable : 4996)
#include "stdafx.h"
#include "InputHandler.h"

Handler::Handler()
{
	this->m_mode = 0;
	this->m_lower = 0;
	this->m_upper = 0;
	this->m_unique = false;
	this->m_numberC = 0;
	this->m_numberN = 0;
	this->m_path = "";
}

char* Handler::GetPath()
{
	return (char*)m_path.c_str();
}

int Handler::GetMode()
{
	return this->m_mode;
}

int Handler::GetLower()
{
	return this->m_lower;
}

int Handler::GetUpper()
{
	return this->m_upper;
}

bool Handler::GetUnique()
{
	return this->m_unique;
}

int Handler::GetNumberC()
{
	return this->m_numberC;
}

int Handler::GetNumberN()
{
	return this->m_numberN;
}

int Handler::CheckCmd(int argc, char** argv) 
throw (IllegalCharException,ParametersNumberException,
	NumberOutOfBoundException,RParametersException,FileNotExistException)
{
	if (argc < 3 || argc > 6)
	{
		throw ParametersNumberException("illegal parameter number.\n\n");
	}
	
	switch (argc)
	{
	case 3:   //-s,-c
		if (strlen(argv[1]) != 2)
		{
			throw IllegalCharException("The parameters contain some illegal characters.\n\n");
		}

		if ((argv[1][0] == '-') && ((argv[1][1] == 'c') || (argv[1][1] == 's')))
		{
			if (argv[1][1] == 'c')
			{
				int number = Str2Num(argv[2], MAX_C);
				this->m_numberC = number;
				return C_CMD;
			}
			else if (argv[1][1] == 's')
			{
				FILE* test;
				fopen_s(&test, argv[2], "r");
				if (!test)
				{
					throw FileNotExistException("The file can't open.\n\n");
				}
				fclose(test);
				m_path = string(argv[2]);
				return S_CMD;
			}
		}

		else
		{
			throw IllegalCharException("There may be some illegal characters or input illegal commands.\n\n");
		}
		break;

	case 4:  //-n,-u
		if (strlen(argv[1]) != 2)
		{
			throw IllegalCharException("The parameters contain some illegal characters.\n\n");
		}

		if ((argv[1][0] == '-') && (argv[1][1] == 'u'))
		{
			if (strlen(argv[2]) != 2)
			{
				throw IllegalCharException("The parameters contain some illegal characters.\n\n");
			}

			if ((argv[2][0] != '-') && (argv[2][1] != 'n'))
			{
				int number = Str2Num(argv[3], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NU_CMD;
			}
		}
		
		if ((argv[1][0] == '-') && (argv[1][1] == 'n'))
		{
			if (strlen(argv[3]) != 2)
			{
				throw IllegalCharException("The parameters contain some illegal characters.\n\n");
			}

			if (!((argv[3][0] == '-') && (argv[3][1] == 'u')))
			{
				throw IllegalCharException("There may be some illegal characters or miss some parameters.\n\n");
			}
			int number = Str2Num(argv[2], MAX_N);
			this->m_numberN = number;
			this->m_unique = true;
			return NU_CMD;
		}

		else
		{
			throw IllegalCharException("There may be some illegal characters or miss some parameters.\n\n");
		}
		break;

	case 5:  // -n -m or -n -r
		if ((strlen(argv[1]) != 2) || (strlen(argv[3]) != 2))
		{
			throw IllegalCharException("The parameters contain some illegal characters.\n\n");
		}

		if ((argv[1][0] == '-') && (argv[1][1] == 'n'))
		{
			// -n -m
			if ((argv[3][0] == '-') && (argv[3][1] == 'm'))
			{
				int mode = Str2Num(argv[4], HARD);
				this->m_mode = mode;

				int number = Str2Num(argv[2], MAX_N);
				this->m_numberN = number;
				return NM_CMD;
			}

			// -n -r
			else if ((argv[3][0] == '-') && (argv[3][1] == 'r'))
			{
				ParseR(argv[4]);
				int number = Str2Num(argv[2], MAX_N);
				this->m_numberN = number;
				return NR_CMD;	
			}
		}
		//-m -n


		if ((argv[1][0] == '-') && (argv[1][1] == 'm'))
		{
			if ((argv[3][0] == '-') && (argv[3][1] == 'n'))
			{
				int mode = Str2Num(argv[2], HARD);
				this->m_mode = mode;
				int number = Str2Num(argv[4], MAX_N);
				this->m_numberN = number;
				return NM_CMD;
			}
		}

		// -r -n
		if ((argv[1][0] == '-') && (argv[1][1] == 'r'))
		{
			if ((argv[3][0] == '-') && (argv[3][1] == 'n'))
			{
				ParseR(argv[2]);
				int number = Str2Num(argv[4], MAX_N);
				this->m_numberN = number;
				return NR_CMD;
			}
		}
		else
		{
			throw IllegalCharException("There may be some illegal characters or the command combination is not right.\n\n");
		}

		break;

	case 6: // -n -r -u

		// -n -r -u 1 3 5
		// -r -n -u 1 3 5
		if ((strlen(argv[1]) == 2) && (strlen(argv[3]) == 2) && (strlen(argv[5]) == 2))
		{
			if (((argv[1][0] == '-') && (argv[1][1] == 'n')) &&
				((argv[3][0] == '-') && (argv[3][1] == 'r')) &&
				((argv[5][0] == '-') && (argv[5][1] == 'u')))
			{
				ParseR(argv[4]);
				int number = Str2Num(argv[2], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NRU_CMD;
			}
			if (((argv[1][0] == '-') && (argv[1][1] == 'r')) &&
				((argv[3][0] == '-') && (argv[3][1] == 'n')) &&
				((argv[5][0] == '-') && (argv[5][1] == 'u')))
			{
				ParseR(argv[2]);
				int number = Str2Num(argv[4], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NRU_CMD;
			}
		}
		// -n -u -r 1 3 4
		// -r -u -n 1 3 4
		if ((strlen(argv[1]) == 2) && (strlen(argv[3]) == 2) && (strlen(argv[4]) == 2))
		{
			if (((argv[1][0] == '-') && (argv[1][1] == 'n')) &&
				((argv[3][0] == '-') && (argv[3][1] == 'u')) &&
				((argv[4][0] == '-') && (argv[4][1] == 'r')))
			{
				ParseR(argv[5]);
				int number = Str2Num(argv[2], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NRU_CMD;
			}
			if (((argv[1][0] == '-') && (argv[1][1] == 'r')) &&
				((argv[3][0] == '-') && (argv[3][1] == 'u')) &&
				((argv[4][0] == '-') && (argv[4][1] == 'n')))
			{
				ParseR(argv[2]);
				int number = Str2Num(argv[5], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NRU_CMD;
			}
		}
		// -u -n -r 1 2 4
		// -u -r -n 1 2 4
		if ((strlen(argv[1]) == 2) && (strlen(argv[2]) == 2) && (strlen(argv[4]) == 2))
		{
			if (((argv[1][0] == '-') && (argv[1][1] == 'u')) &&
				((argv[2][0] == '-') && (argv[2][1] == 'n')) &&
				((argv[4][0] == '-') && (argv[4][1] == 'r')))
			{
				ParseR(argv[5]);
				int number = Str2Num(argv[3], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NRU_CMD;
			}
			if (((argv[1][0] == '-') && (argv[1][1] == 'u')) &&
				((argv[2][0] == '-') && (argv[2][1] == 'r')) &&
				((argv[4][0] == '-') && (argv[4][1] == 'n')))
			{
				ParseR(argv[3]);
				int number = Str2Num(argv[5], MAX_N);
				this->m_numberN = number;
				this->m_unique = true;
				return NRU_CMD;
			}
		}
		
		else
		{
			throw IllegalCharException("There may be some illegal characters the command combination is not right.\n\n");
		}
		
		break;
	
	default:
		throw IllegalCharException("There may be some illegal characters.\n\n");
		break;
	}
	
	return ERROR;
}

int Handler::Str2Num(char* argv,int max) throw (IllegalCharException)
{
	int number = 0;
	for (unsigned i = 0; i < string(argv).length(); i++)
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			if (max == MAX_C)
			{
				throw IllegalCharException("The parameter after -c is not right.\n\n");
			}
			if (max == MAX_N)
			{
				throw IllegalCharException("The parameter after -n is not right.\n\n");
			}
			if (max == EMPTY_UPPER)
			{
				throw IllegalCharException("The parameter after -r is not right.\n\n");
			}
		}

		number = number * 10 + argv[i] - '0';

	}
	return number;
}


void Handler::ParseR(char* argv) throw (RParametersException,IllegalCharException)
{
	if (strlen(argv) != 5)
	{
		throw RParametersException("The parameter of -r is wrong.\n\n");
	}
	
	for (unsigned int i = 0; i < strlen(argv); i++)
	{
		if ((i == 2) && (argv[i] == '~'))
		{
			continue;
		}
		else if ((i != 2) && (argv[i] >= '0') && (argv[i] <= '9'))
		{
			continue;
		}
		else
		{
			throw RParametersException("The parameter of -r is wrong.\n\n");
		}
	}

	string temp = string(argv);
	string lowerStr = temp.substr(0, 2);
	int lowNum;
	lowNum = Str2Num((char*)lowerStr.c_str(), EMPTY_UPPER);
	
	string upperStr = temp.substr(3, 2);
	int highNum;
	
	highNum = Str2Num((char*)upperStr.c_str(), EMPTY_UPPER);

	this->m_lower = lowNum;
	this->m_upper = highNum;
	
	return;
}

