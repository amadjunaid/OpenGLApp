#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QTabWidget>

class ViewManager : public QTabWidget
{
	Q_OBJECT

public:
	ViewManager(QWidget *parent);

	~ViewManager();

protected:
	void paintEvent(QPaintEvent* event);
	void showEvent(QShowEvent* event);

private:
	//Keep in sync with tab order as defined in the GUI
	enum VIEWMANAGER_TABS {RENDERER, TEXTURE};

	public slots:
	
};

#endif // VIEWMANAGER_H
