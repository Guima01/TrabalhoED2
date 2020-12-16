#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;


void leArquivoTextoGeral(ifstream& arq)
{

    if(arq.is_open())
    {

        string str;
        float val;
        for(int i = 0; i < 10000; i++){
        getline(arq, str);
        cout << str << endl; 
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