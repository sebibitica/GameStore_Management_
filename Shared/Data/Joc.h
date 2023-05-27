#ifndef JOC_H
#define JOC_H

#include <string>
#include <iostream>
using namespace std;

class Joc
{
    string id;
    string denumire;
    string categorie;
    double pret;
    double dimensiune;
    int nrCumparari;

public:
    Joc();
    Joc(string id, string denumire, string categorie, double pret, double dimensiune, int nrCumparari);
    string getId();
    string getDenumire();
    string getCategorie();
    double getPret();
    double getDimensiune();
    int getNrCumparari();

    void setId(string id);
    void setDenumire(string denumire);
    void setCategorie(string categorie);
    void setPret(double pret);
    void setDimensiune(double dimensiune);
    void setNrCumparari(int nrCumparari);

    friend ostream &operator<<(ostream &out, Joc &joc);
    Joc &operator=(const Joc &joc);
};

#endif
