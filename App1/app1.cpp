#include "../Shared/Data/Joc.h"
#include "../Shared/Data/Bundle.h"
#include <fstream>
#include <cstring>

using namespace std;

void vizualizareJocuri(Joc *jocuri, int numar_jocuri)
{
    for (int i = 0; i < numar_jocuri; i++)
    {
        cout << jocuri[i] << endl;
    }
    cout << endl;
}

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

void vizualizareBundles(Bundle *bundles, int numar_bundles)
{
    for (int i = 0; i < numar_bundles; i++)
    {
        cout << bundles[i] << endl;
    }
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

void adaugareJoc(Joc *&jocuri, int &numar_jocuri, Joc joc)
{
    Joc *jocuri_noi = new Joc[numar_jocuri + 1];
    for (int i = 0; i < numar_jocuri; i++)
    {
        jocuri_noi[i] = jocuri[i];
    }
    jocuri_noi[numar_jocuri] = joc;
    numar_jocuri++;
    delete[] jocuri;
    jocuri = jocuri_noi;
    ofstream fout("../Shared/Files/jocuri.txt");
    fout << numar_jocuri << endl;
    for (int i = 0; i < numar_jocuri; i++)
    {
        fout << jocuri[i].getId() << " " << jocuri[i].getDenumire() << " " << jocuri[i].getCategorie() << " " << jocuri[i].getPret() << " " << jocuri[i].getDimensiune() << " " << jocuri[i].getNrCumparari() << endl;
    }
}

void stergereJoc(Joc *&jocuri, int &numar_jocuri, string id)
{
    Joc *jocuri_noi = new Joc[numar_jocuri - 1];
    int index = 0;
    for (int i = 0; i < numar_jocuri; i++)
    {
        if (jocuri[i].getId() != id)
        {
            jocuri_noi[index] = jocuri[i];
            index++;
        }
    }
    if (index == numar_jocuri)
    {
        cout << "Nu exista jocul cu id-ul " << id << endl;
        return;
    }
    numar_jocuri--;
    delete[] jocuri;
    jocuri = jocuri_noi;
    ofstream fout("../Shared/Files/jocuri.txt");
    fout << numar_jocuri << endl;
    for (int i = 0; i < numar_jocuri; i++)
    {
        fout << jocuri[i].getId() << " " << jocuri[i].getDenumire() << " " << jocuri[i].getCategorie() << " " << jocuri[i].getPret() << " " << jocuri[i].getDimensiune() << " " << jocuri[i].getNrCumparari() << endl;
    }
}

void adaugareBundle(Bundle *&bundles, int &numar_bundles, Bundle bundle)
{
    Bundle *bundles_noi = new Bundle[numar_bundles + 1];
    for (int i = 0; i < numar_bundles; i++)
    {
        bundles_noi[i] = bundles[i];
    }
    bundles_noi[numar_bundles] = bundle;
    numar_bundles++;
    delete[] bundles;
    bundles = bundles_noi;
    ofstream fout("../Shared/Files/bundles.txt");
    fout << numar_bundles << endl;
    for (int i = 0; i < numar_bundles; i++)
    {
        fout << bundles[i].getId() << " " << bundles[i].getPret() << " " << bundles[i].getNumarJocuri() << " " << endl;
        for (int j = 0; j < bundles[i].getNumarJocuri(); j++)
        {
            fout << bundles[i].getJocuri()[j]->getId() << " ";
        }
        fout << endl;
    }
}

void stergereBundle(Bundle *&bundles, int &numar_bundles, string id)
{
    Bundle *bundles_noi = new Bundle[numar_bundles - 1];
    int index = 0;
    for (int i = 0; i < numar_bundles; i++)
    {
        if (bundles[i].getId() != id)
        {
            bundles_noi[index] = bundles[i];
            index++;
        }
    }
    if (index == numar_bundles)
    {
        cout << "Nu exista bundle-ul cu id-ul " << id << endl;
        return;
    }
    numar_bundles--;
    delete[] bundles;
    bundles = bundles_noi;
    ofstream fout("../Shared/Files/bundles.txt");
    fout << numar_bundles << endl;
    for (int i = 0; i < numar_bundles; i++)
    {
        fout << bundles[i].getId() << " " << bundles[i].getPret() << " " << bundles[i].getNumarJocuri() << " " << endl;
        for (int j = 0; j < bundles[i].getNumarJocuri(); j++)
        {
            fout << bundles[i].getJocuri()[j]->getId() << " ";
        }
        fout << endl;
    }
}

void modificareJoc(Joc *&jocuri, int &numar_jocuri, string id, string camp, string valoare)
{
    for (int i = 0; i < numar_jocuri; i++)
    {
        if (jocuri[i].getId() == id)
        {
            if (camp == "denumire")
            {
                jocuri[i].setDenumire(valoare);
            }
            else if (camp == "categorie")
            {
                jocuri[i].setCategorie(valoare);
            }
            else if (camp == "pret")
            {
                jocuri[i].setPret(stod(valoare));
            }
            else if (camp == "dimensiune")
            {
                jocuri[i].setDimensiune(stod(valoare));
            }
            else if (camp == "nrCumparari")
            {
                jocuri[i].setNrCumparari(stoi(valoare));
            }
        }
    }
    ofstream fout("../Shared/Files/jocuri.txt");
    fout << numar_jocuri << endl;
    for (int i = 0; i < numar_jocuri; i++)
    {
        fout << jocuri[i].getId() << " " << jocuri[i].getDenumire() << " " << jocuri[i].getCategorie() << " " << jocuri[i].getPret() << " " << jocuri[i].getDimensiune() << " " << jocuri[i].getNrCumparari() << endl;
    }
}

void topJocuri(Joc *jocuri, int numar_jocuri)
{
    // afisare top 3 jocuri dupa numarul de cumparari
    Joc max1, max2, max3;
    for (int i = 0; i < numar_jocuri; i++)
    {
        if (jocuri[i].getNrCumparari() > max1.getNrCumparari())
        {
            max3 = max2;
            max2 = max1;
            max1 = jocuri[i];
        }
        else if (jocuri[i].getNrCumparari() > max2.getNrCumparari())
        {
            max3 = max2;
            max2 = jocuri[i];
        }
        else if (jocuri[i].getNrCumparari() > max3.getNrCumparari())
        {
            max3 = jocuri[i];
        }
    }
    cout << "Top 3 jocuri dupa numarul de cumparari: " << endl;
    cout << "1. " << max1.getDenumire() << endl;
    cout << "2. " << max2.getDenumire() << endl;
    cout << "3. " << max3.getDenumire() << endl;
}

int main(int argc, char **argv)
{
    Joc *jocuri = nullptr;
    int numar_jocuri = 0;
    citireDinFisierJocuri(jocuri, numar_jocuri);
    Bundle *bundles = nullptr;
    int numar_bundles = 0;
    citireDinFisierBundles(bundles, numar_bundles, jocuri, numar_jocuri);
    if (argc > 1)
    {
        if (strcmp(argv[1], "vizualizare_jocuri") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            vizualizareJocuri(jocuri, numar_jocuri);
        }
        else if (strcmp(argv[1], "adaugare_joc") == 0)
        {
            if (argc < 7)
            {
                cout << "comanda trebuie sa fie: adaugare_joc <denumire> <categorie> <pret> <dimensiune> <nrCumparari>" << endl;
                return 0;
            }
            Joc joc;
            string id, denumire, categorie;
            double pret, dimensiune;
            int nrCumparari;
            denumire = argv[2];
            categorie = argv[3];
            pret = atof(argv[4]);
            dimensiune = atof(argv[5]);
            nrCumparari = atoi(argv[6]);
            string lastId = jocuri[numar_jocuri - 1].getId();
            int lastIdInt = atoi(lastId.c_str());
            id = to_string(lastIdInt + 1);
            joc.setId(id);
            joc.setDenumire(denumire);
            joc.setCategorie(categorie);
            joc.setPret(pret);
            joc.setDimensiune(dimensiune);
            joc.setNrCumparari(nrCumparari);
            adaugareJoc(jocuri, numar_jocuri, joc);
        }
        else if (strcmp(argv[1], "stergere_joc") == 0)
        {
            if (argc < 3 || argc > 3)
            {
                cout << "comanda trebuie sa fie: stergere_joc <id>" << endl;
                return 0;
            }
            string id = argv[2];
            stergereJoc(jocuri, numar_jocuri, id);
        }
        else if (strcmp(argv[1], "vizualizare_bundles") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            vizualizareBundles(bundles, numar_bundles);
        }
        else if (strcmp(argv[1], "adaugare_bundle") == 0)
        {
            Bundle bundle;
            string id;
            double pret;
            int numarJocuri;
            pret = atof(argv[2]);
            numarJocuri = atoi(argv[3]);
            string lastId = bundles[numar_bundles - 1].getId();
            int lastIdInt = atoi(lastId.c_str());
            id = to_string(lastIdInt + 1);
            bundle.setId(id);
            bundle.setPret(pret);
            bundle.setNumarJocuri(numarJocuri);
            if (argc < 4 + numarJocuri || argc > 4 + numarJocuri)
            {
                cout << "comanda trebuie sa fie: adaugare_bundle <pret> <numar_jocuri> <list_cod_jocuri>" << endl;
                return 0;
            }
            Joc **jocuriBundle = new Joc *[numarJocuri];
            for (int i = 0; i < numarJocuri; i++)
            {
                string idJoc = argv[4 + i];
                for (int j = 0; j < numar_jocuri; j++)
                {
                    if (jocuri[j].getId() == idJoc)
                    {
                        jocuriBundle[i] = &jocuri[j];
                    }
                }
            }
            bundle.setJocuri(jocuriBundle);
            adaugareBundle(bundles, numar_bundles, bundle);
        }
        else if (strcmp(argv[1], "stergere_bundle") == 0)
        {
            if (argc < 3 || argc > 3)
            {
                cout << "comanda trebuie sa fie: stergere_bundle <id>" << endl;
                return 0;
            }
            string id = argv[2];
            stergereBundle(bundles, numar_bundles, id);
        }
        else if (strcmp(argv[1], "modificare_joc") == 0)
        {
            if (argc < 5 || argc > 5)
            {
                cout << "comanda trebuie sa fie: modificare_joc <id> <camp_de_modificat> <valoarea_modificata>" << endl;
                return 0;
            }
            string id = argv[2];
            string camp_de_modificat = argv[3];
            string valoare = argv[4];
            modificareJoc(jocuri, numar_jocuri, id, camp_de_modificat, valoare);
        }
        else if (strcmp(argv[1], "vizualizare_cele_mai_cumparate_jocuri") == 0)
        {
            if (argc > 2)
            {
                cout << "comanda nu trebuie sa aiba argumente" << endl;
                return 0;
            }
            topJocuri(jocuri, numar_jocuri);
        }
        else
        {
            cout << "Comanda invalida" << endl;
        }
    }
    else
    {
        cout << "Lista argumente: " << endl;
        cout << "vizualizare_jocuri" << endl;
        cout << "adaugare_joc <denumire> <categorie> <pret> <dimensiune> <nrCumparari>" << endl;
        cout << "stergere_joc <id>" << endl;
        cout << "vizualizare_bundles" << endl;
        cout << "adaugare_bundle <pret> <numarJocuri> <idJoc1> <idJoc2> ... <idJocN>" << endl;
        cout << "stergere_bundle <id>" << endl;
        cout << "modificare_joc <id> <camp_de_modificat> <valoare>" << endl;
        cout << "viziualizare_cele_mai_cumparate_jocuri" << endl;
    }
    delete[] jocuri;
    return 0;
}