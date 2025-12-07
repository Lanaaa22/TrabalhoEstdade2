#include "consultar_time.h"
#include "../system/system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Consulta o time de acordo com o prefixo digitado e imprime as informações do time (Nome,ID,V,E,D,GM,GS)
void ConsultarTime(bdTimes *bdt, bdPartidas *bdp) {
    setlocale(LC_ALL, "");
    printf("Digite o nome do time ou prefixo: ");
    char busca[50];
    int encontrado = 0;
    while (getchar() != '\n');
    scanf("%[^\n]", busca);
    int cont = 0;
    for(int i = 0; i < getQtdTimes(bdt); i++) {
        if (strncmp(getNomeTime(bdt, i), busca, strlen(busca)) == 0) {
            cont++;
            if (cont == 1) { // Printa os indices apenas se for a primeira vez
                printf("%-4s %-10s %3s %3s %3s %4s %4s %4s %4s\n", "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
            }
            int id = getIDTime(bdt, i);
            int v = vitorias(id, bdp, bdt);
            int e = empates(id, bdp, bdt);
            int d = derrotas(id, bdp, bdt);
            int gm = golsMarcados(id, bdp, bdt);
            int gs = golsSofridos(id, bdp, bdt);
            printf("%-4d %-10s %3d %3d %3d %4d %4d %4d %4d\n", id, getNomeTime(bdt, i), v, e, d, gm, gs, gm-gs, 3*v + e);

            encontrado = 1;
            
        }
    }
    if (!encontrado) {
        LimpaTela();
        printf("---------------------\n\n");
        printf("Nenhum time com o nome %s foi encontrado\n\n", busca);
        printf("---------------------\n\n");
    }
} 

// Retorna a quantidade de Vitórias do time
int vitorias(int id, bdPartidas *bdp, bdTimes *bdt) {
    int cont = 0;
    
    for(int j = 0; j < getQtdPartidas(bdp); j++) {
        int Time1ID = getTime1ID(bdp, j);
        int Time2ID = getTime2ID(bdp, j);
        int Gol1 = getGolsTime1(bdp, j);
        int Gol2 = getGolsTime2(bdp, j);
        
        // Verifica se o time com o ID passado é o time 1 e venceu
        if ((id == Time1ID) && (Gol1 > Gol2)) {
            cont++;
        }
        // Verifica se o time com o ID passado é o time 2 e venceu
        else if ((id == Time2ID) && (Gol2 > Gol1)) {
            cont++;
        }
    }
    
    return cont;
}

// Retorna a quantidade de Empates do time
int empates(int id, bdPartidas *bdp, bdTimes *bdt) {
    int cont = 0;
    
    for(int j = 0; j < getQtdPartidas(bdp); j++) {
        int Time1ID = getTime1ID(bdp, j);
        int Time2ID = getTime2ID(bdp, j);
        int Gol1 = getGolsTime1(bdp, j);
        int Gol2 = getGolsTime2(bdp, j);
        
        // Verifica se o time com o ID passado é o time 1 e venceu
        if ((id == Time1ID) && (Gol1 == Gol2)) {
            cont++;
        }
        // Verifica se o time com o ID passado é o time 2 e venceu
        else if ((id == Time2ID) && (Gol2 == Gol1)) {
            cont++;
        }
    }
    
    return cont;
}

// Retorna a quantidade de Derrotas do time
int derrotas(int id, bdPartidas *bdp, bdTimes *bdt) {
    int cont = 0;
    
    for(int j = 0; j < getQtdPartidas(bdp); j++) {
        int Time1ID = getTime1ID(bdp, j);
        int Time2ID = getTime2ID(bdp, j);
        int Gol1 = getGolsTime1(bdp, j);
        int Gol2 = getGolsTime2(bdp, j);
        
        // Verifica se o time com o ID passado é o time 1 e venceu
        if ((id == Time1ID) && (Gol1 < Gol2)) {
            cont++;
        }
        // Verifica se o time com o ID passado é o time 2 e venceu
        else if ((id == Time2ID) && (Gol2 < Gol1)) {
            cont++;
        }
    }
    
    return cont;
}

// Retorna a quantidade de Gols Marcados do time
int golsMarcados(int id, bdPartidas *bdp, bdTimes *bdt) {
    int cont = 0;
    
    for(int j = 0; j < getQtdPartidas(bdp); j++) {
        int Time1ID = getTime1ID(bdp, j);
        int Time2ID = getTime2ID(bdp, j);
        int Gol1 = getGolsTime1(bdp, j);
        int Gol2 = getGolsTime2(bdp, j);
        
        // Verifica se o time com o ID passado é o time 1 e venceu
        if (id == Time1ID) {
            cont = cont + Gol1;
        }
        // Verifica se o time com o ID passado é o time 2 e venceu
        else if (id == Time2ID) {
            cont = cont + Gol2;
        }
    }
    
    return cont;
}

// Retorna a quantidade de Gols Sofridos do time
int golsSofridos(int id, bdPartidas *bdp, bdTimes *bdt) {
    int cont = 0;
    
    for(int j = 0; j < getQtdPartidas(bdp); j++) {
        int Time1ID = getTime1ID(bdp, j);
        int Time2ID = getTime2ID(bdp, j);
        int Gol1 = getGolsTime1(bdp, j);
        int Gol2 = getGolsTime2(bdp, j);
        
        // Verifica se o time com o ID passado é o time 1 e venceu
        if (id == Time1ID) {
            cont = cont + Gol2;
        }
        // Verifica se o time com o ID passado é o time 2 e venceu
        else if (id == Time2ID) {
            cont = cont + Gol1;
        }
    }
    
    return cont;
}
