#include "Voice.h"

using namespace std;

//Sessao
Sessao::Sessao(string gra, string loc, string trans, string fase)
{
	if (fase == "Semi" || fase == "Final")
		if (gra != trans)
		{
			gravacao = Date(gra);
			transmissao = Date(gra);
			local = loc;
			this->fase = fase;
			return;
		}

	gravacao = Date(gra);
	local=loc;
	transmissao = Date(trans);
	this->fase = fase;
}

void Sessao::setEdicao(Edicao* e1)
{
	edicao = e1;
}

string Sessao::getFase()
{
	return fase;
}

//Concurso

vector<Edicao*> Concurso::getEdicoes()
{
	return edicoes;
}

unsigned int Concurso::getNedicoes()
{
	return nedicoes;
}

unsigned int Concurso::nedicoes = 0;

vector<Edicao*> Concurso::edicoes;

void Concurso::addEdicao(Edicao* e1)
{
	edicoes.push_back(e1);
}

//Edicao

Edicao::Edicao(){}

Edicao::Edicao(int ano)
{
	this->ano = ano;

	Concurso::addEdicao(this);
}

void Edicao::passaFinal(vector<IntSemi*> intsemi)
{
	for (size_t i = 0; i < 9; i++)
		intsemi[i]->getConcorrente()->setEtapaElim("Semi");
}

vector<Mentor*> Edicao::getMentores()
{
	return mentores;
}

int Edicao::getAno()
{
	return ano;
}

Concorrente* Edicao::getVencedor()
{
	if (!vencedor)
		throw (CampoVazio("vencedor"));
	
	return vencedor;
}

vector<Concorrente*> Edicao::getConcorrentes()
{
	return concorrentes;
}

bool Edicao::foiEliminado(Concorrente* c1)					//Assumindo que name pertence a um concorrente do vetor
{
	for(size_t i=0; i<concorrentes.size(); i++)
		if (concorrentes[i] == c1)
		{
			if (concorrentes[i]->getEtapaElim() != "")
				return 0;
			else
				return 1;
		}

	throw ExcecaoConcorrente(c1->getName());
}

void Edicao::addConcorrente(Concorrente* c1)
{
	if (concorrentes.size() == 56)
		throw(VetorCheio(c1->getName()));

	c1->setEdicao(this);

	concorrentes.push_back(c1);
}

void Edicao::addMentor(Mentor* m1)
{
	if (concorrentes.size() == 4)
		throw(VetorCheio(m1->getNome()));

	m1->setEdicao(this);

	mentores.push_back(m1);
}

void Edicao::setVencedor(Concorrente* c1)
{
	vencedor = c1;
}

void Edicao::addSessao(Sessao* s1)
{
	int counter=0;

	for (size_t i = 0; i < sessoes.size(); i++)
		if (sessoes[i]->getFase() == s1->getFase())
			counter++;
	
	if (s1->getFase() == "Provas Cegas")
		if (counter == 8)
			throw(VetorCheio("A prova cega"));

	if (s1->getFase() == "Batalhas")
		if (counter == 4)
			throw(VetorCheio("A batalha"));

	if (s1->getFase() == "Semi")
		if (counter == 2)
			throw(VetorCheio("A semi"));

	if (s1->getFase() == "Final")
		if (counter == 1)
			throw(VetorCheio("A final"));

	s1->setEdicao(this);

	sessoes.push_back(s1);
}

//Concorrentes

Concorrente::Concorrente(){}

Concorrente::Concorrente(string nm)
{
	nome = nm;
}

void Concorrente::setAdversario(Concorrente* c1)
{
	if (c1->getEdicao()->foiEliminado(c1) && this->getMentor()==c1->getMentor())
	{
		adv = c1;
	}
	else
		throw(ExcecaoConcorrente(c1->getName()));
}

Concorrente* Concorrente::getAdversario() const
{
	return adv;
}

void Concorrente::setEdicao(Edicao* e1)
{
	edicao = e1;
}

vector<Interpretacao*> Concorrente::getInterpretacoes() const
{
	return interpretacoes;
}

string Concorrente::getName() const
{
	return nome;
}

string Concorrente::getEtapaElim() const
{
	return EtapaElim;
}

void Concorrente::addInterpretacao(Interpretacao* i1)
{
	interpretacoes.push_back(i1);

	i1->setConcorrente(this);
}

void Concorrente::setMentor(Mentor* m1)
{
	int val = -1;

	for (size_t i = 0; i < this->getEdicao()->getMentores().size(); i++)
	{
		if (this->getEdicao()->getMentores()[i] == m1)
			val = i;
	}

	if (val == -1)
		throw(ExcecaoConcorrente(m1->getNome()));

	if (this->getInterpretacoes()[0]->getVirouMentor()[val])
	{
		mentor = m1;
		m1->addConcorrente(this);
	}
	else
		throw(ExcecaoProvasCegas(m1->getNome()));
}

