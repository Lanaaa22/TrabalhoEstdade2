#include "../partida/remover_partida.h"
#include "../system/system.h"
#include "../partida/partida.h"
#include "../partida/atualizar_partida.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define ARQUIVO_PARTIDAS "arquivos/partidas_completo.csv"

void RemoverPartidaArquivo(int id){
    
    FILE *file = fopen(ARQUIVO_PARTIDAS, "r"); //Abre o arquivo original para leitura
    if (file == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }
    FILE *temp = fopen("arquivos/partidas_temp.csv", "w"); //Cria arquivo temporário 
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }
    char linha[255];
    int encontrou = 0;
    int primeiraLinha = 1;
    while (fgets(linha, sizeof(linha), file) != NULL) { // Percorre as linhas do arquivo
        if (primeiraLinha) { // Se for a primeira linha (cabeçalho)
            fprintf(temp, "%s", linha); // Copia o cabeçalho do arquivo original para o temporário
            primeiraLinha = 0;
            continue;
        }
        int idLinha;
        sscanf(linha, "%d,", &idLinha); // Lê e armazena o id da partida
        if (idLinha != id) { // Se o id da partida lida for diferente da partida que deseja remover, escreve no temporário
            fprintf(temp, "%s", linha);
        } 
        else { // Nesse caso, o ID da partida é igual à que deseja remover.
            encontrou = 1; //essa linha agora não vai entrar no arquivo temporário
        }
    }
    fclose(file);
    fclose(temp);
    
    if (encontrou) {
        //remove o arquivo original e renomeia o temporário
        remove(ARQUIVO_PARTIDAS);
        rename("arquivos/partidas_temp.csv", ARQUIVO_PARTIDAS);
    } 
    else {
        //remove o arquivo temporário se não encontrou
        remove("arquivos/partidas_temp.csv");
        printf("Partida não encontrada\n");
    }
}

void RemoverPartida(bdTimes *bdt, bdPartidas *bdp) {
    if (getQtdPartidas(bdp) == 0){
        printf("---------------------\n");
        printf("Sem registros de Partidas\n");
        printf("---------------------\n");
        return;
    }
    MostrarPartidas(bdp,bdt); // Imprime os dados de todas as partidas
    printf("\n\nDigite o ID da partida que deseja remover ou '-' para cancelar: \n");
    char id[5];
    scanf("%s", id);
    int id2;
    if (strcmp(id,"-") == 0) {
        printf("Operação Cancelada. \n");
        return;
    }
    else {
        id2 = atoi(id); // Transforma pra inteiro
    }
    printf("Tem certeza que deseja remover a partida ID %d? (S/N): ", id2);
    char opcao[5];
    scanf("%s", opcao);
    if (strcmp(opcao, "S") != 0 && strcmp(opcao, "s") != 0) {
        printf("Operação Cancelada.\n");
        return;
    } 
    RemoverPartidaArquivo(id2);
    RemoverPartidaLista(id2,bdp);
    printf("Partida removida com sucesso!\n");
}




