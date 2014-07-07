#ifndef CHARACTER_H
#define CHARACTER_H



#include "common.h"
#include "Profile.h"


namespace EveSnapshot
{
	class Character
	{
	private:
		QString characterName;
		QString characterID;
		std::shared_ptr<Profile> loadedProfile;
	public:
		Character();
		
		~Character() { }


		void setName(QString name) { characterName = name; }
		void setID(QString id) { characterID = id; }

		QString getName() { return characterName; }
		QString getID() { return characterID; }
		std::shared_ptr<Profile> getProfile();

		void setProfile(std::shared_ptr<Profile> pro);
	};
}


#endif