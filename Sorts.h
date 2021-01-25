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

class Sorts{


    public:

    Sorts();
    ~Sorts();
    bool menorElemento(Registro &candidatoInicio, Registro &candidatoFim);
    void merge(vector<Registro> &arr, int l, int m, int r, int &keyComparation, int &keyMovimentation);
    void mergeSort(vector<Registro> &arr, int l, int r, int &keyComparation, int &keyMovimentation);
    void quickSortMediana(vector<Registro> &registrosOrdenados, int inicio, int fim);
    void quickSortCases(vector<Registro> &registrosOrdenados, int inicio, int fim, int &keyComparation, int &keyMovimentation);
};