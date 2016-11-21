#include <iostream>
#include <conio.h>
#include <windows.h>
#include<iomanip>
#include <cstdlib>
#include "Date.h"
#include "Voice.h"
#include"NovaEdicao.h"
#include"Menu.h"
#include "PrintEdicao.h"

/**
 * Imprime uma dada sessao
 * @param n_edicao indice da edicao no vetor de edicoes
 */
void Edicao_Sessoes(int n_edicao)
{
	int edi_index = n_edicao;
	ClrScr();
	gotoXY(18, 1);
	cout << "           SESSOES EDICAO " << n_edicao << "     \n";
	cout << "A edicao de " << Concurso::getEdicoes()[edi_index]->getAno() << " contou com as habituais 15 sessoes, distribuidas da seguinte forma:\n";
	_getch();
	for (auto i = 0; i < Concurso::getEdicoes()[edi_index]->getSessoes().size(); i++)
	{
		cout << endl;
		if (i < 8)
		{
			cout << endl << i + 1 << "a Prova Cega" << endl;
			cout << "Data Gravacao: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().dia << "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().mes
				<< "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().ano << "       " << "Data Transmissao: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getTransmissao().dia << "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getTransmissao().mes
				<< "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getTransmissao().ano << "     " << "Local: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getLocal();

		}
		if (i == 8)
		{
			_getch();
			ClrScr();
			gotoXY(18, 1);
			cout << "           SESSOES EDICAO " << n_edicao << "     \n";
		}
		if ((i >= 8) & (i < 12))
		{
			cout << endl << (i + 1) % 8 << "a Batalha" << endl;
			cout << "Data Gravacao: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().dia << "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().mes
				<< "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().ano << "       " << "Data Transmissao: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getTransmissao().dia << "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getTransmissao().mes
				<< "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getTransmissao().ano << "     " << "Local: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getLocal();
		}
		if (i == 12)
		{
			_getch();
			ClrScr();
			gotoXY(18, 1);
			cout << "           SESSOES EDICAO " << n_edicao << "     \n";
		}
		if ((i >= 12) & (i < 14))
		{
			cout << endl << (i + 1) % 12 << "a Semi" << endl;
			cout << "Data Gravacao/Transmissao: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().dia << "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().mes
				<< "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().ano << "     " << "Local: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getLocal();
		}
		if (i == 14)
		{
			_getch();
			ClrScr();
			gotoXY(18, 1);
			cout << "           SESSOES EDICAO " << n_edicao << "     \n";
			cout << endl << "Final" << endl;
			cout << "Data Gravacao/Transmissao: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().dia << "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().mes
				<< "/" << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getGravacao().ano << "     " << "Local: " << Concurso::getEdicoes()[edi_index]->getSessoes()[i]->getLocal();
			cout << endl;
		}
	}
	_getch();
	ClrScr();
}

/**
 * Imprime o vencedor de uma dada edicao
 * @param n_edicao indice da edicao no vetor de edicoes
 */
void Edicao_Vencedor(int n_edicao)
{
	int edi_index = n_edicao;
	ClrScr();
	gotoXY(18, 1);
	cout << "           VENCEDOR EDICAO " << n_edicao << "     \n";
	cout << "\nO vencedor da edicao de " << Concurso::getEdicoes()[edi_index]->getAno() << " foi " << Concurso::getEdicoes()[edi_index]->getVencedor()->getName() << ", da equipa " <<
		Concurso::getEdicoes()[edi_index]->getVencedor()->getMentor()->getNome() << "\n\nEle cantou: \n\n";
	for (unsigned int j = 0; j < Concurso::getEdicoes()[edi_index]->getVencedor()->getInterpretacoes().size(); j++)
	{
		cout << Concurso::getEdicoes()[edi_index]->getVencedor()->getInterpretacoes()[j]->getMus() << ", de "
			<< Concurso::getEdicoes()[edi_index]->getVencedor()->getInterpretacoes()[j]->getCan();
		if (j == 0)
		{
			int counter = 0;
			cout << " nas Provas Cegas, conseguindo virar as cadeiras de";
			for (auto i = 0; i < Concurso::getEdicoes()[edi_index]->getVencedor()->getInterpretacoes()[0]->getVirouMentor().size(); i++)
			{
				if (Concurso::getEdicoes()[edi_index]->getVencedor()->getInterpretacoes()[0]->getVirouMentor()[i])
				{
					if (counter != 0)
						cout << ",";
					cout << " " << Concurso::getEdicoes()[edi_index]->getMentores()[i]->getNome();
					counter++;
				}

			}
			cout << ".\n";
		}
		if (j == 1)
		{
			cout << " nas Batalhas, frente ao " << Concurso::getEdicoes()[edi_index]->getVencedor()->getAdversario()->getName() << ".\n";
		}
		if (j == 2)
		{
			cout << " na Semi.\n";
		}
		if (j == 3)
		{
			cout << " na Final.\n";
		}
	}

}

