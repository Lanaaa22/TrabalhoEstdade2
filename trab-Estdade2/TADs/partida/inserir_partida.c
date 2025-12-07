#include "inserir_partida.h"
#include "../system/system.h"
#include "../partida/partida.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void InserirPartida(bdTimes *bdt, bdPartidas *bdp) {

    //Requisição dos dados para inserção
    printf("Digite o nome do Time 1: ");
    char time1[50];
    while (getchar() != '\n'); // Limpa o buffer
    scanf("%[^\n]", time1);

    printf("Digite o nome do Time 2: ");
    char time2[50];
    while (getchar() != '\n'); // Limpa o buffer
    scanf("%[^\n]", time2);

    printf("Quantidade de gols que o time 1 fez: ");
    int gol1;
    scanf("%d", &gol1);

    printf("Quantidade de gols que o time 2 fez: ");
    int gol2;
    scanf("%d", &gol2);
    printf("VAI ENTRAR EM ENCONTRARID\n");
    //identificar ID do time mencionado
    int IDtime1;
    int IDtime2;
    int IDproximo;
    IDtime1 = encontrarID(bdt, bdp, time1);
    IDtime2 = encontrarID(bdt, bdp, time2);
    IDproximo = proximoID(bdp);
    printf("Tem certeza de que deseja inserir o registro abaixo?(S/N)");
    char option[5]; 
    scanf("%s", option);
    printf("%-4s %-10s %-7s %-10s\n", "ID", "Time 1", "","Time 2");
    printf("%-4d %-10s %-2d x %-2d %-10s\n", IDproximo, time1, gol1, gol2, time2);
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
    FILE *file = fopen("arquivos/partidas_completo.csv", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }
    char linha[50];
    int ultimoID = 0;
    fgets(linha, sizeof(linha), file); //ler o indice (pula o índice)
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (linha[0] != '\n' && linha[0] != '\0')
            ultimoID++;
    }
    fclose(file);
    return ultimoID;
}

void inserirPartidaArquivo(int id, int time1, int time2, int gol1, int gol2) {
    FILE *file = fopen("arquivos/partidas_completo.csv", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d\n", id, time1, time2, gol1, gol2);
    fclose(file);
}