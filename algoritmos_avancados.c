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
/*
 * Programa: Detective Quest - Coleta de Pistas
 * Disciplina: Estruturas de Dados em C (Árvore Binária + BST)
 * Descrição: Exploração da mansão (árvore binária) com coleta de pistas.
 *            Pistas são inseridas em uma BST e exibidas em ordem alfabética.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== ESTRUTURA DA SALA (ÁRVORE BINÁRIA) ====================
typedef struct Sala {
    char nome[50];           // Nome do cômodo
    char pista[100];         // Pista encontrada (ou vazia)
    struct Sala* esquerda;   // Filho esquerdo
    struct Sala* direita;    // Filho direito
} Sala;

// ==================== ESTRUTURA DA PISTA (BST) ====================
typedef struct PistaNode {
    char pista[100];                 // Conteúdo da pista
    struct PistaNode* esquerda;      // Filho esquerdo
    struct PistaNode* direita;       // Filho direito
} PistaNode;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================
Sala* criarSala(const char* nome, const char* pista);
PistaNode* inserirPista(PistaNode* raiz, const char* nova_pista);
void explorarSalasComPistas(Sala* atual, PistaNode** raiz_pistas);
void exibirPistas(PistaNode* raiz);
void liberarArvoreSalas(Sala* raiz);
void liberarBST(PistaNode* raiz);

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    PistaNode* raiz_pistas = NULL;  // BST de pistas coletadas

    printf("=== DETECTIVE QUEST - COLETA DE PISTAS ===\n\n");
    printf("Explore a mansão e colete todas as pistas!\n");
    printf("Escolha 'e' (esquerda), 'd' (direita) ou 's' (sair).\n\n");

    // === MONTAGEM AUTOMÁTICA DA MANSÃO (ÁRVORE BINÁRIA) ===
    Sala* hall = criarSala("Hall de Entrada", "Nenhuma pista aqui...");

    // Esquerda
    hall->esquerda = criarSala("Sala de Jantar", "O jantar foi às 20h.");
    hall->esquerda->esquerda = criarSala("Cozinha", "Há uma faca faltando.");
    hall->esquerda->direita = criarSala("Despensa", "Encontrou um bilhete rasgado.");

    // Direita
    hall->direita = criarSala("Biblioteca", "Livro aberto na página 47.");
    hall->direita->esquerda = criarSala("Escritório", "Diário com entrada suspeita.");
    hall->direita->esquerda->esquerda = criarSala("Cofre Secreto", "Código: 2519");
    hall->direita->direita = criarSala("Jardim", "Pegadas na terra molhada.");
    hall->direita->direita->direita = criarSala("Piscina", "Relógio parado às 22:15");

    // === INICIA A EXPLORAÇÃO ===
    explorarSalasComPistas(hall, &raiz_pistas);

    // === EXIBE PISTAS COLETADAS EM ORDEM ALFABÉTICA ===
    printf("\n=== RELATORIO FINAL: PISTAS COLETADAS ===\n");
    if (raiz_pistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        printf("Pistas encontradas (em ordem alfabética):\n");
        exibirPistas(raiz_pistas);
    }

    // === LIBERA MEMÓRIA ===
    liberarArvoreSalas(hall);
    liberarBST(raiz_pistas);

    printf("\nInvestigacao finalizada. Boa sorte na resolucao do caso!\n");
    return 0;
}

// ==================== CRIA UMA SALA COM NOME E PISTA ====================
/*
 * criarSala(): Aloca dinamicamente uma nova sala.
 * Copia nome e pista. Inicializa filhos como NULL.
 */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("ERRO: Falha na alocacao de memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ==================== INSERE PISTA NA BST (POR ORDEM ALFABÉTICA) ====================
/*
 * inserirPista(): Insere uma nova pista na BST.
 * Compara strings com strcmp para manter ordem alfabética.
 * Evita duplicatas (não insere se já existe).
 */
PistaNode* inserirPista(PistaNode* raiz, const char* nova_pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        if (novo == NULL) {
            printf("ERRO: Falha na alocacao!\n");
            exit(1);
        }
        strcpy(novo->pista, nova_pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    int cmp = strcmp(nova_pista, raiz->pista);
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, nova_pista);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, nova_pista);
    }
    // Se igual, não insere (evita duplicatas)
    return raiz;
}

// ==================== EXPLORAÇÃO COM COLETA DE PISTAS ====================
/*
 * explorarSalasComPistas(): Navega pela mansão.
 * Se houver pista, adiciona na BST.
 * Permite 'e', 'd' ou 's'.
 */
void explorarSalasComPistas(Sala* atual, PistaNode** raiz_pistas) {
    char escolha;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Coleta pista se existir
        if (strlen(atual->pista) > 0 && strcmp(atual->pista, "Nenhuma pista aqui...") != 0) {
            printf("PISTA ENCONTRADA: \"%s\"\n", atual->pista);
            *raiz_pistas = inserirPista(*raiz_pistas, atual->pista);
        } else {
            printf("Nenhuma pista neste local.\n");
        }

        // Opções de movimento
        printf("\nPara onde deseja ir?\n");
        if (atual->esquerda != NULL)
            printf("  [e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)
            printf("  [d] Direita  -> %s\n", atual->direita->nome);
        printf("  [s] Encerrar investigacao\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            printf("\nInvestigacao encerrada pelo detetive.\n");
            break;
        }

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        }
        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        }
        else {
            printf("Caminho invalido! Tente novamente.\n");
        }
    }
}

// ==================== EXIBE PISTAS EM ORDEM (IN-ORDEM) ====================
/*
 * exibirPistas(): Percorre a BST em ordem (in-order) para exibir pistas alfabeticamente.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esquerda);
    printf("  - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

// ==================== LIBERA ÁRVORE DA MANSÃO ====================
void liberarArvoreSalas(Sala* raiz) {
    if (raiz == NULL) return;
    liberarArvoreSalas(raiz->esquerda);
    liberarArvoreSalas(raiz->direita);
    free(raiz);
}

// ==================== LIBERA BST DE PISTAS ====================
void liberarBST(PistaNode* raiz) {
    if (raiz == NULL) return;
    liberarBST(raiz->esquerda);
    liberarBST(raiz->direita);
    free(raiz);
}