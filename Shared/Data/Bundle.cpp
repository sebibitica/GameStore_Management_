#include "Bundle.h"

Bundle::Bundle()
{
    this->id = "";
    this->pret = 0;
    this->numar_jocuri = 0;
    this->jocuri = nullptr;
}

Bundle::Bundle(string id, double pret, int numar_jocuri, Joc **jocuri)
{
    this->id = id;
    this->pret = pret;
    this->numar_jocuri = numar_jocuri;
    this->jocuri = jocuri;
}

Bundle::Bundle(const Bundle &bundle)
{
    this->id = bundle.id;
    this->pret = bundle.pret;
    this->numar_jocuri = bundle.numar_jocuri;
    this->jocuri = bundle.jocuri;
}

Bundle::~Bundle()
{
    if (this->jocuri != nullptr)
    {
        delete[] this->jocuri;
    }
}

Bundle &Bundle::operator=(const Bundle &bundle)
{
    this->id = bundle.id;
    this->pret = bundle.pret;
    this->numar_jocuri = bundle.numar_jocuri;
    this->jocuri = bundle.jocuri;
    return *this;
}

ostream &operator<<(ostream &out, Bundle &bundle)
{
    out << "Bundle ID: " << bundle.id << endl;
    out << "Pret: " << bundle.pret << "RON" << endl;
    out << "Numar jocuri: " << bundle.numar_jocuri << endl;
    out << "Jocuri:\n";
    for (int i = 0; i < bundle.numar_jocuri; i++)
    {
        out << *bundle.jocuri[i] << endl;
    }
    return out;
}

string Bundle::getId()
{
    return this->id;
}

double Bundle::getPret()
{
    return this->pret;
}

int Bundle::getNumarJocuri()
{
    return this->numar_jocuri;
}

Joc **Bundle::getJocuri()
{
    return this->jocuri;
}

void Bundle::setId(string id)
{
    this->id = id;
}

void Bundle::setPret(double pret)
{
    this->pret = pret;
}

void Bundle::setNumarJocuri(int numar_jocuri)
{
    this->numar_jocuri = numar_jocuri;
}

void Bundle::setJocuri(Joc **jocuri)
{
    this->jocuri = jocuri;
}