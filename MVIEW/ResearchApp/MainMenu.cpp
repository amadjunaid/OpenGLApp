#include "MainMenu.h"
#include <CommonUtils.h>
#include "Globals.h"
#include <QtWidgets\QFileDialog>
#include <gui.h>
#include "SceneLister.h"
#include <Model.h>
#include <PointLight.h>
#include "Dialog_NewTerrain.h"


MainMenu::MainMenu(QObject *parent)
	//: QMenuBar(parent)
{
	
}

MainMenu::~MainMenu()
{

}

void MainMenu::on_New_Terrain()
{
	Dialog_NewTerrain* dialog = new Dialog_NewTerrain(this);
	if (dialog->exec() == QDialog::Accepted)
	{
		mview::TerrainParams data = dialog->getData();
		
		mview::Logger::Message(data.heightFieldFile);

		
		mview::shrd_Zone zone(new mview::Zone());

		zone->AddTerrain(data);

		////Add to scene
		mview::SceneManager::AddObject(zone);

		//Add to UI list
		SceneLister* sceneLister = ((GUI*)(this->parent()))->getSceneLister();
		sceneLister->AddItem(SceneListerType::ZONE, zone);
		
	}

	
}

void MainMenu::on_Create_SampleData()
{
	SceneLister* sceneLister = ((GUI*)(this->parent()))->getSceneLister();
	sceneLister->clear();

	//mview::shrd_PointLight pointLight(new mview::PointLight());	

	////Add to scene
	//mview::SceneManager::AddObject(pointLight);

	////Add to GUI list

	//sceneLister->AddItem(SceneListerType::LIGHTS, pointLight);

	//QString filename = "../Data/fishOBJ/BlenderOBJ.obj";
	//if (!filename.isNull()) {
	//	mview::shrd_Model triMesh = std::make_shared<mview::Model>();
	//	triMesh->LoadFromFile(filename.toStdString());		

	//	//Add t oscene
	//	mview::SceneManager::AddObject(triMesh);

	//	//Add to GUI list
	//	sceneLister = ((GUI*)(this->parent()))->getSceneLister();
	//	sceneLister->AddItem(SceneListerType::MODEL, triMesh);
	//}	

	//mview::shrd_Zone zone(new mview::Zone());

	////Add to scene
	//mview::SceneManager::AddObject(zone);

	////Add to GUI list

	//TODO: add to UI list
	//sceneLister->AddItem(SceneListerType::ZONE, zone);

}

void MainMenu::on_Create_PointLight()
{

	mview::shrd_PointLight pointLight(new mview::PointLight());
	
	//Add to scene
	mview::SceneManager::AddObject(pointLight);
	
	//Add to GUI list
	SceneLister* sceneLister = ((GUI*)(this->parent()))->getSceneLister();
	sceneLister->AddItem(SceneListerType::LIGHTS, pointLight);
	
}

void MainMenu::on_Import_3DModel()
{	
	auto filename = QFileDialog::getOpenFileName(this, 
		tr("Import 3D Model"), "..\\Data", tr("3D Model Files (*.obj)"));
	if (!filename.isNull()) {
		mview::shrd_Model model(new mview::Model());
		model->LoadFromFile(filename.toStdString());

		//Add t oscene
		mview::SceneManager::AddObject(model);

		//Add to GUI list
		SceneLister* sceneLister = ((GUI*)(this->parent()))->getSceneLister();
		sceneLister->AddItem(SceneListerType::MODEL, model);
	}
	
}