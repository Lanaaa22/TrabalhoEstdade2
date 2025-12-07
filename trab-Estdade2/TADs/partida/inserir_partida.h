#ifndef INSERIR_PARTIDA_H
#define INSERIR_PARTIDA_H

#include "../time/time.h"
#include "../partida/partida.h"

void InserirPartida(bdTimes *bdt, bdPartidas *bdp);
int encontrarID(bdTimes *bdt, bdPartidas *bdp, char *nome);
int proximoID(bdPartidas *bdp);
void inserirPartidaArquivo(int id, int time1, int time2, int gol1, int gol2);

#endif