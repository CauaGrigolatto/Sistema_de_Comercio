#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

typedef struct Produto {
    char codigo[10];
    char nome[30];
    float preco;
} Produto;

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

//funções extras
void errorMessage(char message[20]);
void successMessage(char message[20]);

//funções de adm
Administrador criarAdministrador();

//funções usuários
void removerCliente(Cliente usuarios[], int indice);
Cliente copiarCliente(Cliente usuarios[], int indice);
Cliente criarCliente();
void visualizarClientes(Cliente usuarios[], int totalUsuarios);

//funções produtos
void removerProduto(Produto produtos[], int indice);
Produto copiarProduto(Produto produtos[], int indice);
void visualizarProdutos(Produto produtos[], int totalProdutos);
void cadastrarProduto(Produto produtos[], int indice, Produto produto);
Produto criarProduto();
void separar();

int main() {
    Administrador administradores[100];
    Cliente clientes[100];
    Produto produtos[100];

    int idAdministradores[100];
    int idClientes[100];
    int codigosProdutos[100];

    int totalAdms = 0;
    int totalClientes = 0;
    int totalProdutos = 0;

    Cliente novoCliente;
    Administrador novoAdm;
    Produto novoProduto;


    int decisao;

    printf("1- Cadastrar\n");
    printf("2- Entrar\n");
    printf("4- Sair\n");
    scanf("%d", &decisao);
    
    system(CLEAR_SCREEN);
    

    if (decisao == 1) {
        printf("1- Cadastrar cliente\n");
        printf("2- Cadastrar administrador\n");
        scanf("%d", &decisao);

        if (decisao == 1) {

            novoCliente = criarCliente();
            clientes[totalClientes] = novoCliente;
            totalClientes++;
            successMessage("Cliente cadastrado com sucesso!\n");
        
        }
        else if (decisao == 2) {

            novoAdm = criarAdministrador();
            administradores[totalAdms] = novoAdm;
            totalAdms++;
            successMessage("Administrador cadastrado com sucesso!\n");

        }

    }
    else if (decisao == 2) {
        int existeAdm = totalAdms != 0; 
        int existeCliente = totalClientes != 0;
        
        if (existeAdm || existeCliente) {
        
        }
        else {
            errorMessage("Ops, parece que não há cadastros!\n");
        }
    }
    else if (decisao == 3) {

    }

    
    return 0;
}

//funções extras
void errorMessage(char message[20]) {
    printf("\033[1;31m%s\033[1;31m", message);
}

void successMessage(char message[20]) {
    printf("\033[1;32m%s\033[1;32m", message);
}

//funções de adm
Administrador criarAdministrador() {
    Administrador novoAdm;
    
    printf("Id: ");
    scanf("%d", &novoAdm.id);
    getchar();

    printf("Nome: ");
    scanf("%[^\n]", novoAdm.nome);
    getchar();

    printf("Senha: ");
    scanf("%[^\n]", novoAdm.senha);
    getchar();
  
    novoAdm.adm = TRUE;

    return novoAdm;
}

//funções de clientes
void visualizarClientes(Cliente clientes[], int totalClientes) {
    for (int i = 0; i < totalClientes; i++) {
        printf("Adm: %d\n", clientes[i].adm);
        printf("Id: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Senha: %s\n", clientes[i].senha);
        separar();
    }
    
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
        clienteCopia = copiarCliente(clientes, i);
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