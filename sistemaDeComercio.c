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
    int codigo;
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
    Produto produtosComprados[100];
} Cliente;

//funções extras
void redMessage(char message[]);
void greenMessage(char message[]);
void blueMessage(char message[]);

//funções de adm
Administrador criarAdministrador();
int verificacaoSenhaAdm(char senhaEntrada[30], Administrador adms[], int totalAdms);
int verificacaoIdAdm(int idEntrada, Administrador adms[], int totalAdms);
Administrador copiarAdm(Administrador adms[], int indice);
int encontrarIndiceAdm(int idEntrada, Administrador adms[], int totalAdms);

//funções clientes
void removerCliente(Cliente usuarios[], int indice);
Cliente copiarCliente(Cliente usuarios[], int indice);
Cliente criarCliente();
void visualizarClientes(Cliente usuarios[], int totalUsuarios);
int encontrarIndiceCliente(int idEntrada, Cliente clientes[], int totalClientes);
int verificacaoSenhaCliente(char senhaEntrada[30], Cliente clientes[], int totalClientes);
int verificacaoIdCliente(int idEntrada, Cliente clientes[], int totalClientes);

//funções produtos
int contarProdutosComprados(Produto produtos[]);
void comprarProduto(Produto produto, Produto produtosComprados[]);
int encontrarIndiceProduto(int codEntrada, Produto produtos[], int totalProdutos);
void removerProduto(Produto produtos[], int indice);
Produto copiarProduto(Produto produtos[], int indice);
void visualizarProdutos(Produto produtos[], int totalProdutos);
void cadastrarProduto(Produto produtos[], int indice, Produto produto);
Produto criarProduto();

void separar();

