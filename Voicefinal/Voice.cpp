#include "Voice.h"

using namespace std;

class IntFinal;

/**
 * @class Sessao
 *
 * @brief Representam as informações para transmissões televisivas
 *
 * Cada sessão do concurso, independentemente da fase em que ocorre, decorre num dia e local específicos. As
sessões das fases de provas cegas e de batalhas são gravadas e transmitidas na TV em diferido numa data
posterior. Já as sessões da fase de galas são transmitidas em direto
 *
 * @param gra data em que ocorre a gravação
 * @param loc local onde decorrem as gravações
 * @param trans data em que ocorre a tramissão
 * @param fase identifica a fase do The Voice a que a sessão se refere
 *
 */
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
/**
 * @return a data de  gravação da sessão
 */
Date Sessao::getGravacao()
{
	return gravacao;
}
/**
 * @return a data da transmissão da sessão
 */
Date Sessao::getTransmissao()
{
	return transmissao;
}
/**
 * @return o local onde ocorre a sessão
 */
string Sessao::getLocal()
{
	return local;
}
/**
 * determina a edicao do The Voice a que a sessão se refere
 *
 * @param e1 indica a edição é passada por referência para alterar diretamente e assim ocupa menos espaço
 */
void Sessao::setEdicao(Edicao* e1)
{
	edicao = e1;
}
/**
 * @return determina a fase do The Voice a que a sessão se refere
 */
string Sessao::getFase()
{
	return fase;
}
/**
 * @class Concurso -> classe mais geral ou classe mãe
 *
 * @brief Trata-se de um programa de televisão que pode ter várias edições (ano após ano)
 *
 * O The Voice é um concurso televisivo que pretende encontrar as melhores vozes anónimas do país. O concurso
desenrola­se em três fases: uma fase de provas cegas, uma fase de batalhas e uma fase de galas
 *
 * @param gra data em que ocorre a gravação
 * @param loc local onde decorrem as gravações
 * @param trans data em que ocorre a tramissão
 * @param fase identifica a fase do The Voice a que a sessão se refere
 *
 */

/**
 * @return dá o vetor do conjunto de edições em que o concurso ocorre
 */
vector<Edicao*> Concurso::getEdicoes()
{
	return edicoes;
}

/**
 * @return dá o número de edições existentes do concurso
 */
unsigned int Concurso::getNedicoes()
{
	return nedicoes;
}
/**
 * Inicializa o concurso sem edições
 */
unsigned int Concurso::nedicoes = 0;

vector<Edicao*> Concurso::edicoes;
/**
 * acrescenta edições ao concurso à medida que vão surgindo as sucessivas temporadas
 * para isso faz uso da variável static que serve como contador
 *
 * @param e1 adiciona a edição ao vetor
 */
void Concurso::addEdicao(Edicao* e1)
{
	edicoes.push_back(e1);
	nedicoes++;
}

/**
 * remove edições ao concurso
 * acede e altera a variavel static e atualiza com o decremento
 *
 * @param e1 exclui a edição do vetor
 */
void Concurso::removeEdicao(Edicao* e1)
{
	edicoes.erase(edicoes.end() - 1);
	nedicoes--;
}
/**
 * @class Edição -> classe que contêm a lógica do programa televisivo
 *
 * @brief Trata-se de um programa de televisão que pode ter várias edições (ano após ano)
 *
 * Cada edição do programa desenrola­se em três fases: uma fase de provas cegas, uma fase de batalhas e uma fase de galas.
A edição é constituída por concorrentes que são avaliados por quatro mentores, personalidades famosas da música portuguesa, escolhem 14 (elementos) para a sua equipa numa
primeira prova cega. Enquanto o concorrente mostra o seu talento, os mentores, de costas voltadas, consideram
se o seu talento vocal é ou não suficiente para pertencer à sua equipa. Se o jurado considerar que o concorrente
merece pertencer à sua equipa, carrega no botão, o que faz a cadeira rodar e permitir ver o concorrente. Se
existirem dois ou mais mentores a clicar no botão, fica a cargo do concorrente escolher o seu mentor, dentro dos
que carregaram no botão.
 */
/**
 * cria um objecto da classe edição
 */
Edicao::Edicao(){}

/**
 * cria uma edição e inicializa o parametro
 * @param ano em que ocorre a edição
 */
