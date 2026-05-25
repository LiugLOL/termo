#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

void verde(char valor) {
    cout << "\033[32m" << valor << "\033[0m" << " ";
}
void amarelo(char valor) {
    cout << "\033[33m" << valor << "\033[0m" << " ";
}
void vermelho(char valor) {
    cout << "\033[31m" << valor << "\033[0m" << " ";
}
//tira acentos e cedilha, "normaliza" a palavra e a joga para MAIÚSCULO
string normalizar_palavra(string palavra) {
    string resultado = "";
    for (size_t i = 0; i < palavra.length(); i++) {
        unsigned char c = palavra[i];
        
        if (c < 128) {
            resultado += toupper(c);
        } 
        else if (c == 195 || c == 196 || c == 197) {
            if (i + 1 >= palavra.length())
                break;
            i++; 
            unsigned char proximo = palavra[i];
            
            // Variantes do A
            if ((proximo >= 128 && proximo <= 133) || (proximo >= 160 && proximo <= 165)) {
                resultado += 'A';
            }
            // Variantes do E
            else if ((proximo >= 136 && proximo <= 139) || (proximo >= 168 && proximo <= 171)) {
                resultado += 'E';
            }
            // Variantes do I
            else if ((proximo >= 140 && proximo <= 143) || (proximo >= 172 && proximo <= 175)) {
                resultado += 'I';
            }
            // Variantes do O
            else if ((proximo >= 146 && proximo <= 150) || (proximo >= 178 && proximo <= 182)) {
                resultado += 'O';
            }
            // Variantes do U
            else if ((proximo >= 154 && proximo <= 157) || (proximo >= 186 && proximo <= 189)) {
                resultado += 'U';
            }
            // Cedilha
            else if (proximo == 135 || proximo == 167) {
                resultado += 'C';
            }
            else {
                resultado += toupper(c); 
            }
        }
    }
    return resultado;
}

