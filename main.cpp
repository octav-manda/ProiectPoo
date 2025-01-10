#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <map>
using namespace std;

// ========================== Clasa Produs ==========================
class Produs
{
private:
    string nume;
    double lapte;
    double zahar;
    double cafeaMacinata;
    double pret;

public:
    Produs(const string& nume, double lapte, double zahar, double cafeaMacinata, double pret)
            : nume(nume), lapte(lapte), zahar(zahar), cafeaMacinata(cafeaMacinata), pret(pret) {}

    virtual ~Produs() {}

    virtual void preparaCafea() const = 0;

    string getNume() const
    {
        return nume;
    }

    double getPret() const
    {
        return pret;
    }

    double getLapte() const
    {
        return lapte;
    }

    double getZahar() const
    {
        return zahar;
    }

    double getCafeaMacinata() const
    {
        return cafeaMacinata;
    }

    string toCSV() const
    {
        stringstream ss;
        ss << nume << "," << fixed << setprecision(2) << pret;
        return ss.str();
    }

    void afisareProdus() const
    {
        cout << "Produs: " << nume << ", Pret: " << pret << " lei" << endl;
    }
};

class Capucino : public Produs
{
public:
    Capucino() : Produs("Capucino", 200, 10, 15, 15.0) {}

    void preparaCafea() const override
    {
        cout << "Preparare Capucino: Se folosesc 200ml lapte, 10g zahar, 15g cafea macinata." << endl;
    }
};

class FlatWhite : public Produs
{
public:
    FlatWhite() : Produs("Flat White", 150, 5, 20, 12.0) {}

    void preparaCafea() const override
    {
        cout << "Preparare Flat White: Se folosesc 150ml lapte, 5g zahar, 20g cafea macinata." << endl;
    }
};

class Latte : public Produs
{
public:
    Latte() : Produs("Latte", 250, 15, 10, 14.0) {}

    void preparaCafea() const override
    {
        cout << "Preparare Latte: Se folosesc 250ml lapte, 15g zahar, 10g cafea macinata." << endl;
    }
};

class Espresso : public Produs
{
public:
    Espresso() : Produs("Espresso", 0, 0, 30, 10.0) {}

    void preparaCafea() const override
    {
        cout << "Preparare Espresso: Se folosesc 0ml lapte, 0g zahar, 30g cafea macinata." << endl;
    }
};

// ========================== Clasa Comanda ==========================
class Comanda
{
private:
    string numeClient;
    vector<pair<string, double>> produse; // Nume produs + preț
    double pretTotal;

public:
    Comanda(const string& numeClient) : numeClient(numeClient), pretTotal(0) {}

    void adaugaProdus(const string& numeProdus, double pret)
    {
        produse.emplace_back(numeProdus, pret);
        pretTotal += pret;
    }

    double getPretTotal() const
    {
        return pretTotal;
    }

    string getNumeClient() const
    {
        return numeClient;
    }

    const vector<pair<string, double>>& getProduse() const
    {
        return produse;
    }

    void aplicaReducere(double procent)
    {
        pretTotal -= pretTotal * (procent / 100);
    }

    void afisareDetaliiComanda() const
    {
        cout << "Comanda pentru clientul: " << numeClient << endl;
        for (const auto& produs : produse)
        {
            cout << "- " << produs.first << " (Pret: " << produs.second << " lei)" << endl;
        }
        cout << "Pret total: " << fixed << setprecision(2) << pretTotal << " lei" << endl;
    }

    string toCSV() const
    {
        stringstream ss;
        ss << numeClient << ",";
        for (size_t i = 0; i < produse.size(); ++i)
        {
            ss << produse[i].first << ":" << fixed << setprecision(2) << produse[i].second;
            if (i < produse.size() - 1) ss << ";";
        }
        ss << "," << fixed << setprecision(2) << pretTotal;
        return ss.str();
    }
};

// ========================== Clasa RaportZilnic ==========================
class RaportZilnic
{
private:
    double venituriTotale = 0;          // Totalul veniturilor din comenzi
    double costuriIngrediente = 0;     // Costurile totale ale ingredientelor
    double salariiAngajati = 5000;     // Salariile totale (poți adapta valoarea)
    double profitTotal = 0;            // Profitul total calculat
    double costuriEvenimente = 0; // Costurile totale pentru evenimente

public:
    // Constructor implicit
    RaportZilnic() = default;

    // Adaugă venituri în raport
    void adaugaVenituri(double suma)
    {
        venituriTotale += suma;
    }

    // Adaugă costuri pentru ingrediente
    void adaugaCosturiIngrediente(double cost)
    {
        costuriIngrediente += cost;
    }

    // Calculează profitul total
    void calculeazaProfit()
    {
        profitTotal = venituriTotale - costuriIngrediente - salariiAngajati;
    }

    void adaugaCosturiEvenimente(double cost)
    {
        costuriEvenimente += cost;
    }

    double getCosturiEvenimente() const
    {
        return costuriEvenimente;
    }

