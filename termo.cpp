/*
DIFERENCAS:
Adicionado o arquivo com todas as palavras possiveis para o termo no arquivo palavras.txt, adicionado o random para selecionar qualquer palavra aleatoria do palavras.txt,
adicionado controle e numero de tentativas permitidas para cada palavra,
de resto a logica se manteve, so uma breve formatacao das tentativas e quando acertar faz algo mais bonitinho.
*/
#include <iostream>
#include <cstdlib> // Contém as funções rand() e srand()
#include <ctime>
#include <string>
#include <fstream>
#include <vector> 
using namespace std;

int main() {
    ifstream arquivo("palavras.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo palavras.txt! Verifique se ele esta na mesma pasta do codigo." << endl;
        return 1;
    }

    vector<string> lista_palavras;
    string linha;
    while (getline(arquivo, linha)) {
        lista_palavras.push_back(linha);
    }
    arquivo.close();

    srand(time(NULL));
    int total_de_palavras = lista_palavras.size(); 
    int indice_sorteado = rand() % total_de_palavras; 
    string certa = lista_palavras[indice_sorteado];

    string palpite; // CHUTE
    
    // --- MANUAL DO JOGO ---
    cout << "=========================================================\n";
    cout << "                    BEM-VINDO AO TERMO!                  \n";
    cout << "=========================================================\n";
    cout << "Descubra a palavra certa de 5 letras em ate 6 tentativas.\n\n";
    cout << "COMO JOGAR:\n";
    cout << "* Uma letra MAIUSCULA significa que ela esta CORRETA e no LUGAR CERTO.\n";
    cout << "* Uma letra entre PARENTESES (x) significa que ela EXISTE, mas no LUGAR ERRADO.\n";
    cout << "* Uma letra minuscula comum significa que ela NAO EXISTE na palavra.\n\n";
    cout << "EXEMPLO:\n";
    cout << "Se o palpite for J O G O S e o resultado for:\n";
    cout << "j (o) G o s\n";
    cout << "-> A letra 'G' esta no lugar certo.\n";
    cout << "-> A letra 'O' existe na palavra, mas nao nessa posicao.\n";
    cout << "-> As letras 'J' and 'S' nao fazem parte da palavra.\n";
    cout << "=========================================================\n\n";

    int k = 1; // sentinela controladora de tentativas
    
    while (k != 7) {
        int usados[] = {0, 0, 0, 0, 0}; // letras usadas
        int certos[] = {0, 0, 0, 0, 0}; // letras certas nas posicoes certas
        int errados[] = {0, 0, 0, 0, 0}; // letras certas nas posicoes erradas

        cout << "\nTentativa " << k << " de 6 - Insira seu chute: ";
        cin >> palpite;

        // validacao de tamanho
        if (palpite.length() != 5) {
            cout << "Erro! Seu palpite precisa ter exatamente 5 letras.\n";
            continue;
        }

        // transforma o palpite em minusculo para facilitar a comparacao com a palavra certa
        for (int i = 0; i < 5; i++) {
            palpite[i] = tolower(palpite[i]);
        }

        // Validador de palavra existente no dicionário
        int palavra_valida = 0;
        for (int i = 0; i < lista_palavras.size(); i++) {
            if (palpite == lista_palavras[i]) {
                palavra_valida = 1;
                break;
            }
        }

        if (palavra_valida == 0) {
            cout << "Palavra invalida! Essa palavra nao existe no dicionario do jogo.\n";
            continue; // pula sem contar a tentativa, o jogador pode tentar novamente sem perder uma chance
        }

        // primeiro teste para ver se a letra esta na posicao correta da palavra referencia e do palpite
        for (int i = 0; i < 5; i++) {
            if (palpite[i] == certa[i]) {
                certos[i] = 1; // marca que a letra esta na posicao correta
                usados[i] = 1;
            }
        }

        //primeiro as verdes, prioridade absoluta
        //o proximo laco eh pra verificar as letras certas na posicao errada
        for (int i = 0; i < 5; i++) {
            if (certos[i] == 1) {
                continue; //quando for marcada como correta ela so pula pra proxima iteracao
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
        cout << endl;

        if (numero_acertos == 5) {
            cout << endl << "=========================================================" << endl;
            cout << "      PARABENS! Voce acertou a palavra em " << k << " tentativas! " << endl;
            cout << "=========================================================" << endl;
            break; // interrompe se vencer
        }
        k++; // proxima tentativa
    }

    if (k == 7) {
        cout << endl << "Fim de jogo! Suas tentativas acabaram. A palavra era: " << certa << endl;
    }

    return 0;    
}