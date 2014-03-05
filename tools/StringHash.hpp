#ifndef __STRINGHASH_H
#define __STRINGHASH_H

#include <stdexcept>
#include "Node.hpp"

#ifdef __ALATI_DEBUG
#include <cstdio>
#endif

#ifdef __ALATI_ISPIS
#include <iostream>
#endif

namespace MojiAlati {


template <typename THashClass> class TStringHash
{
	THashClass *HashClass;
	TListaNode<char*> *Tabela;
	int Velicina, Sadrzi;
public:
	TStringHash(int Vel)
	{
		Tabela = new TListaNode<char*>[Velicina = Vel];
		for(int i=0; i<Velicina; i++) {
			Tabela[i].Slijedeci = 0;
			Tabela[i].Vrijednost = 0;
		}
		HashClass = new THashClass;
		Sadrzi = 0;
	}

	int Dodaj(char *);
	int Dodaj(const char *String)
	{
		return Dodaj((char*)String);
	}

	char* Pronadji(char*);
	#ifdef __ALATI_ISPIS
	friend std::ostream& operator<< <THashClass>(std::ostream&, TStringHash<THashClass> &);
	#endif
};


template <typename THashClass> int TStringHash<THashClass>::Dodaj(char *String)
{
int Mjesto;
TListaNode<char*> *p;
	if (Sadrzi >= Velicina)
		return -1;
	Mjesto = HashClass->Hash(String) % Velicina;
	p = &Tabela[Mjesto];
	if (p->Vrijednost == 0) {
		p->Vrijednost = new char[strlen(String)+1];
		strcpy(p->Vrijednost, String);
	}
	else {
		while(p->Slijedeci != 0)
			p = p->Slijedeci;
		p->Slijedeci = new TListaNode<char*>;
		p = p->Slijedeci;
		p->Slijedeci = 0;
		p->Vrijednost = new char[strlen(String)+1];
		strcpy(p->Vrijednost, String);
	}
	Sadrzi++;
return Mjesto;
}

template <typename THashClass> char* TStringHash<THashClass>::Pronadji(char *String)
{
int Mjesto = HashClass->Hash(String) % Velicina;
TListaNode<char*> *p = &Tabela[Mjesto];
	if (p->Vrijednost == 0) // nema niti jednog na tom indeksu
		return 0;
	while(p != 0)
	{
		if (!strcmp(String, p->Vrijednost))
			return p->Vrijednost;
		p = p->Slijedeci;
	}
return 0;
}

#ifdef __ALATI_ISPIS
template <typename THashClass> std::ostream& operator<<(std::ostream& c, TStringHash<THashClass> &Hash)
{
TListaNode<char*> *p;
	for(int i=0; i<Hash.Velicina; i++) {
		if (Hash.Tabela[i].Slijedeci == 0) {
			if (Hash.Tabela[i].Vrijednost == 0)
				c << "[]" << endl;
			else c << "[ " << Hash.Tabela[i].Vrijednost << "]" << endl;
		}
		else {
			p = &Hash.Tabela[i];
			c << "[ ";
			while(p != 0) {
				c << p->Vrijednost << " ";
				p = p->Slijedeci;
			}
			c << " ]" << endl; 
		}
	}
return c;
}
#endif

} // kraj namespacea 'MojiAlati'

#endif

