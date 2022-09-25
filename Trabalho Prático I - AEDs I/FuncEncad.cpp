#include <iostream>
#include "HeaderSeq.hpp"
using namespace std;

#define MAXTAM 5
#define INICIO 1

typedef struct TCelula *TApontador;

typedef struct TFuncionario
{

    int numero;                // codigo do funcionario
    char nome[20];             // nome do funcionario
    char endereco[40];         // endereco do funcionario
    int dependentes;           // numero de dependentes do funcionario
    TListaSequencial projetos; // Lista Sequencial que guarda os projetos nos quais o funcionario trabalha

} TFuncionario;

typedef struct TCelula
{
    TFuncionario item;
    TApontador prox;
};

typedef struct TListaEncadeada
{
    TApontador primeiro;
    TApontador ultimo;
};

typedef struct TipoItem
{
    int id;
    string nome;
};

void CriaListaVazia(TListaEncadeada *lista)
{
    lista->primeiro = new TCelula;
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

bool verificaListaVazia(TListaEncadeada *lista)
{
    if (lista->primeiro == lista->ultimo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void InserePrimeiroItem(TListaEncadeada *lista, TFuncionario *item)
{
    TApontador aux;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = new TCelula;
    lista->primeiro->prox->prox = aux;
    lista->primeiro->prox->item = *item;
    lista->ultimo = lista->primeiro->prox;
}

void InsereUltimoItem(TListaEncadeada *lista, TFuncionario *item)
{
    lista->ultimo->prox = new TCelula;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->ultimo->item = *item;
}

TApontador ProcuraItem(TListaEncadeada *lista, int id)
{
    TApontador pont;
    pont = lista->primeiro->prox;
    while (pont != NULL)
    {
        if (id == pont->item.numero)
        {
            return pont;
        }
        pont = pont->prox;
    }
    return NULL;
}

void RemoveItemPorId(TListaEncadeada *lista, int id)
{
    if (verificaListaVazia(lista))
    {
        return;
    }

    TApontador aux, anterior, x;

    x = lista->primeiro;

    while (x != NULL)
    {
        if (x->prox->item.numero == id)
        {
            anterior = x;
            break;
        }
        x = x->prox;
    }
    aux = anterior->prox;
    anterior->prox = aux->prox;
    delete aux;
}

void DesalocaLista(TListaEncadeada *lista)
{
    TApontador aux, excluido;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        excluido = aux;
        aux = aux->prox;
        delete excluido;
    }
    delete aux;
}