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

//particiona as strings by: Gabriel Bronte
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

//remove acentos by: Guilherme Marques
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


//Altera para casos diários by: Guilherme Marques
void alteraCasos(vector<Registro> &registros)
{
    int cases = 10000;
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
    }
}

//salva registros ordenados e altera para casos diários by: todos
void salvarArquivo(vector<Registro> &registros, ofstream &saida)
{
    saida << "date,state,name,code,cases,deaths" << endl;
    for (int i = 0; i < registros.size(); i++)
    {
        saida << registros[i].getDate() << ",";
        saida << registros[i].getState() << ",";
        saida << registros[i].getName() << ",";
        saida << registros[i].getCode() << ",";
        saida << registros[i].getCases() << ",";
        saida << registros[i].getDeaths() << endl;
    }
}

//Analisa cada algoritmo by: todos
void analiseAlgoritmosOrdenacao(vector<Registro> &registros, string nomeAlgoritmo, ofstream &saida)
{
    clock_t timeStart, timeStop;
    int m[] = {10000, 50000, 100000, 500000, 1000000};
    int comparation[] = {0, 0, 0, 0, 0};
    int movimentation[] = {0, 0, 0, 0, 0};
    double time[] = {0.0, 0.0, 0.0, 0.0, 0.0};

    float movimentationMedia = 0;
    float comparationMedia = 0;
    double timeMedia = 0;
    vector<Registro> vetor;
    Sorts sorts;

    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            random_shuffle(registros.begin(), registros.end());

            for (int j = 0; j < m[i]; j++)
            {
                vetor.push_back(registros[j]);
            }

            if (nomeAlgoritmo == "quickSort")
            {
                timeStart = clock();
                sorts.quickSortCases(vetor, 0, vetor.size(), comparation[k], movimentation[k]);
                timeStop = clock();
            }

            else if (nomeAlgoritmo == "mergeSort")
            {
                timeStart = clock();
                sorts.mergeSort(vetor, 0, vetor.size() - 1, comparation[k], movimentation[k]);
                timeStop = clock();
            }

            else if (nomeAlgoritmo == "shellSort")
            {
                timeStart = clock();
                sorts.shellSort(vetor, vetor.size() - 1, comparation[k], movimentation[k]);
                timeStop = clock();
            }

            time[k] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
            timeMedia += time[k];
            movimentationMedia += movimentation[k];
            comparationMedia += comparation[k];

            vetor.clear();

            comparation[k] = 0;
            movimentation[k] = 0;
        }

        saida << "Tempo médio gasto do " << nomeAlgoritmo << " com " << m[i] << " registros aleatórios: " << timeMedia / 5 << endl;
        saida << "Comparacoes médias gasto do " << nomeAlgoritmo << " com " << m[i] << " registros aleatórios : " << comparationMedia / 5 << endl;
        saida << "Movimentacoes médias gastas do " << nomeAlgoritmo << " com " << m[i] << " registros aleatórios : " << movimentationMedia / 5 << endl
              << endl
              << endl;

        movimentationMedia = 0;
        comparationMedia = 0;
        timeMedia = 0;
    }
}

//Leitura das linhas do arquivo
void leLinha(vector<Registro> &registros, ifstream &arq)
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
}

//Faz novamente a leitura para cada algoritmo utilizando como chave de ordenação os casos by:Guilherme Marques, Gabriel Bronte, Matheus Rúbio
void leArquivoNovamente(ifstream &arq)
{
    vector<Registro> registros;
    if (arq.is_open())
    {
        leLinha(registros, arq);
        ofstream saida("saida.txt");
        cout << "Gerando arquivo de analise de dados ..." << endl;
        analiseAlgoritmosOrdenacao(registros, "quickSort", saida);
        analiseAlgoritmosOrdenacao(registros, "mergeSort", saida);
        analiseAlgoritmosOrdenacao(registros, "shellSort", saida);
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

//Algoritmos do módulo de teste by: todos
void moduloTesteAlgoritmos(vector<Registro> &registros, ifstream &arq, int id)
{
    if (arq.is_open())
    {

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

        cout << endl;

        cout << "Escolha o algoritmo de ordenacao" << endl;
        cout << "[1] QuickSort " << endl;
        cout << "[2] MergeSort " << endl;
        cout << "[3] ShellSort " << endl;
        cout << "[0] Sair " << endl;

        do
        {
            cin >> identificaOrdenacao;
        } while (identificaOrdenacao < 0 && identificaOrdenacao > 3);

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
        else if (identificaOrdenacao == 0)
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
            salvarArquivo(ordena, saida);
            cout << "Arquivo de saida salvado com sucesso" << endl<< endl;
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

//Lê arquivo para fazer o pré-processamento dos dados by: todos
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
        cout << "Tempo gasto do Quicksort para o arquivo de entrada: " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " seg" << endl;
        ;
        cout << endl
             << endl
             << endl;
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

//Módulo de testes para verificar a funcionalidade correta de cada algoritmo by:todos
void moduloTeste(vector<Registro> &registros, ifstream &arquivo)
{
    int id;
    do
    {
        cout << "------------------------------" << endl;
        cout << "[1] Saida em console (N = 10)" << endl;
        cout << "[2] Salvar a saida em arquivo (N = 100)" << endl;
        cout << "[0] Sair" << endl;
        cin >> id;
        if (id == 1)
        {
            moduloTesteAlgoritmos(registros, arquivo, 10);
        }
        else if (id == 2)
        {
            moduloTesteAlgoritmos(registros, arquivo, 100);
        }
    } while (id != 0);
}

//Menu para escolha das possíveis opções by: todos
int menu()
{
    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Pre-processamento dos dados" << endl;
    cout << "[2] Modulo de testes" << endl;
    cout << "[3] Gerar analise dos algoritmos de ordenacao" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

//Parte do Menu by: todos
void seleciona(int selecao, ifstream &arq)
{
    vector<Registro> registros;
    switch (selecao)
    {
    case 1:
    {
        leArquivoTextoGeral(registros, arq);
        cout << "Salvando Arquivo..." << endl;
        alteraCasos(registros);
        ofstream saida("brazil_covid19_cities_processado.csv");
        salvarArquivo(registros, saida);
        arq.close();
        break;
    }
    case 2:
    {
        ifstream arquivo;
        arquivo.open("brazil_covid19_cities_processado.csv", ios::in);
        cout << "Lendo arquivo : brazil_covid19_cities_processado.csv ..." << endl;
        leLinha(registros, arquivo);
        cout << endl;
        moduloTeste(registros, arquivo);

        break;
    }
    case 3:
    {
        ifstream arquivo;
        arquivo.open("brazil_covid19_cities_processado.csv", ios::in);
        leArquivoNovamente(arquivo);
        arquivo.close();
        break;
    }
    }
}

//Menu
void mainMenu(ifstream &arq)
{
    int selecao = menu();
    while (selecao != 0)
    {
        seleciona(selecao, arq);
        selecao = menu();
    }
}

//Função principal
int main(int argc, char const *argv[])
{

    ifstream arq;
    arq.open(argv[1], ios::in);
    mainMenu(arq);

    return 0;
}
