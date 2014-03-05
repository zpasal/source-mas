#ifndef __NIZ_H
#define __NIZ_H

#include <stdexcept>

#ifdef __ALATI_DEBUG
#include <cstdio>
#endif

#ifdef __ALATI_ISPIS
#include <iostream>
#endif


namespace MojiAlati
{

/*
 *
 *     template <typename T> TNiz
 *
 *     Jednaostavna implementacija generickog niza.
 *
 *     NAPOMENA: argument templatea mora imati:
 *                   default constructor
 *                   copy constructor
 *
 *
 *     konstruktori
 *            TNiz()        - Prazan niz
 *            TNiz(int v)   - Niz velicine 'v'
 *            TNiz(TNiz &)  - copy konstruktor
 *            ~TNiz()       - destructor
 *     metode
 *            int UzmiVelicinu()          - vraca velicinu niza
 *            void PovecajVelicinu(int A) - povecava niz za 'A'
 *            T& Uzmi(int Index)          - uzimanje elementa na indeksu 'Index'
 *                                          ako je index van ranga throw out_of_range(...)
 *     operatori
 *            T& operator[]        - indeksiranje (ne vodi se racuna o pravilnosti indeksa)
 *            operator<<           - ispis niza (ako je definisan makro __ALATI_ISPIS)
 *
 *     protected:
 *            T* Baza              - pointer na niz
 *            int Velicina         - velicina niza
 */

template <typename T> class TNiz
{
protected:
       T *Baza;
       int Velicina;
public:
       TNiz()
       {
              Baza = 0;
              Velicina = 0;
       }
       
       TNiz(int v)
       {
              try {
                     Baza = new T[Velicina = v];
              }
              catch(std::exception &e) {
                     #ifdef __ALATI_DEBUG
                     fprintf(stderr, "TNiz<T>::TNiz(int) %s\n", e.what());
                     #endif
                     throw; // rethrow korisniku
              }
       }

       TNiz(TNiz &); // copy constructor

       ~TNiz()
       {
              delete Baza;
       }

       T& operator[](int Index)
       {
       return Baza[Index];
       }

       T& Uzmi(int Index) {
              if (Index < 0 || Index >= Velicina) {
                     #ifdef __ALATI_DEBUG
                     fprintf(stderr, "TNiz<T>::Uzmi(int) OutOfRange\n");
                     #endif
                     throw std::out_of_range("OutOfRange");
              }
       return Baza[Index];
       }

       int  UzmiVelicinu()
       {
       return Velicina;
       }

       void PovecajVelicinu(int);
       
       #ifdef __ALATI_ISPIS
       friend std::ostream& operator<< <T>(std::ostream&, TNiz<T> &);
       #endif
};

template <typename T>TNiz<T>::TNiz(TNiz &Niz)
{
       if (this == &Niz) return;
       delete Baza;
       Baza = new T[Velicina = Niz.Velicina];
       for(int i=0; i<Velicina; i++)
              (*this)[i] = Niz[i];
}

template <typename T> void TNiz<T>::PovecajVelicinu(int Add)
{
       if (Add < 0) return;
       T* Temporal;
       try {
              Temporal = new T[Velicina + Add];
       }
       catch(std::exception &e) {
              #ifdef __ALATI_DEBUG
              fprintf(stderr, "TArray<T>::Resize(int) %s", e.what());
              #endif
              throw; // rethrow korisniku da ispita
       }
       for(int i=0; i<Velicina; i++)
              Temporal[i] = Baza[i];
       delete Baza;
       Baza = Temporal;
       Velicina += Add;
}

#ifdef __ALATI_ISPIS
template <typename T> std::ostream& operator<<(std::ostream& c, TNiz<T> &Niz)
{
       for(int i=0; i<Niz.Velicina; i++)
              c << Niz[i] << " ";
return c;
}
#endif


} // end-of-namespace

#endif
