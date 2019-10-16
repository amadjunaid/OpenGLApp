#ifndef VIEWPORT_H
#define VIEWPORT_H


#include <QtWidgets\QWidget>
#include <CommonUtils.h>
#include <Camera.h>
#include <CameraController.h>
#include <Plugin_Renderer.h>

class ViewPort : public QWidget
{
	Q_OBJECT

public:
	ViewPort(QWidget *parent);
	ViewPort();
	~ViewPort();

	void resizeEvent(QResizeEvent* event);

private:
	
	QImage m_viewData;
	
	bool onFirst;

	QPoint m_lastCPos;	

	//Translation qt button identifier to mview identifier
	int getMViewButton( int qtButton );
	int getMViewKey(int qtKey);
protected:
	void paintEvent(QPaintEvent* event);
	void showEvent(QShowEvent* event);

	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);	
	void wheelEvent(QWheelEvent* event);
	void keyPressEvent(QKeyEvent* event);

	public slots:
	
    

};

#endif // VIEWPORT_H
