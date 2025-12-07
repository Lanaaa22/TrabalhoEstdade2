#include "../partida/atualizar_partida.h"
#include "../system/system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Função que retorna o nome do time de acordo com o ID
char *nomeID(int id, bdTimes *bdt) { 
    for (int i = 0; i < getQtdTimes(bdt); i++) { // Percorre todos os times
        if (id == getIDTime(bdt, i)) { // Se o id for igual ao id percorrido no índice i
            return getNomeTime(bdt, i); // Retorna o nome
        }
    }
    return NULL; // Caso não encontre nenhum
}

//acho que está errado considerando que estamos pegando por LISTA ENCADEADA
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

int golsID1(bdPartidas *bdp, int id) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if (id == getPartidaID(bdp, i)) {
            return getGolsTime1(bdp, i);
        }
    }
    return -1;
}

int golsID2(bdPartidas *bdp, int id) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if (id == getPartidaID(bdp, i)) {
            return getGolsTime2(bdp, i);
        }
    }
    return -1;
}

int IDTime1Partida(bdTimes *bdt, bdPartidas *bdp, int idPartida) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if(getPartidaID(bdp, i) == idPartida) {
            return getTime1ID(bdp, i);
        }
    }
    return -1;
}

int IDTime2Partida(bdTimes *bdt, bdPartidas *bdp, int idPartida) {
    for(int i = 0; i < getQtdPartidas(bdp); i++) {
        if(getPartidaID(bdp, i) == idPartida) {
            return getTime2ID(bdp, i);
        }
    }
    return -1;
}

void AtualizarPartida(bdTimes *bdt, bdPartidas *bdp) {
    MostrarPartidas(bdp, bdt);
    int gol1, gol2;
    int idAtualizado;
    char placar1[6], placar2[6];
    printf("Digite o ID do registro a ser atualizado:");
    scanf("%d", &idAtualizado);
    printf("Digite o novo valor para os campos Placar1 e Placar2 (para manter o valor atual de um campo, digite’-’):");
    scanf("%s %s", placar1, placar2);
    if(strcmp(placar1, "-") == 0) {
        gol1 = golsID1(bdp,idAtualizado);
    } else {
        gol1 = atoi(placar1);
    }
    if(strcmp(placar2, "-") == 0) {
        gol2 = golsID2(bdp,idAtualizado);
    } else {
        gol2 = atoi(placar2);
    }
    int IDtime1 = IDTime1Partida(bdt, bdp, idAtualizado);
    int IDtime2 = IDTime2Partida(bdt, bdp, idAtualizado);
    char *time1 = nomeID(IDtime1, bdt);
    char *time2 = nomeID(IDtime2, bdt);
    printf("Confirma os novos valores para o registro abaixo? (S/N)");
    char option[5]; 
    scanf("%s", option);
    printf("%-4s %-10s %-7s %-10s\n", "ID", "Time 1", "","Time 2");
    printf("%-4d %-10s %-2d x %-2d %-10s\n", idAtualizado, time1, gol1, gol2, time2);
    if (strcmp(option, "S") == 0) {
        //AtualizarPartidaArquivo(IDtime1, IDtime2, placar1, placar2);
        AtualizarPartidaLista(idAtualizado, gol1, gol2, bdp);
        AtualizarPartidaArquivo(idAtualizado, gol2, gol1, IDtime1, IDtime2);
        printf("Registro atualizado com sucesso.");
    }
}

void AtualizarPartidaLista(int idAtualizado, int placar1, int placar2, bdPartidas *bdp) {
    Partida *p = getFirstPartida(bdp);
    while (p != NULL) {
        if (getPartidaIDP(bdp, p) == idAtualizado) {
            setTime1Gols(p, placar1);
            setTime2Gols(p, placar2);
        }
        p = getNextPartida(p);
    }
}

void AtualizarPartidaArquivo(int id, int placar1, int placar2, char *time1, char*time2) {
    FILE *file = fopen("arquivos/partidas_completo.csv", "r");
    if (file == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }
    FILE *temp = fopen("arquivos/partidasA_temp.csv", "w");
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
            fprintf(temp, "%d,%d,%d,%d,%d\n", id, time1, time2, placar1, placar2);
            encontrou = 1; 
        }
    }
    fclose(file);
    fclose(temp);
    
    if (encontrou) {
        //remove o arquivo original e renomeia o temporário
        remove("arquivos/partidas_completo.csv");
        rename("arquivos/partidas_temp.csv", "arquivos/partidas_completo.csv");
    } 
    else {
        //remove o arquivo temporário se não encontrou
        remove("arquivos/partidas_temp.csv");
        printf("Partida não encontrada.\n");
    }
}