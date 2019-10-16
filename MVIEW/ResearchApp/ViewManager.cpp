#include "ViewManager.h"
#include <Qtcore\qtimer>
#include <QtGui\qpainter.h>
#include <QtGui\qpixmap.h>
#include "Globals.h"

ViewManager::ViewManager(QWidget *parent)
	: QTabWidget(parent)
{
	mview::shrd_Camera cam = mview::shrd_Camera(new mview::Camera());
	mview::SceneManager::SetCam(cam);	
}



ViewManager::~ViewManager()
{
	
}

void ViewManager::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	
	currentWidget()->update();
}

void ViewManager::showEvent(QShowEvent * event)
{
	
}


