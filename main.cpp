#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main();

struct datiUtente {
    char nome[100];
    char codiceFiscale[17];
    char indirizzo[50];
    double TrimestreAttuale;
    double TrimestrePrecedente;
    double importoNonPagato;
};

void aggiungiUtente() {
    ofstream fTrimestre("TRIMESTRE.BIN", ios::binary | ios::app);
    datiUtente utente;

    cout << "Inserisci il nome e il cognome dell'utente" << endl;
    cin.ignore();
    cin.getline(utente.nome, 50);


    do {
        cout << "Inserisci il codice fiscale dell'utente" << endl;
        cin >> utente.codiceFiscale;
        if (strlen(utente.codiceFiscale) != 16) {
            cout << "non e' stato inserito un valore valido" << endl;
        }
    }while(strlen(utente.codiceFiscale) != 16);

    cout << "Inserisci l'indirizzo dell'utente" << endl;
    cin.ignore();
    cin.getline(utente.indirizzo, 50);

    cout << "Inserire la lettura del contatore alla fine del trimestre attuale (metri cubi)" << endl;
    cin >> utente.TrimestreAttuale;

    cout << "Inserire la lettura del contatore alla fine del trimestre precedente (metri cubi)" << endl;
    cin >> utente.TrimestrePrecedente;

    cout << "Inserire l'importo delle bollette precedenti non pagete (0 se non esistono)" << endl;
    cin >> utente.importoNonPagato;
    fTrimestre.write((char*)&utente, sizeof(datiUtente));
    fTrimestre.close();
}

void modificaUtente() {
    fstream fTrimestre("TRIMESTRE.BIN", ios::in | ios::out | ios::binary);

    if (!fTrimestre) {
        cout << "Errore: file non trovato." << endl;
        return;
    }

    char cfDaCercare[17];
    cout << "Inserisci il Codice Fiscale dell'utente da modificare: ";
    cin >> cfDaCercare;

    datiUtente utente;
    bool trovato = false;
    long posizione;

    while (fTrimestre.read((char*)&utente, sizeof(datiUtente))) {
        if (strcmp(utente.codiceFiscale, cfDaCercare) == 0) {
            trovato = true;

            posizione = (long)fTrimestre.tellg() - sizeof(datiUtente);

            cout << "Utente trovato: " << utente.nome << endl;

            cout << "Inserisci il nome e il cognome dell'utente" << endl;
            cin.ignore();
            cin.getline(utente.nome, 50);

            do {
                    cout << "Inserisci il codice fiscale dell'utente" << endl;
                    cin >> utente.codiceFiscale;
                    if (strlen(utente.codiceFiscale) != 16) {
                        cout << "non e' stato inserito un valore valido" << endl;
                    }
           }while(strlen(utente.codiceFiscale) != 16);

            cout << "Inserisci l'indirizzo dell'utente" << endl;
            cin.ignore();
            cin.getline(utente.indirizzo, 50);

            cout << "Inserire la lettura del contatore alla fine del trimestre attuale (metri cubi)" << endl;
            cin >> utente.TrimestreAttuale;

            cout << "Inserire la lettura del contatore alla fine del trimestre precedente (metri cubi)" << endl;
            cin >> utente.TrimestrePrecedente;

            cout << "Inserire l'importo delle bollette precedenti non pagete (0 se non esistono)" << endl;
            cin >> utente.importoNonPagato;

            fTrimestre.seekp(posizione, ios::beg);

            fTrimestre.write((char*)&utente, sizeof(datiUtente));

            cout << "Dati aggiornati con successo!" << endl;
            break;
        }
    }

    if (!trovato) {
        cout << "Utente non trovato." << endl;
    }

    fTrimestre.close();
}

void eliminaUtente() {
    ifstream fOriginale("TRIMESTRE.BIN", ios::binary);
    if (!fOriginale) {
        perror("Il file non esiste o e' vuoto");
        return;
    }

    ofstream fTemp("TEMP.BIN", ios::binary);
    if (!fTemp) {
        perror("Errore nella creazione del file temporaneo");
        fOriginale.close();
        return;
    }

    char cfDaEliminare[17];
    cout << "Inserisci il Codice Fiscale dell'utente da eliminare: ";
    cin >> cfDaEliminare;

    datiUtente utente;
    bool trovato = false;

    while (fOriginale.read((char*)&utente, sizeof(datiUtente))) {

        if (strcmp(utente.codiceFiscale, cfDaEliminare) != 0) {
            fTemp.write((char*)&utente, sizeof(datiUtente));
        } else {
            trovato = true;
        }
    }

    fOriginale.close();
    fTemp.close();

    if (trovato) {
        remove("TRIMESTRE.BIN");
        rename("TEMP.BIN", "TRIMESTRE.BIN");
        cout << "Utente eliminato" << endl;
    } else {
        remove("TEMP.BIN");
        cout << "Utente non trovato nell'archivio" << endl;
    }
}

int main()
{
    int scelta;
    do {
            cout << "===================MENU===================" << endl;
            cout << "1. Aggiungi Dati Utente" << endl
            << "2. Modifica Dati Utente" << endl
            << "3. Elimina Dati Utente" << endl
            << "4. Esci" << endl;
            do {
                cin >> scelta;
                if (scelta < 1 || scelta > 4) {
                   cout << "E' stato inserito un valore non valido" << endl;
                }
            }while(scelta < 1 || scelta > 4);

            switch (scelta){
                case 1:
                    aggiungiUtente();
                    break;
                case 2:
                    modificaUtente();
                    break;
                case 3:
                    eliminaUtente();
            break;
                case 4:
                    return 0;
            }

    }while(scelta != 4);

}
