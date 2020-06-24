#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_STRING 1000

//VARIAVEIS GLOBAIS
FILE *arquivo;
char arquivoNome[100];


//################ ESTRUTURA DO ARQUIVO CSV (COLUNAS) ###################

typedef struct dadosMercadoImobiliarioCsv {
    char data[TAM_STRING];
    char info[TAM_STRING];
    char valor[TAM_STRING];
} dadosCsv;

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

int main() {
    /* tela inicial do programa */
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Bem vindo ao sistema de navegacao de dados.\n");
    printf("Software desenvolvido por Alexandre Guerreiro / RA - 191106755.\n");
    printf("Curso de Eng. de Software / Disciplina: Estrutura de dados\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Digite o nome do arquivo a ser lido (mercadoimobiliario.csv): ");
    scanf("%s",arquivoNome);
    getchar();
    printf("\n");
    /* verifica se o arquivo que o usuario digitou existe */
    if (get_size(arquivo) == 0) {
        printf("Erro fatal! [%s] indisponível. encerrando o programa.", arquivoNome);
        return 0;
    } else {
        /* definicao das variaveis */
        arquivo = fopen(arquivoNome,"a+");
        dadosCsv *dados;
        char *delimitador = ",";
        char *linhaSplit;
        char linha[BUFSIZ];
        char *linhaBuffer = 0;
        long int contadorLinha = 0;
        int contadorPausa = 100;
        int opcaoMenu;
        size_t strlen_data;
        size_t strlen_info;
        printf("Iniciando a leitura do arquivo [%s]...\n",arquivoNome);
        pausar();
        /* while de leitura do arquivo. enquanto o fgets nao retorna nulo
        ou seja, enquanto tiver linha no arquivo a ser lida, ele ira executar
        os comandos dentro do while. */
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            contadorLinha++;
            linhaBuffer = (char *) malloc (sizeof(linha));
            dados = (dadosCsv *) malloc(sizeof(dadosCsv));
            linhaBuffer = linha;
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            strcpy(dados->data,linhaSplit);
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            strcpy(dados->info,linhaSplit);
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            strcpy(dados->valor,linhaSplit);
            linhaSplit = (strsep(&linhaBuffer, delimitador));
            /* o separador do csv é a virgula. o if abaixo acrescenta o valor
            depois da virgula da coluna valor no atributo da struct. */
            if (linhaSplit != NULL) {
                strcat(dados->valor,",");
                strcat(dados->valor,linhaSplit);
            }
            strlen_data = strlen(dados->data);
            strlen_info = strlen(dados->info);
            /* os whiles abaixo padronizam as linhas exibidas, facilitando
            a leitura pelo usuario das linhas do codigo. */
            while(strlen_data != 10) {
                strcat(dados->data," ");
                strlen_data = strlen(dados->data);
            }

            while(strlen_info != 50) {
                strcat(dados->info," ");
                strlen_info = strlen(dados->info);
            }
               /* imprime as linhas ja formatadas */
            printf("%s | %s | %s",dados->data,dados->info,dados->valor);
               /* o if abaixo pausa da impressao a cada 100 linhas,
               de acordo com o setado na variavel 'contadorPausa'. Alem de imprimir
               o cabecalho das proximas sequencias de linhas impressas */
            if ((contadorLinha % contadorPausa) == 0) {
                do {
                    printf("-------------------------------ATENCAO----------------------------\n");
                    printf("%lu Linhas mostradas até o momento. Deseja continuar? (1-Sim/2-Nao): ",contadorLinha);
                    printf("\n");
                    printf("-------------------------------ATENCAO----------------------------\n");
                    scanf("%d",&opcaoMenu);
                    getchar();
                    if (opcaoMenu == 1) {
                        system("clear");
                        printf("DATA %5s |"," ");
                        printf(" INFO %45s |"," ");
                        printf(" VALOR");
                        printf("\n");
                        break;
                    } else if (opcaoMenu == 2) {
                        printf("--------- ATÉ A PROXIMA!! ---------");
                        return 0;
                    }
                } while (opcaoMenu != 2);
            }
        }
        pausar();
        printf("--------- ATÉ A PROXIMA!! ---------");
        return 0;
    }
}


