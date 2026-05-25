# Termo CLI

Implementação em C++ do jogo de palavras **Termo** para terminal, com suporte a múltiplos modos de jogo simultâneos.

---

## Sobre o projeto

Este projeto é uma recriação do jogo [Termo](https://term.ooo/) para ser jogado diretamente no terminal. Foi desenvolvido como exercício prático de C++, com foco em orientação a objetos, modularização de código e manipulação de strings com suporte a UTF-8/caracteres especiais do português.

---

## Funcionalidades

- **Três modos de jogo:** Solo (1 palavra), Dueto (2 palavras) e Quarteto (4 palavras)
- **Feedback colorido** via códigos ANSI: verde para letra correta, amarelo para letra existente no lugar errado, vermelho para letra ausente
- **Dicionário validado:** apenas palavras presentes no arquivo `palavras.txt` são aceitas
- **Balanceamento de tentativas:** o número de chances aumenta proporcionalmente ao número de palavras
- **Suporte a acentos e cedilha:** normalização automática de entrada do usuário
- **Compatibilidade Windows:** ativação automática do modo ANSI via WinAPI

---

## Como compilar

### Linux / macOS
```bash
g++ -o termo main.cpp
```

### Windows (sem dependências externas)
```bash
g++ -o termo.exe main.cpp -static-libgcc -static-libstdc++
```
A flag `-static` embute as dependências no executável, permitindo rodar em máquinas sem o ambiente MinGW instalado.

---

## Como jogar

1. Coloque o executável e o arquivo `palavras.txt` na mesma pasta
2. Execute o programa
3. Selecione o modo de jogo
4. Digite palavras de 5 letras e analise o feedback a cada tentativa

```
Tentativa 1 de 6 - Insira seu chute: cenas
 | C E N A S |
```

---

## Estrutura do código

| Classe | Responsabilidade |
|---|---|
| `PalavraSecreta` | Armazena a palavra sorteada e o estado de acerto |
| `Palpite` | Armazena o chute do jogador, o status de cada letra e a impressão colorida |
| `JogoTermo` | Orquestra a partida: dicionário, validação, comparação e checagem de vitória |

Funções auxiliares globais:
- `normalizar_palavra()` — remove acentos e converte para maiúsculo
- `decidir_palavra()` — sorteia uma palavra aleatória do dicionário
- `ativarANSI()` — habilita cores no terminal Windows

---

## Algoritmo de comparação

A lógica de coloração segue o mesmo algoritmo do Wordle/Termo original, resolvendo corretamente casos com letras duplicadas:

1. **Primeira passagem:** marca letras na posição correta (verde) e bloqueia essas posições
2. **Segunda passagem:** para letras restantes, verifica existência na palavra sem reutilizar posições já bloqueadas (amarelo)

---

## Requisitos

- Compilador C++ com suporte a C++11 ou superior
- Arquivo `palavras.txt` com uma palavra de 5 letras por linha, na mesma pasta do executável

---

## Tecnologias

- **Linguagem:** C++
- **Bibliotecas:** STL (`vector`, `string`, `fstream`) — sem dependências externas
- **Compatibilidade:** Windows, Linux, macOS
