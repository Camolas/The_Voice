#include <iostream>
#include <conio.h>
#include <windows.h>
#include<iomanip>
#include <cstdlib>
#include "Date.h"
#include "Voice.h"
#include"NovaEdicao.h"
#include"Menu.h"

/**
 * Funcao de suporte para a criacao de uma nova edicao
 */
void NovaEdicao()
{
	ClrScr();
	int edicao = Concurso::getNedicoes();
	int year;
	gotoXY(18, 1);
	cout << "Qual e o ano?\n";
	cin >> year;
	Edicao ed(year);
	Concurso::addEdicao(&ed);
	string n1, n2, n3, n4;

	cout << "Seja bem vindo a edicao numero " << edicao << " do The Voice Portugal!\n";
	cout << "        Nesta nova edicao, quais sao os mentores?\n";
	cin.ignore();
	getline(cin, n1);
	cout << endl;
	Mentor* M1 = new Mentor(n1);
	getline(cin, n2);
	cout << endl;
	Mentor* M2 = new Mentor(n2);
	getline(cin, n3);
	cout << endl;
	Mentor* M3 = new Mentor(n3);
	getline(cin, n4);
	Mentor* M4 = new Mentor(n4);
	ed.addMentor(M1);
	ed.addMentor(M2);
	ed.addMentor(M3);
	ed.addMentor(M4);


	cout << endl << endl;

	_getch();
	cout << "E comecam as provas cegas!\n";
	_getch();
	ClrScr();
	provas_cegas(edicao);
	cout << "Agora, temos 4 equipas, compostas por cada mentor e os seus 14 concorrentes.\n"
		<< "Vamos proceder para a fase das batalhas!\n";
	batalhas(edicao);
	cout << "O numero de concorrentes foi reduzido para 28. O voto do publico sera de extrema importancia a partir de agora\n"
		<< "Vamos para as semi-finais!\n";
	semi_finais(edicao);
	cout << "Tem sido uma edicao espetacular e numero de concorrentes foi cortado para os 10. Quem sera o vencedor?"
		<< "Vamos para as finais!\n";
}

/**
 * Fase das provas cegas
 * @param edicao indice da edicao no vetor de edicoes
 */
