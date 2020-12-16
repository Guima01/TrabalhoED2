#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include "Registro.h"

using namespace std;
using namespace std::chrono;


void leArquivoTextoGeral(ifstream& arq)
{

    vector<Registro> registros;
    if(arq.is_open())
    {
        string str;
        string date;
        string state;
        string name;
        string code;
        string casesString;
        string deathsString;
        int cases;
        int deaths;

        for(int i = 0; i < 10000; i++){
        Registro *registra = new Registro();
        
        getline(arq, date,',');
        getline(arq, state,',');
        getline(arq, name,',');
        getline(arq, code,',');
        getline(arq, casesString,',');
        getline(arq, deathsString);

        cases = atoi(casesString.c_str());
        deaths = atoi(deathsString.c_str());

        registra->setDate(date);
        registra->setState(state);
        registra->setName(name);
        registra->setCode(code);
        registra->setCases(cases);
        registra->setDeaths(deaths);

        registros.push_back(*registra);
        cout << registros[i].getCases()<< endl;
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