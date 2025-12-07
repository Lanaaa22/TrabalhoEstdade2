#include "inserir_partida.h"
#include "../system/system.h"
#include "../partida/partida.h"
#include "../partida/consultar_partida.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define ARQUIVO_PARTIDAS "arquivos/partidas_completo.csv"

void mostrarTimes(bdTimes *bdt) {
    printf("%-4s %-10s\n", "ID", "Time 1");
    for(int i = 0;i < getQtdTimes(bdt); i++) {
        printf("%-4d %-10s\n", getIDTime(bdt,i), getNomeTime(bdt, i));
    }
}
void InserirPartida(bdTimes *bdt, bdPartidas *bdp) {
    mostrarTimes(bdt);
    //Requisição dos dados para inserção
    printf("Digite o id do Time 1: ");
    int IDtime1;
    scanf("%d", &IDtime1);

    printf("Digite o id do Time 2: ");
    int IDtime2;
    scanf("%d", &IDtime2);
    if(IDtime1 == IDtime2){
        printf("---------------------\n");
        printf("TIMES IGUAIS NÃO PODEM JOGAR ENTRE SI\n");
        printf("---------------------\n");
        return;
    }
    printf("Quantidade de gols que o time 1 fez: ");
    int gol1;
    scanf("%d", &gol1);

    printf("Quantidade de gols que o time 2 fez: ");
    int gol2;
    scanf("%d", &gol2);
    int IDproximo;
    IDproximo = proximoID(bdp);
    printf("Tem certeza de que deseja inserir o registro abaixo?(S/N)");
    char option[5]; 
    scanf("%s", option);
    printf("%-4s %-10s %-7s %-10s\n", "ID", "Time 1", "","Time 2");
    printf("%-4d %-10s %-2d x %-2d %-10s\n", IDproximo, nome(IDtime1, bdt), gol1, gol2, nome(IDtime2, bdt));
    if (strcmp(option, "S") == 0) {
        //inserir a partida no arquivo
        inserirPartidaArquivo(IDproximo, IDtime1, IDtime2, gol1, gol2);
        Partida *novaPartida = createPartida(IDproximo, IDtime1, IDtime2, gol1, gol2);
        inserirBDPartidas(novaPartida, bdp);
        
        printf("Partida inserida com sucesso!\n");
    }
}

int encontrarID(bdTimes *bdt, bdPartidas *bdp, char *time) {
    for(int i = 0; i < getQtdTimes(bdt); i++) {
        if (strcmp(time, getNomeTime(bdt, i)) == 0) {
            printf("%d", getIDTime(bdt, i));
            return getIDTime(bdt, i);
        }
    }
    return -1;
}

int proximoID(bdPartidas *bdp) {
    FILE *file = fopen(ARQUIVO_PARTIDAS, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }
    char linha[50];
    int ultimoID = 0;
    fgets(linha, sizeof(linha), file); //ler o indice (pula o índice)
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (linha[0] != '\n' && linha[0] != '\0') {
            ultimoID++;
        }
    }
    fclose(file);
    return ultimoID;
}

void inserirPartidaArquivo(int id, int time1, int time2, int gol1, int gol2) {
    FILE *file = fopen(ARQUIVO_PARTIDAS, "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d\n", id, time1, time2, gol1, gol2);
    fclose(file);
}