void provas_cegas(int edicao)
{
	int res;
	vector <int> escolhidos;
	int m;
	Musica mus;
	string dia;
	string local;
	string transmissao;
	string musica;
	string cantor;
	int answer = -1;
	bool unico = false;
	bool validation = false;
	bool diaValido = true;
	IntProvasCegas* it = new IntProvasCegas(mus);

	ClrScr();

	gotoXY(18, 1);

	cout << "            PROVAS CEGAS             \n";

	cout << "\nNesta fase, os quatro mentores estao virados de costas para os concorrentes\n"
		<< "Estes ultimos terao de mostrar a sua interpretacao e os mentores, caso o/a queiram na equipa, viram as cadeiras.\n\n";

	string con;
	int number = 0;
	cout << "Quais foram os concorrentes selecionados nestas provas cegas?\n";

	while (number != 56)
	{
		if (number % 5 == 0 && number != 0)
			ClrScr();

		cout << "Concorrente " << number + 1 << "\n";
		getline(cin, con);
		Concorrente* c = new Concorrente(con);
		cout << endl;
		Concurso::getEdicoes()[edicao]->addConcorrente(c);
		number++;
	}

	for (size_t i = 0; i < 8; i++)
	{
		Date day;
		do
		{
			diaValido = day.isValid();
			try
			{
				cout << "Qual e o dia de gravacao da " << i + 1 << "a sessao das provas cegas? (Formato: DD/MM/YYYY)\n";
				cin >> dia;
				day = Date(dia);
				diaValido = day.isValid();
				if (!diaValido)
					throw (DiaInvalido(dia));
			}
			catch (DiaInvalido &c)
			{
				cout << c.getDay() << " e uma data impossivel!\n\n";
				diaValido = false;
			}
		} while (!diaValido);
		diaValido = true;
		cout << "Qual o local de gravacao?\n";
		cin.ignore();
		getline(cin, local);
		do
		{
			diaValido = day.isValid();
			try
			{
				cout << "Quando sera a transmissao? (Formato: DD/MM/YYYY)\n";
				cin >> transmissao;
				day = Date(transmissao);
				diaValido = day.isValid();
				if (!diaValido)
					throw (DiaInvalido(transmissao));
			}
			catch (DiaInvalido &c)
			{
				cout << c.getDay() << " e uma data impossivel!\n\n";
				diaValido = false;
			}
		} while (!diaValido);
	}
	Sessao(dia, local, transmissao, "Provas Cegas");
	cout << "Vamos comecar:\n";

	for (unsigned int i = 0; i < Concurso::getEdicoes()[edicao]->getConcorrentes().size(); i++)
	{
		escolhidos.clear();
		validation = false;
		bool mentorValido = true;
		cout << Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->getName() << ": "; //mostra nome
		cout << "Qual foi a musica que cantou?\n";
		getline(cin, musica);
		cout << "Qual e o cantor da musica?\n";
		getline(cin, cantor);
		mus.nome = musica;
		mus.cantor = cantor;
		Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->addInterpretacao(it);

		while (validation == false)
		{
			cout << "Que mentores viraram a cadeira?\n";
			cout << "1-" << Concurso::getEdicoes()[edicao]->getMentores()[0]->getNome() << endl
				<< "2-" << Concurso::getEdicoes()[edicao]->getMentores()[1]->getNome() << endl
				<< "3-" << Concurso::getEdicoes()[edicao]->getMentores()[2]->getNome() << endl
				<< "4-" << Concurso::getEdicoes()[edicao]->getMentores()[3]->getNome() << endl;
			do
			{
				do
				{
					if (!mentorValido)
						cout << "Introduziu um indice errado! Introduza outro mentor!\n";

					try {
						cin >> res;
						if (res < 1 || res>4)
							throw EntradaInvalida("Mentor");
					}
					catch (EntradaInvalida &c)
					{
						cout << c.getName() << " nao existente!\n\n";
						mentorValido = false;
					}
				} while (!mentorValido);
				cout << endl;
				escolhidos.push_back(res);
				cout << "Foi o unico? (0->Nao !0->Sim)\n";
				cin >> answer;
				cout << endl;
			} while (!answer);


			if (escolhidos.size() == 1)
			{

				if (Concurso::getEdicoes()[edicao]->getMentores()[res - 1]->getConcorrentes().size() < 14)
				{
					it->viraMentor(escolhidos[0] - 1);  //o que virou a cadeira entra no vector viraMentor
					it->getConcorrente()->setMentor(escolhidos[0] - 1);// e é set como mentor
					validation = true;
					cout << Concurso::getEdicoes()[edicao]->getMentores()[res - 1]->getNome() << " ja tem " << Concurso::getEdicoes()[edicao]->getMentores()[res - 1]->getConcorrentes().size()
						<< " concorrentes.\n";
				}
				else
				{
					cout << "Esse mentor ja tem um numero maximo de concorrentes para a sua equipa. Escolha outro\n";
					escolhidos.clear();
					validation = false;
					unico = false;
				}
			}
			else
			{
				cout << "Qual dos mentores que viraram a cadeira vai ser o mentor?\n";
				for (unsigned int i = 0; i < escolhidos.size(); i++)
					cout << i << "-" << Concurso::getEdicoes()[edicao]->getMentores()[i]->getNome() << endl; //mostra os mentores que viraram, com o numero colocado atrás do nome que apareceu no ecra antes
				cin >> m;
				if (Concurso::getEdicoes()[edicao]->getMentores()[m]->getConcorrentes().size() < 14)
				{
					it->viraMentor(m);
					it->getConcorrente()->setMentor(m);
					cout << Concurso::getEdicoes()[edicao]->getMentores()[m]->getNome() << " ja tem " << Concurso::getEdicoes()[edicao]->getMentores()[m]->getConcorrentes().size()
						<< " concorrentes.\n";
					validation = true;

				}
				else
				{
					cout << "Esse mentor ja tem um numero maximo de concorrentes para a sua equipa. Escolha outro\n";
					escolhidos.clear();
					validation = false;
				}

			}
		}
	}
}

/**
 * Fase das batalhas
 * @param edicao indice da edicao no vetor de edicoes
 */
