#include "time.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//nó de struct bdtimes
struct time {
    int id; //id dos times
    char nome[50]; //nome do time
    Time *next;
};

//lista simplesmente encadeada (bdtimes)
struct bdtimes {
    Time *first;
    int qtd;
};


// Função que carrega arquivo time.csv
void extraiArquivoTimes(bdTimes *bdt) {
    FILE *file = fopen("arquivos/times.csv", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    Time *novoTime; 
    char linha[255];
    fgets(linha, sizeof(linha), file); //ler o indice (pula o índice)
    while (fgets(linha, sizeof(linha), file) != NULL) {
        novoTime = (Time *)malloc(sizeof(Time));
        if (novoTime == NULL) {
        printf("Erro ao alocar memória");
    }
        sscanf(linha, "%d ,%49[^\n]", &novoTime->id, novoTime->nome);
        inserirBDtimes(novoTime, bdt);
    }
    fclose(file);
}

// Função que insere um novo time (do arquivo times.csv) na struct bdtime
void inserirBDtimes(Time *novoTime, bdTimes *bdt) {
    novoTime->next = bdt->first;
    bdt->first = novoTime;
    bdt->qtd++;
}

// Cria e aloca memória para o estrutura BDTime
bdTimes *createBDTimes() {
   bdTimes *bd = (bdTimes *)malloc(sizeof(bdTimes)); 
    if (bd == NULL) {
        printf("Erro ao alocar memória");
    }
   bd->qtd = 0;                                         
   bd->first = NULL;                    
   return bd; 
}

// Imprime bdTimes
void printBDTimes(bdTimes *bd) {
    int cont = 0;
    for (Time *p = bd->first; p != NULL; p = p->next) {
        printf("Time %d:\n", cont + 1);
        printf("  ID: %d\n", p->id);
        printf("  Nome: %s\n", p->nome);
        cont++;
    }
}

// Libera memória de BDTimes
void liberaBDTimes(bdTimes *bd) {
    Time *p = bd->first;
    Time *t;
    while (p != NULL) {
        t = p->next;
        free(p);
        p = t;
    }
    free(bd);
}

// Retorna a quantidade de times
int getQtdTimes(bdTimes *bdt) {
    return bdt->qtd;
}

// Retorna o ID do time de acordo com o índice
int getIDTime(bdTimes *bdt, int i) { 
    Time *p = bdt->first;
    int cont = 0;
    while(p != NULL && cont < i) {
        p = p->next;
        cont++;
    }
    if(p == NULL) {
        return 1;
    }
    return p->id;
}

// Retorna o nome do time de acordo com o índice
char *getNomeTime(bdTimes *bdt, int i) { 
    Time *p = bdt->first;
    int cont = 0;
    while(p != NULL && cont < i) {
        p = p->next;
        cont++;
    }
    return p->nome;
}

// Função que retorna o nome do time de acordo com o ID
char *nomeID(int id, bdTimes *bdt) { 
    for (int i = 0; i < getQtdTimes(bdt); i++) { // Percorre todos os times
        if (id == getIDTime(bdt, i)) { // Se o id for igual ao id percorrido no índice i
            return getNomeTime(bdt, i); // Retorna o nome
        }
    }
    return NULL; // Caso não encontre nenhum
}

//trocar times para ordenação
void trocarTimes(bdTimes *bdt, int atual, int anterior) {
    Time *pAnterior = bdt->first; //nó aponta para o que first aponta
    int i = 0;
    Time *antesAnterior = NULL;
    while(pAnterior != NULL && i < anterior) { //encontra o ponteiro para o nó anterior
        antesAnterior = pAnterior; //aponta para o anterior
        pAnterior = pAnterior->next; //next do anterior
        i++;
    }
    Time *pAtual = pAnterior->next; //atual
    if (antesAnterior == NULL)  { // então anterior é o primeiro elemento da lista
        bdt->first = pAtual; //first precisa apontar para o atual
    } else { //entao atual é o ultimo/meio elemento
        antesAnterior->next = pAtual; 
    }

    pAnterior->next = pAtual->next; 
    pAtual->next = pAnterior;
}