    // Generează raportul într-un fișier CSV
    void genereazaRaport(const string& filename)
    {
        calculeazaProfit(); // Asigurăm că profitul este calculat înainte de salvare

        ofstream file(filename);
        if (!file.is_open())
        {
            throw runtime_error("Nu s-a putut deschide fisierul pentru raport.");
        }

        // Scriem datele în fișierul CSV
        file << "Tip,Valoare (lei)\n";
        file << "Venituri totale," << fixed << setprecision(2) << venituriTotale << "\n";
        file << "Costuri ingrediente," << fixed << setprecision(2) << costuriIngrediente << "\n";
        file << "Salarii angajati," << fixed << setprecision(2) << salariiAngajati << "\n";
        file << "Profit total," << fixed << setprecision(2) << profitTotal << "\n";

        file.close();

        cout << "Raportul zilnic a fost generat în fisierul: " << filename << endl;
    }
};

// ========================== Clasa Eveniment ==========================
class Eveniment
{
private:
    string nume;
    string descriere;
    double costuri;

public:
    Eveniment(const string& nume, const string& descriere, double costuri)
            : nume(nume), descriere(descriere), costuri(costuri) {}

    string getNume() const
    {
        return nume;
    }

    double getCosturi() const
    {
        return costuri;
    }

    string toCSV() const
    {
        stringstream ss;
        ss << nume << "," << descriere << "," << fixed << setprecision(2) << costuri;
        return ss.str();
    }

    void afisareEveniment() const
    {
        cout << "Eveniment: " << nume << "\nDescriere: " << descriere
             << "\nCosturi: " << fixed << setprecision(2) << costuri << " lei\n";
    }
};


// ========================== Clasa Manager ==========================
class Manager
{
private:
    vector<Produs*> produse;
    vector<Comanda> comenzi;
    map<string, int> clientiFideli; // Nume client -> numărul de comenzi
    double stocLapte = 10000;       // ml
    double stocZahar = 5000;        // g
    double stocCafeaMacinata = 3000; // g
    vector<Eveniment> evenimente; // Lista de evenimente organizate


public:
    ~Manager()
    {
        for (Produs* produs : produse)
        {
            delete produs;
        }
    }

    void adaugaProdus(Produs* produs)
    {
        produse.push_back(produs);
    }

    void afisareProduse() const
    {
        cout << "Produse disponibile in cafenea:\n";
        for (const Produs* produs : produse)
        {
            produs->afisareProdus();
        }
    }

    void adaugaStoc(const string& ingredient, double cantitate)
    {
        if (ingredient == "lapte")
        {
            stocLapte += cantitate;
        }
        else if (ingredient == "zahar")
        {
            stocZahar += cantitate;
        }
        else if (ingredient == "cafeaMacinata")
        {
            stocCafeaMacinata += cantitate;
        }
        cout << "Adaugare in stoc: " << cantitate << " unitati de " << ingredient << ".\n";
    }

    void scadeStoc(double lapte, double zahar, double cafeaMacinata)
    {
        stocLapte -= lapte;
        stocZahar -= zahar;
        stocCafeaMacinata -= cafeaMacinata;

        cout << "Stocuri actualizate:\n";
        cout << "- Lapte ramas: " << stocLapte << " ml\n";
        cout << "- Zahăr ramas: " << stocZahar << " g\n";
        cout << "- Cafea macinata ramasa: " << stocCafeaMacinata << " g\n";
    }

    void afisareStoc() const
    {
        cout << "Stoc curent:\n";
        cout << "- Lapte: " << stocLapte << " ml\n";
        cout << "- Zahar: " << stocZahar << " g\n";
        cout << "- Cafea macinata: " << stocCafeaMacinata << " g\n";
    }

    bool verificaStoc(double lapte, double zahar, double cafeaMacinata) const
    {
        return stocLapte >= lapte && stocZahar >= zahar && stocCafeaMacinata >= cafeaMacinata;
    }

    public:
        double venituriTotale = 0; // Venituri totale din comenzi

    void plaseazaComanda(const string& numeClient, const vector<string>& produseComandate)
    {
        Comanda comanda(numeClient);

        for (const string& numeProdus : produseComandate)
        {
            bool produsGasit = false;

            for (Produs* produs : produse)
            {
                if (produs->getNume() == numeProdus)
                {
                    produsGasit = true;

                    // Verifică dacă există suficiente ingrediente pentru acest produs
                    if (verificaStoc(produs->getLapte(), produs->getZahar(), produs->getCafeaMacinata()))
                    {
                        // Adaugă produsul în comandă
                        comanda.adaugaProdus(produs->getNume(), produs->getPret());
                        // Adauga pretul produsului in veniturile totale
                        venituriTotale += comanda.getPretTotal();
                        // Scade ingredientele din stoc
                        scadeStoc(produs->getLapte(), produs->getZahar(), produs->getCafeaMacinata());
                        cout << "Produsul " << produs->getNume() << " a fost adaugat în comanda. Stoc actualizat.\n";
                    }
                    else
                    {
                        cout << "Ingrediente insuficiente pentru " << produs->getNume() << "!\n";
                    }
                    break;
                }
            }

            if (!produsGasit)
            {
                cout << "Produsul " << numeProdus << " nu exista în meniul cafenelei.\n";
            }
        }

        // Actualizare număr de comenzi pentru client
        if (clientiFideli.find(numeClient) == clientiFideli.end())
        {
            clientiFideli[numeClient] = 1; // Prima comandă
        }
        else
        {
            clientiFideli[numeClient]++;
        }

        // Aplica reducerea dacă clientul este fidel
        if (clientiFideli[numeClient] > 3)
        {
            cout << "Reducere de 10% aplicata clientului fidel: " << numeClient << endl;
            comanda.aplicaReducere(10); // Reducere de 10%
        }

        // Adaugă comanda în lista comenzilor
        comenzi.push_back(comanda);

        // Afișează detalii pentru comanda curentă
        comanda.afisareDetaliiComanda();
    }

