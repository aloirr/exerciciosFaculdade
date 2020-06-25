#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_STRING 1000

//VARIAVEIS GLOBAIS
FILE *arquivo;
FILE *arquivoNovo;
char arquivoNome[100];
char arquivoNovoNome[100];

/* Struct com base nas colunas do arquivo.csv */
typedef struct dadosMercadoImobiliarioCsv {
    char data[TAM_STRING];
    char info[TAM_STRING];
    char valor[TAM_STRING];
} dadosCsv;

typedef struct dadosLista {
    int tamanho;
    dadosCsv dados;
} dadosLista;

//################ FUNCOES UTEIS ###################

/* pausar a tela */
void pausar() {
    printf("\nAperte enter para continuar.\n");
    getchar();
}
/* verificar se o arquivo existe e se tem alguma coisa nele.
retorna 0 se nao tiver nada no arquivo ou ele nao existir */
int get_size(FILE* file_name) {
    file_name = fopen(arquivoNome,"r");
    if(file_name == NULL)
        return 0;
    fseek(file_name, 0, SEEK_END);
    int size = ftell(file_name);
    fclose(file_name);

    return size;
}
/* grava a lista no arquivoNovo */
void gravarNoArquivo(dadosLista *lista) {
    int tamLista = 0;
    while (tamLista <= lista->tamanho) {
        fprintf(arquivoNovo,"%s,%s,%s\n",lista[tamLista].dados.valor,lista[tamLista].dados.info,lista[tamLista].dados.data);
        tamLista++;
    }
}
/* ordena a lista utilizando o metodo bubblesort */
void bubbleSort(dadosLista *lista) {
    int i;
    int j;
    double aValor;
    double bValor;
    dadosCsv dadosTemp;
    for (i = 0; i<lista->tamanho; i++) {
        for (j = i+1; j<lista->tamanho; j++) {
            aValor = strtod(lista[i].dados.valor,NULL);
            bValor = strtod(lista[j].dados.valor,NULL);
            if (aValor > bValor) {
                strcpy(dadosTemp.data,lista[i].dados.data);
                strcpy(dadosTemp.valor,lista[i].dados.valor);
                strcpy(dadosTemp.info,lista[i].dados.info);
                lista[i].dados = lista[j].dados;
                lista[j].dados = dadosTemp;
            }
        }
    }
    return;
}
/* acrescenta a palavra 'Ordenado' no novo arquivo.csv */
char* adicionarAntesDo(char str1[], char str2[],char delim) {
    int i = 0;
    int j = 0;
    char *novaString = (char *) malloc(100 * sizeof(char));
    bzero(novaString,100);
    for (; i<strlen(str1); i++) {
        if (str1[i] == delim) {
            for (; j<strlen(str2); j++) {
                novaString[i+j] = str2[j];
            }
        }
        if (j > 0) {
            novaString[j+i] = str1[i];
        }        else {
            novaString[i] = str1[i];
        }

    }
    return novaString;
}
/* remove um caractere da string. no caso criei para
retirar o \n e o \r das linhas do csv original. */
void removeChar(char str1[], char c) {
    int i;
    for (i = 0; i<strlen(str1); i++) {
        if (str1[i] == c) {
            str1[i] = str1[i+1];
            i++;
        } else {
            str1[i] = str1[i];
        }
    }
    return;
}
/* retorna a quantidade de linha de um arquivo */
int linhasArquivo(FILE *arquivo) {
    arquivo = fopen(arquivoNome,"r");
    char c = '\n';
    char enter = '\n';
    int qtdLinhas = 0;
    while(fread (&c, sizeof(char), 1, arquivo)) {
        if(c == enter) {
            qtdLinhas++;
        }
    }
    fclose(arquivo);
    return qtdLinhas;
}
int main() {
    /* tela inicial do programa */
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Bem vindo ao sistema de ordenacao de dados.\n");
    printf("Software desenvolvido por Alexandre Guerreiro / RA - 191106755.\n");
    printf("Curso de Eng. de Software / Disciplina: Estrutura de dados\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Digite o nome do arquivo a ser organizado (mercadoimobiliario.csv): ");
    scanf("%s",arquivoNome);
    getchar();
    printf("\n");
    /* verifica se o arquivo que o usuario digitou existe */
    if (get_size(arquivo) == 0) {
        printf("Erro fatal! [%s] indisponível. encerrando o programa.", arquivoNome);
        return 0;
    } else {
        /* definicao das variaveis */
        dadosCsv dados;
        int linhasArq = linhasArquivo(arquivo);
        dadosLista *lista;
        lista = (dadosLista *) malloc((linhasArq+2) * sizeof(dadosCsv));
        char *delimitador = ",";
        char *linhaSplit;
        char linha[BUFSIZ];
        char *linhaBuffer = 0;
        int contadorLinha = 0;
        strcpy(arquivoNovoNome,arquivoNome);
        strcpy(arquivoNovoNome,adicionarAntesDo(arquivoNome,"Ordenado",'.'));
        arquivoNovo = fopen(arquivoNovoNome,"w+");
        arquivo = fopen(arquivoNome,"a+");
        printf("Iniciando a organizacao do arquivo [%s] utlizando o método Bubblesort...\n",arquivoNome);
        pausar();
        /* while de leitura do arquivo. enquanto o fgets nao retorna nulo
        ou seja, enquanto tiver linha no arquivo a ser lida, ele ira executar
        os comandos dentro do while. */
        printf("Linhas lidas: ");
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            /* pega 1 linha do arquivo e joga na struct dadosCsv 'dados' */
            linhaBuffer = (char *) malloc (sizeof(linha));
            linhaBuffer = linha;
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            strcpy(dados.valor,linhaSplit);
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            strcpy(dados.data,linhaSplit);
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            strcpy(dados.info,linhaSplit);
            /* remove as quebras do final das linhas */
            removeChar(dados.info,'\n');
            removeChar(dados.info,'\r');
            removeChar(dados.data,'\n');
            removeChar(dados.data,'\r');
            removeChar(dados.valor,'\n');
            removeChar(dados.data,'\r');
            /* acrescenta na lista */
            lista[contadorLinha].dados = dados;
            contadorLinha++;
            printf(" %d ",contadorLinha);
            lista->tamanho = contadorLinha;
        }
        /* ordena a lista */
        bubbleSort(lista);
        /* grava em um novo arquivo ordenado. */
        gravarNoArquivo(lista);
        printf("\n--------------FIM-----------------\n");
        printf("ORDENACAO BUBBLESORT FINALIZADA!\n");
        printf("TOTAL DE LINHAS ORDENADAS: %d\n",contadorLinha);
        printf("ARQUIVO [%s] GERADO COM SUCESSO!\n",arquivoNovoNome);
        printf("--------- ATÉ A PROXIMA!! ---------\n");
        return 0;
    }
}


