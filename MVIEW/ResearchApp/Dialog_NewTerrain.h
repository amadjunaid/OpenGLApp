#ifndef DIALOG_NEWTERRAIN_H
#define DIALOG_NEWTERRAIN_H

#include <QtWidgets\QDialog>
#include "ui_Dialog_NewTerrain.h"
#include <Terrain.h>

class Dialog_NewTerrain : public QDialog
{
	Q_OBJECT

public:
	Dialog_NewTerrain(QWidget *parent = 0);
	~Dialog_NewTerrain();
	const mview::TerrainParams& getData();

private:
	Ui::Dialog_NewTerrain m_ui;
	mview::TerrainParams m_data;
	
public slots:
	void on_button_Ok_clicked();
	void on_button_browseTerrainFile_clicked();
	void on_button_browseTextureFile_clicked();
	void on_button_Cancel_clicked();
};

#endif // DIALOG_NEWTERRAIN_H
