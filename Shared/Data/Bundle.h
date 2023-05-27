#ifndef BUNDLE_H
#define BUNDLE_H

#include <iostream>
#include <string>
#include "Joc.h"

using namespace std;

class Bundle
{
    string id;
    double pret;
    int numar_jocuri;
    Joc **jocuri;

public:
    Bundle();
    Bundle(string id, double pret, int numar_jocuri, Joc **jocuri);
    ~Bundle();
    friend ostream &operator<<(ostream &out, Bundle &bundle);
    Bundle &operator=(const Bundle &bundle);
    Bundle(const Bundle &bundle);
    string getId();
    double getPret();
    int getNumarJocuri();
    Joc **getJocuri();
    void setId(string id);
    void setPret(double pret);
    void setNumarJocuri(int numar_jocuri);
    void setJocuri(Joc **jocuri);
};

#endif