// se for windows, para dar cor no terminal, tem que ativar o modo ANSI
void ativarANSI() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(hOut, dwMode);
#endif
}
string decidir_palavra(vector<string> lista_palavras) {
    int total_de_palavras = lista_palavras.size(); 
    int indice_sorteado = rand() % total_de_palavras; 
    //retorna a palavra sorteada
    return lista_palavras[indice_sorteado]; 
}
class PalavraSecreta {
    private:
        string palavra_secreta;
        bool acerto = false;
    public:
        void setPalavraSecreta(string valor) {
            palavra_secreta = valor;
        }
        string getPalavraSecreta() {
            return palavra_secreta;
        }
        //retorna quando a palavra do palpite for igual a certa, alterar o estado de acerto da palavra
        void setAcerto(bool valor) {
            acerto = valor;
        }
        //no final comparar se a palavra tiver ou nao sido acertada
        bool getAcerto() {
            return acerto;
        }
};
class Palpite {
    private:
        string chute;
        int status[5] = {0,0,0,0,0};
    public:
        void setChute(string valor) {
            chute = valor;
        }
        string getChute() {
            return chute;
        }
        void setStatus(int indice, int valor) {
            if (indice >= 0 && indice < 5) {
                status[indice] = valor;
            }
        }
        int getStatus(int indice) {
            if (indice >= 0 && indice < 5) {
                return status[indice];
            }
            return 0;
        }
        bool testarSeAcertouTudo() {
            int contagem = 0;
            for (int i = 0; i < 5; i++) {
                if (status[i] == 2) {
                    contagem++;
                }
            }
            return contagem == 5;
        }
        void imprimirResultado() {
            cout << " | ";
                for (int i = 0; i < 5; i++) {
                    if (status[i] == 2) {
                        verde(chute[i]);
                    } else if (status[i] == 1) {
                        amarelo(chute[i]);
                    } else {
                        vermelho(chute[i]);
                    }
                }
            cout << " | ";
        }
};
class JogoTermo {
    private:
        vector<PalavraSecreta> palavras_certas;
        vector<Palpite> palpites;
        vector<string> dicionario;
    public:
        bool getPalavraAcertada(int indice) {
            if (indice >= 0 && indice < palavras_certas.size()) {
                return palavras_certas[indice].getAcerto();
            }
            return false; // índice inválido
        }
        int getQuantidadePalavras() {
            return palavras_certas.size();
        }
        bool checarVitoria() {
            for (size_t i = 0; i < palavras_certas.size(); i++) {
                if (palavras_certas[i].getAcerto() == false) {
                    return false;  // ainda tem palavra não acertada
                }
            }
            return true;  // todas acertadas
        }
        void setDicionario(vector<string> valor) {
            dicionario = valor;
        }
        bool validacaoPalavra(string chute) {
            for (size_t i = 0; i < dicionario.size(); i++) {
                if (chute == dicionario[i] && chute.length() == 5) {
                    return true;
                }
            }
            return false;
        }
        //funcao para armazenar todas as palavras do jogo atual num vetor de tamanho variavel, para o caso de ter mais de uma palavra no jogo
        //funcao para retornar quais palavras ja foram acertadas, um status do progresso geral,
        //tipo se acertar so a primeira e a terceira palavra vai ficar como {1, 0, 1, 0} pra quarteto e dps pra imprimir eh mais facil de controlar
        int getNumAcertos() {
            int acertos_acumulados = 0;
            for (int i = 0; i < palavras_certas.size(); i++) {
                if (palavras_certas[i].getAcerto() == true) {
                        acertos_acumulados++;
                }
            }
            return acertos_acumulados;
        }
        //coloca as palavras secretas do jogo num vetor, para o caso de ter mais de uma palavra no jogo, e depois tem a funcao pra retornar cada palavra do jogo, pra comparar com o chute depois
        void setPalavraJogo(PalavraSecreta valor) {
            palavras_certas.push_back(valor);
        }
        //como retorna o atributo de um objeto coloquei a funcao do tipo classe, pq as palavras secretas estao nessa classe, ai pra retornar bonitinho
        PalavraSecreta getPalavraJogo(int indice) {
            if (indice >= 0 && indice < palavras_certas.size()) {
                return palavras_certas[indice];
            }
            PalavraSecreta vazia;
            return vazia;
        }
        //teste de logica do palpite x palavra secreta, mesma logica do anterior soq agora modularizada pra ser usada em 1 palpite e 4 palavras por exemplo, feita pra se por num laco
        bool checkPalpite(Palpite &chute, int indice) {
            chute.setChute(normalizar_palavra(chute.getChute()));
            if (palavras_certas[indice].getAcerto() == true) {
                // substitui as letras do chute pelas da palavra já acertada
                chute.setChute(palavras_certas[indice].getPalavraSecreta());
                for (int i = 0; i < 5; i++) {
                    chute.setStatus(i, 2);
                }
                return true;
            } // se a palavra ja foi acertada nao ha pq comparar dnv, entao o jogo ja tem que pular pra proxima palavra, e o chute atual so vai ser comparado com as palavras que ainda nao foram acertadas
            else {
                int chute_usados[5] = {0,0,0,0,0}; // controla letras da palavra secreta ja consumidas
                for (int i = 0; i < 5; i++) {
                    chute.setStatus(i, 0); // reseta o status do chute antes de comparar, pra evitar que o status de um chute anterior interfira no chute atual
                }
                for (int i = 0; i < 5; i++) {
                    if (chute.getChute()[i] == palavras_certas[indice].getPalavraSecreta()[i]) {
                        chute.setStatus(i, 2);
                        chute_usados[i] = 1;
                    }
                }
                
                for (int i = 0; i < 5; i++) {
                    // se a letra estiver verde, nao precisa checar se ela tem amarelo, entao o proximo laco so checa as letras que nao estao verdes
                    if (chute.getStatus(i) == 2) {
                        continue;
                    }
                //checa as amarelas
                    for (int j = 0; j < 5; j++) {
                        if (chute.getChute()[i] == palavras_certas[indice].getPalavraSecreta()[j] && chute_usados[j] == 0) {
                            chute.setStatus(i, 1);
                            chute_usados[j] = 1;
                            break;
                        }
                    }
            }
                // se a palavra inteira for acertada, troca o atributo do objeto para acerto = true
                if (chute.testarSeAcertouTudo() == true) {
                    palavras_certas[indice].setAcerto(true);
                }
            }
            return true;
        }  
};

