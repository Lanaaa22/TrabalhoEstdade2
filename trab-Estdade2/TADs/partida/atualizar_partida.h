#ifndef ATUALIZAR_PARTIDA_H
#define ATUALIZAR_PARTIDA_H

#include "../time/time.h"
#include "../partida/partida.h"

//acho que está errado considerando que estamos pegando por LISTA ENCADEADA
void MostrarPartidas(bdPartidas *bdp, bdTimes *bdt);

void AtualizarPartida(bdTimes *bdt, bdPartidas *bdp);
//AtualizarPartidaArquivo(IDtime1, IDtime2, placar1, placar2);
void AtualizarPartidaLista(int idAtualizado, int placar1, int placar2, bdPartidas *bdp);
void AtualizarPartidaArquivo(int id, int placar1, int placar2, int time1, int time2);
int golsID2(bdPartidas *bdp, int id);
int golsID1(bdPartidas *bdp, int id);
#endif