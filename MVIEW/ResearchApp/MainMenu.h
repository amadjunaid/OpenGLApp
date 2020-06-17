#ifndef MAINMENU_H
#define MAINMENU_H

#include <QtWidgets\QMenuBar>

class MainMenu : public QMenuBar
{
	Q_OBJECT

public:
	MainMenu(QObject *parent);
	~MainMenu();

private:	
	
public slots :
	void on_Import_3DModel();
	void on_Create_PointLight();
	void on_Create_SampleData();
	void on_New_Terrain();	
};

#endif // MAINMENU_H