Edicao::Edicao(int ano)
{
	this->ano = ano;
}
/**
 * @brief ordenação e seleção dos concorrentes de cada semifinal, de acordo com a votação que obtêm
 *
 * ordena as interpretações fazendo uso do algoritmos de ordenação sort, consoante a votação que foi obtida.
 * usa o critério compareIntSemi, que é o 3º parâmetro do sort
 * resulta na atualização da fase dos concorrentes eliminados na fase semi-final
 * passam os cinco melhores interpretações (com votações mais altas)
 *
 * @param intsemi recebe como parâmetro um vetor de interpretações para cada semi-final
 */
void Edicao::passaFinal(vector<IntSemi*> intsemi)
{
	sort(intsemi.begin(), intsemi.end(), compareIntSemi);

	for (size_t i = 0; i < 9; i++)
		intsemi[i]->getConcorrente()->setEtapaElim("Semi");
}
/**
 * @return devolve os 4 mentores existentes naquela edição
 */
vector<Mentor*> Edicao::getMentores()
{
	return mentores;
}
/**
 * @return devolve o ano em que a edição ocorre
 */
int Edicao::getAno()
{
	return ano;
}
/**
 * @return devolve o vencedor da edição em causa
 */
Concorrente* Edicao::getVencedor()
{
	return vencedor;
}
/**
 * devolve todos os concorretes participantes na edição
 * @return devolve um vetor de apontador para objetos do tipo Concorrente
 */
vector<Concorrente*> Edicao::getConcorrentes()
{
	return concorrentes;
}
/**
 * determina se o concorrente específicado esta fora da edição do The Voice
 *
 *@param c1 corresponde a um apontador para um objecto do tipo Concorrente e edita diretamente (passagem por referência)
 *@return Falso se ainda se encontrar em competição
 */
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

	return 1;
}
/**
 * verifica se a votacao das semi finais esta corrompida, ou nao
 *
 *@return True se nao estiver corrompida, Falso caso contrario
 *
 */
bool Edicao::checkVotacaoSemi() const
{
	float sum = 0;

	for (auto i = 0; i < concorrentes.size(); i++)
		if (concorrentes[i]->getInterpretacoes().size() == 3)
			sum += concorrentes[i]->getInterpretacoes()[2]->getVotacao();

	if (sum > 1)
		return false;
	else
		return true;

}
/**
 * verifica se a votacao das mentores na final esta corrompida, ou nao
 *
 *@return True se nao estiver corrompida, Falso caso contrario
 *
 */
bool Edicao::checkVotacaoFinalMentor() const
{
	float sum = 0;

	for (auto i = 0; i < concorrentes.size(); i++)
		if (concorrentes[i]->getInterpretacoes().size() == 4)
			sum += concorrentes[i]->getInterpretacoes()[3]->getVotacaoMentor();

	if (sum > 1)
		return false;
	else
		return true;
}
/**
 * verifica se a votacao do publico na final esta corrompida, ou nao
 *
 *@return True se nao estiver corrompida, Falso caso contrario
 *
 */
bool Edicao::checkVotacaoFinalPublico() const
{
	float sum = 0;

	for (auto i = 0; i < concorrentes.size(); i++)
		if (concorrentes[i]->getInterpretacoes().size() == 4)
			sum += concorrentes[i]->getInterpretacoes()[3]->getVotacaoPublico();

	if (sum > 1)
		return false;
	else
		return true;
}
/**
 * adiciona o concorrente c1 a edicao
 *
 *@param c1 corresponde a um apontador para um objecto do tipo Concorrente
 *
 */
void Edicao::addConcorrente(Concorrente* c1)
{
	c1->setEdicao(this);

	concorrentes.push_back(c1);
}
/**
 * adiciona o concorrente m1 a edicao
 *
 *@param m1 corresponde a um apontador para um objecto do tipo Mentor
 *
 */
void Edicao::addMentor(Mentor* m1)
{
	m1->setEdicao(this);

	mentores.push_back(m1);
}
/**
 * ordena um vetor de IntFinal conforme a votacao, de forma a determinar o concorrente vencedor
 *
 *@param intfinal corresponde a um vetor de apontadores para objectos do tipo IntFinal
 *
 */
void Edicao::setVencedor(vector<IntFinal*> intfinal)
{
	sort(intfinal.begin(), intfinal.end(), compareIntFinal);

	for (size_t k = 0; k < intfinal.size() - 1; k++)
		intfinal[k]->getConcorrente()->setEtapaElim("Final");

	vencedor = intfinal[9]->getConcorrente();
}
/**
 * adiciona a Sessao s1 a edicao
 *
 *@param s1 corresponde a um apontador para um objecto do tipo Sessao
 *
 */
