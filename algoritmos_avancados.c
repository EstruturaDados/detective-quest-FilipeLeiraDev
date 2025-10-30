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
/*
 * Programa: Detective Quest - Coleta de Pistas e Acusação Final
 * Disciplina: Estruturas de Dados em C (Nível Mestre)
 * Descrição: Exploração da mansão (árvore binária), coleta de pistas (BST),
 *            associação pista-suspeito (tabela hash), e verificação de acusação.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== ESTRUTURA DA SALA (ÁRVORE BINÁRIA) ====================
typedef struct Sala {
    char nome[50];           // Nome do cômodo
    char pista[100];         // Pista associada (ou vazia)
    struct Sala* esquerda;   // Filho esquerdo
    struct Sala* direita;    // Filho direito
} Sala;

// ==================== ESTRUTURA PARA BST DE PISTAS ====================
typedef struct PistaNode {
    char pista[100];                 // Conteúdo da pista
    struct PistaNode* esquerda;      // Filho esquerdo
    struct PistaNode* direita;       // Filho direito
} PistaNode;

// ==================== ESTRUTURA PARA TABELA HASH (PISTA -> SUSPEITO) ====================
#define TAM_HASH 10  // Tamanho da tabela hash
typedef struct HashNode {
    char pista[100];         // Chave (pista)
    char suspeito[50];       // Valor (suspeito)
    struct HashNode* proximo;  // Para colisões (chaining)
} HashNode;

HashNode* tabela_hash[TAM_HASH];  // Array de ponteiros para listas

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================
Sala* criarSala(const char* nome, const char* pista);
PistaNode* inserirPista(PistaNode* raiz, const char* nova_pista);
void explorarSalas(Sala* atual, PistaNode** raiz_pistas);
void inserirNaHash(const char* pista, const char* suspeito);
char* encontrarSuspeito(const char* pista);
void verificarSuspeitoFinal(PistaNode* raiz_pistas);
void liberarArvoreSalas(Sala* raiz);
void liberarBST(PistaNode* raiz);
void liberarHash();
unsigned int hash(const char* chave);

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    PistaNode* raiz_pistas = NULL;

    // Inicializa tabela hash
    for (int i = 0; i < TAM_HASH; i++) {
        tabela_hash[i] = NULL;
    }

    printf("=== DETECTIVE QUEST - ACUSACAO FINAL ===\n\n");
    printf("Explore a mansao, colete pistas e acuse o culpado!\n");
    printf("Escolha 'e' (esquerda), 'd' (direita) ou 's' (sair).\n\n");

    // === MONTAGEM AUTOMÁTICA DA MANSÃO ===
    Sala* hall = criarSala("Hall de Entrada", "");

    // Esquerda
    hall->esquerda = criarSala("Sala de Jantar", "O jantar foi interrompido.");
    hall->esquerda->esquerda = criarSala("Cozinha", "Uma faca com sangue.");
    hall->esquerda->direita = criarSala("Despensa", "Bilhete escondido.");

    // Direita
    hall->direita = criarSala("Biblioteca", "Livro com pagina marcada.");
    hall->direita->esquerda = criarSala("Escritorio", "Diario rasgado.");
    hall->direita->esquerda->esquerda = criarSala("Cofre", "Documento confidencial.");
    hall->direita->direita = criarSala("Jardim", "Pegadas na grama.");
    hall->direita->direita->direita = criarSala("Piscina", "Relogio quebrado.");

    // === ASSOCIAÇÕES PISTA-SUSPEITO NA HASH ===
    inserirNaHash("O jantar foi interrompido.", "Mordomo");
    inserirNaHash("Uma faca com sangue.", "Jardineiro");
    inserirNaHash("Bilhete escondido.", "Mordomo");
    inserirNaHash("Livro com pagina marcada.", "Bibliotecario");
    inserirNaHash("Diario rasgado.", "Empregada");
    inserirNaHash("Documento confidencial.", "Empregada");
    inserirNaHash("Pegadas na grama.", "Jardineiro");
    inserirNaHash("Relogio quebrado.", "Bibliotecario");

    // === EXPLORAÇÃO ===
    explorarSalas(hall, &raiz_pistas);

    // === VERIFICAÇÃO FINAL ===
    verificarSuspeitoFinal(raiz_pistas);

    // === LIBERA MEMÓRIA ===
    liberarArvoreSalas(hall);
    liberarBST(raiz_pistas);
    liberarHash();

    return 0;
}

// ==================== CRIA SALA ====================
/*
 * criarSala(): Aloca uma sala com nome e pista.
 * Inicializa filhos como NULL.
 */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) exit(1);
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ==================== INSERE PISTA NA BST ====================
/*
 * inserirPista(): Insere pista na BST por ordem alfabética.
 * Evita duplicatas.
 */
