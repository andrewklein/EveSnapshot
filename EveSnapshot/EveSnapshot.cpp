#include "EveSnapshot.h"

namespace EveSnapshot
{
	void Data::setSettingsPath(QString newPath)
	{
		settingsPath = newPath;
	}

	void Data::createProfileFromCharacter(QString charName, QString profileName)
	{
		QString charID = "";
		for (auto charIt = characters.begin(); charIt != characters.end(); charIt++)
		{
			if ((*charIt)->getName() == charName)
			{
				charID = (*charIt)->getID();
			}
		}

		if (charID == "") throw CreateProfileException("Unable to create new profile - character not found");

		QString sourcePath = settingsPath + "/core_char_" + charID + ".dat";
		QString profilePath = profileName + ".dat";
		if (QFile(sourcePath).exists())
		{
			for (auto it = profiles.begin(); it != profiles.end(); it++)
			{
				if (profileName == (*it)->getName())
				{
					throw CreateProfileException("Unable to create new profile - profile with name already exists");
				}
			}
			QFile profileSrc(sourcePath);

			profileSrc.copy(profilePath);
		}
		else {
			MessageBox(NULL, sourcePath.toStdString().c_str(), "", 0);
			throw CreateProfileException("Unable to copy character configuration - source file not found");
		}

		std::shared_ptr<Profile> newPro = std::shared_ptr<Profile>(new Profile(profileName, profilePath));
		profiles.push_back(newPro);
	}

	void Data::renameProfile(QString oldName, QString newName)
	{
		for (auto it = profiles.begin(); it != profiles.end(); it++)
		{
			if (oldName == (*it)->getName())
			{
				(*it)->setProfileName(newName);
				(*it)->setProfileFilePath(newName + ".dat");

				QFile profileSrc(oldName + ".dat");
				profileSrc.copy(newName + ".dat");
				profileSrc.remove();
			}
		}
	}

	void Data::removeProfile(QString profileName)
	{
		int i = 0;
		int removeIndex;
		for (auto it = profiles.begin(); it != profiles.end(); it++)
		{
			if (profileName == (*it)->getName())
			{
				
				QString profilePath = (*it)->getPath();
				removeIndex = i;
				QFile profileSrc(profilePath);
				profileSrc.remove();
			}
			i++;
		}

		profiles.erase(profiles.begin()+removeIndex);
	}

	void Data::setCharacterProfile(QString charName, QString profileName)
	{
		//Lookup profile
		for (auto it = profiles.begin(); it != profiles.end(); it++)
		{
			if (profileName == (*it)->getName())
			{
				for (auto charIt = characters.begin(); charIt != characters.end(); charIt++)
				{
					if (charName == (*charIt)->getName())
					{
						(*charIt)->setProfile((*it));
						QFile profileSrc((*it)->getPath());
						QFile profileDest(settingsPath + "\\core_char_" + (*charIt)->getID() + ".dat");
						if (profileDest.exists())
						{
							profileDest.remove();
						}
						profileSrc.copy(settingsPath + "\\core_char_" + (*charIt)->getID() + ".dat");
					}
				}
				
			}
			
		}
	}


	//Scan settings directory for avaliable characters
	void Data::scanCharacters()
	{
		QRegExp regex("core_char_(\\d+)");
		QStringList characterIDList;

		if (QDir(settingsPath).exists())
		{
			
			QStringList fileList = QDir(settingsPath).entryList();
			
			for (auto it = fileList.begin(); it != fileList.end(); it++)
			{
				regex.indexIn((*it));
				if (regex.cap(1).size() > 0)
					characterIDList << regex.cap(1);

			}
			for (auto it = characterIDList.begin(); it != characterIDList.end(); it++)
			{
				bool exists = false;

				//Check if character already exists
				for (auto charIt = characters.begin(); charIt != characters.end(); charIt++)
				{	
					if ((*it) == (*charIt)->getID())
					{
						exists = true;
					}
				}
				if (!exists)
				{
					//Set new character's name to ID initially
					std::shared_ptr<Character> newChar = std::shared_ptr<Character>(new Character());
					newChar->setID((*it));
					newChar->setName((*it));
					std::shared_ptr<Profile> charProfile = NULL;
					characters.push_back(newChar);
					
				}
			}
		}
	}

