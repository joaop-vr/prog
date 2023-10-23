Trabalho Cifras de Beale

Objetivo: implementar o método de codificação de Cifras de Beale

Aluno: Joao Pedro Vicente Ramalho

===============================================

Linha de comando: "./beale -e -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves "

- As funções para esta funcionalidade estão presentes nos arquivos "arq_chaves.c" e "encode.c".

- Os caracteres foram armazenados em uma lista simplesmente encadeada, alocada de forma dinâmica. Cada nodo desta lista é composto por um "char caracter" que guarda o caractere e por uma lista simplesmente encadeada que contém as chaves do caractere.

- A geração de chaves foi realizada através da criação de uma lista que contém todos os caracteres presentes na tabela de codificação. Em seguida, é feita uma varredura pelo Livro de Cifras e a cada leitura, é realizada uma busca na lista de caracteres, que retorna o ponteiro para o nodo correspondente ao caractere lido. Em seguida, a posição da palavra no livro é adicionada à lista de chaves do caractere. Por exemplo, temos um nodo contendo o caractere "e" e uma lista com suas chaves "0 16 23 45 77".

- Para criar o arquivo de chaves, foi necessário percorrer a lista de caracteres e a lista de chaves de cada caractere, transcrevendo-os para o arquivo passado pela linha de comando.

===============================================

Linha de comando: ./beale -d -i MensagemCodificada -c ArquivoDeChaves -o MensagemDecodificada

- As funções para essa funcionalidade se encontram no arquivo "decode.h".

- Essa funcionalidade foi implementada por meio de uma varredura pela mensagem codificada e a cada código lido foi realizado uma busca no "ArqChaves". Se encontrou uma chave compatível com o código retorna-se o caractere referente a chave. Assim, os caracteres obtidos pela busca são transcritos para o arquivo "mensagemDecodificada".

- Obs: Foi necessário criar códigos específicos para espaços, quebras de linhas e caracteres sem códigos, cujas representações ficaram, respectivamente, -1, -3 e -2.

===============================================

Linha de comando: ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada

- As funções para essa funcionalidade se encontram no arquivo "decode.h".

- Foi alocado um vetor de tamanho N (N = número de palavras do Livro de Cifras), onde cada índice guarda uma struct com a primeira letra de uma palavra do Livro de Cifra e a sua posição no livro. Os nodos foram inseridos sequencialmente, ou seja, o primeiro nodo guarda a primeira letra da primeira palavra do livro e tem posição igual a 0, o segundo guarda a primeira letra da segunda palavra e tem posição igual a 1 e assim por diante. A partir disso, foi feita uma varredura pela mensagem codificada e a cada código lido foi realizada uma Busca Binária no vetor, passando o código como parâmetro, que retorna o caractere correspondente ao código.

- Obs: é possível realizar uma Busca Binária graças ao modo de inserção sequencial dos nodos.
