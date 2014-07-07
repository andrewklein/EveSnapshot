#include "common.h"
#include "Character.h"
#include "Profile.h"

namespace EveSnapshot
{
	class Data
	{
	private:
		QString settingsPath;
		
		std::vector<std::shared_ptr<Character>> characters;
		std::vector<std::shared_ptr<Profile>> profiles;

	public:
		QString getSettingsPath() { return settingsPath; }
		bool hasSettingsPath() { return settingsPath.isEmpty(); }
		void setSettingsPath(QString newPath);

		std::vector<std::shared_ptr<Profile>> getProfiles() { return profiles; }
		std::vector<std::shared_ptr<Character>> getCharacters() { return characters; }

		
		

		bool readConfig();
		void writeConfig();
		void scanCharacters();

		void createProfileFromCharacter(QString charID, QString profileName);
		void renameProfile(QString oldName, QString newName);
		void removeProfile(QString profileName);
		void setCharacterProfile(QString charName, QString profileName);

	};
}