#include "FuncEncad.cpp"
#define HEADER_ENCAD_H
#ifndef HEADER_ENCAD_H

void CriaListaVazia(TListaEncadeada *lista);
bool verificaListaVazia(TListaEncadeada *lista);
void InserePrimeiroItem(TListaEncadeada *lista, TFuncionario *item);
void InsereUltimoItem(TListaEncadeada *lista, TFuncionario *item);
TApontador ProcuraItem(TListaEncadeada *lista, int id);
void RemoveItemPorId(TListaEncadeada *lista, int id);
void DesalocaLista(TListaEncadeada *lista);

#endif