#ifndef CONSULTAR_PARTIDA_H
#define CONSULTAR_PARTIDA_H

#include "../time/time.h"
#include "../partida/partida.h"

// Menu de consultar partida
void ConsultarPartida(bdTimes *bdt, bdPartidas *bdp);

// Função que imprime as partidas do time mandante
void timeMandante(bdTimes *bdt, bdPartidas *bdp);

// Função que imprime as partidas do time Visitante
void timeVisitante(bdTimes *bdt, bdPartidas *bdp);

// Função que retorna o nome do time de acordo com o ID
char *nome(int id, bdTimes *bdt);

// Função que imprime todas as partidas do time
void timeMandanteVisitante(bdTimes *bdt, bdPartidas *bdp);

// Retornar o id do time escolhido
int GetIDTimeIndice (bdTimes *bdt, bdPartidas *bdp, char *busca);

// Imprime os times digitados e retorna a escolha
int EscolhaTimes(bdTimes *bdt, bdPartidas *bdp, char *busca);

#endif