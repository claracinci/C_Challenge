#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#define MAX_QUESTOES 24  // numero total de questões

void exibir_wellcome() {
    printf("\n");
    printf("\033[31;43m");//coloca a cor 
    // tirei o negrito pois nenhum terminal em qual testei conseguiu aplicar ele
    printf("=====================================================================================\n");
    printf("| __                __  ____    __        ______   ______  ___        ___   ____    |\n");
    printf("| \\ \\     ____     / / | ___|  |  |     |   ___| |   _  | |  \\      /   | | ___|    |\n");
    printf("|  \\ \\   / /\\ \\   / /  | |__   |  |     |  |     |  | | | |   \\    /    | | |__     |\n");
    printf("|   \\ \\ / /  \\ \\ / /   | __|   |  |     |  |     |  | | | |  \\ \\  / /   | | __|     |\n");
    printf("|    \\   /    \\   /    | |__   |  |___  |  |___  |  --- | |  |\\ \\/ / |  | | |__     |\n");
    printf("|     \\_/      \\_/     |____|  |______| |______| |______| |__| \\__/  |__| |____|    |\n");
    printf("|                                                                                   |\n");
    printf("=====================================================================================\n \033[0m");
}

typedef struct {
    char pergunta[2000];
    char altA[800];
    char altB[800];
    char altC[800];
    char altD[800];
    char resposta_correta;
    char dica[500];
} Pergunta;


// função para printar instruções do jogo
void exibir_instrucoes() {
    printf("\n");
    printf("Instrucoes do Jogo:\n");
    printf("Ola, seja bem-vindo ao C Learning Challenge! Voce sera apresentado a uma serie de perguntas.\n");
    printf("Para cada pergunta, voce deve escolher a alternativa correta.\n");
    printf("O jogo termina quando todas as 10 perguntas forem respondidas.\n");
    printf("Em todas as perguntas, uma dica na alternativa 'E' esta disponivel.\n");
    printf("Boa sorte!");
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

    // avança até a questão desejada, printa a questao e alternativas.
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


    //pegar as dicas
    FILE *fp2 = fopen("dicas.txt", "r");

    if (fp2 == NULL){
        printf("erro ao abrir dicas.txt\n");
        return 1;
    }
    
    for (int i = 0; i <= questao_num; i++) {
    fgets(pergunta.dica, sizeof(pergunta.dica), fp2); // lê a correta
    }

    fclose(fp2);

    // printa a pergunta e alternativas
    if ((questao_num >= 11 && questao_num <= 16) || (questao_num >= 22 && questao_num <= 23)){
        printf("\n%d) %s", questao_num+1, pergunta.pergunta);
        printf("%s", pergunta.altA);
        printf("%s", pergunta.altB);
        printf("E. Pedir dica\n");
    }else{
        // printf("\n%s", pergunta.pergunta);
        printf("\n%d) %s", questao_num+1, pergunta.pergunta);
        printf("%s", pergunta.altA);
        printf("%s", pergunta.altB);
        printf("%s", pergunta.altC);
        printf("%s", pergunta.altD);
        printf("E. Pedir dica\n");
    };

    char alternativa;
    
    while(!(alternativa >= 'a' && alternativa <= 'e') || !(alternativa >= 'A' && alternativa <= 'E')){
        printf("Resposta: ");
        scanf(" %c", &alternativa);
        if (alternativa == 'e' || alternativa == 'E')
            printf("Dica: %s\n", pergunta.dica);
            // printf("Dica: %s\n", pergunta.dica);
        else if (alternativa >= 'a' && alternativa <= 'e'){
            alternativa -= 32;
                // verifica se a resposta ta certa
            if (alternativa == pergunta.resposta_correta) {
                printf("Resposta correta!\n");
                return 1; // retorna 1 para resposta certa
            }else {
                printf("Resposta errada. A resposta correta era %c.\n", pergunta.resposta_correta);
                return 0; // retorna 0 para resposta errada
                    }
            break;}
        else if (alternativa >= 'A' && alternativa <= 'E'){
                // verifica se a resposta ta certa
            if (alternativa == pergunta.resposta_correta) {
                printf("Resposta correta!\n");
                return 1; // retorna 1 para resposta certa
            }else {
                printf("Resposta errada. A resposta correta era %c.\n", pergunta.resposta_correta);
                return 0; // retorna 0 para resposta errada
                    }
            break;}
        else{
            printf("Insira uma alternativa valida!\n");
            continue;}

    }   
};

// função para iniciar o jogo
void iniciar_jogo() {
    int dificuldade;
    int total_acertos = 0;

    // loop para garantir entrada válida na dificukldade
    do {
        printf("Escolha a dificuldade:\n1. Facil\n2. Medio\n3. Dificil\n");
        scanf("%d", &dificuldade);

        if (dificuldade < 1 || dificuldade > 3) {
            printf("Insira uma entrada valida.\n");
        }
    } while (dificuldade < 1 || dificuldade > 3);

    printf("Modo %s selecionado.\n", (dificuldade == 1 ? "Facil" : (dificuldade == 2 ? "Medio" : "Dificil")));

    if (dificuldade == 1){
    for (int i = 0; i < 8; i++) {
        total_acertos += printar_questao(i); // chama a função de imprimir a pergunta
    }}
    if (dificuldade == 2){
    for (int i = 8; i < 16; i++) {
        total_acertos += printar_questao(i); // chama a função de imprimir a pergunta
    }}
    if (dificuldade == 3){
    for (int i = 16; i < MAX_QUESTOES; i++) {
        total_acertos += printar_questao(i); // chama a função de imprimir a pergunta
    }}
    

    printf("\nVoce acertou %d de 8 perguntas!", total_acertos);
}

// função para mostrar o menu do jogo
void mostrar_menu() {
    int opcao;

    do {
        printf("\n");
        printf("====================\n");
        printf("|   Menu do Jogo    |\n");
        printf("|1. Iniciar Jogo    |\n");
        printf("|2. Instrucoes      |\n");
        printf("|3. Sair            |\n");
        printf("====================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciar_jogo();
                break;
            case 2:
                exibir_instrucoes();
                break;
            case 3:
                printf("Saindo do jogo. Ate mais!");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 3);
}


int main() {
    exibir_wellcome();

    srand(time(NULL));

    mostrar_menu();

    return 0;
}