void Edicao::addSessao(Sessao* s1)
{
	int counter=0;

	for (size_t i = 0; i < sessoes.size(); i++)
		if (sessoes[i]->getFase() == s1->getFase())
			counter++;

	s1->setEdicao(this);

	sessoes.push_back(s1);
}
/**
 * retorna o vetor de sessoes da edicao a que se refere
 *
 *
 *@return vetor de Sessoes da edicao
 */
vector<Sessao*> Edicao::getSessoes() const
{
	return sessoes;
}

/**
 * @class Concorrente
 *
 * @brief Representa cada concorrente
 *
 * Cada concorrente do concurso e identificado por um objeto desta classe. Sendo que cada um tem um nome,
 uma edicao em que participou, um vetor das interpretacoes feitas ao longo da edicao. Para alem disso tem
 ainda o mentor que lhe foi associado nas provas cegas e o adversario das batalhas. Por ultimo, e ainda
 identificado pela etapa em que foi eliminado
 *
 * @param nome nome do concorrente
 * @param edicao edicao em que o concorrente participou 
 * @param interpretacoes vetor das interpretacoes do concorrente
 * @param EtapaElim identifica a fase em que o concorrente foi eliminado
 * @param mentor mentor do concorrente
 * @param adv adversario do concorrente nas batalhas
 *
 */

/**
 * cria um objecto da classe concorrente
 */
Concorrente::Concorrente(){}

/**
 * cria um concorrente inicializando o nome
 * @param nome do concorrente
 */
Concorrente::Concorrente(string nm)
{
	nome = nm;
}
/**
 * adiciona o adversario das batalhas
 *
 *@param c1 corresponde a um apontador para um objecto do tipo Concorrente
 *
 */
void Concorrente::setAdversario(Concorrente* c1)
{
	if (c1->getEdicao()->foiEliminado(c1) && this->getMentor()==c1->getMentor())
	{
		adv = c1;
	}
}
/**
 * faz o return do adversario do concorrente a que se refere
 *
 *@return Apontador para o concorrente adversario do concorrente ao qual se refere a funcao
 *
 */
Concorrente* Concorrente::getAdversario() const
{
	return adv;
}
/**
 * atualiza o campo edicao do concorrente
 *
 *@param e1 corresponde a um apontador para um objecto do tipo Edicao
 *
 */
void Concorrente::setEdicao(Edicao* e1)
{
	edicao = e1;
}
/**
 * faz o return do vetor de interpretacoes do concorrente
 *
 *@return vetor Apontador para as interpretacoes do concorrente
 *
 */
vector<Interpretacao*> Concorrente::getInterpretacoes() const
{
	return interpretacoes;
}
/**
 * faz o return do nome do concorrente
 *
 *@return nome do concorrente
 *
 */
string Concorrente::getName() const
{
	return nome;
}
/**
 * faz o return da etapa em que o concorrente foi eliminado
 *
 *@return etapa em que o concorrente foi eliminado
 *
 */
string Concorrente::getEtapaElim() const
{
	return EtapaElim;
}
/**
 * adiciona a interpretacao ao concorrente
 *
 *@param i1 corresponde a um apontador para um objecto do tipo Intepretacao
 *
 */
void Concorrente::addInterpretacao(Interpretacao* i1)
{
	interpretacoes.push_back(i1);

	i1->setConcorrente(this);
}
/**
 * atualiza o campo mentor do concorrente
 *
 *@param m1 corresponde ao indice do mentor no vetor de mentores
 *
 */
void Concorrente::setMentor(int m1)
{
	mentor = this->getEdicao()->getMentores()[m1];
		mentor->addConcorrente(this);
}
/**
 * faz o return do mentor do concorrente
 *
 *@return apontador para o Mentor do concorrente
 *
 */
Mentor* Concorrente::getMentor()
{
	return mentor;
}
/**
 * faz o return da edicao do concorrente
 *
 *@return apontador para a Edicao do concorrente
 *
 */
Edicao* Concorrente::getEdicao()
{
	return edicao;
}
/**
 * atualiza o campo EtapaElim do concorrente correpondente à etapa em que foi eliminado
 *
 *@param fase e uma string com o nome da fase ou etapa em que o concorrente foi elilinado
 *
 */
void Concorrente::setEtapaElim(string fase)
{
	EtapaElim = fase;
}
/**
 * compara concorrentes quanto ao seu nome
 *
 *@param a corresponde a um apontador para um objecto do tipo Concorrente
 *@param b corresponde a um apontador para um objecto do tipo Concorrente
 *@return Verdadeiro se o nome de a for menor que o de b
 */
bool compareConcorrentes(Concorrente* a, Concorrente* b) { return (a->getName() < b->getName()); }

