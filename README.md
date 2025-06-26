# pgdecrypt
Projeto em C que trabalha com **descriptografia de palavras únicas** inspirado em Cifra de Vigenère.

## 📁 Estrutura dos Arquivos

- `/code` — Pasta com todo os arquivos do projeto.
- `/code/descriptografar.c` — Arquivo principal que recebe uma palavra criptografada com Cifra de Vigenère e descriptografa instantaneamente.
- `/code/*.c` — Os demais arquivos .c (todos criados por mim) são usados para gerar os recursos necessários para o projeto, caso já faça o download do projeto com os recursos, não será necessário executá-los.
- `/code/resources/*.txt` — Arquivos de texto utilizados pelo programa. Com a excessão do "lista-palavras" foram todos gerados pelos arquivos .c disponíveis no projeto.

## 🎯 Objetivo do Projeto

Esse software foi criado para um projeto extencionista com o objetivo de despertar o interesse de pessoas pela área de computação. A forma como a descriptografia é apresentada pode causar fascínio, especialmente para quem não tem familiaridade com programação — como se o programa fosse capaz de "ler a mente" do usuário.

## 🧠 Como Funciona a Descriptografia

Este projeto utiliza uma variação da **Cifra de Vigenère** para descriptografar palavras únicas da língua portuguesa, com os seguintes critérios:

- Palavras **entre 6 e 25 letras**.
- Palavras criptografas com uma **chave de até 3 letras/números** (26¹ + 26² + 26³ = **18.278** possibilidades).

O programa é capaz de descriptografar em **tempo médio inferior a 0.05s**, retornando a(s) palavra(s) original(is) e a chave utilizada para criptografar.

## ⚙️ Como o Algoritmo Foi Construído

O algoritmo é otimizado para trabalhar com palavras da língua portuguesa (exceto nomes próprios), incluindo substantivos, adjetivos, verbos em diversas conjugações, etc.

Fluxo resumido:

1. A palavra criptografada é inserida pelo usuário
2. O algoritmo testa todas as **18.278** chaves possíveis.
3. Palavras com **K, Y ou W** são automaticamente descartadas, pois não fazem parte da língua portuguesa padrão.
4. Das restantes, são removidas aquelas que não tem **vogais** o suficiente.
5. Das restantes, são removidas aquelas que possuem **bigramas (pares de letras) inexistentes** no português (lista pré-processada em um dos arquivos de recurso).
6. As palavras restantes são verificadas em uma lista com mais de **230.000 palavras** válidas.


