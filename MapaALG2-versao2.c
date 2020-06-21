/*José, professor universitário de Arquitetura e Urbanismo, possui em seu escritório caixas e
mais caixas de livros e revistas, que aos poucos estão sendo catalogados por sua secretária Vanessa.
Vanessa está catalogando em uma planilha eletrônica os principais dados de Livros e Revistas,
tais como (título da obra, edição, nome do autor, editora, isbn, quantidade de exemplares,
caixa onde a obra está armazenada e ano).

A proposta da atividade mapa, é o desenvolvimento de um sistema de pequeno porte para o
controlar onde estão armazenadas as obras do arquiteto. Para a construção deste sistema,
você deverá utilizar a linguagem C, armazenando os dados em arquivo texto.

O sistema a ser construído necessitará atender aos requisitos funcionais abaixo:

1 - Possuir a sua identificação (RA-Nome-Curso)
2 - Possuir um menu de opção.
2.1 - Incluir o registro das obras.
2.2 - Listar todos os livros.
2.3 - Listar todas as revistas.
2.4- Listar as obras por caixa.

O sistema deverá ser entregue da seguinte forma:
Sistema_<SEU_RA>.c
arquivo.txt


O arquivo com os dados das obras, já devem vir previamente cadastradas com no mínimo:
5 livros e 5 revistas, ambas espalhadas em 3 caixas.

Compacte os dois arquivos (Sistema_<SEU_RA>.c e arquivo.txt) e submeta na plataforma Studeo.

Nota:
1 - Não enviar o .exe.
2 - Durante a disciplina iremos ter vídeos com dicas sobre a construção da atividade mapa.*/



// CRIAR UMA STRUCT DE LISTA COM O NOME CAIXA QUE ARMAZENE OS LIVROS E REVISTAS
// CRIAR UMA STRUCT NÓ QUE RECEBA OS DADOS A SEREM COLOCADOS NA LISTA
// CRIAR UMA MENU QUE GERENCIE ESSA LISTA
// CRIAR AS FUNCOES QUE GERENCIEM OS NOS DA LISTA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#define TAM_STRING 500

//VARIAVEIS GLOBAIS
FILE *arquivo;
int qtdCaixas;


//################ ESTRUTURAS (STRUCTS) ###################


// ESTRUTURA DE DADOS OBRA
typedef struct obraDados {
    int caixa;
    char tipo_obra[TAM_STRING]; //aqui sera definido se a obra é um livro ou revista
    char autor[TAM_STRING];
    char titulo[TAM_STRING];
    char editora[TAM_STRING];
    char edicao[TAM_STRING];
    char isbn[TAM_STRING];
    char qtdExemplares[TAM_STRING];
    char anoLancamento[TAM_STRING];
} obraDados;

// ESTRUTURA NÓ DA CAIXA
typedef struct obraElemento {

    struct obraDados* dados_obra;
    struct obraElemento* anterior;
    struct obraElemento* seguinte;

} obraElemento;

// ESTRUTURA DA CAIXA
typedef struct caixa {

    obraElemento* inicio;
    obraElemento* fim;
    int id;
    int tamanho;
} caixa;
caixa *c;

