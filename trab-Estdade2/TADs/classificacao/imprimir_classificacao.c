#include "../system/system.h"
#include "../time/consultar_time.h"
#include "../partida/consultar_partida.h"
#include "imprimir_classificacao.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// PG, V, SG


void InsertionSort(bdPartidas *bdp, bdTimes *bdt) {
    int tamanho = getQtdTimes(bdt);
    for(int atual = 1; atual < tamanho; atual++) {
        int anterior = atual - 1;
        while(anterior >= 0) {
            int idAtual = getIDTime(bdt, anterior + 1);
            int pgAtual = 3*vitorias(idAtual, bdp, bdt) + empates(idAtual, bdp, bdt);
            int vAtual = vitorias(idAtual, bdp, bdt);
            int sgAtual = golsMarcados(idAtual, bdp, bdt) - golsSofridos(idAtual, bdp, bdt);

            int idAnterior = getIDTime(bdt, anterior);
            int pgAnterior = 3*vitorias(idAnterior, bdp, bdt) + empates(idAnterior,bdp,bdt);
            int vAnterior = vitorias(idAnterior, bdp, bdt);
            int sgAnterior = golsMarcados(idAnterior, bdp, bdt) - golsSofridos(idAnterior, bdp, bdt);
            if (pgAnterior < pgAtual) {
                trocarTimes(bdt, anterior+1, anterior);
                anterior--;                  
            }
            else if (pgAnterior == pgAtual) {
                    if (vAnterior < vAtual) {
                        trocarTimes(bdt, anterior+1, anterior);
                        anterior--;  
                    }
    
                    else if (vAnterior == vAtual) {
                            if (sgAnterior < sgAtual) {
                                trocarTimes(bdt, anterior+1, anterior);
                                anterior--;  
                            } else {
                                break; //para sair do loop infinito
                            }
                    } else {
                        break;
                    }
            } else {
                break;
            }   
        }
    }
}

// Imprime a Classificação do Campeonato
void Classificacao(bdTimes *bdt, bdPartidas *bdp) {
    setlocale(LC_ALL, "");
    printf("Ordenando...\n");
    InsertionSort(bdp, bdt);
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
        int pg = 3*v + e;
        int sg = gm-gs;
        printf("%-4d %-12s %3d %3d %3d %4d %4d %5d %4d\n", id, getNomeTime(bdt, i), v, e, d, gm, gs, sg, pg); // Imprime as informações do time
    }
}
