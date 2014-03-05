#ifndef __STACK_H
#define __STACK_H

#include <stdexcept>
#include "Niz.hpp"

#ifdef __ALATI_DEBUG
#include <cstdio>
#endif

#ifdef __ALATI_ISPIS
#include <iostream>
#endif

namespace MojiAlati {

/*
 *
 *     template <typename T> TStack
 *
 *     Implementacija Stacka pomocu TNiz klase. TStack omogucuje
 *     rad sa stackom neogranicene velicine (koliko ima memorije).
 *     Ako Push(T&) nema mjesta, stack se povecava za StackRast
 *     velicine. Ova memorija se brise destructorom.
 *
 *     konstruktor
 *            TStack()      konstruktor
 *            ~TStack()     destructor
 *     metode
 *            void Push(T Data)     Stavlja vrijednost na stack
 *            T& Pop()              Uzima vrijednost sa stacka
 *                                  Ako nema nista na stacku - throw underflow_error(...)
 *            void PostaviRast(int) Postavlja StackRast na odredjenu velicinu
 *            bool Prazan()         Da li je stack prazan
 *     operatori
 *            operator[]           Ispis na ekran (ako je definisan makto __ALATI_ISPIS)
 *
 */

const int DefStackRast = 25;

template <typename T> class TStack : public TNiz<T>
{
       int StackIndex;
       int StackRast;
public:
       TStack() : TNiz<T>(DefStackRast)
       {
              StackIndex = 0;
              StackRast = 25;
       }
       
       void Push(T Data)
       {
              (*this)[StackIndex++] = Data;
              if (StackIndex >= Velicina)
                     PovecajVelicinu(StackRast);
       }
       
       T& Pop()
       {
              if(--StackIndex < 0) {
                     #ifdef __ALATI_DEBUG
                     fprintf(stderr,"TStack<T>::Pop() Underflow\n");
                     #endif
                     throw std::underflow_error("Underflow");
              }
              return (*this)[StackIndex];
       }
       
       void PostaviRast(int Rast)
       {
              if (Rast <= 0) return;
              StackRast = Rast;
       }
       
       bool Prazan()
       {
              return !StackRast;
       }
       
       #ifdef __ALATI_ISPIS
       friend std::ostream& operator<< <T>(std::ostream&, TStack&);
       #endif
};

#ifdef __ALATI_ISPIS
template <typename T> std::ostream& operator<<(std::ostream &c, TStack<T> &Stack)
{
       for(int i=Stack.StackIndex-1; i>=0; i--)
              c << Stack[i] << endl;
return c;
}
#endif

}; //end-of-namespace

#endif
