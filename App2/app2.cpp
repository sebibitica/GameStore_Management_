#include "../Shared/Data/Joc.h"
#include "../Shared/Data/Bundle.h"
#include "../Shared/Data/Consola.h"
#include <fstream>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

void citireDinFisierJocuri(Joc *&jocuri, int &numar_jocuri)
{
    ifstream fin("../Shared/Files/jocuri.txt");
    fin >> numar_jocuri;
    jocuri = new Joc[numar_jocuri];
    for (int i = 0; i < numar_jocuri; i++)
    {
        string id, denumire, categorie;
        double pret;
        int nrCumparari;
        double dimensiune;
        fin >> id >> denumire >> categorie >> pret >> dimensiune >> nrCumparari;
        jocuri[i].setId(id);
        jocuri[i].setDenumire(denumire);
        jocuri[i].setCategorie(categorie);
        jocuri[i].setPret(pret);
        jocuri[i].setDimensiune(dimensiune);
        jocuri[i].setNrCumparari(nrCumparari);
    }
    fin.close();
}

void citireDinFisierBundles(Bundle *&bundles, int &numar_bundles, Joc *jocuri, int nr_jocuri_total)
{
    ifstream fin("../Shared/Files/bundles.txt");
    fin >> numar_bundles;
    bundles = new Bundle[numar_bundles];
    for (int i = 0; i < numar_bundles; i++)
    {
        string id;
        double pret;
        int numar_jocuri;
        fin >> id >> pret >> numar_jocuri;
        bundles[i].setId(id);
        bundles[i].setPret(pret);
        bundles[i].setNumarJocuri(numar_jocuri);
        Joc **jocuri_bundle = new Joc *[numar_jocuri];
        for (int j = 0; j < numar_jocuri; j++)
        {
            string id_joc;
            fin >> id_joc;
            for (int k = 0; k < nr_jocuri_total; k++)
            {
                if (jocuri[k].getId() == id_joc)
                {
                    jocuri_bundle[j] = &jocuri[k];
                }
            }
        }
        bundles[i].setJocuri(jocuri_bundle);
    }
    fin.close();
}

void citireDinFisierConsola(Consola &consola, Joc *jocuri, int numar_jocuri)
{
    ifstream fin("../Shared/Files/consola.txt");
    double memorie_totala, memorie_utilizata;
    int nr_jocuri_instalate, nr_jocuri_cumparate;
    fin >> memorie_totala >> memorie_utilizata >> nr_jocuri_cumparate;
    Joc **jocuri_cumparate = new Joc *[nr_jocuri_cumparate];
    for (int i = 0; i < nr_jocuri_cumparate; i++)
    {
        string id_joc;
        fin >> id_joc;
        for (int j = 0; j < numar_jocuri; j++)
        {
            if (jocuri[j].getId() == id_joc)
            {
                jocuri_cumparate[i] = &jocuri[j];
            }
        }
    }
    fin >> nr_jocuri_instalate;
    Joc **jocuri_instalate = new Joc *[nr_jocuri_instalate];
    for (int i = 0; i < nr_jocuri_instalate; i++)
    {
        string id_joc;
        fin >> id_joc;
        for (int j = 0; j < numar_jocuri; j++)
        {
            if (jocuri[j].getId() == id_joc)
            {
                jocuri_instalate[i] = &jocuri[j];
            }
        }
    }
    consola.set_memorie_totala(memorie_totala);
    consola.set_memorie_utilizata(memorie_utilizata);
    consola.set_nr_jocuri_cumparate(nr_jocuri_cumparate);
    consola.set_jocuri_cumparate(jocuri_cumparate);
    consola.set_nr_jocuri_instalate(nr_jocuri_instalate);
    consola.set_jocuri_instalate(jocuri_instalate);
    fin.close();
}

void afisareCatalog(Joc *jocuri, int numar_jocuri, Bundle *bundles, int numar_bundles)
{
    // Jocuri pe categorii:
    cout << "Jocuri pe categorii:" << endl;
    map<string, vector<Joc>> jocuri_pe_categorii;
    for (int i = 0; i < numar_jocuri; i++)
    {
        jocuri_pe_categorii[jocuri[i].getCategorie()].push_back(jocuri[i]);
    }
    for (auto it = jocuri_pe_categorii.begin(); it != jocuri_pe_categorii.end(); it++)
    {
        cout << it->first << ":" << endl;
        for (int i = 0; i < it->second.size(); i++)
        {
            cout << it->second[i] << endl;
        }
    }
    cout << endl;
    cout << "Bundles:" << endl;
    for (int i = 0; i < numar_bundles; i++)
    {
        cout << bundles[i] << endl;
    }
}

void cumparareJoc(Joc *jocuri, int numar_jocuri, Consola &consola, string id)
{
    for (int i = 0; i < numar_jocuri; i++)
    {
        if (jocuri[i].getId() == id)
        {
            consola.cumparare_joc(jocuri[i]);
        }
    }
    ofstream fout("../Shared/Files/consola.txt");
    fout << consola.get_memorie_totala() << " " << consola.get_memorie_utilizata() << endl
         << consola.get_nr_jocuri_cumparate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_cumparate(); i++)
    {
        fout << consola.get_jocuri_cumparate()[i]->getId() << " ";
    }
    fout << endl;
    fout << consola.get_nr_jocuri_instalate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_instalate(); i++)
    {
        fout << consola.get_jocuri_instalate()[i]->getId() << " ";
    }
    fout.close();
}

