#include "../partida/atualizar_partida.h"
#include "../partida/partida.h"
#include "../system/system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define ARQUIVO_PARTIDAS "arquivos/partidas_completo.csv"

void MostrarPartidas(bdPartidas *bdp, bdTimes *bdt) {
    printf("ID   Time1        Time2        Placar1  Placar2\n");
    for (int i = 0; i < getQtdPartidas(bdp); i++) {
        int idPartida = getPartidaID(bdp, i);
        char *time1 = nomeID(getTime1ID(bdp, i), bdt);
        char *time2 = nomeID(getTime2ID(bdp, i), bdt);
        int golsTime1 = getGolsTime1(bdp, i);
        int golsTime2 = getGolsTime2(bdp, i);
        printf("%-4d %-12s %-12s %-8d %-8d\n", idPartida, time1,time2, golsTime1, golsTime2);
    }
}

//retorna a quantidade de gols que o time 1 fez
int golsID1(bdPartidas *bdp, int id) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if (id == getPartidaID(bdp, i)) {
            return getGolsTime1(bdp, i);
        }
    }
    return -1;
}

//retorna a quantidade de gols que o time 2 fez
int golsID2(bdPartidas *bdp, int id) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if (id == getPartidaID(bdp, i)) {
            return getGolsTime2(bdp, i);
        }
    }
    return -1;
}

//retorna o time 1 da partida id
int IDTime1Partida(bdTimes *bdt, bdPartidas *bdp, int idPartida) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if(getPartidaID(bdp, i) == idPartida) {
            return getTime1ID(bdp, i);
        }
    }
    return -1;
}

//retorna o time2 da partida id
int IDTime2Partida(bdTimes *bdt, bdPartidas *bdp, int idPartida) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if(getPartidaID(bdp, i) == idPartida) {
            return getTime2ID(bdp, i);
        }
    }
    return -1;
}

void AtualizarPartida(bdTimes *bdt, bdPartidas *bdp) {
    if (getQtdPartidas(bdp) == 0){
        printf("---------------------\n");
        printf("Sem registros de Partidas\n");
        printf("---------------------\n");
        return;
    }
    MostrarPartidas(bdp, bdt); //mostra as partidas
    printf("-----------------------------------------\n");
    int gol1, gol2;
    int idAtualizado;
    char placar1[6], placar2[6];
    printf("Digite o ID do registro a ser atualizado:");
    scanf("%d", &idAtualizado);
    printf("Para manter o valor atual de um campo, digite ’-’\n");
    printf("Digite o novo valor para os seguintes campos: \n");
    printf("🥅 Placar1: \n");
    scanf("%s", placar1);
    printf("🥅 Placar2: \n");
    scanf("%s" , placar2);
    if(strcmp(placar1, "-") == 0) { //então, o placar vai ser o mesmo do anterior
        gol1 = golsID1(bdp,idAtualizado);
    } else {
        gol1 = atoi(placar1); //senão, altera o placar novo para inteiro
    }
    if(strcmp(placar2, "-") == 0) { //então, o placar vai ser o mesmo do anterior
        gol2 = golsID2(bdp,idAtualizado);
    } else {
        gol2 = atoi(placar2); //senão, altera o placar novo para inteiro
    }
    int IDtime1 = IDTime1Partida(bdt, bdp, idAtualizado); //id do time 1
    int IDtime2 = IDTime2Partida(bdt, bdp, idAtualizado); //id do time 2
    char *time1 = nomeID(IDtime1, bdt); //nome do time 1
    char *time2 = nomeID(IDtime2, bdt); //nome do time 2
    //confirmação
    printf("Confirma os novos valores para o registro abaixo? (S/N)");
    char option[5]; 
    scanf("%s", option);
    printf("%-4s %-10s %-7s %-10s\n", "ID", "Time 1", "","Time 2");
    printf("%-4d %-10s %-2d x %-2d %-10s\n", idAtualizado, time1, gol1, gol2, time2);
    if (strcmp(option, "S") != 0 && strcmp(option, "s") != 0) {
        printf("Operação Cancelada");
    } 
    AtualizarPartidaLista(idAtualizado, gol1, gol2, bdp);
    AtualizarPartidaArquivo(idAtualizado, gol1, gol2, IDtime1, IDtime2);
}

//atualiza a partida no arquivo
void AtualizarPartidaArquivo(int id, int placar1, int placar2, int time1, int time2) {
    FILE *file = fopen(ARQUIVO_PARTIDAS, "r");
    if (file == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }
    //cria um arquivo temporário
    FILE *temp = fopen("arquivos/partidas_temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }
    char linha[255];
    int encontrou = 0;
    int primeiraLinha = 1;
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (primeiraLinha) {
            fprintf(temp, "%s", linha); //copia o cabeçalho do arquivo original para o temporário
            primeiraLinha = 0;
            continue;
        }
        int idLinha;
        sscanf(linha, "%d,", &idLinha);
        if (idLinha != id) {
            fprintf(temp, "%s", linha);
        } else {
            fprintf(temp, "%d,%d,%d,%d,%d\n", id, time1, time2, placar1, placar2); //escreve a linha atualizada
            encontrou = 1; //diz que encontrou
        }
    }
    fclose(file);
    fclose(temp);
    
    if (encontrou) {
        //remove o arquivo original e renomeia o temporário
        remove(ARQUIVO_PARTIDAS);
        rename("arquivos/partidas_temp.csv", ARQUIVO_PARTIDAS);
        printf("---------------------\n");
        printf("Registro atualizado com sucesso.\n");
        printf("---------------------\n\n");
    } 
    else {
        //remove o arquivo temporário se não encontrou
        remove("arquivos/partidas_temp.csv");
        printf("---------------------\n");
        printf("Partida não encontrada.\n");
        printf("---------------------\n\n");
    }
}