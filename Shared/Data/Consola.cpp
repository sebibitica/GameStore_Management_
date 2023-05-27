#include "Consola.h"

Consola::Consola()
{
    this->memorie_totala = 0;
    this->memorie_utilizata = 0;
    this->jocuri_instalate = nullptr;
    this->jocuri_cumparate = nullptr;
}

Consola::Consola(double memorie_totala, double memorie_utilizata, Joc **jocuri_instalate, Joc **jocuri_cumparate, int nr_jocuri_instalate, int nr_jocuri_cumparate)
{
    this->memorie_totala = memorie_totala;
    this->memorie_utilizata = memorie_utilizata;
    this->nr_jocuri_cumparate = nr_jocuri_cumparate;
    this->nr_jocuri_instalate = nr_jocuri_instalate;
    this->jocuri_cumparate = new Joc *[nr_jocuri_cumparate];
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        this->jocuri_cumparate[i] = jocuri_cumparate[i];
    }
    this->jocuri_instalate = new Joc *[nr_jocuri_instalate];
    for (int i = 0; i < nr_jocuri_instalate; i++)
    {
        this->jocuri_instalate[i] = jocuri_instalate[i];
    }
}

Consola::Consola(const Consola &c)
{
    this->memorie_totala = c.memorie_totala;
    this->memorie_utilizata = c.memorie_utilizata;
    this->nr_jocuri_cumparate = c.nr_jocuri_cumparate;
    this->nr_jocuri_instalate = c.nr_jocuri_instalate;
    this->jocuri_cumparate = new Joc *[nr_jocuri_cumparate];
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        this->jocuri_cumparate[i] = c.jocuri_cumparate[i];
    }
    this->jocuri_instalate = new Joc *[nr_jocuri_instalate];
    for (int i = 0; i < nr_jocuri_instalate; i++)
    {
        this->jocuri_instalate[i] = c.jocuri_instalate[i];
    }
}

Consola::~Consola()
{
    if (this->jocuri_instalate != nullptr)
        delete[] this->jocuri_instalate;
    if (this->jocuri_cumparate != nullptr)
        delete[] this->jocuri_cumparate;
}

void Consola::set_memorie_totala(double memorie_totala)
{
    this->memorie_totala = memorie_totala;
}

void Consola::set_memorie_utilizata(double memorie_utilizata)
{
    this->memorie_utilizata = memorie_utilizata;
}

void Consola::set_jocuri_instalate(Joc **jocuri_instalate)
{
    if (this->jocuri_instalate != nullptr)
        delete[] this->jocuri_instalate;
    this->jocuri_instalate = new Joc *[nr_jocuri_instalate];
    for (int i = 0; i < nr_jocuri_instalate; i++)
    {
        this->jocuri_instalate[i] = jocuri_instalate[i];
    }
}

void Consola::set_jocuri_cumparate(Joc **jocuri_cumparate)
{
    if (this->jocuri_cumparate != nullptr)
        delete[] this->jocuri_cumparate;
    this->jocuri_cumparate = new Joc *[nr_jocuri_cumparate];
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        this->jocuri_cumparate[i] = jocuri_cumparate[i];
    }
}

double Consola::get_memorie_totala()
{
    return this->memorie_totala;
}

double Consola::get_memorie_utilizata()
{
    return this->memorie_utilizata;
}

Joc **Consola::get_jocuri_instalate()
{
    return this->jocuri_instalate;
}

Joc **Consola::get_jocuri_cumparate()
{
    return this->jocuri_cumparate;
}

Consola &Consola::operator=(const Consola &c)
{
    if (this != &c)
    {
        this->memorie_totala = c.memorie_totala;
        this->memorie_utilizata = c.memorie_utilizata;
        this->nr_jocuri_cumparate = c.nr_jocuri_cumparate;
        this->nr_jocuri_instalate = c.nr_jocuri_instalate;
        if (this->jocuri_instalate != nullptr)
            delete[] this->jocuri_instalate;
        this->jocuri_instalate = new Joc *[nr_jocuri_instalate];
        for (int i = 0; i < nr_jocuri_instalate; i++)
        {
            this->jocuri_instalate[i] = c.jocuri_instalate[i];
        }
        if (this->jocuri_cumparate != nullptr)
            delete[] this->jocuri_cumparate;
        this->jocuri_cumparate = new Joc *[nr_jocuri_cumparate];
        for (int i = 0; i < nr_jocuri_cumparate; i++)
        {
            this->jocuri_cumparate[i] = c.jocuri_cumparate[i];
        }
    }
    return *this;
}

