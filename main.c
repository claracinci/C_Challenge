#include <stdio.h>
#include <stdlib.h>

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

void exibir_instrucoes() {
    printf("Instruções do Jogo:\n");
    printf("Olá, seja bem-vindo ao C Learning Challenge! Você será apresentado a uma série de perguntas.\n");
    printf("Para cada pergunta, você deve escolher a alternativa correta.\n");
    printf("O jogo termina quando todas as perguntas forem respondidas.\n");
    printf("Boa sorte!\n\n");
}

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
                printf("Iniciando o jogo...\n");
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
    } while (opcao != 3);
}

int main() {
    exibir_wellcome();
    mostrar_menu();
    return 0;
}
