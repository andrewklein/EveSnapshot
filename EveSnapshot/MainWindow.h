#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qinputdialog.h>
#include <QWidget>
#include <QTimer>
#include <QtNetwork>
#include <qerrormessage.h>
#include <qmessagebox.h>

#include "GeneratedFiles\ui_window.h"

#include "EveSnapshot.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0) : QMainWindow(parent), ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
		
		networkManager = new QNetworkAccessManager(this);

		eveAPIAddress = QUrl("https://api.eveonline.com/eve/CharacterName.xml.aspx");
		

		try
		{
			data.readConfig();
		}
		catch (EveSnapshot::ReadConfigurationFileException &e)
		{
			data.writeConfig();
		}
		catch (EveSnapshot::ReadConfigurationDataException &e)
		{
			QMessageBox::information(this, tr("Error"), e.what());
		}
		
		data.writeConfig();
		data.scanCharacters();
		updateUI();


		editTimer = new QTimer(this);
		editTimer->setSingleShot(true); 
		connect(editTimer, &QTimer::timeout, this, &MainWindow::updateSettings);
		
		queryEveAPI();
		
	}
	

	~MainWindow()
	{
		delete ui;
	}

	

private:
	Ui::MainWindow *ui;
	EveSnapshot::Data data;
	QNetworkAccessManager *networkManager;
	
	QUrl eveAPIAddress;

	QTimer *editTimer;
	
	void updateSettings();
	void updateUI();

	void queryEveAPI();
	void eveAPICharacterIDToName(QString charID);

private slots:
	void eveAPICharacterIDToNameFinished(QNetworkReply *reply);

	

public slots: 
	void on_evePathInput_textEdited();
	void on_loadProfileBtn_clicked();
	void on_loadProfileAllBtn_clicked();

	void on_createFromSelectedBtn_clicked();
	void on_renameProfileBtn_clicked();
	void on_deleteProfileBtn_clicked();


};


#endif