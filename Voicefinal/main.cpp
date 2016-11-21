#include"voice.h"
#include"Menu.h"

using namespace std;

/**
 * Le o ficheiro de texto de suporte a demonstracao
 * @param edi vetor de Edicao passado por referencia para fazer retorno
 */
void leFicheiro(vector<Edicao>&edi)
{
	ifstream input;
	string str_info, str_info2, str_info3, str_info4;
	float flt_info, flt_info2;
	int int_info;

	input.open("file.txt");

	input >> int_info;
	vector < Mentor*> mentoress;
	Edicao e(int_info);
	getline(input, str_info);
	for (size_t j = 0; j < 4; j++)
	{
		getline(input, str_info);
		Mentor* c=new Mentor(str_info);
		e.addMentor(c);
	}
	for (size_t j = 0; j < 56; j++)
	{
		getline(input, str_info);
		Concorrente* c=new Concorrente(str_info);
		e.addConcorrente(c);
	}
	for (size_t j = 0; j < e.getConcorrentes().size(); j++)
	{
		getline(input, str_info);
		getline(input, str_info2);
		IntProvasCegas* c=new IntProvasCegas({ str_info, str_info2 });
		e.getConcorrentes()[j]->addInterpretacao(c);
		getline(input, str_info);
		istringstream inf(str_info);
		while (inf >> int_info)
			c->viraMentor(int_info);
		getline(input, str_info);
		istringstream mentor(str_info);
		mentor >> int_info;
		c->getConcorrente()->setMentor(int_info);
	}
	for (size_t j = 0; j < e.getConcorrentes().size(); j++)
	{
		if (e.foiEliminado(e.getConcorrentes()[j]))
		{
			getline(input, str_info);
			getline(input, str_info2);
			IntBatalhas* c=new IntBatalhas({ str_info, str_info2 });
			e.getConcorrentes()[j]->addInterpretacao(c);
		}
	}
	for (size_t j = 0; j < e.getConcorrentes().size() / 2; j++)
	{
		Concorrente* c1=new Concorrente, *c2=new Concorrente;
		getline(input, str_info);
		getline(input, str_info2);
		for (size_t j = 0; j < e.getConcorrentes().size(); j++)
			if (e.getConcorrentes()[j]->getName() == str_info)
				c1 = e.getConcorrentes()[j];
			else
				if (e.getConcorrentes()[j]->getName() == str_info2)
					c2 = e.getConcorrentes()[j];
		c1->setAdversario(c2);
		c2->setAdversario(c1);
		getline(input, str_info);
		if (str_info == "0")
			c2->setEtapaElim("Batalhas");
		else
			c1->setEtapaElim("Batalhas");
	}
	
	vector<IntSemi*> intsemi;
	int j = 0;
	do
	{
		if (e.foiEliminado(e.getConcorrentes()[j]))
		{
			getline(input, str_info);
			getline(input, str_info2);
			getline(input, str_info3);
			istringstream inf(str_info3);
			inf >> flt_info;
			IntSemi* c = new IntSemi({ str_info, str_info2 }, flt_info);
			e.getConcorrentes()[j]->addInterpretacao(c);
			intsemi.push_back(c);
		}
		j++;
	} while (intsemi.size() < 14);
	sort(intsemi.begin(), intsemi.end(),compareIntSemi);
	e.passaFinal(intsemi);
	
	intsemi.clear();
	j = 0;
	do
	{
		if (e.foiEliminado(e.getConcorrentes()[j])&& e.getConcorrentes()[j]->getInterpretacoes().size()<3)
		{
			getline(input, str_info);
			getline(input, str_info2);
			getline(input, str_info3);
			istringstream inf(str_info3);
			inf >> flt_info;
			IntSemi* c = new IntSemi({ str_info, str_info2 }, flt_info);
			e.getConcorrentes()[j]->addInterpretacao(c);
			intsemi.push_back(c);
		}
		j++;
	} while (intsemi.size() < 14);
	e.passaFinal(intsemi);

	vector<IntFinal*> intfinal;
	j = 0;
	do
	{
		if (e.foiEliminado(e.getConcorrentes()[j]))
		{
			getline(input, str_info);
			getline(input, str_info2);
			getline(input, str_info3);
			istringstream inf1(str_info3);
			inf1 >> flt_info;
			getline(input, str_info3);
			istringstream inf2(str_info3);
			inf2 >> flt_info2;
			IntFinal* c = new IntFinal({ str_info, str_info2 }, flt_info, flt_info2);
			e.getConcorrentes()[j]->addInterpretacao(c);
			intfinal.push_back(c);
		}
		j++;
	} while (intfinal.size() < 10);

	do
	{
			getline(input, str_info);
			getline(input, str_info2);
			getline(input, str_info3);
			getline(input, str_info4);
			Sessao* c = new Sessao(str_info,str_info2,str_info3,str_info4);
			e.addSessao(c);
	} while (e.getSessoes().size() != 15);

	e.setVencedor(intfinal);

	edi.push_back(e);
}
/**
 * Funcao main onde e lido o ficheiro e chamada a funcao de output do menu
 * @return retorna 0 quando e concluida com sucesso
 */
int main()
{
	
	vector<Edicao> e;
	leFicheiro(e);
	for (size_t i = 0; i < e.size(); i++)
		Concurso::addEdicao(&e[i]);
	printMenu();
	
	return 0;
}
