# ⚽ Campeonato Computacional de Futebol (Parte 2)
Sistema de gerenciamento de campeonatos de futebol em C, com funcionalidades de consulta de times, partidas e classificação.

**Colaboradores:**  
Fernando Bitarães (BitArrays) Stela Montenegro  
Ilanna dos Reis Cardoso

---

## 📂 Estrutura do Projeto
```

TRAB-ESTDADE2/
│
├── arquivos/
│   ├── partidas_completo.csv
│   ├── partidas_parcial.csv
│   ├── partidas_vazio.csv
│   └── times.csv
│
├── TADs/
│   ├── classificacao/
│   │   ├── imprimir_classificacao.c
│   │   └── imprimir_classificacao.h
│   │
│   ├── partida/
│   │   ├── atualizar_partida.c
│   │   ├── atualizar_partida.h
│   │   ├── consultar_partida.c
│   │   ├── consultar_partida.h
│   │   ├── inserir_partida.c
│   │   ├── inserir_partida.h
│   │   ├── partida.c
│   │   ├── partida.h
│   │   ├── remover_partida.c
│   │   └── remover_partida.h
│   │
│   └── system/
│       ├── auxiliares.c
│       ├── auxiliares.h
│       ├── system.c
│       ├── system.h
│       │
│       └── time/
│           ├── consultar_time.c
│           ├── consultar_time.h
│           ├── time.c
│           └── time.h
│
├── main.c
│
└── makefile

```

---

## 👾 Compilação e Execução

### **Pré-requisito:**
Instalar o pacote que contém o compilador GCC e o Make, além de outras bibliotecas necessárias para o desenvolvimento no Ubuntu:
```

sudo apt install build-essential

```

### **Limpando arquivos temporários:**
```

make clean

```

### **Compilando manualmente:**
```

gcc main.c TADs/classificacao/imprimir_classificacao.c TADs/partida/atualizar_partida.c TADs/partida/consultar_partida.c TADs/partida/inserir_partida.c TADs/partida/partida.c TADs/partida/remover_partida.c TADs/system/auxiliares.c TADs/system/system.c TADs/system/time/consultar_time.c TADs/system/time/time.c -I TADs -o programa

```

### **Executando:**
```

./programa

````

---

## 🎲 Estrutura de Dados

### Struct **Partida**
```c
struct partida {
    int id;          // Identificador da partida
    int Time1id;     // ID do primeiro time
    int Time2id;     // ID do segundo time
    int GolsTime1;   // Gols marcados pelo primeiro time
    int GolsTime2;   // Gols marcados pelo segundo time
    Partida *next;
    Partida *prev;
};
typedef struct partida Partida;
````

### Struct **bdPartidas**

```c
struct bdpartida {
    Partida *first;
    Partida *last;
    int qtd;
};
typedef struct bdpartida bdPartidas;
```

### Struct **Time**

```c
struct time {
    int id; //id dos times
    char nome[50]; //nome do time
    Time *next;
};
typedef struct time Time;
```

### Struct **bdTimes**

```c
struct bdtimes {
    Time *first;
    int qtd;
};
typedef struct bdtimes bdTimes;
```

---

## 🪄 Funcionalidades

| Função                                          | Arquivo                  | Descrição                                                 |
| ----------------------------------------------- | ------------------------ | --------------------------------------------------------- |
| lobby(bdTimes *bdt, bdPartidas *bdp)            | system.c                 | Exibe o menu inicial com as opções principais do sistema. |
| ConsultarTime(bdTimes *bdt, bdPartidas *bdp)    | consultar_time.c         | Consulta um time pelo ID e exibe suas informações.        |
| ConsultarPartida(bdTimes *bdt, bdPartidas *bdp) | consultar_partida.c      | Exibe os dados de uma partida específica.                 |
| Classificacao(bdTimes *bdt, bdPartidas *bdp)    | imprimir_classificacao.c | Gera e exibe a tabela de classificação atualizada.        |
| LimpaTela()                                     | auxiliares.c             | Limpa a tela do terminal.                                 |
| InserirPartida(bdTimes *bdt, bdPartidas *bdp)   | inserir_partida.c        | Solicita informações e insere nova partida.               |
| RemoverPartidaArquivo(int id)                   | remover_partida.c        | Remove do arquivo a partida pelo ID.                      |
| AtualizarPartida(bdTimes *bdt, bdPartidas *bdp) | atualizar_partida.c      | Atualiza dados de uma partida existente.                  |

---

## 🏹 Exemplo de Uso

```
Escolha 1 opção: ⚽

1: Consultar Time
2: Consultar Partidas
3: Atualizar Partida
4: Remover Partida
5: Inserir Partida
6: Imprimir Tabela de Classificação
7: Sair do programa
---------------------
```

### Entrada:

```
1
```

### Saída:

```
Digite o nome do time ou prefixo:
```

### Entrada:

```
JAVA
```

### Saída:

```
ID   Time         V   E   D   GM   GS    S   PG
0    JAVAlis      6   2   1   24   12   12   20
```

---

## ♟ Futuras melhorias para Parte 1

* Atualizar partida ✅
* Remover partida ✅
* Inserir partida ✅

## ♟ Futuras melhorias para Parte 2

* Criação de Interface
* Inserir os nomes dos times mesmo se digitar somente o sufixo

---

## 👀 Observações

O projeto atual modifica o arquivo CSV (banco de dados) ao inserir, remover ou atualizar as partidas.


## 🪫 Conclusão

Assim, com a leitura do README, é possível compreender o programa profundamente e executá-lo. Obrigado(a) pela atenção!

![VacationModeVacayModeGIF](https://github.com/user-attachments/assets/b69fa989-6c93-4a74-9eef-8aab9d736e0c)

