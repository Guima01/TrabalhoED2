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
/*
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
    // Se a árvore está vazia, retorna um novo nó 
    if (no == NULL)
        return novoNo(registro);

    if (registro.getCases() < no->registro.getCases())
    {
        no->NoEsquerda = insereNo(no->NoEsquerda, registro);
    }
    else if (registro.getCases() > no->registro.getCases())
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
*/
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

void analiseAlgoritmosOrdenacao(vector<Registro> &registros, string nomeAlgoritmo,ofstream &saida)
{ 
    clock_t timeStart, timeStop;
    int m[] = {10000, 50000, 100000, 500000, 1000000};
    int comparation[] = {0, 0, 0, 0, 0};
    int movimentation[] = {0, 0, 0, 0, 0};
    double time[] = {0.0, 0.0, 0.0, 0.0, 0.0};
    
    float movimentationMedia = 0;
    float comparationMedia = 0;
    double timeMedia = 0;
    vector<Registro> teste;
    Sorts sorts;

    for (int i = 0; i < 5; i++)
        {
            for (int k = 0; k < 5; k++)
            {
                random_shuffle(registros.begin(), registros.end());

                for (int j = 0; j < m[i]; j++)
                {
                    teste.push_back(registros[j]);
                }
                
                if( nomeAlgoritmo == "quickSort")
                {
                    timeStart = clock();
                    sorts.quickSortCases(teste, 0, teste.size(), comparation[k], movimentation[k]);
                    timeStop = clock();

                    time[k] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
                    timeMedia += time[k];
                    movimentationMedia += movimentation[k];
                    comparationMedia += comparation[k];

                }

                if( nomeAlgoritmo == "mergeSort")
                {
                    timeStart = clock();
                    sorts.mergeSort(teste, 0, teste.size() - 1, comparation[k], movimentation[k]);
                    timeStop = clock();

                    time[k] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
                    timeMedia += time[k];
                    movimentationMedia += movimentation[k];
                    comparationMedia += comparation[k];
                }

                if( nomeAlgoritmo == "shellSort")
                {
                    timeStart = clock();
                    sorts.shellSort(teste, teste.size() - 1, comparation[k], movimentation[k]);
                    timeStop = clock();

                    time[k] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
                    timeMedia += time[k];
                    movimentationMedia += movimentation[k];
                    comparationMedia += comparation[k];

                }

                teste.clear();

                comparation[k] = 0;
                movimentation[k] = 0;

            }

            saida << "Tempo médio gasto do " << nomeAlgoritmo << " com " << m[i] << " registros aleatórios: " << timeMedia / 5 << endl;
            saida << "Comparacoes médias gasto do " << nomeAlgoritmo << " com " << m[i] << " registros aleatórios : " << comparationMedia / 5 << endl;
            saida << "Movimentacoes médias gastas do " << nomeAlgoritmo << " com "<< m[i] << " registros aleatórios : " << movimentationMedia / 5 << endl
                  << endl
                  << endl;

            movimentationMedia = 0;
            comparationMedia = 0;
            timeMedia = 0;
        }

}

void leArquivoNovamente(vector<Registro> &registros, ifstream &arq)
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
                registra->setName(stringDados[2]);
                registra->setCode(stringDados[3]);
                registra->setCases(cases);
                registra->setDeaths(deaths);

                registros.push_back(*registra);
            }
        }
        ofstream saida("saida.txt");
        cout << "Gerando arquivo de analise de dados ..." << endl;
        analiseAlgoritmosOrdenacao(registros,"quickSort",saida);
        analiseAlgoritmosOrdenacao(registros,"mergeSort",saida);
        analiseAlgoritmosOrdenacao(registros,"shellSort",saida);

    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

