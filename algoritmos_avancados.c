#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

//int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    //return 0;
//}
/*
 * Programa: Detective Quest - Exploração da Mansão
 * Disciplina: Estruturas de Dados em C (Árvore Binária)
 * Descrição: Simula uma mansão como árvore binária com salas.
 *            Jogador explora a partir do Hall, escolhendo esquerda (e) ou direita (d).
 *            Exploração termina ao chegar em uma sala sem saída (folha).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== ESTRUTURA DA SALA (NÓ DA ÁRVORE) ====================
typedef struct Sala {
    char nome[50];           // Nome do cômodo
    struct Sala* esquerda;   // Ponteiro para filho esquerdo
    struct Sala* direita;    // Ponteiro para filho direito
} Sala;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================
Sala* criarSala(const char* nome);
void explorarSalas(Sala* atual);
void liberarArvore(Sala* raiz);

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    printf("=== DETECTIVE QUEST - EXPLORACAO DA MANSAO ===\n\n");
    printf("Bem-vindo(a) à mansão misteriosa!\n");
    printf("Você começa no HALL DE ENTRADA.\n");
    printf("Escolha 'e' para esquerda, 'd' para direita, 's' para sair.\n\n");

    // Monta a árvore da mansão automaticamente
    Sala* hall = criarSala("Hall de Entrada");

    // Esquerda do Hall
    hall->esquerda = criarSala("Sala de Jantar");
    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Despensa");

    // Direita do Hall
    hall->direita = criarSala("Biblioteca");
    hall->direita->esquerda = criarSala("Escritorio");
    hall->direita->esquerda->esquerda = criarSala("Cofre Secreto");  // Folha
    hall->direita->direita = criarSala("Jardim");
    hall->direita->direita->direita = criarSala("Piscina");         // Folha

    // Inicia exploração a partir do Hall
    explorarSalas(hall);

    // Libera toda a memória alocada
    liberarArvore(hall);

    printf("\nExploracao finalizada. Mansao investigada com sucesso!\n");
    return 0;
}

// ==================== CRIA UMA SALA COM NOME ====================
/*
 * criarSala(): Aloca dinamicamente uma nova sala com o nome fornecido.
 * Inicializa os ponteiros esquerda e direita como NULL.
 * Retorna o ponteiro para a nova sala.
 */
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("ERRO: Falha na alocacao de memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ==================== EXPLORAÇÃO INTERATIVA ====================
/*
 * explorarSalas(): Permite ao jogador navegar pela árvore.
 * Exibe o nome da sala atual e pergunta para onde ir.
 * Continua até chegar em uma folha (sem esquerda nem direita).
 * Exibe o caminho completo visitado.
 */
void explorarSalas(Sala* atual) {
    char escolha;
    Sala* caminho[100];  // Pilha para guardar o caminho
    int profundidade = 0;

    caminho[profundidade++] = atual;

    while (1) {
        printf("Você está em: %s\n", atual->nome);

        // Verifica se é uma folha (fim da exploração)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\nFIM DA LINHA! Você chegou a uma sala sem saída.\n");
            printf("Caminho percorrido:\n");
            for (int i = 0; i < profundidade; i++) {
                printf("  -> %s\n", caminho[i]->nome);
            }
            printf("\nInvestigacao concluida nesta ala!\n");
            break;
        }

        // Mostra opções disponíveis
        printf("Para onde deseja ir?\n");
        if (atual->esquerda != NULL)  printf("  [e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)   printf("  [d] Direita  -> %s\n", atual->direita->nome);
        printf("  [s] Sair da exploracao\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            printf("\nExploracao interrompida pelo jogador.\n");
            break;
        }

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
            caminho[profundidade++] = atual;
        }
        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
            caminho[profundidade++] = atual;
        }
        else {
            printf("Opcao invalida ou caminho inexistente! Tente novamente.\n");
        }
        printf("\n");
    }
}

// ==================== LIBERA A ÁRVORE (POS-ORDEM) ====================
/*
 * liberarArvore(): Libera toda a memória alocada para a árvore.
 * Usa recursão em pós-ordem: libera esquerda, direita, depois o nó.
 */
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}
