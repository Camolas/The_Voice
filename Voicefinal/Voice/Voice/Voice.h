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

#ifndef VOICE_H_
#define VOICE_H_

class Edicao;
class Concorrente;
class Mentor;
class Interpretacao;
class IntSemi;

//Exceções
class ExcecaoConcorrente
{
public:
	ExcecaoConcorrente(string name)
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

class ExcecaoProvasCegas
{
public:
	ExcecaoProvasCegas(string name)
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

class CampoVazio
{
public:
	CampoVazio(string campo)
	{
		this->campo = campo;
	}
	string getCampo() const
	{
		return campo;
	}
private:
	string campo;
};

class VetorCheio
{
public:
	VetorCheio(string c1)
	{
		this->name = c1;
	}
	string getName() const
	{
		return name;
	}
private:
	string name;
};

//Musica
struct Musica
{
	string nome;
	string cantor;
};

//Sessao
class Sessao
{
public:
	Sessao(string gra, string loc, string trans, string fase);
	void setEdicao(Edicao* e1);
	string getFase();
private:
	string fase;
	Date gravacao;
	string local;
	Date transmissao;
	Edicao* edicao;
};

//Concurso
class Concurso
{
public:
	static vector<Edicao*> getEdicoes();
	static void addEdicao(Edicao* e1);
	static unsigned int getNedicoes();
private:
	static vector<Edicao*> edicoes;
	static unsigned int nedicoes;
};

//Concorrente
class Concorrente
{
public:
	Concorrente();
	Concorrente(string nm);
	vector<Interpretacao*> getInterpretacoes() const;
	void addInterpretacao(Interpretacao* i1);
	string getName() const;
	string getEtapaElim() const;
	void setMentor(Mentor* m1);
	void setMentor(int m1);
	Mentor* getMentor();
	void setEdicao(Edicao* e1);
	Edicao* getEdicao();
	void setAdversario(Concorrente* c1);
	Concorrente* getAdversario() const;
	void setEtapaElim(string fase);
private:
	string nome;
	Edicao* edicao;
	vector<Interpretacao*> interpretacoes;
	string EtapaElim;
	Mentor* mentor;
	Concorrente* adv;
};

//Edicao

class Edicao
{
public:
	Edicao();
	Edicao::Edicao(int ano);
	bool foiEliminado(Concorrente* c1);
	vector<Mentor*> getMentores();
	vector<Concorrente*> getConcorrentes();
	Concorrente* getVencedor();
	int getAno();
	void addConcorrente(Concorrente* c1);
	void addMentor(Mentor* m1);
	void setVencedor(Concorrente* c1);
	void addSessao(Sessao* s1);
	void passaFinal(vector<IntSemi*> intsemi);
private:
	vector<Mentor*> mentores;
	vector<Concorrente*> concorrentes;
	unsigned int nEdicao;
	Concorrente* vencedor;
	int ano;									//Assumindo uma edicao por ano
	vector<Sessao*> sessoes;
};

//Mentor
class Mentor
{
public:
	Mentor();
	Mentor(string nm);
	string getNome() const;
	int getNumOrdem() const;
	vector<Concorrente*> getConcorrentes() const;
	void setEdicao(Edicao* e1);
	void addConcorrente(Concorrente* c1);
private:
	Edicao* edicao;
	string nome;
	vector<Concorrente*> concorrentes;
	int numOrdem;
	static int proxOrdem;
};

//Interpretacao
class Interpretacao
{
public:
	Interpretacao();
	Interpretacao(Musica mus);
	string getMus() const;
	string getCan() const;
	void setConcorrente(Concorrente* c1);
	Concorrente* getConcorrente();
	virtual void setEliminado() = 0;
	virtual vector<int> getVirouMentor() const;
private:
	Musica musica;
	Concorrente* c;
};

class IntProvasCegas : public Interpretacao
{
public:
	IntProvasCegas(Musica mus);
	void viraMentor(string nome);
	void viraMentor(int num);
	vector<int> getVirouMentor() const;
	void setMentor(int num);
	void setEliminado();
private:
	vector<int> virouMentor;
};

class IntBatalhas : public Interpretacao //batalha entre elementos do mesmo mentor; Gerador de batalha
{
public:
	IntBatalhas(Musica mus);
	void setEliminado();
	bool IntBatalhas::checkBatalhas();
private:
};

class IntSemi : public Interpretacao
{
public:
	IntSemi(Musica mus, float vot);
	float getVotacao() const;
	void setEliminado();
private:
	float voto;
};

bool compareIntSemi(IntSemi* left, IntSemi* right);



class IntFinal :public Interpretacao
{
public:
	IntFinal(Musica mus, float votP, float votM);
	float getVotacaoPublico() const;
	float getVotacaoMentor() const;
	void setEliminado();
private:
	float votPub;
	float votMen;
};

#endif /* VOICE_H_*/
