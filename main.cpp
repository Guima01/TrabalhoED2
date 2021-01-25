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
        shuffle(registros.begin(), registros.end(), rng);
        for (int i = 0; i < 5; i++)
        {
            quickSortComparation = 0;
            quickSortMovimentation = 0;
            for (int j = 0; j < m[i]; j++)
            {
                teste.push_back(registros[j]);
            }
            teste2 = teste;
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
        sorts.quickSortMediana(registros, 0, registros.size());
        //quickSortCases(registros, 0, registros.size());
        //mergeSort(registros, 0, registros.size() - 1);
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

int main(int argc, char const *argv[])
{
    vector<Registro> registros;
    ifstream arq;
    arq.open(argv[1], ios::in);
    leArquivoTextoGeral(registros, arq);
    salvarArquivo(registros);
    /*arq.open("brazil_covid19_cities_processado.csv", ios::in);
    registros.clear();
    leArquivoNovamente(registros, arq);*/

    return 0;
}
