#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct datiUtente {
    char nome[100];
    char codiceFiscale[17];
    char indirizzo[50];
    double TrimestreAttuale;
    double TrimestrePrecedente;
    double importoNonPagato;
};

int main() {
    ifstream fTrimestre("TRIMESTRE.BIN", ios::binary);

    if (!fTrimestre) {
        perror("Errore: impossibile aprire TRIMESTRE.BIN.")
        return 0;
    }

    datiUtente utente;
    int bolletteGenerate = 0;

    while (fTrimestre.read((char*)&utente, sizeof(datiUtente))) {

        double consumo = utente.TrimestreAttuale - utente.TrimestrePrecedente;
        if (consumo < 0) consumo = 0;

        double quotaFissa = 25.00;
        double quotaVariabile = consumo * 2.80;

        double mora = 0.00;
        if (utente.importoNonPagato > 0) {
            mora = 15.00;
        }

        double totale = quotaFissa + quotaVariabile + mora + utente.importoNonPagato;

        char nomeFile[25];
        strcpy(nomeFile, utente.codiceFiscale);
        strcat(nomeFile, ".TXT");

        ofstream fBolletta(nomeFile);

        if (fBolletta) {
            fBolletta << "Nome: " << utente.nome << endl;
            fBolletta << "Codice Fiscale: " << utente.codiceFiscale << endl;
            fBolletta << "Indirizzo: " << utente.indirizzo << endl;
            fBolletta << "Importo bollette precedenti: " << utente.importoNonPagato << endl;
            fBolletta << "Mora: " << mora << endl;
            fBolletta << "Consumi periodo (mc): " << consumo << endl;
            fBolletta << "Quota fissa: " << quotaFissa << endl;
            fBolletta << "Quota variabile: " << quotaVariabile << endl;
            fBolletta << "Totale da pagare: " << totale << endl;
            fBolletta.close();
            bolletteGenerate++;
        } else {
            cout << "Errore nella creazione della bolletta per: " << utente.codiceFiscale << endl;
        }
    }

    fTrimestre.close();
    cout << "Operazione completata con successo" << endl;
    cout << "Sono state generate " << bolletteGenerate << " bollette nella cartella del programma" << endl;

    return 0;
}
