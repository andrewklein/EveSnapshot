#ifndef PROFILE_H
#define PROFILE_H


#include "common.h"


namespace EveSnapshot
{
	class Profile
	{
	private:
		QString profileName;
		QString profileFilePath;

	public:
		Profile(QString name, QString path) : profileName(name), profileFilePath(path) {}
		~Profile() {}

		void setProfileName(QString name) { profileName = name; }
		void setProfileFilePath(QString path) { profileFilePath = path; }

		QString getName() { return profileName; }
		QString getPath() { return profileFilePath; }

	};
}


#endif