#include <stdio.h>
#include <stdlib.h>
#define MAX_QUESTOES 3  // número total de questões

void exibir_wellcome() {
    printf("\n");
    printf("\033[1m"); // ativa o negrito
    printf("\033[31;43m");//coloca a cor
    printf("=============================================================================================\n");
    printf("| __                __  ____    __       __       ______   ______  ___        ___   ____     |\n");
    printf("| \\ \\     ____     / / | ___|  |  |     |  |     |   ___| |   _  | |  \\      /   | | ___|    |\n");
    printf("|  \\ \\   / /\\ \\   / /  | |__   |  |     |  |     |  |     |  | | | |   \\    /    | | |__     |\n");
    printf("|   \\ \\ / /  \\ \\ / /   | __|   |  |     |  |     |  |     |  | | | |  \\ \\  / /   | | __|     |\n");
    printf("|    \\   /    \\   /    | |__   |  |___  |  |___  |  |___  |  --- | |  |\\ \\/ / |  | | |__     |\n");
    printf("|     \\_/      \\_/     |____|  |______| |______| |______| |______| |__| \\__/  |__| |____|    |\n");
    printf("|                                                                                            |\n");
    printf("=============================================================================================\n \033[0m");
    printf("\033[0m"); // tira o negrito
}

typedef struct {
    char pergunta[300];
    char altA[50];
    char altB[50];
    char altC[50];
    char altD[50];
    char resposta_correta; 
} Pergunta;

// função para gerar questões em um arquivo de texto
int questao_txt() {
    Pergunta perguntas[MAX_QUESTOES] = {
        {"1. Quanto é 1+1?", "A. 2", "B. 3", "C. 4", "D. 5", 'A'},
        {"2. Quanto é 2+1?", "A. 2", "B. 3", "C. 4", "D. 5", 'B'},
        {"3. Quanto é 2+2?", "A. 2", "B. 3", "C. 4", "D. 5", 'C'}
    };

    FILE *fp = fopen("questoes.txt", "w");
    if (fp == NULL) {
        printf("Erro ao escrever no questoes.txt\n");
        return 1;
    }

    for (int i = 0; i < MAX_QUESTOES; i++) {
        fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%c\n", perguntas[i].pergunta, perguntas[i].altA, perguntas[i].altB, perguntas[i].altC, perguntas[i].altD, perguntas[i].resposta_correta);
    }

    fclose(fp);
    return 0;
}

// Função para exibir instruções do jogo
void exibir_instrucoes() {
    printf("Instruções do Jogo:\n");
    printf("Olá, seja bem-vindo ao C Learning Challenge! Você será apresentado a uma série de perguntas.\n");
    printf("Para cada pergunta, você deve escolher a alternativa correta.\n");
    printf("O jogo termina quando todas as perguntas forem respondidas.\n");
    printf("Boa sorte!\n\n");
}

int main() {
    exibir_wellcome();
    questao_txt();
    exibir_instrucoes(); 
    return 0;
}
