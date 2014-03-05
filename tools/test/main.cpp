#define __ALATI_SVE
#define __ALATI_ISPIS
#include "..\alati.hpp"
#include <iostream>

using namespace std;
using namespace MojiAlati;

int main()
{
TLista<int> Lista;
TListaNode<int> *p;
	Lista.Dodaj(1);
	Lista.Dodaj(224);
	p = Lista.Dodaj(325);
	Lista.Dodaj(425);
	Lista.Dodaj(525);
	TListaIterator<int> Iter(Lista);
	while (!Iter.Kraj()) {
		cout << Iter << endl;
		Iter.Slijedeci();
	}
	cout << "nakon brisanja" << endl;
	Lista.Obrisi(p);
	
	TListaIterator<int> i(Lista);
	while (!i.Kraj()) {
		cout << i << endl;
		i.Slijedeci();
	}
	return 0;
}
