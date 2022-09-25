#include <iostream>
using namespace std;

#define MAXTAM 5
#define INICIO 1

typedef struct TProjeto
{
    int codigo;    // codigo do projeto
    char nome[30]; // nome do projeto
    int horas;     // numero de horas trabalhas no projeto
};

typedef struct TListaSequencial
{
    TProjeto item[MAXTAM];
    int tamanho;
};

void criaListaVazia(TListaSequencial *lista)
{
    lista->tamanho = 0;
}

bool verificaListaVazia(TListaSequencial *lista)
{
    if (lista->tamanho == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool verificaListaCheia(TListaSequencial *lista)
{
    if (lista->tamanho == MAXTAM)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool insereItem(TListaSequencial *lista, TProjeto item)
{
    if (!verificaListaCheia(lista))
    {
        lista->item[lista->tamanho] = item;
        lista->tamanho++;

        return true;
    }
    else
    {
        return false;
    }
}

int localizaItem(TListaSequencial *lista, int id)
{
    for (int i = 0; i < lista->tamanho; i++)
    {
        if (lista->item[i].codigo == id)
        {
            return i;
        }
    }
    return -1;
}

int removeItem(TListaSequencial *lista, int id)
{
    int posicao = localizaItem(lista, id);
    for (int i = posicao; i < lista->tamanho; i++)
    {
        lista->item[i] = lista->item[i + 1];
    }
    lista->tamanho--;
}

void imprimeLista(TListaSequencial lista)
{
    for (int i = 0; i < lista.tamanho; i++)
    {
        cout << "Código do projeto: " << lista.item[i].codigo << endl;
        cout << "Nome do projeto: " << lista.item[i].nome << endl;
        cout << "Total de horas: " << lista.item[i].horas << endl;
    }
}