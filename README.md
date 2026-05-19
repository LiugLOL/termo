# Termo em C++ (Console Game)

Uma versão para terminal do famoso jogo **Termo** (inspirado no *Wordle*), desenvolvida inteiramente em C++. O projeto conta com sorteio dinâmico de palavras através de um dicionário externo, tratamento manual de caracteres UTF-8 da língua portuguesa e interface colorida diretamente no terminal.

---

# 🕹️ Como Jogar

O objetivo é descobrir a palavra secreta de 5 letras em no máximo 6 tentativas.

A cada palpite, o jogo fornece um feedback visual utilizando cores:

* 🟩 **Verde:** letra correta na posição correta.
* 🟨 **Amarelo:** letra existe na palavra, mas está na posição errada.
* 🟥 **Vermelho:** letra não existe na palavra secreta.

## Exemplo

Se a palavra correta for:

```txt
JOGOS
```

e o jogador digitar:

```txt
TERMO
```

o terminal exibirá as letras coloridas indicando os acertos e erros.

---

# ⚙️ Funcionalidades

## 📚 Dicionário Dinâmico

O jogo utiliza um arquivo externo chamado `palavras.txt`, permitindo adicionar, remover ou alterar palavras sem modificar o código-fonte.

---

## 🎲 Sorteio Aleatório

A palavra secreta é escolhida aleatoriamente utilizando:

```cpp
srand(time(NULL));
```

garantindo uma experiência diferente a cada partida.

---

## ✅ Validação de Entrada

O sistema verifica:

* se a palavra possui exatamente 5 letras;
* se a palavra existe no dicionário;
* se o arquivo de palavras está vazio;
* se o arquivo foi carregado corretamente.

Palavras inválidas não consomem tentativas.

---

## 🌎 Compatibilidade Cross-Platform

O projeto funciona em:

* Windows
* Linux
* macOS

Foi implementado um sistema condicional com:

```cpp
#ifdef _WIN32
```

para ativar suporte ANSI no terminal do Windows, permitindo cores sem quebrar compatibilidade com Unix/Linux.

---

## 🎨 Interface Colorida no Terminal

O jogo utiliza códigos ANSI Escape para renderizar texto colorido diretamente no console:

```cpp
"\033[32m"
```

Isso permite criar uma experiência visual semelhante ao jogo original mesmo em ambiente de terminal.

---

## 🔤 Normalização UTF-8

O projeto implementa um sistema manual de normalização de caracteres UTF-8.

Palavras com:

* acentos,
* til,
* cedilha,

são convertidas automaticamente para o padrão interno do jogo.

### Exemplos

| Entrada | Normalizado |
| ------- | ----------- |
| maçã    | MACA        |
| órgão   | ORGAO       |
| útil    | UTIL        |

Isso evita problemas comuns de encoding e tamanho de string no terminal.

---

# 🧠 Processo de Desenvolvimento

O projeto foi desenvolvido em múltiplas etapas:

## Fase 1 — Núcleo do Algoritmo

Implementação da lógica principal do jogo:

* sistema de tentativas;
* validação de letras;
* comparação de posições;
* detecção de letras repetidas.

O maior desafio técnico foi implementar corretamente o sistema de prioridade para letras repetidas, evitando falsos positivos.

---

## Fase 2 — Estrutura de Dados e Arquivos

Integração de:

* leitura de arquivos com `ifstream`;
* armazenamento dinâmico utilizando `std::vector`;
* sorteio aleatório de palavras;
* validação de dicionário.

---

## Fase 3 — Compatibilidade e Refinamento

Nesta etapa foram implementados:

* suporte UTF-8;
* compatibilidade Windows/Linux/macOS;
* ativação ANSI no Windows;
* melhorias visuais no terminal;
* tratamento de erros;
* refinamento da experiência do usuário.

Ferramentas de Inteligência Artificial foram utilizadas como apoio de desenvolvimento e debugging durante partes específicas do refinamento técnico do projeto.

---

# 🛠️ Tecnologias Utilizadas

* Linguagem: C++
* Paradigma: Programação Estruturada
* Compilador: GCC / G++
* IDE: Visual Studio Code

## Bibliotecas Utilizadas

```cpp
<iostream>
<vector>
<string>
<fstream>
<cstdlib>
<ctime>
<cctype>
<chrono>
<thread>
```

---

# 🚀 Como Executar

## Opção 1 — Executar o Binário

### Windows

Baixe:

* `termo.exe`
* `palavras.txt`

e coloque ambos na mesma pasta.

Depois execute:

```txt
termo.exe
```

---

## Opção 2 — Compilar Manualmente

### Linux/macOS

```bash
g++ termo.cpp -o termo
./termo
```

### Windows (MinGW)

```bash
g++ termo.cpp -o termo.exe
termo.exe
```

---

# 📂 Estrutura do Projeto

```txt
/
├── termo.cpp
├── palavras.txt
└── README.md
```

