#include "Joc.h"

Joc::Joc()
{
    this->id = "";
    this->denumire = "";
    this->categorie = "";
    this->pret = 0;
    this->dimensiune = 0;
    this->nrCumparari = 0;
}

Joc::Joc(string id, string denumire, string categorie, double pret, double dimensiune, int nrCumparari)
{
    this->id = id;
    this->denumire = denumire;
    this->categorie = categorie;
    this->pret = pret;
    this->dimensiune = dimensiune;
    this->nrCumparari = nrCumparari;
}

string Joc::getId()
{
    return this->id;
}

string Joc::getDenumire()
{
    return this->denumire;
}

string Joc::getCategorie()
{
    return this->categorie;
}

double Joc::getPret()
{
    return this->pret;
}

double Joc::getDimensiune()
{
    return this->dimensiune;
}

int Joc::getNrCumparari()
{
    return this->nrCumparari;
}

void Joc::setId(string id)
{
    this->id = id;
}

void Joc::setDenumire(string denumire)
{
    this->denumire = denumire;
}

void Joc::setCategorie(string categorie)
{
    this->categorie = categorie;
}

void Joc::setPret(double pret)
{
    this->pret = pret;
}

void Joc::setDimensiune(double dimensiune)
{
    this->dimensiune = dimensiune;
}

void Joc::setNrCumparari(int nrCumparari)
{
    this->nrCumparari = nrCumparari;
}

ostream &operator<<(ostream &out, Joc &joc)
{
    out << "Id: " << joc.id << " | ";
    for (int j = 0; j < joc.denumire.size(); j++)
    {
        if (joc.denumire[j] == '_')
        {
            joc.denumire[j] = ' ';
        }
    }
    for (int j = 0; j < joc.categorie.size(); j++)
    {
        if (joc.categorie[j] == '_')
        {
            joc.categorie[j] = ' ';
        }
    }
    out << "Denumire: " << joc.denumire << " | ";
    out << "Categorie: " << joc.categorie << " | ";
    out << "Pret: " << joc.pret << "RON | ";
    out << "Dimensiune: " << joc.dimensiune << "GB | ";
    out << "Nr. cumparari: " << joc.nrCumparari;
    return out;
}

Joc &Joc::operator=(const Joc &joc)
{
    this->id = joc.id;
    this->denumire = joc.denumire;
    this->categorie = joc.categorie;
    this->pret = joc.pret;
    this->dimensiune = joc.dimensiune;
    this->nrCumparari = joc.nrCumparari;
    return *this;
}