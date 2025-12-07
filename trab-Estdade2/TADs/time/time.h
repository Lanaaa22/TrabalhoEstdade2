#ifndef TAD_TIME_H
#define TAD_TIME_H
#include "../partida/partida.h"

//Definição do dado Time para representar uma informação de time
typedef struct time Time;

//Definição do tipo de dados bdTime para representar uma informação de bdtime
typedef struct bdtimes bdTimes;
typedef struct bdpartida bdPartidas;

//Definição de função que carrega o arquivo times.csv
void extraiArquivoTimes(bdTimes *bdt);

//Definição de função que insere a struct novoTime em bdtime
void inserirBDtimes(Time *novoTime, bdTimes *bdt);

//Definição de função que cria um novo bdtime
bdTimes *createBDTimes();

//Definição de função que imprime um bdtime
void printBDTimes(bdTimes *bd);

//Definição de função que libera bdtime
void liberaBDTimes(bdTimes *bd);

// Funções para acessar dados de bdTimes
int getQtdTimes(bdTimes *bdt);
int getIDTime(bdTimes *bdt, int i);
char* getNomeTime(bdTimes *bdt, int i);
char *nomeID(int id, bdTimes *bdt);
#endif