void Concorrente::setMentor(int m1)
{
	if ((size_t) m1 >= this->getEdicao()->getMentores().size())
		throw ExcecaoConcorrente(to_string(m1));

	if (this->getInterpretacoes()[0]->getVirouMentor()[m1])
	{
		mentor = this->getEdicao()->getMentores()[m1];
		mentor->addConcorrente(this);
	}
	else
		throw(ExcecaoProvasCegas(to_string(m1)));
}

Mentor* Concorrente::getMentor()
{
	return mentor;
}

Edicao* Concorrente::getEdicao()
{
	return edicao;
}

void Concorrente::setEtapaElim(string fase)
{
	EtapaElim = fase;
}

//Mentor

Mentor::Mentor() {}

Mentor::Mentor(string nm) :numOrdem(proxOrdem++)
{
	nome=nm;
}

void Mentor::setEdicao(Edicao* e1)
{
	edicao = e1;
}

int Mentor::getNumOrdem() const
{
	return numOrdem;
}

int Mentor::proxOrdem = 0;

vector<Concorrente*> Mentor::getConcorrentes() const
{
	return concorrentes;
}

string Mentor::getNome() const
{
	return nome;
}

void Mentor::addConcorrente(Concorrente* c1)
{
	if (concorrentes.size() < 14)
		concorrentes.push_back(c1);
	else
		throw VetorCheio(c1->getName());
}

//Interpretacao

Interpretacao::Interpretacao(){}

Interpretacao::Interpretacao(Musica mus)
{
	musica = mus;
}

string Interpretacao::getMus() const
{
	return musica.nome;
}

string Interpretacao::getCan() const
{
	return musica.cantor;
}

void Interpretacao::setConcorrente(Concorrente* c1)
{
	c = c1;
}

Concorrente* Interpretacao::getConcorrente()
{
	return c;
}

vector<int> Interpretacao::getVirouMentor() const
{
	return this->getVirouMentor();
}

//IntProvasCegas
IntProvasCegas::IntProvasCegas(Musica mus) :Interpretacao(mus)
{
	for (size_t i = 0; i < 4; i++)
		virouMentor.push_back(0);
}

void IntProvasCegas::setEliminado()
{
	if (this->getConcorrente())
		this->getConcorrente()->setEtapaElim("ProvasCegas");
	else	
		throw CampoVazio("concorrente");
	
}

void IntProvasCegas::viraMentor(string nome)
{
	bool ret=false;

	for (size_t m = 0; m < this->getConcorrente()->getEdicao()->getMentores().size(); m++)
	{
		if (this->getConcorrente()->getEdicao()->getMentores()[m]->getNome() == nome)
		{
			virouMentor[this->getConcorrente()->getEdicao()->getMentores()[m]->getNumOrdem()] = true;
			ret = true;
			return;
		}
		
	}

 if(!ret)
		throw(ExcecaoConcorrente (nome));
}

void IntProvasCegas::viraMentor(int num)
{
	if ((size_t) num >= this->getConcorrente()->getEdicao()->getMentores().size())
		throw(ExcecaoConcorrente(to_string(num)));
	else
		virouMentor[num] = 1; 
}

vector<int> IntProvasCegas::getVirouMentor() const
{
	return virouMentor;
}

//IntBatalhas

IntBatalhas::IntBatalhas(Musica mus) :Interpretacao(mus){}

bool IntBatalhas::checkBatalhas()	//Executa para a primeira Interpretação Batalhas
{
	int ret=0;
	for (size_t j = 0; j < 4; j++)
		for (size_t i = 0; i < (this->getConcorrente()->getEdicao()->getMentores()[j]->getConcorrentes().size()); i++)
			if (this->getConcorrente()->getEdicao()->foiEliminado(this->getConcorrente()->getEdicao()->getMentores()[j]->getConcorrentes()[i]))
				ret++;

	if (ret != 8)
		return false;
	else
		return true;
}

void IntBatalhas::setEliminado()
{
	if (this->getConcorrente() == NULL)
		throw CampoVazio("concorrente");
	
	this->getConcorrente()->setEtapaElim("Batalhas");
}

//IntSemi

IntSemi::IntSemi(Musica mus, float vot):Interpretacao(mus)
{
	voto = vot;
}

float IntSemi::getVotacao() const
{
	return voto;
};

void IntSemi::setEliminado()
{
	if (this->getConcorrente() == NULL)
		throw CampoVazio("concorrente");

	this->getConcorrente()->setEtapaElim("Semi");
}

bool compareIntSemi(IntSemi* left, IntSemi* right)
{
	return left->getVotacao() < right->getVotacao();
}

//IntFinal

IntFinal::IntFinal(Musica mus, float votP, float votM):Interpretacao(mus)
{
	votPub = votP;
	votMen = votM;
}

float IntFinal::getVotacaoPublico() const
{
	return votPub;
}

float IntFinal::getVotacaoMentor() const
{
	return votMen;
}

void IntFinal::setEliminado()
{
	this->getConcorrente()->setEtapaElim("Final");
}

