#ifndef __NODE_H
#define __NODE_H

namespace MojiAlati 
{

template <typename T> class TListaNode
{
public:
       T Vrijednost;
       TListaNode<T> *Slijedeci;
};


} //end-of-namespace

#endif
