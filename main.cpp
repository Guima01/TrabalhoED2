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

int comparaStrings(string elementoAtual, string elementoPivo){
    int i = 0;
    int j = 0;
    char aux;
    while( true ){
        if(elementoAtual[j] != elementoPivo[i]){
            if(elementoAtual[j] == ' ')
                j++;
            if(elementoPivo[i] == ' ')
                i++;
            
            if(elementoAtual[j]>='A' && elementoAtual[j]<='Z'){
                if(elementoPivo[i]>='a' && elementoPivo[i]<='z')
                    aux = elementoPivo[i] + 'A' - 'a';
                else
                    aux = elementoPivo[i];
            }
            else{
                if(elementoPivo[i]>='A' && elementoPivo[i]<='Z')
                    aux = elementoPivo[i] - 'A' + 'a' ;
                else
                    aux = elementoPivo[i];
            }

            if(elementoAtual[j] != aux){
                if(elementoAtual[j] < aux)
                    return -1;
                else
                    return 1;
            }
        }
        i++;
        j++;

        if(i == elementoAtual.length() && j != elementoPivo.length())
            return -1;

        if( i != elementoAtual.length() && j == elementoPivo.length())
            return 1;

        if(i == elementoAtual.length() && j == elementoPivo.length())
            return 0;

    }
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
            if (comparaStrings(registrosOrdenados[j].getName(), pivo.getName()) <= -1)
            {
                i++;
                swap(registrosOrdenados[i], registrosOrdenados[j]);
            }
            else if (!comparaStrings(registrosOrdenados[j].getName(), pivo.getName()))
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
        if( str[j] == ' ' && (str[j+1] >= 'a' && str[j+1]<='z')){
            str[j+1] = str[j+1] + 'A'- 'a';
        }
    }
}

bool validaComparacao(Registro candidato, Registro pivo)
{
    if (strcmp(candidato.getState().c_str(), pivo.getState().c_str()) <= 0)
    {
        if ( !strcmp( candidato.getState().c_str(), pivo.getState().c_str() ) )
        {
            if(comparaStrings(candidato.getName(), pivo.getName()) >= 0)
            {
                if(( !comparaStrings(candidato.getName(), pivo.getName()) ))
                {
                    if (strcmp(candidato.getDate().c_str(), pivo.getDate().c_str()) <= -1)
                    {
                        return true;
                    }
                }
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

void quickSortMedio(vector<Registro> &registrosOrdenados,int inicio, int fim)
{    
    int i = inicio;
    int j = fim - 1;
    
    Registro pivo = registrosOrdenados[ (inicio+fim)/2 ];

    while(i<=j)
    {
        while(validaComparacao(registrosOrdenados[i],pivo) && i<fim)
        {
            i++;
        }
        while(validaComparacao(pivo,registrosOrdenados[j]) && j>inicio)
        {
            j--;
        }

        if(i<=j){
            swap(registrosOrdenados[i], registrosOrdenados[j]);
            i++;
            j--;
        }
    }
    if(j > inicio){
        quickSortMedio(registrosOrdenados,inicio,j+1);
    }
    if(i < fim){
        quickSortMedio(registrosOrdenados,i,fim);
    }
}

bool menorElemento(Registro candidatoInicio, Registro candidatoFim)
{
    if( strcmp( candidatoInicio.getState().c_str(), candidatoFim.getState().c_str() ) <= 0 )
    {
        if( !strcmp( candidatoInicio.getState().c_str(), candidatoFim.getState().c_str() ) )
        {
            if( comparaStrings( candidatoInicio.getName(), candidatoFim.getName() ) <= 0 )
            {
                if( !comparaStrings( candidatoInicio.getName(), candidatoFim.getName() ) )
                {
                    if( strcmp( candidatoInicio.getDate().c_str(), candidatoFim.getDate().c_str() ) < 0)
                    {
                        return true;
                    }
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


void quickSortMediana(vector<Registro> &registrosOrdenados,int inicio, int fim)
{
    int i = inicio;
    int j = fim - 1;
    
    Registro pivo;

    if( menorElemento( registrosOrdenados[inicio], registrosOrdenados[(inicio + fim ) / 2 ] ) )
    {
        if( menorElemento( registrosOrdenados[(inicio+fim) / 2 ], registrosOrdenados[ j ] ))
        {
            pivo = registrosOrdenados[(inicio+fim) / 2 ];
        }
        else
        {
            if( menorElemento(registrosOrdenados[inicio],registrosOrdenados[j]))
            {
                pivo = registrosOrdenados[j];
            }
            else
            {
                pivo = registrosOrdenados[inicio];
            }
        }
    }
    else
    {
        if( menorElemento(registrosOrdenados[j],registrosOrdenados[ (inicio+fim) / 2] ) )
        {
            pivo = registrosOrdenados[(inicio+fim) / 2 ];
        }
        else
        {
            if( menorElemento( registrosOrdenados[j], registrosOrdenados[inicio]))
            {
                pivo = registrosOrdenados[ j ];
            }
            else
            {
                pivo = registrosOrdenados[ inicio ];
            }
        }
    }

    while(i<=j)
    {
        while(validaComparacao(registrosOrdenados[i],pivo) && i<fim)
        {
            i++;
        }
        while(validaComparacao(pivo,registrosOrdenados[j]) && j>inicio)
        {
            j--;
        }

        if(i<=j){
            swap(registrosOrdenados[i], registrosOrdenados[j]);
            i++;
            j--;
        }
    }
    if(j > inicio){
        quickSortMediana(registrosOrdenados,inicio,j+1);
    }
    if(i < fim){
        quickSortMediana(registrosOrdenados,i,fim);
    }   
}

void salvarArquivo(ofstream &arq, vector<Registro>registros){
    int cases = 10000;
    arq << "date,state,name,code,cases,deaths"<<endl;
    for(int i=0; i < registros.size(); i++){
        if(registros[i].getDate() == "2020-03-27"){
            cases = registros[i].getCases();
        }
        else{
            int aux = cases;
            cases = registros[i].getCases();
            registros[i].setCases(registros[i].getCases() - aux); 
        }
        arq << registros[i].getDate()<<",";
        arq << registros[i].getState()<<",";
        arq << registros[i].getName()<<",";
        arq << registros[i].getCode()<<",";
        arq << registros[i].getCases()<<",";
        arq << registros[i].getDeaths()<<endl;
    }
}

void leArquivoTextoGeral(ifstream &arq)
{
    ofstream saida("brazil_covid19_cities_processado.csv");
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

            }
        }

        clock_t timeStart, timeStop;
        timeStart = clock();

        //random_shuffle(registros.begin(),registros.end());

        //quickSort(registros, 0, registros.size()-1);
        //quickSortMedio(registros, 0, registros.size());
        quickSortMediana(registros, 0, registros.size());

        //insertionSort(registros);
        //mergeSort(registros,0,registros.size() - 1);

        timeStop = clock();
        cout << "Tempo Gasto: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << endl;

        cout << endl
             << endl
             << endl;

        /*for (int i = 0; i < registros.size(); i++)
        {
            cout << i << " " << registros[i].getDate() << " " << registros[i].getState();
            cout << " " << registros[i].getName() << endl;
        }*/
        salvarArquivo(saida, registros);
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
