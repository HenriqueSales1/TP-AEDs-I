#include "FuncSeq.cpp"
#define HEADER_SEQ_H
#ifndef HEADER_SEQ_H

#define MAXTAM 5
#define INICIO 1

void criaListaVazia(TListaSequencial *lista);
bool verificaListaVazia(TListaSequencial *lista);
bool verificaListaCheia(TListaSequencial *lista);
bool insereItem(TListaSequencial *lista, TProjeto item);
int localizaItem(TListaSequencial *lista, int id);
int removeItem(TListaSequencial *lista, int id);
void imprimeLista(TListaSequencial lista);

#endif