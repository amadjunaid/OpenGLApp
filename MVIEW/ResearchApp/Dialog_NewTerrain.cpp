#include "Dialog_NewTerrain.h"
#include <QtWidgets\QFileDialog>
#include <CommonUtils.h>

Dialog_NewTerrain::Dialog_NewTerrain(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	QValidator *terrainSizeValidator = new QIntValidator(8, 2048);
	m_ui.input_width->setValidator(terrainSizeValidator);
	m_ui.input_height->setValidator(terrainSizeValidator);

	m_ui.input_heightFile->setText(QString(m_data.heightFieldFile.c_str()));
	m_ui.input_textureFile->setText(QString(m_data.terrainTextureFile.c_str()));
	m_ui.input_width->setText(QString(m_data.width));
	m_ui.input_height->setText(QString(m_data.height));
	m_ui.input_scale->setText(QString(std::to_string(m_data.scale).c_str()));

	//QObject::connect(ui.button_Ok, SIGNAL(clicked()), this, SLOT(accept()));
	//QObject::connect(ui.button_Cancel, SIGNAL(clicked()), this, SLOT(reject()));	
}

Dialog_NewTerrain::~Dialog_NewTerrain()
{

}

const mview::TerrainParams & Dialog_NewTerrain::getData()
{
	return m_data;
}


void Dialog_NewTerrain::on_button_Ok_clicked()
{
	m_data = mview::TerrainParams(m_ui.input_heightFile->text().toStdString(),
		m_ui.input_textureFile->text().toStdString(),
		m_ui.input_width->text().toInt(),
		m_ui.input_height->text().toInt(),
		m_ui.input_scale->text().toFloat());

	accept();
}

void Dialog_NewTerrain::on_button_Cancel_clicked()
{
	m_ui.input_heightFile->setText(QString(m_data.heightFieldFile.c_str()));
	m_ui.input_textureFile->setText(QString(m_data.terrainTextureFile.c_str()));
	m_ui.input_width->setText(QString(m_data.width));
	m_ui.input_height->setText(QString(m_data.height));
	m_ui.input_scale->setText(QString(std::to_string(m_data.scale).c_str()));

	
	reject();
}

void Dialog_NewTerrain::on_button_browseTerrainFile_clicked()
{
	auto filename = QFileDialog::getOpenFileName(this,
		tr("Select Heightfield File"), m_ui.input_heightFile->text(), tr("Heightfields (*.bmp)"));
	if (!filename.isNull()) {
		m_ui.input_heightFile->setText(filename);
	};
}

void Dialog_NewTerrain::on_button_browseTextureFile_clicked()
{
	auto filename = QFileDialog::getOpenFileName(this,
		tr("Select Terrain Texture File"), m_ui.input_textureFile->text(), tr("Texture Files (*.tga)"));
	if (!filename.isNull()) {
		m_ui.input_textureFile->setText(filename);
	};
}