void batalhas(int edicao)
{
	ClrScr();
	string winner;
	string dia;
	string local;
	string transmissao;
	string musica1;
	string cantor1;
	string musica2;
	string cantor2;
	Musica mus1;
	Musica mus2;



	bool validation = false;
	bool diaValido = true;


	ClrScr();

	gotoXY(18, 1);

	cout << "            BATALHAS             \n";

	cout << "\nNesta fase, dois concorrentes da mesma equipa combatem um contra o outro com uma interpretacao. O vencedor sera decidido pelo mentor da equipa respetiva\n";
	for (size_t i = 0; i < 4; i++)
	{
		Date day;
		do
		{
			try
			{
				cout << "Qual e o dia de gravacao da " << i + 1 << "a sessao das batalhas? (Formato: DD/MM/YYYY)\n";
				cin >> dia;
				day = Date(dia);
				diaValido = day.isValid();
				if (!diaValido)
					throw (DiaInvalido(dia));
			}
			catch (DiaInvalido &c)
			{
				cout << c.getDay() << " e uma data impossivel!\n\n";
				diaValido = false;
			}
		} while (!diaValido);
		diaValido = true;
		cout << "Qual o local de gravacao?\n";
		getline(cin, local);
		do
		{
			try
			{
				cout << "Qual e o dia de gravacao da transmissao? (Formato: DD/MM/YYYY)\n";
				cin >> transmissao;
				day = Date(transmissao);
				diaValido = day.isValid();
				if (!diaValido)
					throw (DiaInvalido(transmissao));
			}
			catch (DiaInvalido &c)
			{
				cout << c.getDay() << " e uma data impossivel!\n\n";
				diaValido = false;
			}
		} while (!diaValido);
		Sessao(dia, local, transmissao, "Batalhas");
	}
	ClrScr();
	cout << "Vamos começar!\n";

	for (unsigned int i = 0; i < Concurso::getEdicoes()[edicao]->getConcorrentes().size(); i++)
	{

		if (Concurso::getEdicoes()[edicao]->foiEliminado(Concurso::getEdicoes()[edicao]->getConcorrentes()[i]))
		{
			cout << Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->getName() << endl;
			//concorrente
			string adversario;
			bool sucGet = true, sucAdv = true;
			Concorrente* adv = 0;
			do {
				if (!sucAdv)
					cout << "Este concorrente ja tem adversario! Escolha outro!\n";
				cout << "Quem foi o adversario?\n";
				getline(cin, adversario);
				cout << endl;
				for (size_t j = 0; j < Concurso::getEdicoes()[edicao]->getConcorrentes().size(); j++)
					if (Concurso::getEdicoes()[edicao]->getConcorrentes()[j]->getName() == adversario)
					{
						if (Concurso::getEdicoes()[edicao]->getConcorrentes()[j]->getAdversario())
							sucAdv = false;
						adv = Concurso::getEdicoes()[edicao]->getConcorrentes()[j];
						sucGet = true;
						sucAdv = true;
					}
				if (!sucGet)
					cout << "O nome introduzido nao foi encontrado!\n";
				else
				{
					Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->setAdversario(adv);
					adv->setAdversario(Concurso::getEdicoes()[edicao]->getConcorrentes()[i]);
				}

			} while (!sucAdv || !sucGet);
			cout << "Qual foi a musica que o " << adv->getName() << "cantou?\n";
			getline(cin, musica1);
			cout << "Qual e o cantor da musica?\n";
			getline(cin, cantor1);
			mus1.nome = musica1;
			mus1.cantor = cantor1;
			IntBatalhas* it1 = new IntBatalhas(mus1);
			Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->addInterpretacao(it1);

			//adversario
			cout << Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->getAdversario()->getName();
			cout << "Qual foi a musica que o " << adv->getName() << "cantou?\n";
			getline(cin, musica2);
			cout << "Qual e o cantor da musica?\n";
			getline(cin, cantor2);
			mus2.nome = musica2;
			mus2.cantor = cantor2;
			IntBatalhas* it2 = new IntBatalhas(mus2);
			adv->addInterpretacao(it2);

			while (validation == false)
			{
				cout << "Quem foi o vencedor?\n";

				getline(cin, winner);

				if (winner == Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->getName())
				{
					adv->setEtapaElim("Batalhas");
					validation = true;
					ClrScr();
				}

				else if (winner == adv->getName())
				{
					Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->setEtapaElim("Batalhas");
					validation = true;
					ClrScr();
				}

				else
				{
					cerr << "Esse concorrente nao existe. Tente de novo\n";
					validation = false;
				}
			}
		}
	}
}

/**
 * Fase das semi finais
 * @param edicao indice da edicao no vetor de edicoes
 */
