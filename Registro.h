#include <string>

using namespace std;

class Registro {

    private: 

    string date;
    string state;
    string name;
    string code;
    int cases;
    int deaths;

    public:

    void setDate(string date);
    void setState(string state);
    void setName(string name);
    void setCode(string code);
    void setCases(int cases);
    void setDeaths(int deaths);

    string getDate();
    string getState();
    string getName();
    string getCode();
    int getCases();
    int getDeaths();

}