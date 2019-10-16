#ifndef LISTER_H
#define LISTER_H

#include <QtWidgets\QTreeWidget>
#include <QtWidgets\QMenu>
#include <SceneObject.h>
#include "Globals.h"
#include <CommonUtils.h>

//ADD More Item types here and then n the class (member variable, getItemList)
enum SceneListerType {MODEL, ZONE, LIGHTS, EXTRAS, DEFAULTS, SL_COUNT};
class SceneListItem: public QTreeWidgetItem
{
public:
	SceneListItem(QTreeWidgetItem* parent, mview::shrd_MObject sceneObj, int type):QTreeWidgetItem(parent)
	{
		m_sceneObject = sceneObj;
		m_type = type;
	}
	~SceneListItem(){
		mview::Logger::Message(mview::LOG_INFO, "Removing scene object " + m_sceneObject->m_name);
		
		mview::SceneManager::DeleteObject(m_sceneObject);
	}

	mview::shrd_MObject m_sceneObject;
	int m_type;
private:
	
};

class SceneLister: public QTreeWidget
{
	Q_OBJECT
			
public:
	SceneLister(QObject *parent);
	~SceneLister();
	void AddItem(int type, mview::shrd_MObject sceneObj);
	void clear();

private:
	QTreeWidgetItem* m_modelsList;
	QTreeWidgetItem* m_lightsList;
	QTreeWidgetItem* m_zonesList;
	QTreeWidgetItem* m_extrasList;
	QTreeWidgetItem* m_defaultsList;
	QTreeWidgetItem* getItemList(int type);
	
	QMenu* m_contextMenu;
	QAction* m_action_delete;

	private slots:
	void showContextMenu(const QPoint& point);
	void deleteItem();	
};

#endif // LISTER_H
