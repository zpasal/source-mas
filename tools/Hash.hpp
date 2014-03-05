#ifndef __HASH_H
#define __HASH_H

#include <stdexcept>
#include "Node.hpp"

#ifdef __ALATI_DEBUG
#include <cstdio>
#endif

#ifdef __ALATI_ISPIS
#include <iostream>
#endif

namespace MojiAlati {

/*
 * template <typename T, typename THashClass> clas THash
 *
 * Jednostavna implementacija hashiranje.
 *
 * template parametri
 * 	T		- tip podataka u hash tabeli
 * 	THashClass 	- vidi ispod
 *
 * THashClass je klasa koja mora imati default constructor i
 * javnu funkciju koja prima tip T kao argumnet i vraca int.
 * Ova funkcija treba da mapira podatak u odredjenu lokaciju
 * u hash tabeli. Ako je hash tabela premala da bi se indeksirala
 * sa dobijenom vrijednoscu uzima se ostatak pri djeljenju sa
 * Velicina (predstavlja velicinu tabele):
 *
 * class MojStringHash
 * {
 * public:
 * 	int Hash(string &s) {
 * 	char *p = s.c_ptr();
 * 	int v = 0;
 * 		while(*p)
 * 			v = v << 1 ^ *p++;
 * 		if (v < 0)
 * 			v = -v;
 * 	return v;
 * 	}
 * };
 *
 * int main()
 * {
 * THash<string, MojStringHash> h(8);
 * 		h.Dodaj(string("Hallo"));
 * 		h.Dodaj(string("Hallo"));
 * 		cout << h << endl
 * }
 *
 * cons/dest
 * 	THash(int V)	konstruktor (V - velicina tabele)
 * 	~THash()	destruktor
 * metode
 * 	int Dodaj(T &)	dodavanje podatka u hash tabelu. Vraca broj
 * 			koji predstavlja indeks unutar hash tabele
 * 	int Dodaj(const T&)	dodavanje ....
 * 	T* Pronadji(T&)	trazenje podatka (ako podataka postoji vraca
 * 			poiner na njega, inace NULL)
 * operator
 * 	operator<<	Ispis na ekran (ako je definisan makro __ALATI_ISPIS)
 * private
 * 	KillTableOn(int) Izbaciva sve podatke iz tabele na indeksu
 * 			 (ovu funkciju koristi destruktor)
 */



template <typename T, typename THashClass> class THash
{
	TListaNode<T> **Tabela;
	THashClass *HashClass;
	int Velicina, Sadrzi;
public:
	THash(int Vel)
	{
		try {
			HashClass = new THashClass;
			Tabela = new TListaNode<T>*[Velicina = Vel];
		}
		catch(std::exception &e) {
			#ifdef __ALATI_DEBUG
			fprintf(stderr,"THash<T, THashClass> %s", e.what());
			#endif
			delete HashClass;
			delete Tabela;
			throw;
		}
		for(int i=0; i<Velicina; i++)
			Tabela[i] = 0;
		Sadrzi = 0;
	}

	~THash();

	int Dodaj(T &);

	int Dodaj(const T &Pod)
	{
		return Dodaj((T&)Pod);
	}

	T* Pronadji(T &);

	T* Pronadji(const T &Pod)
	{
		return Pronadji((T&)Pod);
	}

	#ifdef __ALATI_ISPIS
	friend std::ostream& operator<< <T, THashClass>(std::ostream&, THash<T, THashClass>&);
	#endif
private:
	void KillTabelaOn(int i);
};

template <typename T, typename THashClass> void THash<T,THashClass>::KillTabelaOn(int i)
{
TListaNode<T> *p, *n;
	p = Tabela[i];
	if (p == 0) return;
	if (p->Slijedeci == 0) 
		delete p;
	else {
		n = p->Slijedeci;
		while(n != 0) {
			delete p;
			p = n;
			n = n->Slijedeci;
		}
		delete p;
	}
}

template <typename T, typename THashClass> THash<T,THashClass>::~THash()
{
	for(int i=0; i<Velicina; i++) 
		KillTabelaOn(i);
}

template <typename T, typename THashClass> int THash<T,THashClass>::Dodaj(T &Pod)
{
int Mjesto;
	if (Sadrzi >= Velicina) 
		return -1;
	Mjesto = HashClass->Hash(Pod) % Velicina;
	if (Tabela[Mjesto] == 0) {
		Tabela[Mjesto] = new TListaNode<T>;
		Tabela[Mjesto]->Slijedeci = 0;
		Tabela[Mjesto]->Vrijednost = Pod;
	}
	else {
		TListaNode<T>* p = Tabela[Mjesto];
		while(p->Slijedeci != 0) 
			p = p->Slijedeci;
		p->Slijedeci = new TListaNode<T>;
		p = p->Slijedeci;
		p->Slijedeci = 0;
		p->Vrijednost = Pod;
	} 
	Sadrzi++;
return 0;
}

template <typename T, typename THashClass> T* THash<T,THashClass>::Pronadji(T &Pod)
{
int Mjesto = HashClass->Hash(Pod) % Velicina;
TListaNode<T> *p;
	if (Tabela[Mjesto] == 0) return 0;
	p = Tabela[Mjesto];
	while(p != 0) {
		if (p->Vrijednost == Pod) 
			return &p->Vrijednost;
		p = p->Slijedeci;
	}
return 0;	
}


#ifdef __ALATI_ISPIS
template <typename T, typename THashClass> std::ostream& operator<<(std::ostream& c, THash<T, THashClass>& Hash)
{
TListaNode<T> *p;
	for(int i=0; i<Hash.Velicina; i++) {
		p = Hash.Tabela[i];
		if (p == 0)
			c << "[]" << endl;
		else {
			c << "[ ";
			while(p->Slijedeci) {
				c << p->Vrijednost << " | ";
				p = p->Slijedeci;
			}
			c << p->Vrijednost << " ]" << endl;
		}
	}
return c;
}
#endif

} // end-of-namespace

#endif