void moduloTeste(vector<Registro> &registros, ifstream &arq, int id)
{
    if (arq.is_open())
    {
        string str;
        int cases, deaths;
        cout<< "Lendo arquivo : brazil_covid19_cities_processado.csv ..." << endl;

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

        vector<Registro> ordena;

        Sorts sorts;
        int identificaOrdenacao;
        int comparation = 0;
        int movimentation = 0;

        random_shuffle(registros.begin(), registros.end());

        for (int j = 0; j < id; j++)
        {
            ordena.push_back(registros[j]);
        }

        cout << endl ;

        cout << "Escolha o algoritmo de ordenaçao" << endl;
        cout << "[1] QuickSort " << endl;
        cout << "[2] MergeSort " << endl;
        cout << "[3] ShellSort " << endl;
        cout << "[0] Sair " << endl;

        do
        {
            cin >> identificaOrdenacao;
        }
        while( identificaOrdenacao < 0 && identificaOrdenacao > 3 );
        
        if (identificaOrdenacao == 1)
        {
            sorts.quickSortCases(ordena, 0, ordena.size(), comparation, movimentation);
        }

        else if (identificaOrdenacao == 2)
        {
            sorts.mergeSort(ordena, 0, ordena.size() - 1, comparation, movimentation);
        }
        else if (identificaOrdenacao == 3)
        {
            sorts.shellSort(ordena, ordena.size(), comparation, movimentation);
        }
        else if(identificaOrdenacao == 0)
        {
            return;
        }

        if (id == 10)
        {
            for (int i = 0; i < ordena.size(); i++)
            {
                cout << ordena[i].getDate() << ", ";
                cout << ordena[i].getState() << ", ";
                cout << ordena[i].getName() << ", ";
                cout << ordena[i].getCode() << ", ";
                cout << ordena[i].getCases() << ", ";
                cout << ordena[i].getDeaths() << endl;
            }
        }
        else if (id == 100)
        {
            ofstream saida("moduloTestes.txt");
            for (int i = 0; i < ordena.size(); i++)
            {
                saida << ordena[i].getDate() << ", ";
                saida << ordena[i].getState() << ", ";
                saida << ordena[i].getName() << ", ";
                saida << ordena[i].getCode() << ", ";
                saida << ordena[i].getCases() << ", ";
                saida << ordena[i].getDeaths() << endl;
            }
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
        cout << "Lendo arquivo de entrada..." << endl;

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

        cout << "Leitura do arquivo de entrada finalizada." << endl
             << endl
             << endl;

        cout << "Executando o quickSort..." << endl;

        clock_t timeStart, timeStop;
        Sorts sorts;
        timeStart = clock();
        sorts.quickSort(registros, 0, registros.size());

        timeStop = clock();
        cout << "QuickSort executado com sucesso" << endl;
        cout << "Tempo gasto do Quicksort para o arquivo de entrada: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        cout << " seg" << endl;

        cout << endl
             << endl
             << endl;

    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

int menu()
{
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Pre-processamento dos dados" << endl;
    cout << "[2] Importar N registros aleatorios" << endl;
    cout << "[0] Gerar analise dos algoritmos de ordenaçao" << endl;

    cin >> selecao;

    return selecao;
}

void seleciona(int selecao)
{
    switch (selecao)
    {
        case 1:
        {
            ifstream arquivo;

            arquivo.open("brazil_covid19_cities_processado.csv", ios::in);
            if (arquivo.is_open())
            {
                string str;

                for (int i = 0; getline(arquivo, str); i++)
                {
                    cout << str << endl;
                }
            }
            else
                cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;

            break;
        }
        case 2:
        {
            int id;
            vector<Registro> registros;
            ifstream arquivo;

            arquivo.open("brazil_covid19_cities_processado.csv", ios::in);
            cout << endl;
            cout <<  "------------------------------" << endl;

            cout << "[1] Saida em console" << endl;
            cout << "[2] Salvar a saida em arquivo" << endl;
            cout << "[0] Sair" << endl;
            

            do
            {
                cin >> id;
            }
            while( id < 0 && id > 2);

            if (id == 1)
            {
                moduloTeste(registros, arquivo, 10);
            }
            else if (id == 2)
            {
                moduloTeste(registros, arquivo, 100);
                cout << "Arquivo de saida salvado com sucesso" << endl << endl ;
            }


            break;
        }
    }
}

void mainMenu()
{
    int selecao = menu();
    while (selecao != 0)
    {
        seleciona(selecao);
        selecao = menu();
    }
}

int main(int argc, char const *argv[])
{
    vector<Registro> registros;
    ifstream arq;
    arq.open(argv[1], ios::in);

    leArquivoTextoGeral(registros, arq);
    cout << "Salvando Arquivo..." << endl;
    salvarArquivo(registros);
    mainMenu();

    arq.open("brazil_covid19_cities_processado.csv", ios::in);
    leArquivoNovamente(registros, arq);

    return 0;
}
