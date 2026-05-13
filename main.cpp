#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct datiUtente {
    char nome[100];
    char codiceFiscale[15];
    char indirizzo[50];
    double TrimestreAttuale;
    double TrimestrePrecedente;
    double importoNonPagato;
};

void AggiungiUtente() {
    ofstream fTrimestre("TRIMESTRE.BIN", ios::binary);
    datiUtente utente;

    cout << "Inserisci il nome e il cognome dell'utente" << endl;
    cin.ignore();
    cin.getline(utente.nome, 50);
    fTrimestre.write((char*)&utente, sizeof(datiUtente));

    do {
        cout << "Inserisci il codice fiscale dell'utente" << endl;
        cin >> utente.codiceFiscale;
        if (strlen(utente.codiceFiscale) != 2) {
            cout << "non e' stato inserito un valore valido" << endl;
        }
    }while(strlen(utente.codiceFiscale) != 2);
    fTrimestre.write((char*)&utente, sizeof(datiUtente));

    cout << "Inserisci l'indirizzo dell'utente" << endl;
    cin.ignore();
    cin.getline(utente.indirizzo, 50);
    fTrimestre.write((char*)&utente, sizeof(datiUtente));


    cout << "Inserire la lettura del contatore alla fine del trimestre attuale (metri cubi)" << endl;
    cin >> utente.TrimestreAttuale;
    fTrimestre.write((char*)&utente, sizeof(datiUtente));

    cout << "Inserire la lettura del contatore alla fine del trimestre precedente (metri cubi)" << endl;
    cin >> utente.TrimestrePrecedente;
    fTrimestre.write((char*)&utente, sizeof(datiUtente));

    cout << "Inserire l'importo delle bollette precedenti non pagete (0 se non esistono)" << endl;
    cin >> utente.importoNonPagato;
    fTrimestre.write((char*)&utente, sizeof(datiUtente));
}

void ModificaUtente() {
}
void EliminaUtente() {
}


int main()
{
    ofstream fTrimestre("TRIMESTRE.BIN", ios::binary);
    if (!fTrimestre.is_open()) {
        perror("Errore di apertura del file.");
    }

    int scelta;
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
            AggiungiUtente();
            break;
        case 2:
            ModificaUtente();
            break;
        case 3:
            EliminaUtente();
            break;
        case 4:
            fTrimestre.close();
            return 0;
    }
}
