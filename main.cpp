#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
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