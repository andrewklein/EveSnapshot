#include "MainWindow.h"

void MainWindow::queryEveAPI()
{
	std::vector<std::shared_ptr<EveSnapshot::Character>> characters = data.getCharacters();
	for (auto charIt = characters.begin(); charIt != characters.end(); charIt++)
	{
		if ((*charIt)->getID() == (*charIt)->getName())
		{
			eveAPICharacterIDToName((*charIt)->getID());
		}
		
	}
}

void MainWindow::eveAPICharacterIDToName(QString charID)
{
	QUrlQuery query;
	query.addQueryItem("ids", charID);
	eveAPIAddress.setQuery(query);

	QNetworkRequest request(eveAPIAddress);
	

	connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(eveAPICharacterIDToNameFinished(QNetworkReply *)));

	networkManager->get(request);

	//connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateDataReadProgress(qint64, qint64)));
}

void MainWindow::eveAPICharacterIDToNameFinished(QNetworkReply *reply)
{
	boost::property_tree::ptree propTree;

	if (reply->error())
	{
		qDebug() << "[-] ERROR";
		qDebug() << reply->errorString();
		QMessageBox::information(this, tr("Error"), reply->errorString());
	}
	else
	{
		QByteArray result = reply->readAll();
		if (result.size() > 0)
		{	
			try
			{
				std::stringstream ss; 
				ss << QString(result).toStdString();
				boost::property_tree::read_xml(ss, propTree);

				boost::property_tree::ptree childTree = propTree.get_child("eveapi.result.rowset");

				QString charID = QString::fromStdString(childTree.get<std::string>("row.<xmlattr>.characterID"));
				QString charName = QString::fromStdString(childTree.get<std::string>("row.<xmlattr>.name"));

				std::vector<std::shared_ptr<EveSnapshot::Character>> characters = data.getCharacters();
				for (auto charIt = characters.begin(); charIt != characters.end(); charIt++)
				{
					if ((*charIt)->getID() == charID)
					{
						(*charIt)->setName(charName);
					}

				}
			}
			catch (boost::property_tree::xml_parser_error &e)
			{
				qDebug() << "[-] ERROR";
				qDebug() << "XML Parser Error";
				QMessageBox::information(this, tr("Error"), tr("XML Parser Error"));
			}
			catch (boost::property_tree::ptree_bad_path &e)
			{
				qDebug() << "[-] ERROR";
				qDebug() << "XML Bad Path";
				QMessageBox::information(this, tr("Error"), tr("XML Bad Path"));
			}
		}
	}

	reply->deleteLater();
	this->updateUI();
	data.writeConfig();

}


void MainWindow::updateSettings()
{
	data.setSettingsPath(ui->evePathInput->text());
	
	this->updateUI();
	data.writeConfig();

	data.scanCharacters();
	queryEveAPI();

}

void MainWindow::on_evePathInput_textEdited()
{
	editTimer->start(100);
}

void MainWindow::on_loadProfileBtn_clicked()
{
	QString currentCharName;
	QList<QTreeWidgetItem *> selected = ui->profileLoadedTree->selectedItems();
	QString selectedProfileName = ui->profileComboBox->currentText();

	for (auto it = selected.begin(); it != selected.end(); it++)
	{
		currentCharName = (*it)->text(0);
		data.setCharacterProfile(currentCharName, selectedProfileName);
	}

	this->updateUI();
	data.writeConfig();
}

void MainWindow::on_loadProfileAllBtn_clicked()
{
	QString currentCharName;
	QString selectedProfileName = ui->profileComboBox->currentText();

	for (int i = 0; i < ui->profileLoadedTree->topLevelItemCount(); ++i)
	{
		QTreeWidgetItem *item = ui->profileLoadedTree->topLevelItem(i);
		currentCharName = item->text(0);
		data.setCharacterProfile(currentCharName, selectedProfileName);
	}


	this->updateUI();
	data.writeConfig();
}

void MainWindow::on_createFromSelectedBtn_clicked()
{
	bool ok;
	QString profileName = QInputDialog::getText(this, tr("Enter a profile name"), tr("Profile Name:"), QLineEdit::Normal, "", &ok);

	if (ok && profileName != "")
	{
		try
		{
			data.createProfileFromCharacter(ui->charSelectCombo->currentText(), profileName);
			this->updateUI();
			data.writeConfig();
		}
		catch (EveSnapshot::CreateProfileException &e)
		{
			QMessageBox::information(this, tr("Error"), e.what());
			
		}


	}
	else if(ok) {
		QMessageBox::information(this, tr("Error"), tr("No profile name specified"));
	}


	
}

void MainWindow::on_renameProfileBtn_clicked()
{
	bool ok;
	QString currentName;
	QList<QTreeWidgetItem *> selected = ui->profileTree->selectedItems();

	for (auto it = selected.begin(); it != selected.end(); it++)
	{
		currentName = (*it)->text(0);
	}
	
	QString profileName = QInputDialog::getText(this, tr("Enter a new profile name"), tr("Profile Name:"), QLineEdit::Normal, 
		currentName, &ok);

	if (ok && profileName != "")
	{
		data.renameProfile(currentName, profileName);
		this->updateUI();
		data.writeConfig();
	}
	else if (ok) {
		QMessageBox::information(this, tr("Error"), tr("Profile name may not be empty"));
	}

}

void MainWindow::on_deleteProfileBtn_clicked()
{
	QString currentName;
	QList<QTreeWidgetItem *> selected = ui->profileTree->selectedItems();
	for (auto it = selected.begin(); it != selected.end(); it++)
	{
		currentName = (*it)->text(0);
	}

	if(currentName != NULL)
		data.removeProfile(currentName);

	this->updateUI();
	data.writeConfig();
}

void MainWindow::updateUI()
{
	
	std::vector<std::shared_ptr<EveSnapshot::Profile>> profiles = data.getProfiles();
	std::vector<std::shared_ptr<EveSnapshot::Character>> characters = data.getCharacters();

	//Update UI profiles information
	ui->profileComboBox->clear();
	ui->profileTree->clear();
	for (auto profileIterator = profiles.begin(); profileIterator != profiles.end(); profileIterator++)
	{
		QString profileItemText = (*profileIterator)->getName();
		ui->profileComboBox->addItem(profileItemText);


		QTreeWidgetItem *profileTreeItem = new QTreeWidgetItem();
		profileTreeItem->setText(0, profileItemText);

		ui->profileTree->addTopLevelItem(profileTreeItem);
		
	}

	//Update UI character information
	ui->charSelectCombo->clear();
	ui->profileLoadedTree->clear();
	for (auto characterIterator = characters.begin(); characterIterator != characters.end(); characterIterator++)
	{
		QString charName = (*characterIterator)->getName();
		QString charProfileName;
		if ((*characterIterator)->getProfile() != NULL)
		{
			charProfileName = (*characterIterator)->getProfile()->getName();
		}
		else {
			charProfileName = "None";
		}
		ui->charSelectCombo->addItem(charName);

		QTreeWidgetItem *charTreeItem = new QTreeWidgetItem();
		charTreeItem->setText(0, charName);
		charTreeItem->setText(1, charProfileName);

		ui->profileLoadedTree->addTopLevelItem(charTreeItem);

		

	}

	for (int i = 0; i < characters.size(); i++)
		ui->profileLoadedTree->resizeColumnToContents(i);

	//Update UI settings information
	ui->evePathInput->setText(data.getSettingsPath());

}


