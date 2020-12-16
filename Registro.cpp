#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include "Registro.h"

using namespace std;

Registro::Registro(){

    this->date;
    this->state;
    this->name;
    this->code;
    this->cases;
    this->deaths;
}

Registro::~Registro(){}

string Registro::getDate(){
    return this->date;
}

string Registro::getState(){
    return this->state;
}

string Registro::getName(){
    return this->name;
}

string Registro::getCode(){
    return this->code;
}

int Registro::getCases(){
    return this->cases;
}

int Registro::getDeaths(){
    return this->deaths;
}

void Registro::setDate(string date){
    this->date = date;
}

void Registro::setState(string state){
    this->state = state;
}

void Registro::setName(string name){
    this->name = name;
}

void Registro::setCode(string code){
    this->code = code;
}

void Registro::setCases(int cases){
    this->cases = cases;
}

void Registro::setDeaths(int deaths){
    this->deaths = deaths;
}
