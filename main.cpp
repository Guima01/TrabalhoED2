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

void quickSortInt(vector<int>&values, int began, int end){
    int i, j, pivo, aux;
	i = began;
	j = end-1;
	pivo = values[(began + end) / 2];
	while(i <= j)
	{
		while(values[i] < pivo && i < end)
		{
			i++;
		}
		while(values[j] > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			aux = values[i];
			values[i] = values[j];
			values[j] = aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quickSortInt(values, began, j+1);
	if(i < end)
		quickSortInt(values, i, end);
}

void leArquivoTextoGeral(ifstream &arq)
{
    ofstream saida("brazil_covid19_cities_processado.csv");
    vector<Registro> registros;
    vector<int> teste;
    if(arq.is_open())
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

                teste.push_back(cases);

                if(i == 100000){
                    break;
                }
            }
        }

        clock_t timeStart, timeStop;
        timeStart = clock();
        //quickSortInt(teste,0,teste.size());
        //quickSortMediana(registros, 0, registros.size());

        timeStop = clock();
        cout << "Tempo Gasto: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << endl;

        cout << endl
             << endl
             << endl;

        /*for (int i = 0; i < teste.size(); i++)
        {
            cout<<teste[i]<<endl;
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
