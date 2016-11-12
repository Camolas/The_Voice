#include"Menu.h"
#include"Voice.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

using namespace std;

void gotoXY(int x, int y) // x and y coordinates on the console
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void ClrScr()
{
	cout << "\033[2J" << flush;
	//cout << "\033[2J\033[1;1H";
}

void mostraEdicoes()
{
	//int ans;

	cout << "Qual edicao deseja ver?\n";
	//ciclo que mostra edicoes com respetivo nr de ordem
	cout << endl;
}


void printMenu()
{
	cout << endl << endl;

	int menu_item = 0, x = 7;
	bool running = true;

	gotoXY(18, 7); cout << "->";
	while (running)
	{
		gotoXY(18, 3);
		cout << "             BEM VINDO AO THE VOICE             \n";
		gotoXY(18, 4);
		cout << "               O que deseja ver?\n";		
		
		gotoXY(20, 7); cout << " Nova Edicao";
		gotoXY(20, 8); cout << " Continuar Edicao";
		gotoXY(20, 9); cout << " Opcoes";
		gotoXY(20, 10); cout << " Sair";

		system("pause>nul"); // the >nul bit causes it the print no message

		// x is between the options, which is [7,10]

		if (GetAsyncKeyState(VK_DOWN) && x != 10) //down button pressed  
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu_item++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {

			case 0: {
				gotoXY(0, 16);
			    NovaEdicao();
				ClrScr();
				gotoXY(18, 7); cout << "->";
				break;
			}

			case 1: {
				gotoXY(0, 16);
				ContinuarEdicao();
				ClrScr();
				gotoXY(18, 7); cout << "->";
				break;
			}

			case 2: {
				gotoXY(20, 16);
				printMenu_Opcoes();
				break;
			}

			case 3: {
				gotoXY(20, 16);
				cout << "Voltem sempre!";
				running = false;
		}	

	  }

	 }

	}
}

int NovaEdicao()
{
	string conf;
	ifstream ifile("tmp.txt"); 
	if (ifile) //checks if there is a edition in progress
	{
		cout << "Existe uma Edicao em progresso!\n";
		cout << "Se quiser criar uma nova, esta em progresso sera apagada\n";
		cout << "Deseja criar uma nova Edicao?\n";
		cin >> conf;
		if (conf == "Nao" || conf == "nao")
		{
			cout << "Ira regressar ao menu anterior\n";
			Sleep(1500);
			return 0;
		}
		else if (conf == "Sim" || conf == "sim")
		{
			remove("tmp.txt");
		}
	}

	cout << "yiss\n";
	Sleep(1500);
	return 0;
	// Processo de nova edicao 
	
}

int ContinuarEdicao()
{
	ifstream ifile("tmp.txt");
	if (!ifile) //checks if there is a edition in progress
	{
		cout << "Nao ha nenhuma edicao em progresso!\n";
		cout << "Ira regressar ao menu anterior\n";
		Sleep(1500);
		return 0;
	}
	cout << "e queeeeeee\n";
	Sleep(1500);
	return 0;
}


void printMenu_Opcoes()
{
	int menu_item = 0, x = 17;
	bool running = true;

	gotoXY(22, 15);
	cout << "             OPCOES             \n";

	gotoXY(24, 17); cout << "->";

	while (running)
	{
		gotoXY(26, 17);  cout << "Opcao 1";
		gotoXY(24, 18);  cout << "Opcao 2";
		gotoXY(24, 19);  cout << "Opcao 3";
		gotoXY(24, 20);  cout << "Sair";

		system("pause>nul"); // the >nul bit causes it the print no message

				 // x is between the options, which is [17,20]

		if (GetAsyncKeyState(VK_DOWN) && x != 17) //down button pressed  
		{
			gotoXY(24, x); cout << "  ";
			x++;
			gotoXY(24, x); cout << "->";
			menu_item++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && x != 20) //up button pressed
		{
			gotoXY(24, x); cout << "  ";
			x--;
			gotoXY(24, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {

			case 0: {

				gotoXY(20, 16);
				//printMenu_NovaEdicao();
			}


			case 1: {
				gotoXY(20, 16);
				//printMenu_ContinuarEdicao();
				break;
			}

			case 2: {
				gotoXY(20, 16);
				printMenu_Opcoes();
				break;
			}

			case 3: {
				gotoXY(20, 16);
				cout << "Voltem sempre!";
				running = false;
			}

			}

		}

	}

	gotoXY(20, 21);

}