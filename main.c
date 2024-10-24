#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>


#define MAX_QUESTOES 3  // numero total de questões

void exibir_wellcome() {
    printf("\n");
    printf("\033[31;43m");//coloca a cor 
    // tirei o negrito pois nenhum terminal em qual testei conseguiu aplicar ele
    printf("=============================================================================================\n");
    printf("| __                __  ____    __       __       ______   ______  ___        ___   ____     |\n");
    printf("| \\ \\     ____     / / | ___|  |  |     |  |     |   ___| |   _  | |  \\      /   | | ___|    |\n");
    printf("|  \\ \\   / /\\ \\   / /  | |__   |  |     |  |     |  |     |  | | | |   \\    /    | | |__     |\n");
    printf("|   \\ \\ / /  \\ \\ / /   | __|   |  |     |  |     |  |     |  | | | |  \\ \\  / /   | | __|     |\n");
    printf("|    \\   /    \\   /    | |__   |  |___  |  |___  |  |___  |  --- | |  |\\ \\/ / |  | | |__     |\n");
    printf("|     \\_/      \\_/     |____|  |______| |______| |______| |______| |__| \\__/  |__| |____|    |\n");
    printf("|                                                                                            |\n");
    printf("=============================================================================================\n \033[0m");
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

// função para printar instruções do jogo
void exibir_instrucoes() {
    printf("Instruções do Jogo:\n");
    printf("Olá, seja bem-vindo ao C Learning Challenge! Você será apresentado a uma série de perguntas.\n");
    printf("Para cada pergunta, você deve escolher a alternativa correta.\n");
    printf("O jogo termina quando todas as perguntas forem respondidas.\n");
    printf("Boa sorte!\n\n");
}

// função para printar questões
int printar_questao(int questao_num) {
    char linha[256];
    Pergunta pergunta;

    FILE *fp = fopen("questoes.txt", "r");
    if (fp == NULL) {
        printf("Erro na leitura do questoes.txt\n");
        return 1;
    }

    // avança até a questão desejada
    for (int i = 0; i <= questao_num; i++) {
        if (fgets(linha, sizeof(linha), fp) == NULL) break; // lê a pergunta
        strcpy(pergunta.pergunta, linha);
        fgets(pergunta.altA, sizeof(pergunta.altA), fp); // lê alternativa A
        fgets(pergunta.altB, sizeof(pergunta.altB), fp); // lê alternativa B
        fgets(pergunta.altC, sizeof(pergunta.altC), fp); // lê alternativa C
        fgets(pergunta.altD, sizeof(pergunta.altD), fp); // lê alternativa D
        fgets(linha, sizeof(linha), fp); // lê a correta
        pergunta.resposta_correta = linha[0]; // guarda a correta
    }

    fclose(fp);

    // printa a pergunta e alternativas
    printf("\n%s", pergunta.pergunta);
    printf("%s", pergunta.altA);
    printf("%s", pergunta.altB);
    printf("%s", pergunta.altC);
    printf("%s", pergunta.altD);

    char alternativa;
    printf("Resposta: ");
    scanf(" %c", &alternativa);

    // verifica se a resposta ta certa
    if (alternativa == pergunta.resposta_correta) {
        printf("Resposta correta!\n");
        return 1; // retorna 1 para resposta certa
    } else {
        printf("Resposta errada! A resposta correta era %c.\n", pergunta.resposta_correta);
        return 0; // retorna 0 para resposta errada
    }
}

// função para iniciar o jogo
void iniciar_jogo() {
    int dificuldade;
    int total_acertos = 0;

    // loop para garantir entrada válida na dificukldade
    do {
        printf("Escolha a dificuldade:\n1. Fácil\n2. Médio\n3. Difícil\n");
        scanf("%d", &dificuldade);

        if (dificuldade < 1 || dificuldade > 3) {
            printf("Insira uma entrada válida.\n");
        }
    } while (dificuldade < 1 || dificuldade > 3);

    printf("Modo %s selecionado.\n", (dificuldade == 1 ? "Fácil" : (dificuldade == 2 ? "Médio" : "Difícil")));

    for (int i = 0; i < MAX_QUESTOES; i++) {
        total_acertos += printar_questao(i); // chama a função de imprimir a pergunta
    }

    printf("\nVocê acertou %d de %d perguntas!\n", total_acertos, MAX_QUESTOES);
}

// função para mostrar o menu do jogo
void mostrar_menu() {
    int opcao;

    do {
        printf("\n");
        printf("====================\n");
        printf("|   Menu do Jogo    |\n");
        printf("|1. Iniciar Jogo    |\n");
        printf("|2. Instruções      |\n");
        printf("|3. Sair            |\n");
        printf("====================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciar_jogo();
                break;
            case 2:
                exibir_instrucoes();
                break;
            case 3:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 3);
}


int main() {
    exibir_wellcome();

    srand(time(NULL));

    questao_txt(); 

    mostrar_menu();

    return 0;
}