/* INICIALIZANDO TODAS AS CAIXAS */
void inicializarCaixa(caixa* c, int tamCaixa) {
    int i;
    for(i = 0; i<tamCaixa; i++) {
        (c+i)->inicio = NULL;
        (c+i)->fim = NULL;
        (c+i)->tamanho = 0;
        (c+i)->id = i;
    }
}
void addElementoTxt(obraDados* nObra) {
    fprintf(arquivo,"%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
            nObra->caixa,nObra->tipo_obra,nObra->titulo,nObra->autor,
            nObra->edicao,nObra->editora,nObra->isbn,nObra->qtdExemplares);
}
void addElementoCaixa(obraDados* dados) {
    obraElemento *obraNovoElemento;
    obraNovoElemento = (obraElemento *) malloc(sizeof(obraElemento));
    if ((c+dados->caixa)->inicio == NULL) {
        obraNovoElemento->dados_obra = dados;
        obraNovoElemento->anterior = NULL;
        obraNovoElemento->seguinte = NULL;
        (c+dados->caixa)->inicio = obraNovoElemento;
        (c+dados->caixa)->fim = obraNovoElemento;
        (c+dados->caixa)->tamanho++;
        return;
    } else {
        obraNovoElemento->dados_obra = dados;
        obraNovoElemento->anterior = NULL;
        obraNovoElemento->seguinte = (c+dados->caixa)->inicio;
        (c+dados->caixa)->inicio->anterior = obraNovoElemento;
        (c+dados->caixa)->inicio = obraNovoElemento;
        (c+dados->caixa)->tamanho++;
        return;
    }
    free(obraNovoElemento);
}
obraDados* registrarObra(int numCaixa) {
    obraDados* novaObra;
    int opcaoObra;
    novaObra = (obraDados *) malloc(sizeof(obraDados));
    while (opcaoObra != 1 && opcaoObra != 2) {
        printf("LIVRO OU REVISTA? (1 = LIVRO/2 = REVISTA): ");
        scanf("%d", &opcaoObra);
        getchar();
        if (opcaoObra == 1) {
            strcpy(novaObra->tipo_obra,"LIVRO");
        } else if (opcaoObra == 2) {
            strcpy(novaObra->tipo_obra,"REVISTA");
        }
    }
    printf("TITULO: ");
    fgets(novaObra->titulo, sizeof(novaObra->titulo),stdin);
    novaObra->titulo[strcspn(novaObra->titulo, "\n")] = 0;
    printf("AUTOR: ");
    fgets(novaObra->autor, sizeof(novaObra->autor),stdin);
    novaObra->autor[strcspn(novaObra->autor, "\n")] = 0;
    printf("EDICAO: ");
    fgets(novaObra->edicao, sizeof(novaObra->edicao),stdin);
    novaObra->edicao[strcspn(novaObra->edicao, "\n")] = 0;
    printf("EDITORA: ");
    fgets(novaObra->editora, sizeof(novaObra->editora),stdin);
    novaObra->edicao[strcspn(novaObra->edicao, "\n")] = 0;
    novaObra->editora[strcspn(novaObra->editora, "\n")] = 0;
    printf("ISBN: ");
    fgets(novaObra->isbn, sizeof(novaObra->isbn),stdin);
    novaObra->isbn[strcspn(novaObra->isbn, "\n")] = 0;
    printf("Qtd de exemplares: ");
    fgets(novaObra->qtdExemplares, sizeof(novaObra->qtdExemplares),stdin);
    novaObra->qtdExemplares[strcspn(novaObra->qtdExemplares, "\n")] = 0;
//    strcpy(novaObra->caixa,numCaixaChar); OLD
//    strcat(novaObra->caixa,"\t"); OLD
    novaObra->caixa = numCaixa;
    return novaObra;
}
void listarObraPorCaixa(int numCaixa, char *opcaoObra) {
    caixa *caixaTmp;
    caixaTmp = (caixa *) malloc (sizeof(caixa));
    obraElemento* elementoTmp;
    elementoTmp = (obraElemento *) malloc (sizeof(obraElemento));
    int contador;
    caixaTmp = (c+numCaixa);
    contador = 0;
    elementoTmp = caixaTmp->inicio;
    while (elementoTmp != NULL) {
        if (strcmp(elementoTmp->dados_obra->tipo_obra,opcaoObra) == 0) {
            printf("############################\n");
            printf("CAIXA: %d\n",elementoTmp->dados_obra->caixa+1);
            printf("TITULO: %s\n",elementoTmp->dados_obra->titulo);
            printf("AUTOR: %s\n",elementoTmp->dados_obra->autor);
            printf("EDITORA: %s\n",elementoTmp->dados_obra->editora);
            printf("NRO EDICAO: %s\n",elementoTmp->dados_obra->edicao);
            printf("QTD EXEMPLARES: %s\n",elementoTmp->dados_obra->qtdExemplares);
            printf("NRO ISBN: %s\n",elementoTmp->dados_obra->isbn);
            printf("TIPO DE OBRA: %s\n",elementoTmp->dados_obra->tipo_obra);
            printf("\n");
            contador++;
        }
        if (elementoTmp->seguinte != NULL) {
            elementoTmp = elementoTmp->seguinte;
        } else {
            elementoTmp = NULL;
        }
    }
    if (contador == 0)
        printf("NENHUM(A) %s ENCONTRADA NA CAIXA %d\n",opcaoObra,numCaixa+1);
}
void listarTodasAsObras(char *opcaoObra) {
    caixa *caixaTmp;
    obraElemento* elementoTmp;
    elementoTmp = (obraElemento *) malloc (sizeof(obraElemento));
    int contador;
    int i;
    for (i = 0; i<qtdCaixas; i++) {
        caixaTmp = (caixa *) malloc (sizeof(caixa));
        caixaTmp = (c+i);
        contador = 0;
        elementoTmp = caixaTmp->inicio;
        while (elementoTmp != NULL) {
            if (strcmp(elementoTmp->dados_obra->tipo_obra,opcaoObra) == 0) {
                printf("############################\n");
                printf("CAIXA: %d\n",elementoTmp->dados_obra->caixa+1);
                printf("TITULO: %s\n",elementoTmp->dados_obra->titulo);
                printf("AUTOR: %s\n",elementoTmp->dados_obra->autor);
                printf("EDITORA: %s\n",elementoTmp->dados_obra->editora);
                printf("NRO EDICAO: %s\n",elementoTmp->dados_obra->edicao);
                printf("QTD EXEMPLARES: %s\n",elementoTmp->dados_obra->qtdExemplares);
                printf("NRO ISBN: %s\n",elementoTmp->dados_obra->isbn);
                printf("TIPO DE OBRA: %s\n",elementoTmp->dados_obra->tipo_obra);
                printf("\n");
                contador++;
            }
            if (elementoTmp->seguinte != NULL) {
                elementoTmp = elementoTmp->seguinte;
            } else {
                elementoTmp = NULL;
            }
        }
        if (contador == 0)
            printf("NENHUM(A) %s ENCONTRADA NA CAIXA %d\n",opcaoObra,i+1);
    }
}
void pausar() {
    printf("\nAperte enter para continuar.\n");
    getchar();
}
void menuSistema() {
    int opcao;
    int opcaoCaixa;
    int caixasTemp;
    while (opcao != 5) {
        system("clear");
        printf("## SISTEMA DE GERENCIAMENTO DE BIBLIOTECA ###\n");
        printf("PROPRIETARIO: ALEXANDRE LOHAN / RA: 191106755\n");
        printf("1 - Incluir Obra\n");
        printf("2 - Listas todos os livros\n");
        printf("3 - Listas todas as revistas\n");
        printf("4 - Listas obras por caixa\n");
        printf("5 - Sair\n");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
        case 1:
            system("clear");
            caixasTemp = 0;
            while (caixasTemp != -1) {
                system("clear");
                printf("(%d) CAIXAS DISPONIVEIS. QUAL NUMERO DA CAIXA QUE DESEJA UTILIZAR?",qtdCaixas);
                scanf("%d", &opcaoCaixa);
                getchar();
                for (caixasTemp = qtdCaixas; caixasTemp>0; caixasTemp--) {
                    if (opcaoCaixa == caixasTemp) {
                        caixasTemp = -1;
                        break;
                    }
                }
            }
            obraDados *obraTmp = registrarObra(opcaoCaixa-1);
            addElementoTxt(obraTmp);
            addElementoCaixa(obraTmp);
            printf("\nOBRA ADICIONADA COM SUCESSO!\n");
            pausar();
            system("clear");
            break;
        case 2:
            system("clear");
            listarTodasAsObras("LIVRO");
            pausar();
            system("clear");
            break;
        case 3:
            system("clear");
            listarTodasAsObras("REVISTA");
            pausar();
            system("clear");
            break;
        case 4:
            system("clear");
            caixasTemp = 0;
            while (caixasTemp != -1) {
                system("clear");
                printf("(%d) CAIXAS DISPONIVEIS. QUAL NUMERO DA CAIXA QUE DESEJA LISTAR?",qtdCaixas);
                scanf("%d", &opcaoCaixa);
                getchar();
                for (caixasTemp = qtdCaixas; caixasTemp>0; caixasTemp--) {
                    if (opcaoCaixa == caixasTemp) {
                        caixasTemp = -1;
                        break;
                    }
                }
            }
            listarObraPorCaixa((opcaoCaixa)-1,"LIVRO");
            listarObraPorCaixa((opcaoCaixa)-1,"REVISTA");
            pausar();
            system("clear");
            break;
        case 5:
            fclose(arquivo);
            break;
        default:
            system("clear");
            printf("OPCAO INVALIDA! TENTE NOVAMENTE\n");
            pausar();
            system("clear");
            break;
        }
    }
}
int fileExists(char *cpfileName) {
    int errcode = access(cpfileName, F_OK);
    if (errcode == ENOENT)
        return 0; /* nao existe */
    return 1; /* existe */
}

