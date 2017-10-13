#include "GUITest.h"
#include <QtWidgets/QApplication>
#include "Core.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GUITest w;

	w.show();
	return a.exec();
}
