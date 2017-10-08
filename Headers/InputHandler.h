#pragma once
#include "Core.h"

class Handler
{
public:
	Handler();
	int GetLower();
	int GetUpper();
	bool GetUnique();
	int GetNumberC();
	int GetNumberN();
	char* GetPath();
	int GetMode();
	int CheckCmd(int argc, char** argv);
private:
	int m_mode;
	int m_lower;
	int m_upper;
	bool m_unique;
	int m_numberC;
	int m_numberN;
	string m_path;
	int Str2Num(char* toNum,int max);
	void ParseR(char* argv);
};