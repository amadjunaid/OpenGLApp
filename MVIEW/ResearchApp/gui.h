#ifndef GUI_H
#define GUI_H

#include <QtWidgets\qmainwindow.h>
#include "ui_gui.h"
#include "SceneLister.h"


class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(QWidget *parent = 0);
	~GUI();

private:
	Ui::GUI ui;

	

public:
	SceneLister* getSceneLister();
signals:

	public slots:
		void on_camController();


};

#endif // GUI_H
