#include "system.h"
#include "../time/consultar_time.h"
#include "../partida/consultar_partida.h"
#include "../classificacao/imprimir_classificacao.h"
#include "../partida/inserir_partida.h"
#include "../partida/remover_partida.h"
#include "../partida/atualizar_partida.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

// Menu do programa (Interface)
void lobby(bdTimes *bdt, bdPartidas *bdp) {  
    setlocale(LC_ALL, "");
    printf("Escolha 1 opcao: ⚽\n\n");
    printf("---------------------\n");
    printf("1: Consultar Time\n");
    printf("2: Consultar Partidas\n");
    printf("3: Atualizar Partida\n");
    printf("4: Remover Partida\n");
    printf("5: Inserir Partida\n");
    printf("6: Imprimir Tabela de Classificação\n");
    printf("7: Sair do programa\n");
    printf("---------------------\n\n");
    char option[5];
    scanf("%s", option); // lê a opção digitada pelo usuário
    if (strcmp(option, "1") == 0) {
        LimpaTela();
        ConsultarTime(bdt, bdp);
        sleep(1.5);
        printf("---------------------\n\n");
        lobby(bdt,bdp);
    } 
    else if (strcmp(option, "2") == 0) {
        LimpaTela();
        ConsultarPartida(bdt, bdp);
        sleep(1.5);
        printf("---------------------\n\n");
        lobby(bdt, bdp);
    } 
    else if (strcmp(option, "3") == 0) {
        LimpaTela();
        AtualizarPartida(bdt, bdp);
        sleep(1.5);
        printf("---------------------\n\n");
        lobby(bdt, bdp);
    }
    else if (strcmp(option, "4") == 0) {
        LimpaTela();
        RemoverPartida(bdt, bdp);
        sleep(1.5);
        printf("---------------------\n\n");
        lobby(bdt, bdp);
    }
    else if (strcmp(option, "5") == 0) {
        LimpaTela();
        InserirPartida(bdt, bdp);
        sleep(1.5);
        printf("---------------------\n\n");
        lobby(bdt, bdp);
    }
    else if (strcmp(option, "6") == 0) {
        LimpaTela();
        Classificacao(bdt, bdp);
        sleep(1.5);
        printf("---------------------\n\n");
        lobby(bdt, bdp);
    }
    else if (strcmp(option, "7") == 0) {
        LimpaTela();
        printf("Saindo do programa...\n");
        return;
    }
    else {
        LimpaTela();
        printf("Digite uma opção válida\n");
        printf("---------------------\n");
        lobby(bdt, bdp);
    }
    //printBDPartidas(bdp);
}
