#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Administrador {
    int adm;
    int id;
    char nome[30];
    char senha[30];
} Administrador;


typedef struct Cliente {
    int adm;
    int id;
    char nome[30];
    char senha[30];
    Produto carrinho[100];
} Cliente;


typedef struct Produto {
    char codigo[10];
    char nome[30];
    float preco;
} Produto;

//funções usuários
void removerUsuario(Cliente usuarios[], int indice);
Cliente copiarUsuario(Cliente usuarios[], int indice);
Cliente criarCliente();
void cadastrarCliente(Cliente usuarios[], int indice);
void visualizarClientes(Cliente usuarios[], int totalUsuarios);

//funções produtos
void removerProduto(Produto produtos[], int indice);
Produto copiarProduto(Produto produtos[], int indice);
void visualizarProdutos(Produto produtos[], int totalProdutos);
void cadastrarProduto(Produto produtos[], int indice, Produto produto);
Produto criarProduto();
void separar();

int main() {
    int idAdministradores[100];
    int idClientes[100];
    int codigosProdutos[100];

    


    return 0;
}

void visualizarClientes(Cliente clientes[], int totalClientes) {
    for (int i = 0; i < totalClientes; i++) {
        printf("Adm: %d\n", clientes[i].adm);
        printf("Id: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Senha: %s\n", clientes[i].senha);
        separar();
    }
    
}

void cadastrarCliente(Cliente clientes[], int indice) {
    Cliente novoCliente = criarCliente();
    clientes[indice] = novoCliente;
}

Cliente criarCliente() {
    Cliente novoCliente;
    
    printf("Id: ");
    scanf("%d", &novoCliente.id);
    getchar();

    printf("Nome: ");
    scanf("%[^\n]", novoCliente.nome);
    getchar();

    printf("Senha: ");
    scanf("%[^\n]", novoCliente.senha);
    getchar();
  
    novoCliente.adm = FALSE;

    return novoCliente;
}

void removerCliente(Cliente clientes[], int indice) {
    Cliente clienteCopia;
    int i = indice + 1;

    while (clientes[i].nome[0] != '\0') {
        clienteCopia = copiarUsuario(clientes, i);
        clientes[i-1] = clienteCopia;
        i++;
    }
    
    clientes[i].adm = 0;
    clientes[i].id = 0;
    strcpy(clientes[i].nome, "");
    strcpy(clientes[i].senha, "");
}

Cliente copiarCliente(Cliente clientes[], int indice) {
    Cliente clienteCopia;

    clienteCopia.adm = clientes[indice].adm;
    clienteCopia.id = clientes[indice].id;
    strcpy(clienteCopia.nome, clientes[indice].nome);
    strcpy(clienteCopia.senha, clientes[indice].senha);
    
    return clienteCopia;
}


//funções produtos
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
    Produto copiaProduto;
    int i = indice + 1;

    while (produtos[i].nome[0] != '\0') {
        copiaProduto = copiarProduto(produtos, i);
        produtos[i-1] = copiaProduto;
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