    void afisareComenzi() const
    {
        cout << "\nComenzi plasate:\n";
        for (const auto& comanda : comenzi)
        {
            comanda.afisareDetaliiComanda();
            cout << "--------------------------\n";
        }
    }

    public:
    RaportZilnic raportZilnic; // Instanță pentru gestionarea raportului zilnic

    void afisareProfitZilnic() const
    {
        cout << "Profitul zilnic: " << fixed << setprecision(2) << venituriTotale << " lei\n";
    }
public:
    // Adaugă costurile ingredientelor în raport
    void adaugaCostIngredient(double cantitate, double pretPerUnitate)
    {
        double cost = cantitate * pretPerUnitate;
        raportZilnic.adaugaCosturiIngrediente(cost);

        cout << "Adaugare cost ingrediente: " << cantitate
             << " unitati (Cost total: " << fixed << setprecision(2) << cost << " lei)\n";
    }

    // Adaugă veniturile unei comenzi în raport
    void adaugaVenituriComanda(double venit)
    {
        raportZilnic.adaugaVenituri(venit);
        cout << "Venit adaugat din comanda: " << fixed << setprecision(2) << venit << " lei\n";
    }


    void adaugaEveniment(const string& nume, const string& descriere, double costuri) {
        Eveniment eveniment(nume, descriere, costuri);
        evenimente.push_back(eveniment);
        raportZilnic.adaugaCosturiEvenimente(costuri); // Adaugă costurile evenimentului în raport
        cout << "Evenimentul \"" << nume << "\" a fost adaugat cu succes.\n";
    }


    void afisareEvenimente() const {
        cout << "\nLista evenimentelor organizate:\n";
        for (const auto& eveniment : evenimente) {
            eveniment.afisareEveniment();
            cout << "--------------------------\n";
        }
    }

    void exportaEvenimenteCSV(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Nu s-a putut deschide fisierul pentru exportarea evenimentelor.");
        }

        file << "Nume,Descriere,Costuri (lei)\n";
        for (const auto& eveniment : evenimente) {
            file << eveniment.toCSV() << "\n";
        }

        file.close();
        cout << "Evenimentele au fost exportate în fisierul: " << filename << endl;
    }


    // Generează raportul zilnic
    void genereazaRaportFinal(const string& filename) {
        raportZilnic.adaugaVenituri(venituriTotale); // Sincronizează veniturile totale
        raportZilnic.genereazaRaport(filename);

        ofstream file(filename, ios::app); // Deschide fișierul în modul append pentru a adăuga informațiile suplimentare
        if (!file.is_open()) {
            throw runtime_error("Nu s-a putut deschide fisierul pentru raport.");
        }

        file << "Costuri evenimente," << fixed << setprecision(2) << raportZilnic.getCosturiEvenimente() << "\n";
        file.close();
    }


};



// ========================== Funcția principală ==========================
int main()
{
    try
    {
        Manager manager;

        manager.adaugaProdus(new Capucino());
        manager.adaugaProdus(new FlatWhite());
        manager.adaugaProdus(new Latte());
        manager.adaugaProdus(new Espresso());

        manager.afisareProduse();

        manager.adaugaCostIngredient(500, 0.5);    // Lapte
        manager.adaugaCostIngredient(200, 0.3);    // Zahăr
        manager.adaugaCostIngredient(300, 0.8);    // Cafea măcinată
        manager.afisareStoc();

        manager.plaseazaComanda("Maria", {"Capucino", "Espresso"});
        manager.plaseazaComanda("Andrei", {"Latte", "Flat White"});
        manager.plaseazaComanda("Maria", {"Flat White", "Latte", "Espresso"});
        manager.plaseazaComanda("Maria", {"Flat White", "Latte"});
        manager.plaseazaComanda("Maria", {"Capucino"});

        manager.adaugaEveniment("Degustare de cafea", "Degustare pentru clienții fideli", 1000.0);
        manager.adaugaEveniment("Seară de muzică live", "Concert acustic", 1500.0);
        manager.genereazaRaportFinal("raport_zilnic.csv");
        manager.exportaEvenimenteCSV("evenimente.csv");

        manager.afisareComenzi();
        manager.afisareProfitZilnic();
        manager.genereazaRaportFinal("raport_zilnic.csv");
    }
    catch (const runtime_error& e)
    {
        cerr << "Eroare: " << e.what() << endl;
    }

    return 0;
}
