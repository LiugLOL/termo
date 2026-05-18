#include <iostream>
using namespace std;
#include <string>

int main() {
    string certa = "ARDEM"; // PALAVRA CORRETA FIXA
    string palpite; // CHUTE
    
    int usados[] = {0, 0, 0, 0, 0};
    int certos[] = {0, 0, 0, 0, 0}; 
    int errados[] = {0, 0, 0, 0, 0}; 

    cout << "Insira seu chute: ";
    cin >> palpite;

    for (int i = 0; i < 5; i++) {
        palpite[i] = toupper(palpite[i]);
    }

    // primeiro teste para ver se a letra esta na posicao correta da palavra referencia e do palpite
    for (int i = 0; i < 5; i++) {
        if (palpite[i] == certa[i]) {
            certos[i] = 1; // marca que a letra esta na posicao correta
            usados[i] = 1;
        }
    }

    // primeiro as verdes, prioridade absoluta
    // o proximo laco eh pra verificar as letras certas na posicao errada
    for (int i = 0; i < 5; i++) {
        if (certos[i] == 1) {
            continue; // quando for marcada como correta ela so pula pra proxima iteracao
        }
        for (int j = 0; j < 5; j++) {
            if (palpite[i] == certa[j] and usados[j] == 0) {
                errados[i] = 1;
                usados[j] = 1;
                break;
            }
        }
    }

    int numero_acertos = 0;
    for (int i = 0; i < 5; i++) {
        if (certos[i] == 1) {
            cout << certa[i] << " ";
            numero_acertos++;
        }
        else if (errados[i] == 1) {
            cout << "(" << (char)tolower(palpite[i]) << ")" << " ";
        }
        else {
            cout << (char)tolower(palpite[i]) << " ";
        }
    }

    if (numero_acertos == 5) {
        cout << endl << "Parabens! Voce acertou a palavra!" << endl;
    }

    return 0;    
}