void semi_finais(int edicao)
{
	ClrScr();
	float votacao;
	string dia;
	string local;
	string musica;
	string cantor;
	Musica mus;
	int semis = 0;

	bool validation = false;
	bool diaValido = true;
	vector<IntSemi*> auxiliar;

	cout << "AVISO: A partir desta fase vao ser pedidas votacoes no intervalo [0,1], sempre que a votacao total for superior a 1, esta edicao e apagada e tem que comecar de novo!\n";


	gotoXY(15, 4);
	cout << "             SEMIS             \n";

	for (size_t i = 0; i < 2; i++)
	{
		Date day;
		do {
			if (!diaValido)
				cout << "O dia introduzido e invalido!\n";
			cout << "Quando e que foi a emissao (ao vivo) da " << i + 1 << "a Semi Final?\n";
			cin >> dia;
			day = Date(dia);
			diaValido = day.isValid();
		} while (!diaValido);
		diaValido = true;
		cout << "Onde e que foi a emissao?\n";
		getline(cin, local);
		cout << endl;
		Sessao(dia, local, dia, "Semi");
	}
	cout << "Nesta fase, cada concorrente faz uma interpretacao e a votacao do publico dira se passa ou nao\n"
		<< "Vamos comecar:\n";

	for (unsigned int i = 0; i < Concurso::getEdicoes()[edicao]->getConcorrentes().size(); i++)
	{
		if (Concurso::getEdicoes()[edicao]->foiEliminado(Concurso::getEdicoes()[edicao]->getConcorrentes()[i]))
		{
			if (auxiliar.size() == 14) //14 de cada vez para verificar se passa ou nao e só 5 passam
			{
				semis++;
				Concurso::getEdicoes()[edicao]->passaFinal(auxiliar);
				auxiliar.clear();
				if (semis == 2)
					return;
			}

			cout << "Qual foi a musica que cantou?\n";
			getline(cin, musica);
			cout << "Qual e o cantor da musica?\n";
			getline(cin, cantor);
			mus.nome = musica;
			mus.cantor = cantor;


			while (validation = false)
			{
				cout << "Qual foi a votacao do publico? [0,1] \n";
				cin >> votacao;
				if (votacao < 0 || votacao > 1)
				{
					cout << "Ultrapassou os limites dos valores possiveis. Tente de novo\n";
					validation = false;
				}
				else
				{
					IntSemi* it = new IntSemi(mus, votacao);
					Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->addInterpretacao(it);
					auxiliar.push_back(it);
					if (!Concurso::getEdicoes()[edicao]->checkVotacaoSemi())
						Concurso::removeEdicao(Concurso::getEdicoes()[edicao]);
					validation = true;
					ClrScr();
				}
			}
		}
	}
}

/**
 * Fase da final
 * @param edicao indice da edicao no vetor de edicoes
 */
void finais(int edicao)
{
	ClrScr();

	Musica mus;
	string dia;
	string local;
	string transmissao;
	string musica;
	string cantor;
	float votPublico;
	float votMentor;
	bool validation = false;
	bool diaValido = true;
	vector<IntFinal*> auxiliar;

	gotoXY(15, 1);
	cout << "             FINAL             \n";

	Date day;
	do {
		if (!diaValido)
			cout << "O dia introduzido e invalido!\n";
		cout << "Quando e que foi a emissao (ao vivo)?\n";
		cin >> dia;
		day = Date(dia);
		diaValido = day.isValid();
	} while (!diaValido);
	diaValido = true;
	cout << "Onde e que foi a emissao?\n";
	getline(cin, local);
	cout << endl;
	Sessao(dia, local, dia, "Final");
	cout << "Nesta ultima fase, cada concorrente faz uma interpretacao e a votacao do publico e do mentor dira se passa ou nao\n"
		<< "Vamos comecar:\n";

	for (unsigned int i = 0; i < Concurso::getEdicoes()[edicao]->getConcorrentes().size(); i++)
		if (Concurso::getEdicoes()[edicao]->foiEliminado(Concurso::getEdicoes()[edicao]->getConcorrentes()[i]))
		{
			cout << "Qual foi a musica que cantou?\n";
			getline(cin, musica);
			cout << "Qual e o cantor da musica?\n";
			getline(cin, cantor);
			mus.nome = musica;
			mus.cantor = cantor;
			while (validation = false)
			{
				cout << "Qual foi a votacao do publico? [0,1] \n";
				cin >> votPublico;
				if (votPublico < 0 || votPublico > 1)
				{
					cout << "\nUltrapassou os limites dos valores possiveis. Tente de novo\n";
					validation = false;
				}
				cout << "Qual foi a votacao do mentor? [0,1] \n";
				cin >> votMentor;
				if (votMentor < 0 || votMentor > 1)
				{
					cout << "\nUltrapassou os limites dos valores possiveis. Tente de novo\n";
					validation = false;
				}

				else
				{
					IntFinal* it = new IntFinal(mus, votPublico, votMentor);
					Concurso::getEdicoes()[edicao]->getConcorrentes()[i]->addInterpretacao(it);
					if (!Concurso::getEdicoes()[edicao]->checkVotacaoFinalMentor() || !Concurso::getEdicoes()[edicao]->checkVotacaoFinalPublico())
					{
						Concurso::removeEdicao(Concurso::getEdicoes()[edicao]);
						cout << "\nOverflow nas votacoes! Esta edicao foi apagada!\n";
						_getch();
						ClrScr();
						printMenu();
					}
					auxiliar.push_back(it);
					validation = true;
					ClrScr();
				}
			}
		}
	Concurso::getEdicoes()[edicao]->setVencedor(auxiliar);
	cout << "\nO grande vencedor foi " << Concurso::getEdicoes()[edicao]->getVencedor() << "!\n";
	cout << "\nConcluimos assim esta edicao!\nPode consultar os seus detalhes no menu Informacoes!\n";

}
