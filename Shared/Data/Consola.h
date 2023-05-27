#ifndef CONSOLA_H
#define CONSOLA_H

#include <iostream>
#include <string>
#include "Joc.h"
#include "Bundle.h"

using namespace std;

class Consola
{
    double memorie_totala;
    double memorie_utilizata;
    int nr_jocuri_instalate;
    int nr_jocuri_cumparate;
    Joc **jocuri_instalate;
    Joc **jocuri_cumparate;

public:
    Consola();
    Consola(double, double, Joc **, Joc **, int, int);
    Consola(const Consola &);
    ~Consola();
    void set_memorie_totala(double);
    void set_memorie_utilizata(double);
    void set_jocuri_instalate(Joc **);
    void set_jocuri_cumparate(Joc **);
    void set_nr_jocuri_instalate(int);
    void set_nr_jocuri_cumparate(int);
    int get_nr_jocuri_instalate();
    int get_nr_jocuri_cumparate();
    double get_memorie_totala();
    double get_memorie_utilizata();
    Joc **get_jocuri_instalate();
    Joc **get_jocuri_cumparate();
    Consola &operator=(const Consola &);
    friend ostream &operator<<(ostream &, const Consola &);
    void cumparare_joc(Joc &);
    void instalare_joc(Joc &);
    void dezinstalare_joc(Joc &);
    void cumparare_bundle(Bundle &);
    void vizualizare_memorie();
    void vizualizare_jocuri_instalate();
    void vizualizare_jocuri_cumparate();
    int cautare_joc_cumparat(string);
};

#endif