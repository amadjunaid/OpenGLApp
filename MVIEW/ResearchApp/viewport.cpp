#include "viewport.h"
#include <QtGui\qpainter.h>
#include <QtCore\qtimer.h>
#include <QtGui\qevent.h>
#include <QtGui\qpixmap.h>
//#include <qbytearray.h>
#include "Globals.h"
#include <Qtcore\qstring.h>
#include "gui.h"
#include "SceneLister.h"




ViewPort::ViewPort(QWidget *parent)
	: QWidget(parent)
{
	//this->parent = parent;
}

ViewPort::ViewPort()
{	
	setFocusPolicy(Qt::ClickFocus);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
	m_viewData = QImage(width(), height(), QImage::Format_RGB888);
	m_viewData.fill(QColor(0, 0, 0));
	g_width.reset(new int(width()));
	g_height.reset(new int(height()));
	
	g_currentRenderer.reset(new mview::Plugin_Renderer_GL(g_width, g_height)); //Use a base size for the initialization
	
	g_currentRenderer->execute();
	setFocusPolicy(Qt::ClickFocus);
	setMouseTracking(false);
	onFirst = true;

	m_lastCPos = this->mapFromGlobal(QCursor::pos());	
	//mview::SceneManager::ChangeData(mview::SceneManager::getCam()->m_id, mview::PARAM_NAME::CAMERA_PROJ);
}

ViewPort::~ViewPort()
{
	g_currentRenderer->terminate();
}

void ViewPort::showEvent(QShowEvent * event)
{
	*g_width = width(); *g_height = height();	
}

void ViewPort::resizeEvent(QResizeEvent* event)
{
	QSize sz = event->size();
	*g_width = sz.width(); *g_height = sz.height();
	mview::SceneManager::getCam()->Resize(45.0f, *g_width, *g_height, 0.1f, 500.0f);
	//mview::SceneManager::ChangeData(mview::SceneManager::getCam()->m_id, mview::PARAM_NAME::CAMERA_PROJ);
	
	g_currentRenderer->DoResize();		
}



void ViewPort::paintEvent(QPaintEvent*) {
	
	QPainter widgetPainter(this);
	widgetPainter.setRenderHint(QPainter::Antialiasing, true);
	widgetPainter.setCompositionMode(QPainter::CompositionMode_Source);
	
	
	//m_pluginRenderer->OnPaint();

	auto threadedRenderedData = g_currentRenderer->GetThreadedRenderedData();
	uchar* renderedData = nullptr;
	threadedRenderedData[mview::RenderBuffers::FRONT].AtomicClose();
	renderedData = threadedRenderedData[mview::RenderBuffers::FRONT].m_dataPtr;
	if (renderedData) {

		//TODO: Fix flickering by snycronising properly with the rendering thread
		//Might have something to do with resizing
		m_viewData = QImage(renderedData, *g_width, *g_height, QImage::Format_RGB888);
	}

	//*********** Using QImage
	//////m_viewData.save("QtestImg1.png");
	//widgetPainter.drawImage(rect(), m_viewData.mirrored(false, true), m_viewData.rect());

	//************ Using QPixmap
	QPixmap pxmap = QPixmap::fromImage(m_viewData);
	////
	////// Transform to upside down as GL outputs upside down image
	////// TODO: Should implement a separate class for this uchar data.. which supports transformations like this to remove dependency
	////
	//////translate to the origin
	widgetPainter.translate(width() / 2, height() / 2);

	////scale
	widgetPainter.scale(1, -1);

	////translate back
	widgetPainter.translate(-width() / 2, -height() / 2);

	widgetPainter.drawPixmap(rect(), pxmap);

	widgetPainter.resetTransform();

	threadedRenderedData[mview::RenderBuffers::FRONT].AtomicOpen();


		
	
	if (m_lastCPos == mapFromGlobal(QCursor::pos())) {
		mview::SceneManager::getCam()->Get_controller()->MouseStopped(m_lastCPos.x(), m_lastCPos.y());
	}
	
}

void ViewPort::mouseMoveEvent(QMouseEvent* event) {
	
	if (auto btn = event->buttons()) {
		mview::SceneManager::getCam()->Get_controller()->MouseClick((mview::BUTTON)getMViewButton(btn), event->x(), event->y());
	}
	else {
		mview::SceneManager::getCam()->Get_controller()->MouseRelease(event->x(), event->y());
	}

	m_lastCPos = event->pos();
	//mview::SceneManager::ChangeData(mview::SceneManager::getCam()->m_id, mview::PARAM_NAME::CAMERA_VIEW);	
}

int ViewPort::getMViewButton(int qtButton)
{
	switch (qtButton) {
	case Qt::LeftButton:
		return mview::BUTTON::LEFT;
		break;
	case Qt::RightButton:
		return mview::BUTTON::RIGHT;
		break;
	case Qt::MiddleButton:
		return mview::BUTTON::MIDDLE;
		break;
	default:
		return -1;
	}
}

int ViewPort::getMViewKey(int qtKey)
{
	switch (qtKey) {
	case Qt::Key_W:
		return mview::KEY::W;
		break;
	case Qt::Key_S:
		return mview::KEY::S;
		break;
	case Qt::Key_A:
		return mview::KEY::A;
		break;
	case Qt::Key_D:
		return mview::KEY::D;
		break;
	case Qt::Key_E:
		return mview::KEY::E;
		break;
	case Qt::Key_C:
		return mview::KEY::C;
		break;
	case Qt::Key_Q:
		return mview::KEY::Q;
		break;
	case Qt::Key_Y:
		return mview::KEY::Y;
		break;
	default:
		return -1;
	}
}

void ViewPort::wheelEvent(QWheelEvent* event) {
	float numDegrees = (float)event->delta() / 8.f;
	mview::SceneManager::getCam()->Zoom(numDegrees, width(), height());
	//mview::SceneManager::ChangeData(mview::SceneManager::getCam()->m_id, mview::PARAM_NAME::CAMERA_PROJ);
}

void ViewPort::keyPressEvent(QKeyEvent * event)
{
	auto key = event->key();
	mview::SceneManager::getCam()->Get_controller()->KeyPressed((mview::KEY)getMViewKey(key));
}

void ViewPort::mouseReleaseEvent(QMouseEvent * event)
{
	mview::SceneManager::getCam()->Get_controller()->MouseRelease(event->x(), event->y());
	//mview::SceneManager::ChangeData(mview::SceneManager::getCam()->m_id, mview::PARAM_NAME::CAMERA_VIEW);	
}