/**
 * Imprime os mentores de uma dada edicao
 * @param n_edicao indice da edicao no vetor de edicoes
 */
void Edicao_Mentores(int n_edicao)
{
	int edi_index = n_edicao;
	vector<Mentor*> mentores = Concurso::getEdicoes()[edi_index]->getMentores();
	ClrScr();
	sort(mentores.begin(), mentores.end(),compareMentores);
	gotoXY(18, 1);
	cout << "           MENTORES EDICAO " << n_edicao << "     \n";
	cout << "\nOs mentores da edicao de " << Concurso::getEdicoes()[edi_index]->getAno() << " foram:";

	for (unsigned int j = 0; j < mentores.size(); j++)
	{
		cout << endl << mentores[j]->getNome();
	}

	cout << "\n\nSendo que o vencedor foi: \n";
	cout << Concurso::getEdicoes()[edi_index]->getVencedor()->getMentor()->getNome() << endl;

}

/**
 * Imprime as equipas de uma dada edicao
 * @param n_edicao indice da edicao no vetor de edicoes
 */
void Edicao_Equipas(int n_edicao)
{
	int edi_index = n_edicao;
	ClrScr();
	gotoXY(18, 1);
	cout << "           EQUIPAS EDICAO " << n_edicao << "     \n";
	for (unsigned int j = 0; j < Concurso::getEdicoes()[edi_index]->getMentores().size(); j++)
	{
		cout << endl << Concurso::getEdicoes()[edi_index]->getMentores()[j]->getNome();
		cout << "\nLiderou a equipa composta pelos concorrentes: \n";
		for (size_t k = 0; k < Concurso::getEdicoes()[edi_index]->getMentores()[j]->getConcorrentes().size(); k++)
		{
			vector<Concorrente*> concorrentes = Concurso::getEdicoes()[edi_index]->getMentores()[j]->getConcorrentes();
			sort(concorrentes.begin(), concorrentes.end(),compareConcorrentes);

			if (k == 5||k==10)
				cout << endl;
			if (k != 13)
				cout << concorrentes[k]->getName() << ", ";
			else
				cout << concorrentes[k]->getName();
		}
		cout << endl;

	}

}

/**
 * Imprime o concorrente de uma dada edicao
 * @param n_edicao indice da edicao no vetor de edicoes
 */
void Edicao_VerConcorrente(int n_edicao)
{
	int edi_index = n_edicao;
	string nome;
	bool found = false;
	cin.ignore();
	ClrScr();
	gotoXY(18, 1);
	cout << "           VER CONCORRENTE EDICAO " << n_edicao << "     \n";
	cout << "\nQue concorrente procura?\n";
	getline(cin, nome);
	cout << endl;
	for (unsigned int k = 0; k < Concurso::getEdicoes()[edi_index]->getConcorrentes().size(); k++)
	{
		if (nome == Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getName())
		{
			found = true;
			cout << Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getName() << " cantou ";

			for (unsigned int j = 0; j < Concurso::getEdicoes()[edi_index]->getVencedor()->getInterpretacoes().size(); j++)
			{
				cout << Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[j]->getMus() << ", de "
					<< Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[j]->getCan();
				switch (j)
				{
				case 0:
				{
					int counter = 0;
					cout << " nas Provas Cegas, conseguindo virar as cadeiras de";
					for (auto i = 0; i < Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[0]->getVirouMentor().size(); i++)
					{
						if (Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[0]->getVirouMentor()[i])
						{
							if (counter != 0)
								cout << ",";
							cout << " " << Concurso::getEdicoes()[edi_index]->getMentores()[i]->getNome();
							counter++;
						}

					}
					cout << ".\n";
					break;
				}
				case 1:
					cout << " nas Batalhas, frente ao " << Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getAdversario()->getName() << ".\n";
					break;
				case 2:
					cout << " na Semi" << ", tendo obtido " << Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[j]->getVotacao() * 100 << "% dos votos do publico.\n";
					break;
				case 3:
					cout << " na Final" << ", tendo obtido " << Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[j]->getVotacaoPublico() * 100 << "% dos votos do publico e "
						<< Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getInterpretacoes()[j]->getVotacaoMentor() * 100 << "% dos votos dos mentores.\n";
					if (Concurso::getEdicoes()[edi_index]->getConcorrentes()[k] != Concurso::getEdicoes()[edi_index]->getVencedor())
						cout << "\nFoi eliminado na fase " << Concurso::getEdicoes()[edi_index]->getConcorrentes()[k]->getEtapaElim() << ".\n";
					break;
				}
			}
		}
	}

	if (!found)
		cout << "Nao foi encontrado nenhum concorrente com o nome " << nome << ".\n";

	return;
}
