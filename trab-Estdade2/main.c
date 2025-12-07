#include <stdio.h>
#include "TADs/system/system.h"
#include <locale.h>

int main() {
    //FUNÇÕES PARA TIME
    setlocale(LC_ALL, "");
    //cria o bdTime
    bdTimes *bdtime = createBDTimes();
    //Carrega os times no arquivo e insere em bdtime
    extraiArquivoTimes(bdtime);
    
    //FUNÇÕES PARA PARTIDA
    bdPartidas *bdpartida = createBDPartidas();
    extraiArquivoPartidas(bdpartida);
    
    LimpaTela();
    lobby(bdtime, bdpartida); // Entra no Menu

    //desaloca memória de bdtime e bdpartida
    liberaBDTimes(bdtime);
    liberaBDPartidas(bdpartida);

    return 0;
}