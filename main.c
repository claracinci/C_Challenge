#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#define USERFILE "users.bin"
#define MAX_QUESTOES 24  // numero total de questões

typedef struct {
    char username[10];
    int score;
} User;

typedef struct {
    char pergunta[2000];
    char altA[800];
    char altB[800];
    char altC[800];
    char altD[800];
    char resposta_correta;
    char dica[500];
} Pergunta;

// limpar todos os buffers 
void limparBuffer() {
    while (getchar() != '\n');  // limpa até encontrar a nova linha
}

// checar os usuários existentes
int checar_usuarios_existentes(const char *username) {
    User user;
    FILE *file = fopen(USERFILE, "rb");
    if (file == NULL) {
        return 0; // arquivo não existe, então o usuário não existe
    }

    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0) {
            fclose(file);
            return 1; // usuário já existe
        }
    }
    fclose(file);
    return 0; // usuário não existe
}

void cadastrar_usuario() {
    User newUser;
    printf("\033[35mDigite o nome do usuário: \033[35m");
    scanf("%s", newUser.username);

    // verifica se o usuário já existe
    if (checar_usuarios_existentes(newUser.username)) {
        printf("Usuário já existe, escolha outro nome.\n");
        return;
    }

    newUser.score = 0; // inicializa a pontuação do usuario

    // armazena o novo usuário no arquivo binário
    FILE *file = fopen(USERFILE, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);
    printf("Usuário cadastrado com sucesso!\n");
}

void mostrar_pontuacao() {
    User user;
    FILE *file = fopen(USERFILE, "rb");
    if (file == NULL) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("Pontuações dos usuários:\n");
    while (fread(&user, sizeof(User), 1, file)) {
        printf("Usuário: %s, Pontuação: %d\n", user.username, user.score);
    }
    fclose(file);
}

void exibir_bem_vindo() {
    printf("\n");
    printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
    printf("\033[35;40m▒ __                __  ____    __       ______   ______   __        __   ____    ▒\033[0m\n");
    printf("\033[35;40m▒ \\ \\     ____     / / | ___|  |  |     |   ___| |   _  | |  \\      /  | | ___|   ▒\033[0m\n");
    printf("\033[35;40m▒  \\ \\   / /\\ \\   / /  | |__   |  |     |  |     |  | | | |   \\    /   | | |__    ▒\033[0m\n");
    printf("\033[35;40m▒   \\ \\ / /  \\ \\ / /   | __|   |  |     |  |     |  | | | |  \\ \\  / /  | | __|    ▒\033[0m\n");
    printf("\033[35;40m▒    \\   /    \\   /    | |__   |  |___  |  ----- |   -- | | | \\ \\/ / | | | |__    ▒\033[0m\n");
    printf("\033[35;40m▒     \\_/      \\_/     |____|  |______| |______| |______| |_|  \\__/  |_| |____|   ▒\033[0m\n");
    printf("\033[35;40m▒                                                                                 ▒\033[0m\n");
    printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
    printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒Bem-vindo ao C Learning Challenge!▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
    printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒↓↓ Escolha uma opção abaixo ↓↓ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m");
}

// função para printar instruções do jogo
void exibir_instrucoes() {
    printf("\n");
    printf("\033[35mInstrucoes do Jogo:\n");
    printf("Olá, seja bem-vindo ao C Learning Challenge! Você sera apresentado a uma série de perguntas.\n");
    printf("Para cada pergunta, você deve escolher a alternativa correta.\n");
    printf("O jogo termina quando todas as perguntas forem respondidas.\n");
    printf("Em todas as perguntas, uma dica na alternativa 'E' esta disponível.\n");
    printf("Boa sorte!\033[0m\n");
}

