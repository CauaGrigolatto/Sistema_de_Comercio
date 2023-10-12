#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Usuario
{
    int administrador;
    int id;
    char nome[30];
    char senha[30];
} Usuario;


typedef struct Produto {
    char codigo[10];
    char nome[30];
    float preco;
} Produto;

void removerProduto(Produto produtos[], int indice);
Produto copiarProduto(Produto produtos[], int indice);
void visualizarProdutos(Produto produtos[], int totalProdutos);
void cadastrarProduto(Produto produtos[], int indice, Produto produto);
Produto criarProduto();
void separar();

int main() {
    
    Produto produtos[30];
    Produto novoProduto;
    int totalProdutos = 0;

    for (int i = 0; i < 2; i++) {
        novoProduto = criarProduto();    
        cadastrarProduto(produtos, i, novoProduto);
        totalProdutos++;
        
        separar();
    }

    visualizarProdutos(produtos, totalProdutos);
    
    


    return 0;
}

void visualizarProdutos(Produto produtos[], int totalProdutos) {
    for (int i = 0; i < totalProdutos; i++) {
        printf("%d - ",i);
        printf("Código: %s\n", produtos[i].codigo);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preço: %.2f\n", produtos[i].preco);
        separar();
    }
    
}

void removerProduto(Produto produtos[], int indice) {
    Produto produtoCopia;
    int i = indice + 1;

    while (produtos[i].nome[0] != '\0') {
        produtoCopia = copiarProduto(produtos, i);
        produtos[i-1] = produtoCopia;
        i++;
    }
    
    strcpy(produtos[i].codigo, "");
    strcpy(produtos[i].nome, "");
    produtos[i].preco = 0.0;
    
}

Produto copiarProduto(Produto produtos[], int indice) {
    Produto copiaProduto;

    strcpy(copiaProduto.codigo, produtos[indice].codigo);
    strcpy(copiaProduto.nome, produtos[indice].nome);
    copiaProduto.preco = produtos[indice].preco;

    return copiaProduto;
}

void cadastrarProduto(Produto produtos[], int indice, Produto produto) {
    produtos[indice] = produto;
}

Produto criarProduto() {
    Produto produto;

    printf("Informe código do produto: ");
    scanf("%[^\n]", produto.codigo);
    getchar();

    printf("Informe nome do produto: ");
    scanf("%[^\n]", produto.nome);
    getchar();

    printf("Informe preço do produto: ");
    scanf("%f", &produto.preco);
    getchar();

    return produto;
}

void separar() {
    for (int i = 0; i < 50; i++) {
        printf(".");
    }
    printf("\n");
}