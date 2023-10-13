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

//validações
int verificacaoSenhaCliente(char senhaEntrada[30], Cliente clientes[], int totalClientes);
int verificacaoIdCliente(int idEntrada, Cliente clientes[], int totalClientes);

int verificacaoSenhaAdm(char senhaEntrada[30], Administrador adms[], int totalAdms);
int verificacaoIdAdm(int idEntrada, Administrador adms[], int totalAdms);

//funções extras
void redMessage(char message[]);
void greenMessage(char message[]);
void blueMessage(char message[]);

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

    int idLogin;
    char senhaLogin[30];

    int decisao;

    int existeAdm; 
    int existeCliente;

    int idValido = FALSE;
    int senhaValida = FALSE; 

    int permitirAcessoAdm;
    int permitirAcessoCliente;


    while (decisao != 3) {            

        idValido = FALSE;
        senhaValida = FALSE;

        permitirAcessoAdm = FALSE;
        permitirAcessoCliente = FALSE;

        blueMessage("1- Cadastrar\n");
        blueMessage("2- Entrar\n");
        blueMessage("3- Sair\n");
        scanf("%d", &decisao);
        
        system(CLEAR_SCREEN);
 
        if (decisao == 1) {
            blueMessage("1- Cadastrar administrador\n");
            blueMessage("2- Cadastrar cliente\n");
            scanf("%d", &decisao);

            if (decisao == 1) {

                novoAdm = criarAdministrador();
                existeAdm = verificacaoIdAdm(novoAdm.id, administradores, totalAdms);

                if (existeAdm == FALSE) {
                    administradores[totalAdms] = novoAdm;
                    totalAdms++;

                    system(CLEAR_SCREEN);
                    greenMessage("Administrador cadastrado com sucesso!\n"); 
                }
                else {
                    redMessage("ID já cadastrado\n");
                }
            
            }
            else if (decisao == 2) {

                novoCliente = criarCliente();
                existeCliente = verificacaoIdCliente(novoCliente.id, clientes, totalAdms);

                if (existeCliente == FALSE) {

                    clientes[totalClientes] = novoCliente;
                    totalClientes++;

                    system(CLEAR_SCREEN);
                    greenMessage("Cliente cadastrado com sucesso!\n");
                }
                else {
                    redMessage("ID já cadastrado\n");
                }
                
            }
        }
        else if (decisao == 2) {
            existeAdm = totalAdms != 0; 
            existeCliente = totalClientes != 0;
            
            if (existeAdm || existeCliente) {
                blueMessage("1- Entrar como administrador\n");
                blueMessage("2- Entrar como cliente\n");
                scanf("%d", &decisao);

                if ((decisao == 1) && existeAdm) {

                    blueMessage("ID:\n");
                    scanf("%d", &idLogin);
                    getchar();

                    blueMessage("Senha:\n");
                    scanf("%[^\n]", senhaLogin);
                    getchar();

                    idValido = verificacaoIdAdm(idLogin, administradores, totalAdms);
                    senhaValida = verificacaoSenhaAdm(senhaLogin, administradores, totalAdms);
                    permitirAcessoAdm = idValido && senhaValida;
                    system(CLEAR_SCREEN);

                    if (permitirAcessoAdm) {    
                        greenMessage("Você entrou como administrador\n");
                    }
                    else {
                        redMessage("ID ou senha incorretos\n");
                    }
                
                
                }
                else if ((decisao == 2) && existeCliente) {

                    blueMessage("ID:\n");
                    scanf("%d", &idLogin);
                    getchar();

                    blueMessage("Senha:\n");
                    scanf("%[^\n]", senhaLogin);
                    getchar();

                    idValido = verificacaoIdCliente(idLogin, clientes, totalClientes);
                    senhaValida = verificacaoSenhaCliente(senhaLogin, clientes, totalClientes);
                    permitirAcessoCliente = idValido && senhaValida;
                    system(CLEAR_SCREEN);

                    if (permitirAcessoCliente) {    
                        greenMessage("Você entrou como cliente\n");
                    }
                    else {
                        redMessage("ID ou senha incorretos\n");
                    }

                }
                else {
                    redMessage("Ops, parece que não há cadastros!\n");    
                }
            }
            else {
                redMessage("Ops, parece que não há cadastros!\n");
            }
        }
        else if (decisao == 3) {
            system(CLEAR_SCREEN);
            blueMessage("Bye\n");
        }

        if (permitirAcessoAdm) {

            while (decisao != 6) {
                blueMessage("1- Cadastrar produto\n");
                blueMessage("2- Visualizar produtos\n");
                blueMessage("3- Remover produto\n");
                blueMessage("4- Visualizar clientes\n");
                blueMessage("5- Remover cliente\n");
                blueMessage("6- Logout\n");
                scanf("%d", &decisao);
                getchar();

                if (decisao == 1) {

                    novoProduto = criarProduto();
                    cadastrarProduto(produtos, totalProdutos, novoProduto);
                    totalProdutos++;

                    system(CLEAR_SCREEN);
                    greenMessage("Novo produto cadastrado!\n");
                
                }
                else if (decisao == 2) {
                    visualizarProdutos(produtos, totalProdutos);
                }
                else if (decisao == 3) {

                    if (totalProdutos > 0) {
                        redMessage("Excluir produto:\n");
                        visualizarProdutos(produtos, totalProdutos);
                        scanf("%d", &decisao);
                        getchar();

                        removerProduto(produtos, decisao);
                        totalProdutos--;    
                    }
                    else {
                        redMessage("Não há produtos cadastrados\n");
                    }

                }
                else if (decisao == 4) {
                    visualizarClientes(clientes, totalClientes);
                }
                else if (decisao == 5) {
                    
                    if (totalClientes > 0) {
                        visualizarClientes(clientes, totalClientes);
                        scanf("%d", &decisao);
                        getchar();

                        removerCliente(clientes, decisao);
                        totalClientes--;
                    }
                    else {
                        redMessage("Não há clientes cadastrados\n");
                    }

                }
                else if (decisao == 6) {
                    redMessage("Saiu da conta\n");
                }
            
            }
            
        }
        else if (permitirAcessoCliente) {
            //opções de clientes
        }
        
    }
    
    return 0;
}

