
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
#include "Registro.h"
#include "Sorts.h"

using namespace std;
using namespace std::chrono;

Sorts::Sorts()
{
}

Sorts::~Sorts()
{
}

//função para retornar o menor elemento utilizando a chave do pré-processamento by: Gabriel Bronte
bool Sorts::menorElemento(Registro &candidatoInicio, Registro &candidatoFim)
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

//MergeSort para casos by: Guilherme Marques
void Sorts::merge(vector<Registro> &arr, int l, int m, int r, int &keyComparation, int &keyMovimentation)
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
        keyComparation = keyComparation + 1;
        if (j >= n2 || (i < n1 && L[i].getCases() < R[j].getCases()))
        {
            keyMovimentation = keyMovimentation + 1;
            arr[k] = L[i];
            i++;
        }
        else
        {
            keyMovimentation = keyMovimentation + 1;
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    delete[] L;
    delete[] R;
}

void Sorts::mergeSort(vector<Registro> &arr, int l, int r, int &keyComparation, int &keyMovimentation)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, keyComparation, keyMovimentation);
        mergeSort(arr, m + 1, r, keyComparation, keyMovimentation);
        keyComparation = keyComparation + 1;
        if (arr[m + 1].getCases() < arr[m].getCases())
        {
            merge(arr, l, m, r, keyComparation, keyMovimentation);
        }
    }
}

//QuickSort para o pré-processamento by: Gabriel Bronte
void Sorts::quickSort(vector<Registro> &registrosOrdenados, int inicio, int fim)
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
        quickSort(registrosOrdenados, inicio, j + 1);
    }
    if (i < fim)
    {
        quickSort(registrosOrdenados, i, fim);
    }
}

//QuickSort apenas para os casos by: Guilherme Marques, Gabriel Bronte
void Sorts::quickSortCases(vector<Registro> &registrosOrdenados, int inicio, int fim, int &keyComparation, int &keyMovimentation)
{
    int i = inicio;
    int j = fim - 1;

    Registro pivo = registrosOrdenados[(inicio + fim) / 2];

    while (i <= j)
    {
        keyComparation = keyComparation + 1;
        while ((registrosOrdenados[i].getCases() < pivo.getCases()) && i < fim)
        {
            keyComparation = keyComparation + 1;
            i++;
        }

        keyComparation = keyComparation + 1;
        while ((registrosOrdenados[j].getCases() > pivo.getCases()) && j > inicio)
        {
            keyComparation = keyComparation + 1;
            j--;
        }
        if (i <= j)
        {
            keyMovimentation = keyMovimentation + 1;
            swap(registrosOrdenados[i], registrosOrdenados[j]);
            i++;
            j--;
        }
    }
    if (j > inicio)
    {
        quickSortCases(registrosOrdenados, inicio, j + 1, keyComparation, keyMovimentation);
    }
    if (i < fim)
    {
        quickSortCases(registrosOrdenados, i, fim, keyComparation, keyMovimentation);
    }
}

//ShellSort apenas para casos by: Matheus Rúbio
void Sorts::shellSort(vector<Registro> &arr, int n, int &keyComparation, int &keyMovimentation) 
{ 
    for (int gap = n/2; gap > 0; gap /= 2) 
    {  
        for (int i = gap; i < n; i += 1) 
        { 
            Registro temp = arr[i]; 

            int j;          
            
            keyComparation++;
            for (j = i; j >= gap && arr[j - gap].getCases() > temp.getCases(); j -= gap)
            {
                keyComparation++;
                keyMovimentation++;
                arr[j] = arr[j - gap]; 
            } 
            keyMovimentation++; 
            arr[j] = temp; 
        } 
    } 
} 