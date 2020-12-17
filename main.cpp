#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <cstring>
#include <typeinfo>
#include "Registro.h"

using namespace std;
using namespace std::chrono;

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int particao(vector<Registro>&registrosOrdenados, int menorIndice, int maiorIndice)
{


    Registro pivo = registrosOrdenados[maiorIndice];
    int i = (menorIndice-1 );


    for(int j = menorIndice; j < maiorIndice; j++)
    {

        if(strcmp(registrosOrdenados[j].getState().c_str(), pivo.getState().c_str()) == -1)
        {
            i++;
            swap(registrosOrdenados[i],registrosOrdenados[j]);
        }
        else if(strcmp(registrosOrdenados[j].getState().c_str(), pivo.getState().c_str()) == 0){

            if(strcmp(registrosOrdenados[j].getName().c_str(), pivo.getName().c_str()) == -1){
                i++;
                swap(registrosOrdenados[i],registrosOrdenados[j]);
            }
            else if(strcmp(registrosOrdenados[j].getName().c_str(), pivo.getName().c_str()) == 0){

                if(strcmp(registrosOrdenados[j].getDate().c_str(), pivo.getDate().c_str()) == -1){
                i++;
                swap(registrosOrdenados[i],registrosOrdenados[j]);
                }
            }
        }

    }
    swap(registrosOrdenados[i+1],registrosOrdenados[maiorIndice]);

    return i+1;

}

void quickSort(vector<Registro>&registrosOrdenados, int menorIndice, int maiorIndice)
{



    if(menorIndice<maiorIndice)
    {

        int pi = particao(registrosOrdenados,menorIndice,maiorIndice);


        quickSort(registrosOrdenados,menorIndice,pi-1);
        quickSort(registrosOrdenados,pi+1,maiorIndice);
    }

}

void leArquivoTextoGeral(ifstream& arq)
{

    vector<Registro> registros;
    if(arq.is_open())
    {
        string str;
        int cases, deaths;

        for(int i = 0; getline(arq,str); i++){
            if(i!=0){
                Registro *registra = new Registro();

                vector<string> teste = split(str,',');

                cases = atoi(teste[4].c_str());
                deaths = atoi(teste[5].c_str());

                registra->setDate(teste[0]);
                registra->setState(teste[1]);
                registra->setName(teste[2]);
                registra->setCode(teste[3]);
                registra->setCases(cases);
                registra->setDeaths(deaths);

                registros.push_back(*registra);
            }
        }
        quickSort(registros, 0, registros.size() - 1);
        for(int i = 0; i < registros.size(); i++){
            cout<<registros[i].getName()<<endl;
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    
}

int main(int argc, char const *argv[]){

    ifstream arq;
    arq.open(argv[1],ios::in);
    leArquivoTextoGeral(arq);
    return 0;
}