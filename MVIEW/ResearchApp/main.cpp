
#include <Qtcore\QCoreApplication>
#include <QtWidgets\QApplication>
#include "gui.h"
#include <CommonUtils.h>


int main(int argc, char *argv[])
{
	//int* i = new int[100];
	QApplication a(argc, argv);
	
	GUI w;// = new GUI();
	
	w.show();
	
	return a.exec();
}
