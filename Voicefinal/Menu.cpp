
#include <iostream>
#include <conio.h>
#include <windows.h>
#include<iomanip>
#include <cstdlib>
#include "Date.h"
#include "Voice.h"
#include"Menu.h"
#include"NovaEdicao.h"
#include "PrintEdicao.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

/**
 * desloca para a posicao (x,y) na consola
 * 
 * @param x coordenada x
 * @param y coordenada y
*/
void gotoXY(int x, int y) // x and y coordinates on the console
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
/**
 * limpa a consola
*/
void ClrScr()
{
	system("cls");
}
/**
 * imprime o menu raiz
*/
void printMenu()
{
	ClrScr();
	cout << endl << endl;
		int ans;

		gotoXY(15, 1);
		cout << "             BEM VINDO AO THE VOICE             \n";
		gotoXY(15, 2);
		cout << "               O que deseja fazer?\n";

		gotoXY(17, 4); cout << " 1 - Nova Edicao";
		gotoXY(17, 5); cout << " 2 - Informacoes";
		gotoXY(17, 6); cout << " 3 - Sair\n";

		try {
			cin >> ans;
			if (ans < 1 || ans>3)
				throw (EntradaInvalida("Opcao"));
		}
		catch (EntradaInvalida &c)
		{
			cout << c.getName() << " nao existente!\n\n";
			_getch();
			ClrScr();
			printMenu();
		}

		switch (ans)
		{
		case 1:
		{
			gotoXY(0, 16);
			NovaEdicao();
			ClrScr();
			gotoXY(15, 4); cout << "->";
			break;
		}

		case 2:
		{
			printMenu_Informacoes();
			ClrScr();
			break;
		}

		case 3:
		{
			gotoXY(0, 12);
			cout << "Programa desenvolvido por Bruno Pinto, Manuel Curral e Vitor Magalhaes\n";
			_getch();
			return;
		}

		}
}
/**
 * imprime o menu de informacoes
*/
void printMenu_Informacoes()
{
	ClrScr();
	int ans;


	gotoXY(18, 1);

	cout << "            INFORMACOES             \n";

	gotoXY(20, 3);  cout << "1 - Ver edicao";
	gotoXY(20, 4);  cout << "2 - Creditos";
	gotoXY(20, 5);  cout << "3 - Vencedores anteriores\n\n";
	gotoXY(20, 6);  cout << "4 - Sair\n\n";

	try {
		cin >> ans;
		if (ans < 1 || ans>4)
			throw (EntradaInvalida("Opcao"));
	}
	catch (EntradaInvalida &c)
	{
		cout << c.getName() << " nao existente!\n\n";
		_getch();
		ClrScr();
		printMenu();
	}

	switch (ans)
	{
	case 1:
	{	printMenu_EdicoesAnteriores();
	break;
	}
	case 2:
	{
		printMenu_Creditos();
		break;
	}

	break;
	case 3:
		printMenu_VencedoresAnteriores();
		break;
	case 4:
		printMenu();
		break;
	default:
		break;
	}

}
/**
 * imprime o menu de vencedores anteriores
*/
void printMenu_VencedoresAnteriores()
{
	struct vencedor
	{
		string nome;
		int counter;
	};

	vector<vencedor> winners;

	ClrScr();
	gotoXY(18, 1);
	cout << "           VENCEDORES ANTERIORES      \n";

	cout << "\nOs concorrentes vencedores anteriores foram:\n";
	for (auto i = 0; i < Concurso::getEdicoes().size(); i++)
	{
		cout << Concurso::getEdicoes()[i]->getVencedor()->getName() << "(" << Concurso::getEdicoes()[i]->getVencedor()->getMentor()->getNome() << ")\n";
	}

	cout << "\nSendo assim, o mentor com mais vitorias foi ";
	for (auto i = 0; i < Concurso::getEdicoes().size(); i++)
	{
		for (auto j = 0; j < winners.size(); j++)
			if (winners[j].nome == Concurso::getEdicoes()[i]->getVencedor()->getMentor()->getNome())
				winners[j].counter++;
		winners.push_back({ Concurso::getEdicoes()[i]->getVencedor()->getMentor()->getNome(),0 });
	}

	string mentor;
	int vitorias = -1;

	for (auto i = 0; i < winners.size(); i++)
		if (winners[i].counter>vitorias)
		{
			mentor = winners[i].nome;
			vitorias = winners[i].counter;
		}

	cout << mentor << ".\n";
	_getch();
	ClrScr();
	printMenu();
}
/**
 * imprime o menu de creditos
*/
void printMenu_Creditos()
{
	ClrScr();
	gotoXY(18, 1);
	cout << "           CREDITOS     \n";
	cout << "\nEste programa foi desenvolvido e testado por Bruno Pinto, Manuel Curral e Vitor Magalhaes\n";
	_getch();
}
/**
 * imprime o menu de edicoes anteriores
*/
void printMenu_EdicoesAnteriores()   //falta saber como guardar as edicoes para que o Concurso c contenha as edicoes
{
	ClrScr();
	int ans;
	int edi;

	ClrScr();
	gotoXY(18, 1);
	cout << "           EDICOES ANTERIORES     \n";

	gotoXY(18, 2);
	cout << "\nQue edicao quer pesquisar? ";
	cout << " [0," << Concurso::getEdicoes().size() - 1 << "]\n";
	try {
		cin >> edi;
		if (edi < 0 || edi > Concurso::getEdicoes().size() - 1)
			throw (EntradaInvalida("Edicao"));
	}
	catch (EntradaInvalida &c)
	{
		cout << c.getName() << " nao existente!\n\n";
		_getch();
		ClrScr();
		printMenu();
	}

	ClrScr();
	gotoXY(18, 1);
	cout << "           EDICAO NUMERO " << edi << "     \n";

	gotoXY(20, 3);  cout << "1 - Vencedor";
	gotoXY(20, 4);  cout << "2 - Mentores";
	gotoXY(20, 5);  cout << "3 - Ver Equipas";
	gotoXY(20, 6);	cout << "4 - Ver Concorrente";
	gotoXY(20, 7);	cout << "5 - Ver Sessoes";
	gotoXY(20, 8);  cout << "6 - Sair\n";
	try {
		cin >> ans;
		if (ans < 1 || ans>6)
			throw (EntradaInvalida("Opcao"));
	}
	catch (EntradaInvalida &c)
	{
		cout << c.getName() << " nao existente!\n\n";
		_getch();
		ClrScr();
		printMenu();
	}

	switch (ans)
	{
	case 1:
	{
		Edicao_Vencedor(edi);
		_getch();
		ClrScr();
		break;
	}
	case 2:
	{
		Edicao_Mentores(edi);
		_getch();
		ClrScr();
		break;
	}
	case 3:
	{
		Edicao_Equipas(edi);
		_getch();
		ClrScr();
		break;
	}
	case 4:
	{
		cin.clear();
		Edicao_VerConcorrente(edi);
		_getch();
		ClrScr();
		break;
	}
	case 5:
	{
		Edicao_Sessoes(edi);
		printMenu();
		_getch();
		ClrScr();
		break;
	}
	}
}
