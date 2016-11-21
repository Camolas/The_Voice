#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <climits>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include<algorithm>
#include "Date.h"

using namespace std;

#ifndef EXCECOES_H
#define EXCECOES_H

class Edicao;
class Concorrente;
class Mentor;
class Interpretacao;
class IntSemi;

//Exceções
class EntradaInvalida				//throw (EntradaInvalida("Opcao")); catch (EntradaInvalida &c){cout << c.getName() << " nao existente!\n\n";_getch();ClrScr();printMenu();}
{
public:
	EntradaInvalida(string name)
	{
		this->name = name;
	}
	string getName() const
	{
		return name;
	}
private:
	string name;
};

class DiaInvalido
{
public:
	DiaInvalido(string day)
	{
		this->day = day;
	}
	string getDay() const
	{
		return day;
	}
private:
	string day;
};

#endif