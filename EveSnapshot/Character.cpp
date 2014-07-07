#include "Character.h"

namespace EveSnapshot
{
	Character::Character()
	{
		loadedProfile = NULL;
	}

	void Character::setProfile(std::shared_ptr<Profile> pro)
	{
		loadedProfile = pro;
	}

	std::shared_ptr<Profile> Character::getProfile()
	{ 
		return loadedProfile; 
	}


}