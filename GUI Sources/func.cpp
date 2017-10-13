#include "func.h"
#include <string>
bool IsValidChar(QString str)
{

	if (str.length() != 1)
	{
		return false;
	}
	std::string stdstr = str.toStdString();
	if (stdstr[0] <= '9' && stdstr[0] >= '1')
	{
		return true;
	}
	return false;
}