long ler_apenas_se_for_inteiro() {
    char buffer_de_entrada[64];
    char* onde_a_funcao_de_conversao_parou;

    while (1) {
        fgets(buffer_de_entrada, 64, stdin);
        long numero_lido = strtol(buffer_de_entrada, &onde_a_funcao_de_conversao_parou, 0);

        /* Se o número resultante é zero e o ponteiro que aponta para o caractere da string
         * no final da conversão não andou é porque não ocorreu conversão, ou seja, falhou. Além disso, o caractere onde a conversão parou
         * tem que ser uma quebra de linha, caso contrário há caracteres não numéricos
         * que foram ignorados pelo strtol, o que significa que a entrada
         * não possui somente números.
         */
        if ((numero_lido == 0 && onde_a_funcao_de_conversao_parou == buffer_de_entrada)
                || *onde_a_funcao_de_conversao_parou != '\n') {
            printf("Número inválido. Digite novamente.\n");
            continue;
        } else {
            return numero_lido;
        }
    }
}
void selecionaCriarNovaCaixa() {
    char arquivoBiblioteca[50];
    printf("QUANTAS CAIXAS VOCÊ DESEJA ABRIR PARA ARMAZENAS SUAS OBRAS? R: ");
    qtdCaixas = (int) ler_apenas_se_for_inteiro();
//    getchar();
    printf("DIGITE O NOME DO ARQUIVO DE SUA BIBLIOTECA (EX.: obras.txt). R: ");
    scanf("%s", arquivoBiblioteca);
    getchar();
    if (fileExists(arquivoBiblioteca) == 1) {
        remove(arquivoBiblioteca);
    }
    c = malloc(qtdCaixas * sizeof(struct caixa));
    inicializarCaixa(c, qtdCaixas);
    arquivo = fopen (arquivoBiblioteca,"a+");
    fprintf(arquivo, "%d\n", qtdCaixas);
    if (arquivo == NULL) {
        printf("ERRO AO LER/GERAR BANCO DE DADOS! FALTA DE ESPACO OU PERMISSAO NEGADA. SAINDO!");
        return;
    }
}

