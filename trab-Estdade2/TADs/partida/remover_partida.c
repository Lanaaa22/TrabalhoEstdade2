#include "../partida/remover_partida.h"
#include "../system/system.h"
#include "../partida/partida.h"
#include "../partida/atualizar_partida.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void RemoverPartidaArquivo(int id){
    FILE *file = fopen("arquivos/partidas_completo.csv", "r");
    if (file == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }
    FILE *temp = fopen("arquivos/partidas_temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }
    char linha[255];
    int encontrou = 0;
    int primeiraLinha = 1;
    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (primeiraLinha) {
            fprintf(temp, "%s", linha); //copia o cabeçalho do arquivo original para o temporário
            primeiraLinha = 0;
            continue;
        }
        int idLinha;
        sscanf(linha, "%d,", &idLinha);
        if (idLinha != id) {
            fprintf(temp, "%s", linha);
        } else {
            encontrou = 1; //essa linha agora não vai entrar no arquivo temporário
        }
    }
    fclose(file);
    fclose(temp);
    
    if (encontrou) {
        //remove o arquivo original e renomeia o temporário
        remove("arquivos/partidas_completo.csv");
        rename("arquivos/partidas_temp.csv", "arquivos/partidas_completo.csv");
        printf("Partida removida com sucesso!\n");
    } 
    else {
        //remove o arquivo temporário se não encontrou
        remove("arquivos/partidas_temp.csv");
        printf("Partida não encontrada.\n");
    }
}

void RemoverPartida (bdTimes *bdt, bdPartidas *bdp) {
    MostrarPartidas(bdp,bdt);
    printf("Digite o ID da partida que deseja remover ou 0 para cancelar: \n");
    int id;
    scanf("%d", &id);
    if (id == 0) {
        printf("Operação Cancelada. \n");
        return;
    }
    printf("Tem certeza que deseja remover a partida ID %d? (S/N): ", id);
    char opcao[5];
    scanf("%s", opcao);
    if (strcmp(opcao, "S") != 0 && strcmp(opcao, "s") != 0) {
        printf("Operação cancelada.\n");
        return;
    }
    RemoverPartidaArquivo(id);
    RemoverPartidaLista(id,bdp);
}