	void Data::writeConfig()
	{
		boost::property_tree::ptree propTree;

		propTree.put("EveSnapshot.Settings", settingsPath.toStdString().c_str());

		//Save characters
		int i = 1;
		boost::property_tree::ptree childCharTree;

		for (auto it = characters.begin(); it != characters.end(); it++)
		{
			std::string n = std::to_string(i);

			boost::property_tree::ptree charTree;

			charTree.add("Name", (*it)->getName().toStdString().c_str());
			charTree.add("ID", (*it)->getID().toStdString().c_str());
			if ((*it)->getProfile() != NULL)
			{
				charTree.add("Profile", (*it)->getProfile()->getName().toStdString().c_str());
			}
			childCharTree.add_child(n, charTree);

			i++;
		}
		propTree.put_child("EveSnapshot.Characters", childCharTree);
		
		//Save Profiles
		i = 1;
		boost::property_tree::ptree childProfileTree;
		for (auto it = profiles.begin(); it != profiles.end(); it++)
		{
			std::string n = std::to_string(i);

			boost::property_tree::ptree profileTree;

			profileTree.add("Name", (*it)->getName().toStdString().c_str());
			profileTree.add("Path", (*it)->getPath().toStdString().c_str());
			childProfileTree.add_child(n, profileTree);

			i++;
		}
		propTree.put_child("EveSnapshot.Profiles", childProfileTree);
		
		
		write_xml("config.xml", propTree, std::locale(), boost::property_tree::xml_writer_settings<char>(' ', 4));
	}

	bool Data::readConfig()
	{
		boost::property_tree::ptree propTree;
		
		//Try and open config file/read to memory
		try
		{
			boost::property_tree::read_xml("config.xml", propTree);
		}
		catch (boost::property_tree::xml_parser_error &e)
		{
			std::string msg = "Config Load Error: ";
			msg += e.what();
			throw ReadConfigurationFileException(msg);
		}

		//Read profiles in config file
		try
		{
			boost::property_tree::ptree child = propTree.get_child("EveSnapshot.Profiles");

			for (auto it = child.begin(); it != child.end(); it++)
			{
				boost::property_tree::ptree profileTree = it->second;
				QString profileName = QString::fromStdString(profileTree.get<std::string>("Name"));
				QString profilePath = QString::fromStdString(profileTree.get<std::string>("Path"));
				std::shared_ptr<Profile> pro = std::shared_ptr<Profile>(new Profile(profileName, profilePath));
				profiles.push_back(pro);
			}
		}
		catch (boost::property_tree::xml_parser_error &e)
		{
			std::string msg = "Error Reading Profile Data: ";
			msg += e.what();
			throw ReadConfigurationDataException(msg);
		}
		catch (boost::property_tree::ptree_bad_path &e)
		{
			std::string msg = "Error Reading Profile Data: ";
			msg += e.what();
			throw ReadConfigurationDataException(msg);
		}

		//Read character data
		try
		{
			settingsPath = QString::fromStdString(propTree.get<std::string>("EveSnapshot.Settings"));

			boost::property_tree::ptree child = propTree.get_child("EveSnapshot.Characters");
			for (auto it = child.begin(); it != child.end();  it++)
			{
				

				boost::property_tree::ptree characterTree = it->second;
				std::string name = characterTree.get<std::string>("Name");
				std::string ID = characterTree.get<std::string>("ID");
				boost::optional<std::string> profileName = characterTree.get_optional<std::string>("Profile");
				
				std::shared_ptr<Character> charData = std::shared_ptr<Character>(new Character());
				charData->setName(QString::fromStdString(name));
				charData->setID(QString::fromStdString(ID));

				std::shared_ptr<Profile> charProfile = NULL;

				if (profileName.is_initialized())
				{
					for (auto profileIterator = profiles.begin(); profileIterator != profiles.end(); profileIterator++)
					{
						if (profileName == (*profileIterator)->getName().toStdString())
						{
							charProfile = (*profileIterator);
						}
					}
					charData->setProfile(charProfile);
				}
				characters.push_back(charData);

			}
		}
		catch (boost::property_tree::xml_parser_error &e)
		{
			std::string msg = "Error Reading Character Data: ";
			msg += e.what();
			throw ReadConfigurationDataException(msg);
		}
		catch (boost::property_tree::ptree_bad_path &e)
		{
			std::string msg = "Error Reading Character Data: ";
			msg += e.what();
			throw ReadConfigurationDataException(msg);
		}

		return true;
		
	}
}