void selecionaCaixaExistente() {
// **** BUSCA O ARQUIVO.TXT COM AS OBRAS JA ARMAZENADAS
    obraDados* dados;
    char arquivoBiblioteca[50];
    char delim[] = "\t";
    char buffer[BUFSIZ];
    char *linhaBuffer = 0;
    char *linhaSpliter = 0;
    char *linhaBufferCpy = 0;
    printf("DIGITE O NOME DO ARQUIVO (EX.: obras.txt). R: ");
    fgets(arquivoBiblioteca, sizeof(char[50]),stdin);
    arquivoBiblioteca[strcspn(arquivoBiblioteca, "\n")] = 0;
    arquivo = fopen (arquivoBiblioteca,"a+");
    fgets(buffer, BUFSIZ, arquivo);
    linhaBuffer = strdup(buffer);
    qtdCaixas = strtol(linhaBuffer,NULL,0);
    c = (caixa *) malloc(qtdCaixas * sizeof(caixa));
    inicializarCaixa(c, qtdCaixas);
    while(fgets(buffer, BUFSIZ, arquivo) != NULL) {
        dados = (obraDados *) malloc(sizeof(obraDados));
        linhaBuffer = strdup(buffer); //  TENTA ALOCAR NA NOVA STRING, MEMORIA SUFICIENTE PARA CONTER A STRING MAIS ANTIGA E +1 CHAR "\0
        linhaBufferCpy = linhaBuffer;
        linhaSpliter = 0;
        while ((linhaSpliter = strsep(&linhaBufferCpy, delim)) != NULL) {
            dados->caixa = strtol(linhaSpliter,NULL,0);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            strcpy(dados->tipo_obra,linhaSpliter);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            strcpy(dados->titulo,linhaSpliter);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            strcpy(dados->autor,linhaSpliter);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            strcpy(dados->edicao,linhaSpliter);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            strcpy(dados->editora,linhaSpliter);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            strcpy(dados->isbn,linhaSpliter);
            linhaSpliter = strsep(&linhaBufferCpy, delim);
            linhaSpliter[strcspn(linhaSpliter,"\n")] = 0;
            strcpy(dados->qtdExemplares,linhaSpliter);
        }
        addElementoCaixa(dados);
    }
}

int main() {
// **** DE    FINICAO DA QUANTIDADE DE CAIXAS PARA ARMAZENAMENTO DE OBRAS
    int opcaoInicial;
    while ((opcaoInicial == 0) || (opcaoInicial > 2)) {
        printf("BEM VINDO A BIBLIOTECA DE OBRAS!\n");
        printf("CRIAR BIBLIOTECA OU USAR EXISTENTE? (1-EXISTENTE / 2-NOVA)? R: ");
        opcaoInicial = (int) ler_apenas_se_for_inteiro();
    }
    if (opcaoInicial == 2) {
        selecionaCriarNovaCaixa();
        menuSistema();
    } else if (opcaoInicial == 1) {
        selecionaCaixaExistente();
        menuSistema();
    }
    return 0;
}

