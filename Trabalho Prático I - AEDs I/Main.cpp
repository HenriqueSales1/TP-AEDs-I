#include <iostream>
#include <fstream>
#include <windows.h>
// #include <string.h>
#include "HeaderEncad.hpp"

using namespace std;

void LerArquivo(TListaEncadeada *listaEnc, int *IDFuncionario, int *IDProjeto)
{
    FILE *file = fopen("funcionarios.bin", "r");
    TFuncionario funcionario;
    if (file != NULL)
    {
        while (fread(&funcionario, sizeof(TFuncionario), 1, file))
        {
            if (funcionario.numero > *IDFuncionario)
            {
                *IDFuncionario = funcionario.numero;
            }
            for (int i = 0; i < funcionario.projetos.tamanho; i++)
            {
                if (funcionario.projetos.item[i].codigo > *IDProjeto)
                {
                    *IDProjeto = funcionario.projetos.item[i].codigo;
                }
            }
            InsereUltimoItem(listaEnc, &funcionario);
        }
    }
}

void SalvaArquivo(TListaEncadeada *listaEnc)
{
    FILE *file = fopen("funcionarios.bin", "w");
    TApontador aux = listaEnc->primeiro->prox;
    while (aux != NULL)
    {
        fwrite(&aux->item, sizeof(TFuncionario), 1, file);
        aux = aux->prox;
    }
}

int main()
{
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);

    TListaEncadeada listaEnc; // lista que contém os funcionários
    CriaListaVazia(&listaEnc);

    int IDProjeto = 0;     // ID do projeto (contador)
    int IDFuncionario = 0; // ID do funcionário (contador)

    LerArquivo(&listaEnc, &IDFuncionario, &IDProjeto);

    IDFuncionario++;
    IDProjeto++;

    int escolha;  // define o "case" no switch
    int IDRemove; // define o ID do projeto a ser removido
    int IDDesejo; // define o ID do funcionario que terá um projeto incluido

    float SalarioBruto;
    float SalarioLiq;
    float INSS;
    float IR;

    TApontador apont; // apontador para os dados das structs

    do
    {
        cout << "Menu\n\n";
        cout << "1. Cadastrar novo funcionário\n";
        cout << "2. Cadastrar novo projeto\n";
        cout << "3. Excluir projeto\n";
        cout << "4. Excluir funcionário sem projeto\n";
        cout << "5. Consultar funcionário\n";
        cout << "6. Imprimir contracheque\n";
        cout << "7. Sair\n";
        cout << "\n";
        cin >> escolha;
        switch (escolha)
        {

        case 1:

            TFuncionario funcionario;

            funcionario.numero = IDFuncionario;
            cout << "\nInsira os dados do funcionário - nome, endereço e número de dependentes, respectivamente.\n\n";
            cin.ignore();
            cin.getline(funcionario.nome, 20);
            cin.getline(funcionario.endereco, 40);
            cin >> funcionario.dependentes;

            criaListaVazia(&funcionario.projetos);

            InsereUltimoItem(&listaEnc, &funcionario);

            cout << "\n\nFuncionário cadastrado com sucesso.\n\n";

            break;

        case 2:

            TProjeto projeto;
            projeto.codigo = IDProjeto;

            cout << "\nInsira as especificações do projeto - nome e total de horas, respectivamente.\n\n";

            cin.ignore();
            cin.getline(projeto.nome, 30);
            cin >> projeto.horas;

            cout << "\n\nA qual funcionário deseja designar o projeto?\n\n";
            cin >> IDDesejo;

            apont = ProcuraItem(&listaEnc, IDDesejo);

            if (apont == NULL)
            {
                cout << "Erro";
            }
            else
            {
                insereItem(&apont->item.projetos, projeto);
            }

            cout << "\n\nProjeto cadastrado com sucesso no funcionário de ID " << IDDesejo << ".\n\n";

            break;

        case 3:

            cout << "\n\nInsira o ID do projeto a ser excluido.\n";
            cin >> IDDesejo;

            apont = ProcuraItem(&listaEnc, IDDesejo);
            imprimeLista(apont->item.projetos);

            cin >> IDRemove;

            removeItem(&apont->item.projetos, IDRemove);
            cout << "\n\nProjeto removido com sucesso.\n\n";

            break;

        case 4:

            apont = listaEnc.primeiro->prox;

            while (apont != NULL)
            {
                if (apont->item.projetos.tamanho == 0)
                {
                    RemoveItemPorId(&listaEnc, apont->item.numero);
                }
                apont = apont->prox;
            }

            cout << "\n\nOs funcionários sem projetos cadastrados foram removidos.\n\n";

            break;

        case 5:

            cout << "\n\nInsira o ID do funcionário a ser consultado.\n\n";

            cin >> IDDesejo;
            apont = ProcuraItem(&listaEnc, IDDesejo);
            if (apont != NULL)
            {
                cout << "ID do funcionário: " << apont->item.numero << endl;
                cout << "Nome: " << apont->item.nome << endl;
                cout << "Endereço: " << apont->item.endereco << endl;
                cout << "Número de dependentes: " << apont->item.dependentes << endl;

                imprimeLista(apont->item.projetos);
            }
            else
            {
                cerr << "Funcionario inexistente\n";
            }

            break;

        case 6:

            apont = listaEnc.primeiro->prox;

            while (apont != NULL)
            {
                int cont = 0; // contador de horas do projeto

                for (int i = 0; i < apont->item.projetos.tamanho; i++)
                {
                    cont += apont->item.projetos.item[i].horas;
                }

                SalarioBruto = cont * 45 + apont->item.dependentes * 35;
                INSS = SalarioBruto * 0.085;
                IR = SalarioBruto * 0.15;
                SalarioLiq = SalarioBruto - INSS - IR;

                cout << "ID do funcionário: " << apont->item.numero << endl;
                cout << "Nome: " << apont->item.nome << endl;
                cout << "Horas de projeto realizadas: " << cont << endl;
                cout << "\n";
                cout << "Salário bruto (sem descontos): " << SalarioBruto << endl;
                cout << "Desconto do INSS: " << INSS << endl;
                cout << "Desconto do imposto de renda: " << IR << endl;
                cout << "Salário recebido (líquido): " << SalarioLiq << endl;

                break;
            }
        }

        system("pause");
        system("cls");

    } while (escolha != 7);

    SalvaArquivo(&listaEnc);
}