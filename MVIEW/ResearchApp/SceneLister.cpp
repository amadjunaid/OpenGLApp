#include "SceneLister.h"
#include <algorithm>

SceneLister::SceneLister(QObject *parent)//: QWidget(parent)
{
	m_modelsList = new QTreeWidgetItem(this);
	m_modelsList->setText(0, "Models");
	addTopLevelItem(m_modelsList);	
	m_modelsList->setFlags(m_modelsList->flags() ^ Qt::ItemIsSelectable);

	m_zonesList = new QTreeWidgetItem(this);
	m_zonesList->setText(0, "Zones");
	addTopLevelItem(m_zonesList);
	m_zonesList->setFlags(m_zonesList->flags() ^ Qt::ItemIsSelectable);

	m_lightsList = new QTreeWidgetItem(this);
	m_lightsList->setText(0, "Lights");
	addTopLevelItem(m_lightsList);
	m_lightsList->setFlags(m_lightsList->flags() ^ Qt::ItemIsSelectable);

	m_extrasList = new QTreeWidgetItem(this);
	m_extrasList->setText(0, "Extras");
	addTopLevelItem(m_extrasList);
	m_extrasList->setFlags(m_extrasList->flags() ^ Qt::ItemIsSelectable);

	m_defaultsList = new QTreeWidgetItem(this);
	m_defaultsList->setText(0, "Defaults");
	addTopLevelItem(m_defaultsList);	

	m_contextMenu = new QMenu(this);
	setContextMenuPolicy(Qt::CustomContextMenu);
	m_action_delete = m_contextMenu->addAction("Delete");
	
	connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(showContextMenu(const QPoint&)));
	connect(m_action_delete, SIGNAL(triggered()), this, SLOT(deleteItem()));
}

SceneLister::~SceneLister()
{

}

void SceneLister::AddItem(int type, mview::shrd_MObject sceneObj)
{
	QTreeWidgetItem* selectedList = getItemList(type);
	SceneListItem* itm = new SceneListItem(selectedList, sceneObj, type);
	itm->setText(0, sceneObj->m_name.c_str());
	selectedList->addChild(itm);
	selectedList->setExpanded(true);
	itm->setSelected(true);	
}

QTreeWidgetItem * SceneLister::getItemList(int type)
{
	switch (type)
	{
	case SceneListerType::MODEL:
		return m_modelsList;		
	case SceneListerType::LIGHTS:
		return m_lightsList;
	case SceneListerType::ZONE:
		return m_zonesList;
	case SceneListerType::EXTRAS:
		return m_extrasList;
	case SceneListerType::DEFAULTS:
		return m_defaultsList;
	default:
		break;
	}

	return nullptr;
}

void SceneLister::showContextMenu(const QPoint& point) {
	
	m_contextMenu->popup(mapToGlobal(point));
}

void SceneLister::deleteItem()
{
	QList<QTreeWidgetItem *> itms = selectedItems();
	for (int i = 0; i < itms.size(); i++)
	{
		delete itms[i];		
	}
	
}

void SceneLister::clear()
{
	//All scene items are cleared except items added as defaults
	for (int i = 0; i < SceneListerType::SL_COUNT-1; i++)
	{
		QTreeWidgetItem* list = getItemList(i);
		qDeleteAll(list->takeChildren());		
	}
	
}