/**
 * @class Mentor
 *
 * @brief Representam cada Mentor
 *
 * Cada mentor do concurso e identificado por um objeto desta classe. Sendo que cada um tem um nome,
 uma edicao em que participou, um vetor das interpretacoes feitas ao longo da edicao. Para alem disso tem
 ainda o mentor que lhe foi associado nas provas cegas e o adversario das batalhas. Por ultimo, e ainda
 identificado pela etapa em que foi eliminado
 *
 * @param nome nome do mentor
 * @param edicao edicao em que o mentor participou 
 * @param concorrentes vetor das concorrentes do mentor
 *
 */

/**
 * cria um objecto da classe mentor
 */
Mentor::Mentor() {}

/**
 * cria um mentor inicializando o nome
 * @param nome do mentor
 */
Mentor::Mentor(string nm)
{
	nome=nm;
}
/**
 * atualiza o campo edicao do mentor
 *
 *@param e1 corresponde a um apontador para um objecto do tipo Edicao
 *
 */
void Mentor::setEdicao(Edicao* e1)
{
	edicao = e1;
}
/**
 * compara mentores quanto ao seu nome
 *
 *@param a corresponde a um apontador para um objecto do tipo Mentor
 *@param b corresponde a um apontador para um objecto do tipo Mentor
 *@return Verdadeiro se o nome de a for menor que o de b
 */
bool compareMentores(Mentor* a, Mentor* b) { return (a->getNome() < b->getNome()); }
/**
 * devolve os concorrentes do mentor
 * @return devolve um vetor de apontador para objetos do tipo Concorrente
 */
vector<Concorrente*> Mentor::getConcorrentes() const
{
	return concorrentes;
}
/**
 * faz o return do nome do mentor
 *
 *@return nome do mentor
 *
 */
string Mentor::getNome() const
{
	return nome;
}
/**
 * adiciona o concorrente c1 ao mentor
 *
 *@param c1 corresponde a um apontador para um objecto do tipo Concorrente
 *
 */
void Mentor::addConcorrente(Concorrente* c1)
{
	concorrentes.push_back(c1);
}

/**
 * @class Intepretacao
 *
 * @brief Classe base das interpretacoes de cada fase
 *
 * Cada mentor do concurso e identificado por um objeto desta classe. Sendo que cada um tem um nome,
 uma edicao em que participou, um vetor das interpretacoes feitas ao longo da edicao. Para alem disso tem
 ainda o mentor que lhe foi associado nas provas cegas e o adversario das batalhas. Por ultimo, e ainda
 identificado pela etapa em que foi eliminado
 *
 * @param musica musica da intepretacao, do tipo Musica definida por uma struct
 * @param c concorrente a que se refere a interpretacao
 *
 */

/**
 * cria um objecto da classe interpretacao
 */
Interpretacao::Interpretacao(){}

/**
 * cria uma interpretacao incializando a musica
 * @param mus musica cantada
 */
Interpretacao::Interpretacao(Musica mus)
{
	musica = mus;
}
/**
 * retorna o nome da musica
 * @return nome da musica
 */
string Interpretacao::getMus() const
{
	return musica.nome;
}
/**
 * retorna o cantor da musica
 * @return cantor da musica
 */
string Interpretacao::getCan() const
{
	return musica.cantor;
}
/**
 * atualiza o campo c da interpretacao
 * @param c1 apontador para um objeto da classe Concorrente
 */
void Interpretacao::setConcorrente(Concorrente* c1)
{
	c = c1;
}
/**
 * retorna o concorrente a que se refere a interpretacao
 * @return retorna o concorrente a que se refere a interpretacao
 */
Concorrente* Interpretacao::getConcorrente()
{
	return c;
}
/**
 * retorna o vetor de mentores que contem a informacao dos que viraram ou nao
 * @return vetor de inteiros onde 1 representa que o mentor virou e 0 que o mentor nao virou
 */
vector<int> Interpretacao::getVirouMentor() const
{
	return this->getVirouMentor();
}

/**
 * @class IntProvasCegas
 *
 * @brief Classe derivada das interpretacoes pela qual sao representadas as interpretacoes das provas cegas
 *
 * Tem como parametro adicional o vetor de inteiros representando os mentores que viraram ou nao a cadeira
 *
 * @param virouMentor vetor de inteiros representando os mentores que viraram ou nao a cadeira
 *
 */
 /**
 * cria uma interpretacao das provas cegas incializando a musica
 * @param mus musica cantada
 */