ostream &operator<<(ostream &os, const Consola &c)
{
    os << "Memorie totala: " << c.memorie_totala << endl;
    os << "Memorie utilizata: " << c.memorie_utilizata << endl;
    os << "Jocuri instalate: " << endl;
    for (int i = 0; i < c.nr_jocuri_instalate; i++)
    {
        os << *c.jocuri_instalate[i] << endl;
    }
    os << "Jocuri cumparate: " << endl;
    for (int i = 0; i < c.nr_jocuri_cumparate; i++)
    {
        os << *c.jocuri_cumparate[i] << endl;
    }
    return os;
}

void Consola::cumparare_joc(Joc &joc)
{
    Joc **jocuri_cumparate_nou = new Joc *[nr_jocuri_cumparate + 1];
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        jocuri_cumparate_nou[i] = jocuri_cumparate[i];
    }
    jocuri_cumparate_nou[nr_jocuri_cumparate] = &joc;
    nr_jocuri_cumparate++;
    if (jocuri_cumparate != nullptr)
        delete[] jocuri_cumparate;
    jocuri_cumparate = jocuri_cumparate_nou;
}

void Consola::instalare_joc(Joc &joc)
{
    if (memorie_utilizata + joc.getDimensiune() > memorie_totala)
    {
        cout << "Nu exista suficienta memorie pentru instalarea jocului!" << endl;
    }
    else
    {
        Joc **jocuri_instalate_nou = new Joc *[nr_jocuri_instalate + 1];
        for (int i = 0; i < nr_jocuri_instalate; i++)
        {
            jocuri_instalate_nou[i] = jocuri_instalate[i];
        }
        jocuri_instalate_nou[nr_jocuri_instalate] = &joc;
        nr_jocuri_instalate++;
        if (jocuri_instalate != nullptr)
            delete[] jocuri_instalate;
        jocuri_instalate = jocuri_instalate_nou;
        memorie_utilizata += joc.getDimensiune();
    }
}

void Consola::dezinstalare_joc(Joc &joc)
{
    Joc **jocuri_instalate_nou = new Joc *[nr_jocuri_instalate - 1];
    int j = 0;
    for (int i = 0; i < nr_jocuri_instalate; i++)
    {
        if (jocuri_instalate[i] != &joc)
        {
            jocuri_instalate_nou[j] = jocuri_instalate[i];
            j++;
        }
    }
    nr_jocuri_instalate--;
    if (jocuri_instalate != nullptr)
        delete[] jocuri_instalate;
    jocuri_instalate = jocuri_instalate_nou;
    memorie_utilizata -= joc.getDimensiune();
}

void Consola::vizualizare_memorie()
{
    cout << "Memorie totala: " << memorie_totala << endl;
    cout << "Memorie utilizata: " << memorie_utilizata << endl;
    cout << "Memorie disponibila: " << memorie_totala - memorie_utilizata << endl;
}

void Consola::vizualizare_jocuri_instalate()
{
    cout << "Jocuri instalate: " << endl;
    for (int i = 0; i < nr_jocuri_instalate; i++)
    {
        cout << *jocuri_instalate[i] << endl;
    }
}

void Consola::vizualizare_jocuri_cumparate()
{
    cout << "Jocuri cumparate: " << endl;
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        cout << *jocuri_cumparate[i] << endl;
    }
}

void Consola::set_nr_jocuri_cumparate(int nr_jocuri_cumparate)
{
    this->nr_jocuri_cumparate = nr_jocuri_cumparate;
}

void Consola::set_nr_jocuri_instalate(int nr_jocuri_instalate)
{
    this->nr_jocuri_instalate = nr_jocuri_instalate;
}

int Consola::get_nr_jocuri_cumparate()
{
    return nr_jocuri_cumparate;
}

int Consola::get_nr_jocuri_instalate()
{
    return nr_jocuri_instalate;
}

int Consola::cautare_joc_cumparat(string id)
{
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        if (jocuri_cumparate[i]->getId() == id)
        {
            return 1;
        }
    }
    return -1;
}

void Consola::cumparare_bundle(Bundle &bundle)
{
    for (int i = 0; i < bundle.getNumarJocuri(); i++)
    {
        if (cautare_joc_cumparat(bundle.getJocuri()[i]->getId()) == -1)
            cumparare_joc(*bundle.getJocuri()[i]);
    }
}