#pragma once

#include <string>
#include <sstream>

class Date
{
private:
	int dia;
	int mes;
	int ano;
	bool valid;

public:
	Date() { dia = 1; mes = 1; ano = 1; valid = true; }

	Date(int d, int m, int a)
	{
		dia = d;
		mes = m;
		ano = a;
		valid = true;

		isValid();
	}

	Date(std::string s)
	{
		char ignore;
		std::stringstream ss;

		ss << s;
		ss >> dia;
		ss >> ignore;
		ss >> mes;
		ss >> ignore;
		ss >> ano;

		isValid();
	}

	bool isValid()
	{
		if ((dia < 1) || (dia > 31))
			return false;
		if ((mes < 1) || (mes > 12))
			return false;
		if (ano < 1)
			return false;

		return true;
	}
};