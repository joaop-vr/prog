Autor: João Pedro Vicente Ramalho

Objetivo: implementar um concatenador de arquivos de forma que o início do arquivo concatenador
correspondesse a uma região com os metadados dos arquivos concatenados.
(Obs.: todo arquivo adicionado seria alocado ao final do arquivo concatenador,
ou seja, ao final da "vina").

===========================================================================

src: diretório que contêm os arquivos fontes .c e .h necessários para o programa

===========================================================================

Optei por criar arquivos individuais .c e .h para as operações que possuiam muitas funções (ex.: inserir, excluir e extrair). As operações de "mover" e "imprimir" ficaram em complementares.c juntamente com funções de uso geral.

===========================================================================

main.c: contêm chamada para as funções "gerarDiretorio()" e "operacoes()" (implementadas complementares.c) e para a função "destruirLista()" (implementada em lista.c);

===========================================================================

lista.c: contêm a implementação das funções "inserirNodo()", "criarNodo()" e "destruirLista()". Ou seja, possui as funções responsáveis pela manipulação dos nodos da lista encadeada (diretório);

inserirNodo(): insere o novo nodo na lista;

criarNodo(): armazena os meta dados do arquivo que está sendo adicionado em uma "struct nodo";

destruirLista(): desaloca a a lista;

struct lista contêm os seguintes campos:
int tam; // número de membros no diretório
long int posicao; // ptr para o diretório
struct nodo* inicio; // ptr para o primeiro nodo da lista
struct nodo* fim; // ptr para o final da lista

struct nodo contêm os seguintes campos:
char nome[TAM_NOME]; // nome do Membro
uid_t UID; // UID do usuário
mode_t permissoes; // permissões do Membro
off_t tam; // tamanho de bytes do Membro
long int ultimaMod; // data da última modificação
int ordemArq; // ordem de inserção do Membro no archiver
char local[TAM_BUFFER]; // local do Membro (caminho)
struct nodo\* proximo; // ptr para o próximo nodo da lista

===========================================================================

inserir.c: contêm a implementação das funções "inserir()", "iniciarArchive()", "inserirMembro()", "substituirMembro()" e "escreverMembro()";

inserir: se o Archive estiver vazio chamamos a função "iniciarArchive()", do contrário chamamos "inserirMembro()" para cada arquivo passado pelo usuário. Um dos argumentos desta função é o "Mode", que corresponde ao modo de inserção, ou seja, inserção padrão ou inserção pra substituir ([mode 0]: inserção padrão "inserir -i" e [mode 1]: inserção pra substituir "inserir -a"). Optei por essa abordagem porque considero mais otimizada e consigo tratar os dois "modes" com a utilização de "if()";

inserirMembro: insere no archive os metadados do membro novo e chama a função "escreverMembro()" para escrever o seu conteúdo;

substituiMembro: checa se a versão arquivada é menos recente do que a versão que se deseja inserir. Se for esse o caso, excluímos o membro do archive e escrevemos a versão mais recente ao final deste;

===========================================================================

excluir.c: contêm a implementação das funções "excluir()", "excluirMembro()" e "excluirNoDiretorio()";

excluir: chama a função "excluir()" para cada arquivo passado pelo usuário;

excluirMembro: manipulamos ponteiros de leitura para o início do conteúdo a ser excluído e para o próximo conteúdo presente no archive. Nesse contexto, realizamos um "shift" para a esquerda com o próximo conteúdo de forma que ele sobrescreva o alvo da exclusão. Posteriormente, truncamos o arquivo para descartar os bytes excluídos e reescrevemos o diretório no final do archive;

excluirNoDiretorio: exclui o nodo que contêm os metadados do membro que desejamos excluir;

===========================================================================

extrair.c: contêm implementação das funções "extrair()", "extrairMembro()", "criarArquivo()" e "transcreverMembro()";

extrair: o comando de extrair deve ser "./vina++ -x archive.vpp [membro1.. membro2]". Se o usuário quer extração total dos membros o argc é igual a 3. Assim, essa função verifica o valor de argc, se "argc == 3" percorremos o diretório e chamamos a função "excluirMembro()" para cada membro, caso contrário a chamamos apenas para os membros indicados pelo usuário;

excluirMembro: responsável por chamar as funções para recriar o arquivo e sua hierarquia de diretórios. Depois que essas etapas forem concluídas, chama-se a função de "excluirMembro()";

criarArquivo: recria a hierarquia de diretórios (se necessário), posteriormente cria o arquivo com as permissões adequadas e chama a função "transcreverMembro()";

transcrevermembro: transcreve o conteúdo do membro do archive para o "arquivo.txt" recém criado;

===========================================================================

complementares.c: contêm a implementação das operações "-c" (imprimir()) e "-m target" (mover()). Além disso, possui as implementações de funções mais gerais, cujos comentários estão em complementares.h;

imprimir: imprime no terminal os meta dados de cada membro do diretório (nome, UID, permissões, tamanho e data de modificação);

mover: realiza a manipulação dos ponteiros na lista, movendo o "arquivo.txt" passado pelo usuário para logo depois de "target". Obs.: se o "arquivo.txt" for igual ao "target" não realizamos o deslocamento;
