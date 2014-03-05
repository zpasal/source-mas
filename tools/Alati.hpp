#ifndef __ALATI_H
#define __ALATI_H

#ifdef __ALATI_SVE
#define TNIZ
#define TSTACK
#define TLISTA
#define THASH
#define TSTRINGHASH
#define TLISTANODE
#endif


#ifdef TNIZ
#include "Niz.hpp"
#endif

#ifdef TSTACK
#include "Stack.hpp"
#endif

#ifdef TLISTA
#include "Lista.hpp"
#endif

#ifdef THASH
#include "Hash.hpp"
#endif

#ifdef TSTRINGHASH
#include "StringHash.hpp"
#endif

#ifdef TLISTANODE
#include "Node.hpp"
#endif


#endif
