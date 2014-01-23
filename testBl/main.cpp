#include "testbl.h"
#include <QtGui/QApplication>
 #include <QWindowsVistaStyle>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(new QWindowsVistaStyle);
	testBl w;
	w.show();

	return a.exec();
}
