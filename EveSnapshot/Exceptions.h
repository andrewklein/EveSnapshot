#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace EveSnapshot
{
	class CreateProfileException : public std::runtime_error
	{
	public:
		CreateProfileException(const std::string &what) : runtime_error(what) {}

		~CreateProfileException() throw() {}
	};

	class ReadConfigurationFileException : public std::runtime_error
	{
	public:
		ReadConfigurationFileException(const std::string &what) : runtime_error(what) {}

		~ReadConfigurationFileException() throw() {}
	};

	class ReadConfigurationDataException : public std::runtime_error
	{
	public:
		ReadConfigurationDataException(const std::string &what) : runtime_error(what) {}

		~ReadConfigurationDataException() throw() {}
	};
}

#endif