PistaNode* inserirPista(PistaNode* raiz, const char* nova_pista) {
    if (!raiz) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        if (!novo) exit(1);
        strcpy(novo->pista, nova_pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    int cmp = strcmp(nova_pista, raiz->pista);
    if (cmp < 0) raiz->esquerda = inserirPista(raiz->esquerda, nova_pista);
    else if (cmp > 0) raiz->direita = inserirPista(raiz->direita, nova_pista);
    return raiz;
}

// ==================== EXPLORAÇÃO DAS SALAS ====================
/*
 * explorarSalas(): Navega pela mansão, coleta pistas se existirem.
 * Insere na BST.
 */
void explorarSalas(Sala* atual, PistaNode** raiz_pistas) {
    char escolha;
    while (1) {
        printf("Voce esta em: %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("PISTA ENCONTRADA: %s\n", atual->pista);
            *raiz_pistas = inserirPista(*raiz_pistas, atual->pista);
        } else {
            printf("Nenhuma pista aqui.\n");
        }

        printf("\nOpcoes:\n");
        if (atual->esquerda) printf(" [e] Esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita) printf(" [d] Direita -> %s\n", atual->direita->nome);
        printf(" [s] Sair\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else printf("Opcao invalida!\n");
    }
}

// ==================== INSERE NA TABELA HASH ====================
/*
 * inserirNaHash(): Adiciona pista-suspeito na hash.
 * Usa chaining para colisões.
 */
void inserirNaHash(const char* pista, const char* suspeito) {
    unsigned int idx = hash(pista);
    HashNode* novo = (HashNode*) malloc(sizeof(HashNode));
    if (!novo) exit(1);
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabela_hash[idx];
    tabela_hash[idx] = novo;
}

// ==================== ENCONTRA SUSPEITO PELA PISTA ====================
/*
 * encontrarSuspeito(): Busca suspeito pela pista na hash.
 * Retorna nome ou NULL se não encontrado.
 */
char* encontrarSuspeito(const char* pista) {
    unsigned int idx = hash(pista);
    HashNode* atual = tabela_hash[idx];
    while (atual) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// ==================== VERIFICAÇÃO FINAL DO SUSPEITO ====================
/*
 * verificarSuspeitoFinal(): Lista pistas, pede acusação.
 * Conta pistas por suspeito (recursivo) e verifica >=2.
 */
void verificarSuspeitoFinal(PistaNode* raiz_pistas) {
    if (!raiz_pistas) {
        printf("\nNenhuma pista coletada. Acusacao impossivel!\n");
        return;
    }

    printf("\nPistas coletadas (ordenadas):\n");
    exibirPistas(raiz_pistas);

    char acusado[50];
    printf("\nQuem voce acusa? (ex: Mordomo): ");
    scanf("%s", acusado);

    int cont = contarPistasPorSuspeito(raiz_pistas, acusado);
    if (cont >= 2) {
        printf("Acusacao correta! %d pistas apontam para %s.\n", cont, acusado);
    } else {
        printf("Acusacao errada! Apenas %d pistas para %s.\n", cont, acusado);
    }
}

// Função auxiliar para contar pistas (recursiva)
int contarPistasPorSuspeito(PistaNode* raiz, const char* suspeito) {
    if (!raiz) return 0;
    int cont = 0;
    char* susp = encontrarSuspeito(raiz->pista);
    if (susp && strcmp(susp, suspeito) == 0) cont = 1;
    return cont + contarPistasPorSuspeito(raiz->esquerda, suspeito) + contarPistasPorSuspeito(raiz->direita, suspeito);
}

// ==================== FUNÇÃO HASH SIMPLES ====================
unsigned int hash(const char* chave) {
    unsigned int valor = 0;
    for (int i = 0; chave[i]; i++) {
        valor = (valor * 31 + chave[i]) % TAM_HASH;
    }
    return valor;
}

// ==================== EXIBE PISTAS (IN-ORDER) ====================
void exibirPistas(PistaNode* raiz) {
    if (!raiz) return;
    exibirPistas(raiz->esquerda);
    printf(" - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

// ==================== LIBERAÇÕES ====================
void liberarArvoreSalas(Sala* raiz) {
    if (!raiz) return;
    liberarArvoreSalas(raiz->esquerda);
    liberarArvoreSalas(raiz->direita);
    free(raiz);
}

void liberarBST(PistaNode* raiz) {
    if (!raiz) return;
    liberarBST(raiz->esquerda);
    liberarBST(raiz->direita);
    free(raiz);
}

void liberarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        HashNode* atual = tabela_hash[i];
        while (atual) {
            HashNode* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}