int main() {
    srand(time(NULL)); // semente para a funcao de decidir palavra aleatoria
    ativarANSI();
    // --- MANUAL DO JOGO ---
    cout << "=========================================================\n";
    cout << "                    BEM-VINDO AO TERMO!                  \n";
    cout << "=========================================================\n";
    cout << "Descubra a palavra certa de 5 letras em ate 6 tentativas.\n\n";
    cout << "COMO JOGAR:\n";
    cout << "* Uma letra \033[32mVERDE\033[0m significa que ela esta \033[32mCORRETA\033[0m e no \033[32mLUGAR CERTO\033[0m.\n";
    cout << "* Uma letra \033[33mAMARELA\033[0m significa que ela \033[32mEXISTE\033[0m, mas no \033[33mLUGAR ERRADO\033[0m.\n";
    cout << "* Uma letra \033[31mVERMELHA\033[0m significa que ela \033[31mNAO EXISTE\033[0m na palavra.\n\n";
    cout << "EXEMPLO:\n";
    cout << "Se o palpite for J O G O S e o resultado for:\n";
    cout << "\033[31mJ\033[0m \033[33mO\033[0m \033[32mG\033[0m \033[31mO\033[0m \033[31mS\033[0m\n";
    cout << "-> A letra 'G' esta no lugar certo.\n";
    cout << "-> A letra 'O' existe na palavra, mas nao nessa posicao.\n";
    cout << "-> As letras 'J', 'S' e o segundo 'O' nao fazem parte da palavra.\n";
    cout << "=========================================================\n\n";
    int modo_de_jogo;

    cout << "Selecione o modo de jogo:\n";
    cout << "1 - Solo(Uma palavra)\n";
    cout << "2 - Dueto(Duas palavras)\n";
    cout << "3 - Quarteto(Quatro palavras)\n";
    cout << "Sua opcao(1, 2 ou 3): ";
    cin >> modo_de_jogo;
    bool modo_valido = false;

    if (modo_de_jogo == 3) {
        modo_de_jogo = 4; // para o quarteto, por ser a terceira opcao e 4 palavras, no loop em baixo so assim p funcionar legal
    }

    JogoTermo partida; // inicia o jogo
    
    ifstream arquivo("palavras.txt");
    vector<string> dicionario;
    string linha;
    while (getline(arquivo, linha)) {
        dicionario.push_back(normalizar_palavra(linha)); // normaliza as palavras do dicionario e joga pro vetor
    }
    partida.setDicionario(dicionario);
    for (int i = 0; i < modo_de_jogo; i++) {
        PalavraSecreta palavra_secreta;
        palavra_secreta.setPalavraSecreta(decidir_palavra(dicionario)); // decide aleatoriamente cada palavra secreta que exista no dicionario
        for (int j = 0; j < partida.getQuantidadePalavras(); j++) {
            // checa se a palavra secreta ja foi escolhida antes, se sim, sorteia outra palavra
            while (palavra_secreta.getPalavraSecreta() == partida.getPalavraJogo(j).getPalavraSecreta()) {
                palavra_secreta.setPalavraSecreta(decidir_palavra(dicionario));
                j = -1; // reinicia o loop para checar novamente todas as palavras ja escolhidas
            }
        }
        partida.setPalavraJogo(palavra_secreta); // coloca as palavras secretas no vetor do jogo
    }

    int k = 0; // sentinela controladora de tentativas
    int chances = 5 + modo_de_jogo; // numero total de chances, quanto mais palavras, mais chances, para balancear a dificuldade
    while (k < chances) {
        Palpite chute;
        string chute_usuario;
        cout << "\nTentativa " << k + 1 << " de " << chances << " - Insira seu chute: ";
        cin >> chute_usuario;
        chute.setChute(normalizar_palavra(chute_usuario)); // normaliza o chute do usuario antes de validar e comparar com as palavras secretas
        bool valido = partida.validacaoPalavra(normalizar_palavra(chute.getChute()));
        if (valido == false) {
            cout << "Palavra invalida(Nao esta no dicionario ou nao tem 5 letras)! Tente novamente.\n";
            continue; // se o chute for invalido, nao conta a tentativa e pede outro chute
        }
        for (int i = 0; i < modo_de_jogo; i++) {
            Palpite chute_atual = chute; // cria um chute atual para cada palavra, pra comparar o mesmo chute com as 4 palavras do quarteto, por exemplo, e cada chute atual vai ter um status diferente dependendo da palavra que ele estiver comparando
            partida.checkPalpite(chute_atual, i);
            chute_atual.imprimirResultado();
        }
        cout << endl; // pula a linha dps do loop de palavras
        if (partida.checarVitoria() == true) {
            cout << "\nParabens! Voce acertou todas as palavras em " << k+1 << " tentativas!\n";
            break;
        }
    k++;
        
    }
    if (k == chances) {
        cout << endl << "Fim de jogo! Suas tentativas acabaram. Voce acertou " << partida.getNumAcertos() << " palavras.\n";
        cout << "A(s) palavra(s) secreta(s) era(m): " << endl;
        for (int i = 0; i < modo_de_jogo; i++) {
                if (partida.getPalavraAcertada(i) == true) {
                    continue; // se a palavra ja tiver sido acertada, nao precisa mostrar qual era, entao o jogo ja tem que pular pra proxima palavra
                }
                 else {
                    cout << partida.getPalavraJogo(i).getPalavraSecreta() << endl;
                }
        }
        cout << endl;
    }

    
    cout << "\nPressione Enter para sair...";
    cin.ignore(); // limpa o buffer de entrada
    cin.get(); // pressionar enter fecha o programa
    
    
   
    return 0;    
}