int main() {
    system(CLEAR_SCREEN);

    Administrador administradores[100];
    Cliente clientes[100];
    Produto produtos[100];

    Cliente novoCliente;
    Administrador novoAdm;
    Produto novoProduto;

    Cliente *clienteLogado;
    Administrador *admLogado;

    int totalAdms = 0;
    int totalClientes = 0;
    int totalProdutos = 0;
    int totalComprados = 0;

    int idAdministradores[100];
    int idClientes[100];
    int codigosProdutos[100];


    int decisao;

    int idLogin;
    char senhaLogin[30];

    int indiceAdm;
    int indiceCliente;
    int indiceProduto;

    //Flags
    int existeAdm; 
    int existeCliente;

    int idValido;
    int senhaValida; 

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

            system(CLEAR_SCREEN);

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
            else {
                redMessage("Opção inválida\n");
                decisao = 0;
            }
        }
        else if (decisao == 2) {
            existeAdm = totalAdms != 0; 
            existeCliente = totalClientes != 0;
            
            if (existeAdm || existeCliente) {
                blueMessage("1- Entrar como administrador\n");
                blueMessage("2- Entrar como cliente\n");
                scanf("%d", &decisao);

                system(CLEAR_SCREEN);

                if ((decisao == 1) && existeAdm) {

                    blueMessage("ID:\n");
                    scanf("%d", &idLogin);
                    getchar();

                    blueMessage("Senha:\n");
                    scanf("%[^\n]", senhaLogin);
                    getchar();

                    system(CLEAR_SCREEN);

                    idValido = verificacaoIdAdm(idLogin, administradores, totalAdms);
                    senhaValida = verificacaoSenhaAdm(senhaLogin, administradores, totalAdms);

                    permitirAcessoAdm = idValido && senhaValida;
                    
                    if (permitirAcessoAdm) { 
                        indiceAdm = encontrarIndiceAdm(idLogin, administradores, totalAdms);
                        admLogado = &administradores[indiceAdm];

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

                    system(CLEAR_SCREEN);

                    idValido = verificacaoIdCliente(idLogin, clientes, totalClientes);
                    senhaValida = verificacaoSenhaCliente(senhaLogin, clientes, totalClientes);
                    permitirAcessoCliente = idValido && senhaValida;
                    
                    if (permitirAcessoCliente) {    
                        indiceCliente = encontrarIndiceCliente(idLogin, clientes, totalClientes);
                        clienteLogado = &clientes[indiceCliente];

                        greenMessage("Você entrou como cliente\n");
                    }
                    else {
                        redMessage("ID ou senha incorretos\n");
                    }

                }
                else {
                    redMessage("Opção inválida\n");    
                    decisao = 0;
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
        else {
            redMessage("Opção inválida\n");
        }

        if (permitirAcessoAdm) {
            printf("Bem-vindo(a), %s\n\n", admLogado->nome);

            while (decisao != 6) {
                blueMessage("1- Cadastrar produto\n");
                blueMessage("2- Visualizar produtos\n");
                blueMessage("3- Remover produto\n");
                blueMessage("4- Visualizar clientes\n");
                blueMessage("5- Remover cliente\n");
                blueMessage("6- Sair da conta\n");
                scanf("%d", &decisao);
                getchar();

                system(CLEAR_SCREEN);

                if (decisao == 1) {

                    novoProduto = criarProduto();
                    cadastrarProduto(produtos, totalProdutos, novoProduto);
                    totalProdutos++;
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
                    if (totalClientes > 0){
                        visualizarClientes(clientes, totalClientes);
                    }
                    else {
                        redMessage("Não há clientes cadastrados\n");
                    }
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
            printf("Bem-vindo(a), %s\n\n", clienteLogado->nome);

            while (decisao != 3) {

                blueMessage("1- Comprar produtos\n");
                blueMessage("2- Visualizar produtos comprados\n");
                blueMessage("3- Sair da conta\n");
                scanf("%d", &decisao);

                system(CLEAR_SCREEN);

                if (decisao == 1) {
                    if (totalProdutos > 0) {
                        visualizarProdutos(produtos, totalProdutos);
                        blueMessage("Cód. produto (-1 para sair): \n");
                        scanf("%d", &decisao);

                        system(CLEAR_SCREEN);

                        if (decisao != -1) {
                            indiceProduto = encontrarIndiceProduto(decisao, produtos, totalProdutos);
                            novoProduto = copiarProduto(produtos, indiceProduto);
                            comprarProduto(novoProduto, clienteLogado->produtosComprados);

                            system(CLEAR_SCREEN);
                            greenMessage("Produto adquirido\n");
                        }
                        else if (decisao == -1) {
                            redMessage("Compra cancelada\n");
                        }
                    }
                    else {
                        redMessage("Não há produtos cadastrados\n");
                    }

                } else if (decisao == 2) {
                    totalComprados = contarProdutosComprados(clienteLogado->produtosComprados);
                    
                    if (totalComprados > 0) {
                        visualizarProdutos(clienteLogado->produtosComprados, totalComprados);
                    }
                    else {
                        redMessage("Você ainda não comprou nenhum produto\n");
                    }
                }
                else if (decisao == 3) {
                    redMessage("Saiu da conta\n");
                }

                decisao = 0;
            
            }
                        
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

Administrador copiarAdm(Administrador adms[], int indice) {
    Administrador admCopia;

    admCopia.adm = adms[indice].adm;
    admCopia.id = adms[indice].id;
    strcpy(admCopia.nome, adms[indice].nome);
    strcpy(admCopia.senha, adms[indice].senha);
    
    return admCopia;
}

int encontrarIndiceAdm(int idEntrada, Administrador adms[], int totalAdms) {
    int indice = -1;
    int i = 0;

    while ((i < totalAdms) && (indice == -1)) {
        if (adms[i].id == idEntrada) {
            indice = i;
        }
        i++;
    }
    
    return indice;
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
    int produtosComprados;
    for (int i = 0; i < totalClientes; i++) {
        produtosComprados = contarProdutosComprados(clientes[i].produtosComprados);

        printf("Adm: %d\n", clientes[i].adm);
        printf("Id: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Senha: %s\n", clientes[i].senha);
        printf("Produtos comprados: %d\n", produtosComprados);
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

int encontrarIndiceCliente(int idEntrada, Cliente clientes[], int totalClientes) {
    int indice = -1;
    int i = 0;

    while ((i < totalClientes) && (indice == -1)) {
        if (clientes[i].id == idEntrada) {
            indice = i;
        }
        i++;
    }
    
    return indice;
}

//funções produtos
int contarProdutosComprados(Produto produtos[]) {
    int i = 0;

    while (produtos[i].nome[0] != '\0') {
        i++;
    }

    return i;
}

void comprarProduto(Produto produto, Produto produtosComprados[]) {
    int i = contarProdutosComprados(produtosComprados);
    produtosComprados[i] = produto;
}

int encontrarIndiceProduto(int codEntrada, Produto produtos[], int totalProdutos) {
    int indice = -1;
    int i = 0;

    while ((i < totalProdutos) && (indice == -1)) {
        if (produtos[i].codigo == codEntrada) {
            indice = i;
        }
        i++;
    }
    
    return indice;
}

void visualizarProdutos(Produto produtos[], int totalProdutos) {
    for (int i = 0; i < totalProdutos; i++) {
        printf("Código: %d\n", produtos[i].codigo);
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

        produtos[i].codigo = 0;
        strcpy(produtos[i].nome, "");
        produtos[i].preco = 0.0;
    }
    else {
        produtos[indice].codigo = 0;
        strcpy(produtos[indice].nome, "");
        produtos[indice].preco = 0.0;
    }    
    
}

Produto copiarProduto(Produto produtos[], int indice) {
    Produto copiaProduto;

    copiaProduto.codigo = produtos[indice].codigo;
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
    scanf("%d", &produto.codigo);
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