void instalareJoc(Joc *jocuri, int numar_jocuri, Consola &consola, string id)
{
    for (int i = 0; i < numar_jocuri; i++)
    {
        if (jocuri[i].getId() == id)
        {
            // daca jocul nu a fost cumparat, nu poate fi instalat
            if (consola.cautare_joc_cumparat(id) == -1)
            {
                cout << "Jocul nu a fost cumparat!" << endl;
                return;
            }
            else
            {
                consola.instalare_joc(jocuri[i]);
            }
        }
    }
    ofstream fout("../Shared/Files/consola.txt");
    fout << consola.get_memorie_totala() << " " << consola.get_memorie_utilizata() << endl
         << consola.get_nr_jocuri_cumparate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_cumparate(); i++)
    {
        fout << consola.get_jocuri_cumparate()[i]->getId() << " ";
    }
    fout << endl;
    fout << consola.get_nr_jocuri_instalate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_instalate(); i++)
    {
        fout << consola.get_jocuri_instalate()[i]->getId() << " ";
    }
    fout.close();
}

void dezinstalareJoc(Joc *jocuri, int numar_jocuri, Consola &consola, string id)
{
    for (int i = 0; i < numar_jocuri; i++)
    {
        if (jocuri[i].getId() == id)
        {
            consola.dezinstalare_joc(jocuri[i]);
        }
    }
    ofstream fout("../Shared/Files/consola.txt");
    fout << consola.get_memorie_totala() << " " << consola.get_memorie_utilizata() << endl
         << consola.get_nr_jocuri_cumparate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_cumparate(); i++)
    {
        fout << consola.get_jocuri_cumparate()[i]->getId() << " ";
    }
    fout << endl;
    fout << consola.get_nr_jocuri_instalate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_instalate(); i++)
    {
        fout << consola.get_jocuri_instalate()[i]->getId() << " ";
    }
    fout.close();
}

void cumparareBundle(Bundle *bundles, int numar_bundles, Consola &consola, string id)
{
    for (int i = 0; i < numar_bundles; i++)
    {
        if (bundles[i].getId() == id)
        {
            consola.cumparare_bundle(bundles[i]);
        }
    }
    ofstream fout("../Shared/Files/consola.txt");
    fout << consola.get_memorie_totala() << " " << consola.get_memorie_utilizata() << endl
         << consola.get_nr_jocuri_cumparate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_cumparate(); i++)
    {
        fout << consola.get_jocuri_cumparate()[i]->getId() << " ";
    }
    fout << endl;
    fout << consola.get_nr_jocuri_instalate() << endl;
    for (int i = 0; i < consola.get_nr_jocuri_instalate(); i++)
    {
        fout << consola.get_jocuri_instalate()[i]->getId() << " ";
    }
    fout.close();
}

int main(int argc, char **argv)
{
    Joc *jocuri = nullptr;
    int numar_jocuri = 0;
    citireDinFisierJocuri(jocuri, numar_jocuri);
    Bundle *bundles = nullptr;
    int numar_bundles = 0;
    citireDinFisierBundles(bundles, numar_bundles, jocuri, numar_jocuri);
    Consola consola;
    citireDinFisierConsola(consola, jocuri, numar_jocuri);
    if (argc > 1)
    {
        if (strcmp(argv[1], "vizualizare_catalog") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            afisareCatalog(jocuri, numar_jocuri, bundles, numar_bundles);
        }
        else if (strcmp(argv[1], "cumparare_joc") == 0)
        {
            if (argc < 3 || argc > 3)
            {
                cout << "comanda trebuie sa fie: cumparare_joc <id> " << endl;
                return 0;
            }
            cumparareJoc(jocuri, numar_jocuri, consola, argv[2]);
        }
        else if (strcmp(argv[1], "vizualizare_jocuri_cumparate") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            consola.vizualizare_jocuri_cumparate();
        }
        else if (strcmp(argv[1], "vizualizare_jocuri_instalate") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            consola.vizualizare_jocuri_instalate();
        }
        else if (strcmp(argv[1], "instalare_joc") == 0)
        {
            if (argc < 3 || argc > 3)
            {
                cout << "comanda trebuie sa fie: instalare_joc <id> " << endl;
                return 0;
            }
            instalareJoc(jocuri, numar_jocuri, consola, argv[2]);
        }
        else if (strcmp(argv[1], "dezinstalare_joc") == 0)
        {
            if (argc < 3 || argc > 3)
            {
                cout << "comanda trebuie sa fie: dezinstalare_joc <id> " << endl;
                return 0;
            }
            dezinstalareJoc(jocuri, numar_jocuri, consola, argv[2]);
        }
        else if (strcmp(argv[1], "cumparare_bundle") == 0)
        {
            if (argc < 3 || argc > 3)
            {
                cout << "comanda trebuie sa fie: cumparare_bundle <id> " << endl;
                return 0;
            }
            cumparareBundle(bundles, numar_bundles, consola, argv[2]);
        }
        else if (strcmp(argv[1], "vizualizare_memorie") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            consola.vizualizare_memorie();
        }
    }
    return 0;
}