//funções extras
void redMessage(char message[]) {
    printf("\033[1;31m%s\033[1;31m", message);
    printf("\033[0m");
}

void greenMessage(char message[]) {
    printf("\033[1;32m%s\033[1;32m", message);
    printf("\033[0m");
}

void blueMessage(char message[]) {
    printf("\033[34m%s\033[0m", message);
}

//funções de adm
int verificacaoIdAdm(int idEntrada, Administrador adms[], int totalAdms) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalAdms) && (validacao == FALSE)) {
        if (adms[i].id == idEntrada) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

int verificacaoSenhaAdm(char senhaEntrada[30], Administrador adms[], int totalAdms) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalAdms) && (validacao == FALSE)) {
        if (strcmp(senhaEntrada, adms[i].senha) == 0) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

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
int verificacaoSenhaCliente(char senhaEntrada[30], Cliente clientes[], int totalClientes) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalClientes) && (validacao == FALSE)) {
        if (strcmp(senhaEntrada, clientes[i].senha) == 0) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

int verificacaoIdCliente(int idEntrada, Cliente clientes[], int totalClientes) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalClientes) && (validacao == FALSE)) {
        if (clientes[i].id == idEntrada) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
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

    if (clientes[i].nome[0] != '\0') {
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
    else {
        clientes[indice].adm = 0;
        clientes[indice].id = 0;
        strcpy(clientes[indice].nome, "");
        strcpy(clientes[indice].senha, "");
    }
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

    if (produtos[i].nome[0] != '\0') {
        while (produtos[i].nome[0] != '\0') {
            copiaProduto = copiarProduto(produtos, i);
            produtos[i-1] = copiaProduto;
            i++;
        }

        strcpy(produtos[i].codigo, "");
        strcpy(produtos[i].nome, "");
        produtos[i].preco = 0.0;
    }
    else {
        strcpy(produtos[indice].codigo, "");
        strcpy(produtos[indice].nome, "");
        produtos[indice].preco = 0.0;
    }    
    
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