# pgdecrypt
Projeto em C que trabalha com descriptografia de palavras únicas inspirado em Cifra de Vigenère.

## 📁 Estrutura dos Arquivos

- `/code` — Pasta com todo os arquivos do projeto.
- `/code/descriptografar.c` — Arquivo principal que recebe uma palavra criptografada com Cifra de Vigenère e descriptografa instantaneamente.
- `/code/*.c` — Os demais arquivos .c (todos criados por mim) são usados para gerar os recursos necessários para o projeto, caso já faça o download do projeto com os recursos, não será necessário executá-los.
- `/code/resources/*.txt` — Arquivos de texto utilizados pelo programa. Com a excessão do "lista-palavras" foram todos gerados pelos arquivos .c disponíveis no projeto.

## Objetivo do projeto

Esse software foi criado para um proejto extencionista com o objetivo de interessar pessoas pela área da computação. Acredito que a implementação da descriptografia, da forma como implementada, causa fascínio e interesse em pessoas não familiarizadas com a programação, como se o programa pudesse "ler sua mente".

## Como funciona essa descriptografia

Uma fórmula muito comum de criptografia básica, é a Cifra de Vigenère. Para contexto, pesquise a respeito. Esse projeto trabalha com uma variação dessa criptografia para descriptografar palavras únicas da língua portuguesa seguindo os seguintes critérios:

- Palavras entre 6 e 25 letras.
- Palavras criptografas com uma chave de até 3 letras/números (17.576 possibilidades).

O software é capaz de instantanemanete (menos de 0.05s em média) descriptografar e exibir a palavra original (todas as possíveis, caso haja mais de uma) assim como a chave usada para criptografar.

## Como o algoritmo foi construído

O algoritmo trabalha apenas com palavras da língua portuguesa, exceto nomes próprios, incluindo substantivos, adjetivos, verbos em diversas conjugações, etc. Para otimizar o tempo de execução e garantir descriptografia instantânea, o algoritmo segue o seguinte passo a passo:

1. A palavra criptografada é inserida pelo usuário
2. O algoritmo começa a iterar todas as possibilidades para chaves de até 3 letras/numeros.
3. Palavras com K, Y ou W são automaticamente descartadas, pois não fazem parte da língua portuguesa padrão.
4. Das restantes, são removidas aquelas que não tem vogais o suficiente.
5. Das restantes, são removidas aquelas que possuem bigramas inexistentes no português (lista pré-processada em um dos arquivos de recurso).
6. As restantes são buscadas de forma otimizada em uma lista completa de palavras da lingua portuguesa (+230.000 palavras).


