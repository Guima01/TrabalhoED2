#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <cstring>
#include <algorithm>
#include <typeinfo>
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

int particao(vector<Registro> &registrosOrdenados, int menorIndice, int maiorIndice)
{

    Registro pivo = registrosOrdenados[maiorIndice];
    int i = menorIndice - 1;

    for (int j = menorIndice; j < maiorIndice; j++)
    {
        if (strcmp(registrosOrdenados[j].getState().c_str(), pivo.getState().c_str()) <= -1)
        {
            i++;
            swap(registrosOrdenados[i], registrosOrdenados[j]);
        }
        else if (!strcmp(registrosOrdenados[j].getState().c_str(), pivo.getState().c_str()))
        {
            if (strcmp(registrosOrdenados[j].getName().c_str(), pivo.getName().c_str()) <= -1)
            {
                i++;
                swap(registrosOrdenados[i], registrosOrdenados[j]);
            }
            else if (!strcmp(registrosOrdenados[j].getName().c_str(), pivo.getName().c_str()))
            {
                if (strcmp(registrosOrdenados[j].getDate().c_str(), pivo.getDate().c_str()) <= -1)
                {
                    i++;
                    swap(registrosOrdenados[i], registrosOrdenados[j]);
                }
            }
        }
    }
    swap(registrosOrdenados[i + 1], registrosOrdenados[maiorIndice]);

    return i + 1;
}

void quickSort(vector<Registro> &registrosOrdenados, int menorIndice, int maiorIndice)
{
    if (menorIndice < maiorIndice)
    {
        int pi = particao(registrosOrdenados, menorIndice, maiorIndice);

        quickSort(registrosOrdenados, menorIndice, pi - 1);
        quickSort(registrosOrdenados, pi + 1, maiorIndice);
    }
}

bool verifica(Registro valor1, Registro valor2)
{
    if (strcmp(valor1.getState().c_str(), valor2.getState().c_str()) >= 1)
    {
        return true;
    }
    else if (strcmp(valor1.getState().c_str(), valor2.getState().c_str()) == 0)
    {
        if (strcmp(valor1.getName().c_str(), valor2.getName().c_str()) >= 1)
        {
            return true;
        }
        else if (strcmp(valor1.getName().c_str(), valor2.getName().c_str()) == 0)
        {
            if (strcmp(valor1.getDate().c_str(), valor2.getDate().c_str()) >= 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

bool verifica2(Registro valor1, Registro valor2)
{
    if (strcmp(valor1.getState().c_str(), valor2.getState().c_str()) >= 1)
    {
        return true;
    }
    else if (strcmp(valor1.getState().c_str(), valor2.getState().c_str()) == 0)
    {
        if (strcmp(valor1.getName().c_str(), valor2.getName().c_str()) >= 1)
        {
            return true;
        }
        else if (strcmp(valor1.getName().c_str(), valor2.getName().c_str()) == 0)
        {
            if (strcmp(valor1.getDate().c_str(), valor2.getDate().c_str()) >= 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

void insertionSort(vector<Registro> &registrosOrdenados)
{
    for (int i = 1; i < registrosOrdenados.size(); i++)
    {
        Registro pivo = registrosOrdenados[i];
        int j = i - 1;
        while (j >= 0 && verifica(registrosOrdenados[j], pivo))
        {
            registrosOrdenados[j + 1] = registrosOrdenados[j];
            j--;
        }
        registrosOrdenados[j + 1] = pivo;
    }
}

void merge(vector<Registro> arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    vector<Registro> L, R;
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L.push_back(arr[l + i]);
    for (int j = 0; j < n2; j++)
        R.push_back(arr[m + 1 + j]);
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (verifica2(R[j],L[i])) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector<Registro> arr,int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
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
    }
}

void leArquivoTextoGeral(ifstream &arq)
{

    vector<Registro> registros;
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
                if (i == 10000)
                {
                    break;
                }
            }
        }
        //random_shuffle(registros.begin(),registros.end());
        //quickSort(registros, 0, registros.size() - 1);
        //insertionSort(registros);
        //mergeSort(registros,0,registros.size() - 1);

        cout << endl
             << endl
             << endl;

        for (int i = 0; i < registros.size(); i++)
        {
            cout << i << " " << registros[i].getDate() << " " << registros[i].getState();
            cout << " " << registros[i].getName() << endl;
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

int main(int argc, char const *argv[])
{

    ifstream arq;
    arq.open(argv[1], ios::in);
    leArquivoTextoGeral(arq);

    return 0;
}
