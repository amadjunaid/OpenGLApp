#include "gui.h"
#include <Camera.h>

GUI::GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

GUI::~GUI()
{

}

SceneLister * GUI::getSceneLister()
{
	return ui.sceneLister;
}

void GUI::on_camController()
{
	if (ui.combo_camController->currentText().toStdString() == "Arcball")
	{
		mview::SceneManager::getCam()->ChangeController(mview::CONTROLLER_ARCBALL, ui.renderView->width(), ui.renderView->height());
#ifndef NDEBUG
		mview::Logger::Message("Arcball Controller Selected");
#endif // DEBUG

	}
	else if (ui.combo_camController->currentText().toStdString() == "Walker")
	{
		mview::SceneManager::getCam()->ChangeController(mview::CONTROLLER_WALKER, ui.renderView->width(), ui.renderView->height());
#ifndef NDEBUG
		mview::Logger::Message("Walker Controller Selected");
#endif // DEBUG
	}
	
}



