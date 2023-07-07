#include "movefile.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MoveFile w;
	w.show();
	return a.exec();
}
