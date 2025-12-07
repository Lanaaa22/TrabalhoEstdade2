#include "../system/system.h"
#include "../time/consultar_time.h"
#include "../partida/consultar_partida.h"
#include "imprimir_classificacao.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Imprime a Classificação do Campeonato
void Classificacao(bdTimes *bdt, bdPartidas *bdp) {
    setlocale(LC_ALL, "");
    printf("Imprimindo classificação...\n");
    printf("%-4s %-12s %3s %3s %3s %4s %4s %5s %4s\n", "ID", "Time","V", "E", "D", "GM", "GS", "S", "PG"); // Imprime o Cabeçalho
    for(int i = 0; i < getQtdTimes(bdt); i++) { // Percorre os times
        //Pega todas as informações do Time para imprimir
        int id = getIDTime(bdt, i);
        int v = vitorias(id, bdp, bdt);
        int e = empates(id, bdp, bdt);
        int d = derrotas(id, bdp, bdt);
        int gm = golsMarcados(id, bdp, bdt);
        int gs = golsSofridos(id, bdp, bdt);
        printf("%-4d %-12s %3d %3d %3d %4d %4d %5d %4d\n", id, getNomeTime(bdt, i), v, e, d, gm, gs, gm-gs, 3*v + e); // Imprime as informações do time
    }
}