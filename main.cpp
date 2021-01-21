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
#include<bits/stdc++.h> 
#include "Registro.h"

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

bool menorElemento(Registro &candidatoInicio, Registro &candidatoFim)
{
    bool verificaState = (candidatoInicio.getState() == candidatoFim.getState());

    if (candidatoInicio.getState() < candidatoFim.getState() || verificaState)
    {
        if (verificaState)
        {
            bool verificaName = (candidatoInicio.getName() == candidatoFim.getName());

            if (candidatoInicio.getName() < candidatoFim.getName() || verificaName)
            {
                if (verificaName)
                {
                    if (candidatoInicio.getDate() < candidatoFim.getDate())
                    {
                        return true;
                    }
                    else
                        return false;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }

    return false;
}

void merge(vector<Registro> &arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Registro *L = new Registro[n1], *R = new Registro[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 || j < n2)
    {
        if (j >= n2 || (i < n1 && menorElemento(L[i], R[j])))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(vector<Registro> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        if (menorElemento(arr[m + 1], arr[m]))
        {
            merge(arr, l, m, r);
        }
    }
}

void quickSortMediana(vector<Registro> &registrosOrdenados, int inicio, int fim)
{
    int i = inicio;
    int j = fim - 1;

    Registro pivo = registrosOrdenados[(inicio + fim) / 2];

    while (i <= j)
    {
        while (menorElemento(registrosOrdenados[i], pivo) && i < fim)
        {
            i++;
        }

        while (menorElemento(pivo, registrosOrdenados[j]) && j > inicio)
        {
            j--;
        }
        if (i <= j)
        {
            swap(registrosOrdenados[i], registrosOrdenados[j]);
            i++;
            j--;
        }
    }
    if (j > inicio)
    {
        quickSortMediana(registrosOrdenados, inicio, j + 1);
    }
    if (i < fim)
    {
        quickSortMediana(registrosOrdenados, i, fim);
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
  
No* insereNo(No* no, Registro registro) 
{ 
    /* Se a árvore está vazia, retorna um novo nó */
    if (no == NULL) return novoNo(registro); 
  
    if (menorElemento(registro, no->registro)) 
        no->NoEsquerda  = insereNo(no->NoEsquerda, registro); 
    else
        no->NoDireita = insereNo(no->NoDireita, registro); 
  
    return no; 
} 

void treeSort(vector<Registro> &arr, int n) 
{ 
    struct No *root = NULL; 
  
    // Constrói a árvore
    root = insereNo(root, arr[0]); 
    for (int i=1; i<n; i++) 
        root = insereNo(root, arr[i]); 
  
    int i = 0; 
    armazenaOrdenado(root, arr, i); 
} 

void leArquivoNovamente(vector<Registro> &registros, ifstream &arq)
{
    int m[] = {50000, 100000, 200000, 500000, 1000000};
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
        auto rng = std::default_random_engine {};
        shuffle(registros.begin(),registros.end(),rng);
        for (int i = 0; i < 5; i++)
        {
            for(int j = 0; j < m[i]; j++){
                teste.push_back(registros[j]);
            }
            clock_t timeStart, timeStop;
            timeStart = clock();
            //quickSortInt(teste,0,teste.size());
            //quickSortMediana(registros, 0, registros.size());
            mergeSort(teste, 0, teste.size() - 1);
            //treeSort(registros, registros.size());

            timeStop = clock();
            cout << "Tempo Gasto: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << endl;

            cout << endl
                 << endl
                 << endl;

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
        timeStart = clock();
        quickSortMediana(registros, 0, registros.size());
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
