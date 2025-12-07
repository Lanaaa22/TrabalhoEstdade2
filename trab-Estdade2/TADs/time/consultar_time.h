#ifndef CONSULTAR_TIME_H
#define CONSULTAR_TIME_H

#include "../time/time.h"
#include "../partida/partida.h"

// Função de consultar as informações do time
void ConsultarTime(bdTimes *bdt, bdPartidas *bdp);

// Retorna a quantidade de Vitórias do time
int vitorias(int id, bdPartidas *bdp, bdTimes *bdt);

// Retorna a quantidade de Empates do time
int empates(int id, bdPartidas *bdp, bdTimes *bdt);

// Retorna a quantidade de Derrotas do time
int derrotas(int id, bdPartidas *bdp, bdTimes *bdt);

// Retorna a quantidade de Gols Marcados do time
int golsMarcados(int id, bdPartidas *bdp, bdTimes *bdt);

// Retorna a quantidade de Gols Sofridos do time
int golsSofridos(int id, bdPartidas *bdp, bdTimes *bdt);

#endif