int printar_questao(int questao_num) {
    char linha[256];
    Pergunta pergunta;

    FILE *fp = fopen("questoes.txt", "r");
    if (fp == NULL) {
        printf("\033[35mErro na leitura do questoes.txt\033[0m\n");
        return 1;
    }

    for (int i = 0; i <= questao_num; i++) {
        if (fgets(linha, sizeof(linha), fp) == NULL) break;
        strcpy(pergunta.pergunta, linha);
        fgets(pergunta.altA, sizeof(pergunta.altA), fp);
        fgets(pergunta.altB, sizeof(pergunta.altB), fp);
        fgets(pergunta.altC, sizeof(pergunta.altC), fp);
        fgets(pergunta.altD, sizeof(pergunta.altD), fp);
        fgets(linha, sizeof(linha), fp);
        pergunta.resposta_correta = linha[0];
    }
    fclose(fp);

    FILE *fp2 = fopen("dicas.txt", "r");
    if (fp2 == NULL) {
        printf("\033[35merro ao abrir dicas.txt\033[0m\n");
        return 1;
    }
    for (int i = 0; i <= questao_num; i++) {
        fgets(pergunta.dica, sizeof(pergunta.dica), fp2);
    }
    fclose(fp2);

    printf("\n\033[35m%d) %s", questao_num + 1, pergunta.pergunta);
    printf("%s", pergunta.altA);
    printf("%s", pergunta.altB);
    printf("%s", pergunta.altC);
    printf("%s", pergunta.altD);
    printf("E. Pedir dica\n\033[0m");

    char alternativa;
    do {
        printf("\033[35mResposta: \033[0m");
        scanf(" %c", &alternativa);
        limparBuffer();

        if (alternativa == 'e' || alternativa == 'E') {
            printf("\033[35mDica: %s\033[0m\n", pergunta.dica);
        } else if ((alternativa >= 'A' && alternativa <= 'D') || (alternativa >= 'a' && alternativa <= 'd')) {
            // normaliza p/ maiúsculas
            if (alternativa >= 'a') {
                alternativa -= 32;
            }
            if (alternativa == pergunta.resposta_correta) {
                printf("\033[32mResposta correta!\033[0m\n");
                return 1; 
            } else {
                printf("\033[31mResposta errada. A resposta correta era %c.\033[0m\n", pergunta.resposta_correta);
                return 0;
            }
        } else {
            printf("\033[35mInsira uma alternativa valida!\033[0m\n");
        }
    } while (1); 
}


void iniciar_jogo() {
    int dificuldade;
    int total_acertos = 0;

    // loop para garantir entrada válida na dificuldade
    do {
        printf("\033[35m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ Escolha a dificuldade:\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ 1. Fácil\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ 2. Médio\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ 3. Difícil\n\033[0m");
        scanf("%d", &dificuldade);

        if (dificuldade < 1 || dificuldade > 3) {
            printf("Insira uma entrada valida.\n");
        }
    } while (dificuldade < 1 || dificuldade > 3);

    printf("Modo %s selecionado.\n", (dificuldade == 1 ? "Facil" : (dificuldade == 2 ? "Medio" : "Dificil")));

    if (dificuldade == 1){
        for (int i = 0; i < 8; i++) {
            total_acertos += printar_questao(i); // chama a função de imprimir a pergunta
        }
    }
    if (dificuldade == 2){
        for (int i = 8; i < 16; i++) {
            total_acertos += printar_questao(i); // chama dnv
        }
    }
    if (dificuldade == 3){
        for (int i = 16; i < MAX_QUESTOES; i++) {
            total_acertos += printar_questao(i); // chama dnv
        }
    }

    printf("\nVocê acertou %d de 8 perguntas!", total_acertos);
}

void mostrar_menu() {
    int opcao;

    do {
        printf("\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   Menu do Jogo    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒→ 1. Iniciar Jogo  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒→ 2. Instruções    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒→ 3. Cadastro      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒→ 4. Ver Pontuação ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒→ 5. Sair          ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
        printf("\033[35;40m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[0m");
        printf("\n");
        printf("\033[35m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ Insira a opção:\033[0m");
        printf("\033[35m"); 
        scanf("%d", &opcao);
        printf("\033[0m"); 

        // usando um printf adicional para mostrar a opção após a entrada
        printf("\n");

        switch (opcao) {
            case 1:
                iniciar_jogo();
                break;
            case 2:
                exibir_instrucoes();
                break;
            case 3:
                cadastrar_usuario(); 
                break;
            case 4:
                mostrar_pontuacao();
                break;
            case 5:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 5);
}


int main() {
    exibir_bem_vindo();

    srand(time(NULL));

    mostrar_menu();

    return 0;
}