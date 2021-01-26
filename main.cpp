#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <cstring>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>
#include "Registro.h"
#include "Sorts.h"

using namespace std;
using namespace std::chrono;

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}

struct No
{
    Registro registro;
    struct No *NoEsquerda, *NoDireita;
};

struct No *novoNo(Registro registro)
{
    struct No *temp = new No;
    temp->registro = registro;
    temp->NoEsquerda = temp->NoDireita = NULL;
    return temp;
}

void armazenaOrdenado(No *root, vector<Registro> &arr, int &i)
{
    if (root != NULL)
    {
        armazenaOrdenado(root->NoEsquerda, arr, i);
        arr[i++] = root->registro;
        armazenaOrdenado(root->NoDireita, arr, i);
    }
}

No *insereNo(No *no, Registro registro)
{
    /* Se a árvore está vazia, retorna um novo nó */
    if (no == NULL)
        return novoNo(registro);

    if (registro.getCases() < no->registro.getCases())
    {
        no->NoEsquerda = insereNo(no->NoEsquerda, registro);
    }
    else if(registro.getCases() > no->registro.getCases())
    {
        no->NoDireita = insereNo(no->NoDireita, registro);
    }

    return no;
}

void treeSort(vector<Registro> &arr, int n)
{
    struct No *root = NULL;

    // Constrói a árvore
    root = insereNo(root, arr[0]);
    for (int i = 1; i < n; i++)
    {
        root = insereNo(root, arr[i]);
    }

    int i = 0;
    armazenaOrdenado(root, arr, i);
}

void removeAccents(string &str)
{
    string accent_chars = "ÁÀÃÂÇáàãâçÉÊéêÍíÑÓÔÕñóôõÚÜúü";
    string unnacent_chars = "AAAAAAAACCaaaaaaaaccEEEEeeeeIIiiNNOOOOOOnnooooooUUUUuuuu";
    for (int j = 0; str[j] != *"\0"; j++)
    {
        for (int i = 0; i < accent_chars.size(); i = i + 1)
        {
            if (str[j] == accent_chars[i])
            {
                if (str[j + 1] == accent_chars[i + 1])
                {
                    str[j] = unnacent_chars[i];
                    if (str[j] == *"\0")
                    {
                        break;
                    }
                    str.erase(str.begin() + j + 1);
                    break;
                }
                else
                {
                    i++;
                }
            }
        }
        if (str[j] == ' ' && (str[j + 1] >= 'a' && str[j + 1] <= 'z'))
        {
            str[j + 1] = str[j + 1] + 'A' - 'a';
        }
    }
}


void salvarArquivo(vector<Registro> &registros)
{
    ofstream saida("brazil_covid19_cities_processado.csv");
    int cases = 10000;
    saida << "date,state,name,code,cases,deaths" << endl;
    for (int i = 0; i < registros.size(); i++)
    {
        if (registros[i].getDate() == "2020-03-27")
        {
            cases = registros[i].getCases();
        }
        else
        {
            int aux = cases;
            cases = registros[i].getCases();
            registros[i].setCases(registros[i].getCases() - aux);
        }
        saida << registros[i].getDate() << ",";
        saida << registros[i].getState() << ",";
        saida << registros[i].getName() << ",";
        saida << registros[i].getCode() << ",";
        saida << registros[i].getCases() << ",";
        saida << registros[i].getDeaths() << endl;
    }
}