IntProvasCegas::IntProvasCegas(Musica mus) :Interpretacao(mus)
{
	for (size_t i = 0; i < 4; i++)
		virouMentor.push_back(0);
}
 /**
 * coloca a 1 (verdadeiro) os mentores que viram a cadeira
 * @param num indice do mentor no vetor de mentores
 */
void IntProvasCegas::viraMentor(int num)
{
	virouMentor[num] = 1; 
}
/**
 * retorna o vetor de mentores que contem a informacao dos que viraram ou nao
 * @return vetor de inteiros onde 1 representa que o mentor virou e 0 que o mentor nao virou
 */
vector<int> IntProvasCegas::getVirouMentor() const
{
	return virouMentor;
}

/**
 * @class IntBatalhas
 *
 * @brief Classe derivada das interpretacoes pela qual sao representadas as interpretacoes das batalhas
 *
 * Nao tem parametros adicionais, sendo que tem apenas funcoes de suporte a implementacao
 *
 */
  /**
 * cria uma interpretacao das provas cegas incializando a musica
 * @param mus musica cantada
 */
IntBatalhas::IntBatalhas(Musica mus) :Interpretacao(mus){}
 
 /**
 * verifica a existencia, ou nao, dos 8 concorrentes 
 * @return Verdaeiro se =8, Falso se !=8
 */
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
/**
 * auxiliar na atualizacao do campo EtapaElim do concorrente correpondente à etapa em que foi eliminado
 *
 */
void IntBatalhas::setEliminado()
{
	this->getConcorrente()->setEtapaElim("Batalhas");
}

/**
 * @class IntSemi
 *
 * @brief Classe derivada das interpretacoes pela qual sao representadas as interpretacoes das semis
 *
 * Nas semis, o voto do publico e crucial na continuidade do concorrente no concurso
 *
 * @param voto voto do publico
 */
  /**
 * cria uma interpretacao das semis incializando a musica e o voto
 * @param mus musica cantada
 * @param vot voto do publico
 */
IntSemi::IntSemi(Musica mus, float vot):Interpretacao(mus)
{
	voto = vot;
}
 /**
 * retorna o voto do publico
 * @return voto retorna o voto do publico
 */
float IntSemi::getVotacao() const
{
	return voto;
};
/**
 * auxliar na atualizacao do campo EtapaElim do concorrente correpondente à etapa em que foi eliminado
 *
 */
void IntSemi::setEliminado()
{
	this->getConcorrente()->setEtapaElim("Semi");
}
/**
 * compara interpretcoes da semi de acordo com a votacao obtida em cada
 * @param left objeto do tipo apontador para IntSemi
 * @param right objeto do tipo apontador para IntSemi
 * @return retorna Verdadeiro se a IntSemi left teve menos votos que IntSemi right, Falso noutro caso
 */
bool compareIntSemi(IntSemi* left, IntSemi* right)
{
	return left->getVotacao() < right->getVotacao();
}

/**
 * @class IntFinal
 *
 * @brief Classe derivada das interpretacoes pela qual sao representadas as interpretacoes da final
 *
 * Na final do concurso, cada interpretacao recebe votacao do publico e dos mentores
 *
 * @param votPub representa a votacao do publico
 * @param votMen representa a votacao dos mentores
 */
  /**
 * cria uma interpretacao da final incializando a musica e os votos
 * @param mus musica cantada
 * @param votP voto do publico
 * @param votM voto do mentor 
 */
IntFinal::IntFinal(Musica mus, float votP, float votM):Interpretacao(mus)
{
	votPub = votP;
	votMen = votM;
}
 /**
 * retorna o voto do publico
 * @return votPub retorna o voto do publico
 */
float IntFinal::getVotacaoPublico() const
{
	return votPub;
}
 /**
 * retorna o voto dos mentores
 * @return votMen retorna o voto dos mentores
 */
float IntFinal::getVotacaoMentor() const
{
	return votMen;
}
/**
 * auxliar na atualizacao do campo EtapaElim do concorrente correpondente à etapa em que foi eliminado
 *
 */
void IntFinal::setEliminado()
{
	this->getConcorrente()->setEtapaElim("Final");
}
/**
 * compara interpretcoes da final de acordo com a soma das votacoes obtidas em cada
 * @param left objeto do tipo apontador para IntFinal
 * @param right objeto do tipo apontador para IntFinal
 * @return retorna Verdadeiro se a IntFinal left teve menos votos que IntFinal right, Falso noutro caso
 */
bool compareIntFinal(IntFinal* left, IntFinal* right)
{
	return ((left->getVotacaoMentor() + left->getVotacaoPublico()) < (right->getVotacaoMentor() + right->getVotacaoPublico()));
}
