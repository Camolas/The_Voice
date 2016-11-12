#include"voice.h"
#include"Menu.h"

using namespace std;

bool leFicheiro()
{
	ifstream i;
	string info, infoo, infooo;
	double year, concorrenteCounter=0;

	i.open("file.txt");

	i >> year;
	vector < Mentor*> mentoress;
	Edicao e(year);
	getline(i, info);
	for (size_t j = 0; j < 4; j++)
	{
		getline(i, info);
		Mentor* c=new Mentor(info);
		e.addMentor(c);
	}
	for (size_t j = 0; j < 56; j++)
	{
		getline(i, info);
		Concorrente* c=new Concorrente(info);
		e.addConcorrente(c);
	}
	for (size_t j = 0; j < e.getConcorrentes().size(); j++)
	{
		getline(i, info);
		getline(i, infoo);
		IntProvasCegas* c=new IntProvasCegas({ info, infoo });
		e.getConcorrentes()[j]->addInterpretacao(c);
		getline(i, info);
		istringstream inf(info);
		while (inf >> year)
			c->viraMentor(year);
		getline(i, info);
		istringstream mentor(info);
		mentor >> year;
		c->getConcorrente()->setMentor(year);
	}
	for (size_t j = 0; j < e.getConcorrentes().size(); j++)
	{
		if (e.foiEliminado(e.getConcorrentes()[j]))
		{
			getline(i, info);
			getline(i, infoo);
			IntBatalhas* c=new IntBatalhas({ info, infoo });
			e.getConcorrentes()[j]->addInterpretacao(c);
		}
	}
	for (size_t j = 0; j < e.getConcorrentes().size() / 2; j++)
	{
		Concorrente* c1=new Concorrente, *c2=new Concorrente;
		getline(i, info);
		getline(i, infoo);
		for (size_t j = 0; j < e.getConcorrentes().size(); j++)
			if (e.getConcorrentes()[j]->getName() == info)
				c1 = e.getConcorrentes()[j];
			else
				if (e.getConcorrentes()[j]->getName() == infoo)
					c2 = e.getConcorrentes()[j];
		c1->setAdversario(c2);
		getline(i, info);
		if (info == "0")
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
			getline(i, info);
			getline(i, infoo);
			getline(i, infooo);
			istringstream inf(infooo);
			inf >> year;
			IntSemi* c = new IntSemi({ info, infoo }, year);
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
		if (e.foiEliminado(e.getConcorrentes()[j])&&e.getConcorrentes()[j]->getEtapaElim()!="Semi")
		{
			getline(i, info);
			getline(i, infoo);
			getline(i, infooo);
			istringstream inf(infooo);
			inf >> year;
			IntSemi* c = new IntSemi({ info, infoo }, year);
			e.getConcorrentes()[j]->addInterpretacao(c);
			intsemi.push_back(c);
		}
		j++;
	} while (intsemi.size() < 14);
	sort(intsemi.begin(), intsemi.end(), compareIntSemi);
	e.passaFinal(intsemi);

	intsemi.clear();
	j = 0;
	do
	{
		if (e.foiEliminado(e.getConcorrentes()[j]) && e.getConcorrentes()[j]->getEtapaElim() != "Semi")
		{
			getline(i, info);
			getline(i, infoo);
			getline(i, infooo);
			istringstream inf(infooo);
			inf >> year;
			IntSemi* c = new IntSemi({ info, infoo }, year);
			e.getConcorrentes()[j]->addInterpretacao(c);
			intsemi.push_back(c);
		}
		j++;
	} while (intsemi.size() < 10);
	sort(intsemi.begin(), intsemi.end(), compareIntSemi);

	for (size_t k = 0; k < intsemi.size()-1;k++)
		intsemi[k]->getConcorrente()->setEtapaElim("Final");

	e.setVencedor(intsemi[9]->getConcorrente());

	return true;
}

int main()
{
	leFicheiro();
	Edicao e1(2016);
	Concorrente c1("Maria Leal");
	Concorrente c2("C4 Pedro");
	Mentor m1("Quim Barreiros");
	Mentor m2("Ze Cabra");
	Mentor m3("Rosinha");
	Mentor m4("Ana Malhoa");
	e1.addMentor(&m1);
	e1.addMentor(&m2);
	e1.addMentor(&m3);
	e1.addMentor(&m4);
	e1.addConcorrente(&c1);
	e1.addConcorrente(&c2);
	IntProvasCegas i1({ "Madness","Muse" });
	IntProvasCegas i5({ "Bad","Michael Jackson" });
	c1.addInterpretacao(&i1);
	try { i1.viraMentor(2); }
	catch (ExcecaoConcorrente &c1)
	{
		cout << c1.getName() << " nao foi encontrado!\n";								//foiEliminado()
	}
	try { c1.setMentor(1); }
	catch (ExcecaoProvasCegas &c1)
	{
		cout << c2.getName() << " nao virou a cadeira!\n";									//setMentor()
	}
	catch (ExcecaoConcorrente &c1)
	{
		cout << c1.getName() << " nao foi encontrado!\n";								//foiEliminado()
	}
	try{ e1.getVencedor(); }
	catch (CampoVazio &c)
	{
		cout << "Ainda nao ha " << c.getCampo() << "!\n";								//gets
	}
	c2.addInterpretacao(&i5);
	IntBatalhas i2({ "The Lines","Beartooth" });
	try {
		i5.setEliminado();
	}
	catch (ExcecaoConcorrente &c2)
	{
		cout << c2.getName() << " ja foi eliminado!\n";									//setAdversario()
	}
	catch (CampoVazio &c)
	{
		cout << "Ainda nao ha " << c.getCampo() << "!\n";								//gets
	}
	try{ c1.setAdversario(&c2); }
	catch (ExcecaoConcorrente &c2)
	{
		cout << c2.getName() << " ja foi eliminado!\n";									//setAdversario()
	}
	IntSemi i3({ "Some Nights","Fun." },0.44);
	c1.addInterpretacao(&i3);
	IntFinal i4({ "Quero Ser Tua","Suzy" }, 0.27, 0.57);
	c1.addInterpretacao(&i4);
	e1.setVencedor(&c1);
	Sessao s1("01/11/2016","Porto","01/11/2016","Provas Cegas");
	Sessao s2("01/11/2016", "Porto", "01/11/2016","Batalhas");
	Sessao s3("01/11/2016", "Porto", "01/11/2016","Semi");
	Sessao s4("01/11/2016", "Porto", "01/11/2016","Final");
	e1.addSessao(&s1);
	e1.addSessao(&s2);
	e1.addSessao(&s3);
	e1.addSessao(&s4);

	//printMenu();

	try{}
	catch (CampoVazio c)
	{
		cout << "Ainda nao ha " << c.getCampo() << "!\n";								//gets
	}
	catch (ExcecaoConcorrente c1)
	{
		cout << c1.getName() << " nao foi encontrado!\n";								//foiEliminado()
	}
	catch (VetorCheio c)
	{
		cout << c.getName() << "nao foi adicionado/a! O vetor ja se encontra cheio!\n";	//addConcorrente() & addMentor()
	}
/*	*/
}