void leArquivoNovamente(vector<Registro> &registros, ifstream &arq)
{
    int m[] = {10000, 50000, 100000, 500000, 1000000};
    if (arq.is_open())
    {
        string str;
        int cases, deaths;

        for (int i = 0; getline(arq, str); i++)
        {
            if (i != 0)
            {
                Registro *registra = new Registro();

                vector<string> stringDados = split(str, ',');

                cases = atoi(stringDados[4].c_str());
                deaths = atoi(stringDados[5].c_str());

                registra->setDate(stringDados[0]);
                registra->setState(stringDados[1]);
                registra->setName(stringDados[2]);
                registra->setCode(stringDados[3]);
                registra->setCases(cases);
                registra->setDeaths(deaths);

                registros.push_back(*registra);
            }
        }


        vector<Registro> teste;
        vector<Registro> teste2;
        Sorts sorts;

        int quickSortComparation = 0;
        int quickSortMovimentation = 0;
        int mergeSortComparation = 0;
        int mergeSortMovimentation = 0;
        
        clock_t timeStart, timeStop;
        auto rng = std::default_random_engine{};

        random_shuffle(registros.begin(), registros.end());
        for (int i = 0; i < 5; i++)
        {
            quickSortComparation = 0;
            quickSortMovimentation = 0;
            for (int j = 0; j < m[i]; j++)
            {
                teste.push_back(registros[j]);
            }
            teste2 = teste;
            timeStart = clock();
            sorts.quickSortCases(teste2, 0, teste2.size(), quickSortComparation, quickSortMovimentation);
            timeStop = clock();
            cout << "Tempo Gasto com o QuickSort: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << endl;
            cout << "Comparacoes no QuickSort: " << quickSortComparation << endl;            
            cout << "Movimentacoes no QuickSort: " << quickSortMovimentation << endl << endl;

            teste2 = teste;
            timeStart = clock();
            sorts.mergeSort(teste, 0, teste.size() - 1, mergeSortComparation, mergeSortMovimentation);
            timeStop = clock();
            cout << "Tempo Gasto com o mergeSort: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << endl;
            cout << "Comparacoes no MergeSort: " << mergeSortComparation << endl;            
            cout << "Movimentacoes no MergeSort: " << mergeSortMovimentation << endl << endl;

            teste.clear();
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

void moduloTeste(vector<Registro> &registros, ifstream &arq, int id)
{
    int identificaOrdenacao;
    if (arq.is_open())
    {
        string str;
        int cases, deaths;

        for (int i = 0; getline(arq, str); i++)
        {
            if (i != 0)
            {
                Registro *registra = new Registro();

                vector<string> stringDados = split(str, ',');

                cases = atoi(stringDados[4].c_str());
                deaths = atoi(stringDados[5].c_str());

                registra->setDate(stringDados[0]);
                registra->setState(stringDados[1]);
                registra->setName(stringDados[2]);
                registra->setCode(stringDados[3]);
                registra->setCases(cases);
                registra->setDeaths(deaths);

                registros.push_back(*registra);
            }
        }

        vector<Registro> ordena;

        Sorts sorts;
        int mergeComparation = 0 ;
        int mergeMovimentation = 0 ;


        int quickComparation = 0 ;
        int quickMovimentation = 0 ;
        

        
        auto rng = std::default_random_engine{};

        random_shuffle(registros.begin(), registros.end());

        for (int j = 0; j < id; j++)
        {
            ordena.push_back(registros[j]);
        }

        cout << "Se quiser utilizar o quickSort digite 1"<< endl;
        cout << "Se quiser utilizar o mergeSort digite 2"<< endl;
            
        cin >> identificaOrdenacao;

        if(identificaOrdenacao == 1)
        {
            sorts.quickSortCases(ordena, 0, ordena.size(), quickComparation, quickMovimentation);
        }

        else if(identificaOrdenacao == 2)
        {
            sorts.mergeSort(ordena, 0, ordena.size() - 1, mergeComparation, mergeMovimentation);
        }
        if (id == 10)
        {
            for(int i=0 ; i <ordena.size() ; i++)
            {
                cout<< ordena[i].getDate() << ", ";
                cout<< ordena[i].getState() << ", ";
                cout<< ordena[i].getName() << ", ";
                cout<< ordena[i].getCode() << ", ";
                cout<< ordena[i].getCases() << ", ";
                cout<< ordena[i].getDeaths() << endl;
                
            }
        }
        else if(id == 100)
        {
            ofstream saida("saida.txt");
            for(int i=0 ; i <ordena.size() ; i++)
            {
                saida << ordena[i].getDate() << ", ";
                saida << ordena[i].getState() << ", ";
                saida << ordena[i].getName() << ", ";
                saida << ordena[i].getCode() << ", ";
                saida << ordena[i].getCases() << ", ";
                saida << ordena[i].getDeaths() << endl;
            }
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

void leArquivoTextoGeral(vector<Registro> &registros, ifstream &arq)
{
    if (arq.is_open())
    {
        string str;
        int cases, deaths;

        for (int i = 0; getline(arq, str); i++)
        {
            if (i != 0)
            {
                Registro *registra = new Registro();

                vector<string> stringDados = split(str, ',');

                cases = atoi(stringDados[4].c_str());
                deaths = atoi(stringDados[5].c_str());

                registra->setDate(stringDados[0]);
                registra->setState(stringDados[1]);
                removeAccents(stringDados[2]);
                registra->setName(stringDados[2]);
                registra->setCode(stringDados[3]);
                registra->setCases(cases);
                registra->setDeaths(deaths);

                registros.push_back(*registra);
            }

        }

        clock_t timeStart, timeStop;
        Sorts sorts;
        timeStart = clock();
        sorts.quickSort(registros, 0, registros.size());
        //quickSortCases(registros, 0, registros.size());
        //sorts.mergeSort(registros, 0, registros.size() - 1,a,b);
        //treeSort(registros, (registros.size()));

        timeStop = clock();
        cout << "Tempo Gasto: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << endl;

        cout << endl
             << endl
             << endl;
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

int menu()
{
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Pre-processamento dos dados" << endl;
    cout << "[2] Importar N registros aleatorios" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void seleciona(int selecao)
{
    switch(selecao)
    {
        case 1:
        {
            ifstream arquivo;
            arquivo.open("brazil_covid19_cities_processado.csv", ios::in);
            if (arquivo.is_open())
            {
                string str;

                for (int i = 0; getline(arquivo, str); i++)
                {
                    cout << str << endl;                    
                }
            }
            else
                cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;

            break;
        }
        case 2:
        {
            int id;
            vector<Registro> registros;
            ifstream arquivo;
            arquivo.open("brazil_covid19_cities_processado.csv", ios::in);

            cout << "Para saida em console, digite 10" << endl;
            cout << "Para salvar a saida em arquivo, digite 100" << endl;
            cin >> id;

            if( id == 10)
            {
                moduloTeste(registros, arquivo, 10);
            }
            else if( id == 100){
                moduloTeste(registros, arquivo, 100);
            }

            break;
        }
    }
}

void mainMenu()
{
    int selecao = menu();
    while (selecao != 0)
    {
        seleciona(selecao);
        selecao = menu();
    }
}

int main(int argc, char const *argv[])
{
    vector<Registro> registros;
    ifstream arq;
    arq.open(argv[1], ios::in);
    leArquivoTextoGeral(registros, arq);
    salvarArquivo(registros);
    mainMenu();
    arq.open("brazil_covid19_cities_processado.csv", ios::in);
    leArquivoNovamente(registros, arq);
    return 0;
}
