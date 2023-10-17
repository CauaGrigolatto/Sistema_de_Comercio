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
    int id;
    char nome[30];
    char senha[30];
} Administrador;


typedef struct Cliente {
    int id;
    char nome[30];
    char senha[30];
    Produto produtosComprados[100];
    float credito;
} Cliente;

//funções extras
int ehIdValido(int id);
int confirmarComCredenciais(int idEntrada, char senhaEntrada[]);
void redMessage(char message[]);
void greenMessage(char message[]);
void blueMessage(char message[]);
void yellowMessage(char message[]);

//funções de adm
Administrador criarAdministrador();
int verificacaoSenhaAdm(char senhaEntrada[30], Administrador adms[], int totalAdms);
int verificacaoIdAdm(int idEntrada, Administrador adms[], int totalAdms);
Administrador copiarAdm(Administrador adms[], int indice);
int encontrarIndiceAdm(int idEntrada, Administrador adms[], int totalAdms);

//funções clientes
int ehCreditoValido(float valor);
void removerCliente(Cliente usuarios[], int indice);
Cliente copiarCliente(Cliente usuarios[], int indice);
Cliente criarCliente();
void listarClientes(Cliente usuarios[], int totalUsuarios);
void visualizarDetalhesCliente(Cliente cliente);
int encontrarIndiceCliente(int idEntrada, Cliente clientes[], int totalClientes);
int verificacaoSenhaCliente(char senhaEntrada[30], Cliente clientes[], int totalClientes);
int verificacaoIdCliente(int idEntrada, Cliente clientes[], int totalClientes);

//funções produtos
int contarProdutosComprados(Produto produtos[]);
void comprarProduto(Produto produto, Produto produtosComprados[]);
int encontrarIndiceProduto(int codEntrada, Produto produtos[], int totalProdutos);
void removerProduto(Produto produtos[], int indice);
Produto copiarProduto(Produto produtos[], int indice);
void listarProdutos(Produto produtos[], int totalProdutos);
int verificacaoCodigoProduto(int codEntrada, Produto produtos[], int totalProdutos);
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

    int decisao;

    int idLogin;
    char senhaLogin[30];

    int idEntrada;

    int indiceAdm;
    int indiceCliente;
    int indiceProduto;

    float precoProduto;
    float credito;

    //Flags
    int existeAdm; 
    int existeCliente;
    int existeProduto;

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
            blueMessage("Escolha uma das opções de cadastro\n\n");

            blueMessage("1- Cadastrar administrador\n");
            blueMessage("2- Cadastrar cliente\n");
            scanf("%d", &decisao);

            system(CLEAR_SCREEN);

            if (decisao == 1) {
                blueMessage("Cadastro de administrador\n\n");


                novoAdm = criarAdministrador();
                existeAdm = verificacaoIdAdm(novoAdm.id, administradores, totalAdms);
                idValido = ehIdValido(novoAdm.id);

                system(CLEAR_SCREEN);

                if ((existeAdm == FALSE) && (idValido)) {
                    administradores[totalAdms] = novoAdm;
                    totalAdms++;

                    greenMessage("Administrador cadastrado com sucesso!\n\n"); 
                }
                else {
                    redMessage("ID inválido\n\n");
                }
            
            }
            else if (decisao == 2) {
                blueMessage("Cadastro de cliente\n\n");

                novoCliente = criarCliente();
                existeCliente = verificacaoIdCliente(novoCliente.id, clientes, totalClientes);
                idValido = ehIdValido(novoCliente.id);

                system(CLEAR_SCREEN);

                if ((existeCliente == FALSE) && (idValido)) {

                    clientes[totalClientes] = novoCliente;
                    totalClientes++;

                    greenMessage("Cliente cadastrado com sucesso!\n\n");
                }
                else {
                    redMessage("ID inválido\n\n");
                }
            }
            else {
                redMessage("Opção inválida\n\n");
                decisao = 0;
            }
        }
        else if (decisao == 2) {
            existeAdm = totalAdms != 0; 
            existeCliente = totalClientes != 0;
            
            if (existeAdm || existeCliente) {
                blueMessage("Escolha uma das opções de entrada\n\n");

                blueMessage("1- Entrar como administrador\n");
                blueMessage("2- Entrar como cliente\n");
                scanf("%d", &decisao);

                system(CLEAR_SCREEN);

                if ((decisao == 1) && existeAdm) {
                    blueMessage("Entrar como adminstrador\n\n");

                    blueMessage("ID: ");
                    scanf("%d", &idLogin);
                    getchar();

                    blueMessage("Senha: ");
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
                        redMessage("ID ou senha incorretos\n\n");
                    }
                }
                else if ((decisao == 2) && existeCliente) {
                    blueMessage("Entrar como cliente\n\n");

                    blueMessage("ID: ");
                    scanf("%d", &idLogin);
                    getchar();

                    blueMessage("Senha: ");
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
                        redMessage("ID ou senha incorretos\n\n");
                    }

                }
                else {
                    redMessage("Não há cadastros\n\n");    
                    decisao = 0;
                }
            }
            else {
                redMessage("Não há cadastros\n\n");
            }
        }
        else if (decisao == 3) {
            system(CLEAR_SCREEN);
            blueMessage("Bye\n");
        }
        else {
            redMessage("Opção inválida\n\n");
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
                    blueMessage("Cadastro de produto\n\n");

                    novoProduto = criarProduto();
                    existeProduto = verificacaoCodigoProduto(novoProduto.codigo, produtos, totalProdutos);
                    idValido = ehIdValido(novoProduto.codigo);

                    system(CLEAR_SCREEN);

                    if ((existeProduto == FALSE) && (idValido)) {
                        cadastrarProduto(produtos, totalProdutos, novoProduto);
                        totalProdutos++;
                        greenMessage("Novo produto cadastrado!\n\n");
                    }
                    else {
                        redMessage("Código inválido\n\n");
                    }

                }
                else if (decisao == 2) {
                    if (totalProdutos > 0) {
                        listarProdutos(produtos, totalProdutos);
                        yellowMessage("Pressione ENTER para voltar\n");
                        getchar();
                        system(CLEAR_SCREEN);
                    }
                    else {
                        redMessage("Não há produtos cadastrados\n\n");
                    }
                }
                else if (decisao == 3) {

                    if (totalProdutos > 0) {
                        blueMessage("Excluir produto:\n\n");
                        listarProdutos(produtos, totalProdutos);
                        blueMessage("Cód. produto: ");
                        scanf("%d", &idEntrada);
                        getchar();

                        system(CLEAR_SCREEN);

                        indiceProduto = encontrarIndiceProduto(idEntrada, produtos, totalProdutos);
                        existeProduto = indiceProduto != -1;

                        if (existeProduto) {
                            permitirAcessoAdm = confirmarComCredenciais(admLogado->id, admLogado->senha);

                            if (permitirAcessoAdm) {
                                removerProduto(produtos, indiceProduto);
                                totalProdutos--;    
                                greenMessage("Produto removido\n\n");
                            }
                            else {
                                redMessage("ID ou senha incorretos\n\n");
                            }
                        }
                        else {
                            redMessage("Código inválido\n\n");
                        }
                    }
                    else {
                        redMessage("Não há produtos cadastrados\n\n");
                    }

                }
                else if (decisao == 4) {
                    if (totalClientes > 0){
                        listarClientes(clientes, totalClientes);

                        blueMessage("1- Visualizar cliente com detalhes\n");
                        blueMessage("2- Voltar\n");
                        scanf("%d", &decisao);

                        system(CLEAR_SCREEN);

                        if (decisao == 1) {
                            listarClientes(clientes, totalClientes);
                            blueMessage("ID Cliente: ");
                            scanf("%d", &idEntrada);
                            getchar();

                            system(CLEAR_SCREEN);

                            indiceCliente = encontrarIndiceCliente(idEntrada, clientes, totalClientes);
                            existeCliente = indiceCliente != -1;

                            if (existeCliente) {
                                novoCliente = clientes[indiceCliente];
                                visualizarDetalhesCliente(novoCliente);

                                yellowMessage("Pressione ENTER para voltar\n");
                                getchar();
                                system(CLEAR_SCREEN);
                            }
                            else {
                                redMessage("ID inválido\n\n");
                            }
                        }
                        else if (decisao != 2){
                            redMessage("Opção inválida\n\n");
                        }   
                    }
                    else {
                        redMessage("Não há clientes cadastrados\n\n");
                    }
                }
                else if (decisao == 5) {
                    
                    if (totalClientes > 0) {
                        blueMessage("Excluir cliente\n\n");
                        listarClientes(clientes, totalClientes);
                        blueMessage("ID Cliente: ");
                        scanf("%d", &idEntrada);
                        getchar();

                        system(CLEAR_SCREEN);

                        indiceCliente = encontrarIndiceCliente(idEntrada, clientes, totalClientes);
                        existeCliente = indiceCliente != -1;

                        if (existeCliente) {
                            permitirAcessoAdm = confirmarComCredenciais(admLogado->id, admLogado->senha);

                            if (permitirAcessoAdm) {
                                removerCliente(clientes, indiceCliente);
                                totalClientes--;
                                greenMessage("Cliente removido\n\n");
                            }
                            else {
                                redMessage("ID ou senha incorretos\n\n");
                            }
                        }
                        else {
                            redMessage("ID inválido\n\n");
                        }
                    }
                    else {
                        redMessage("Não há clientes cadastrados\n\n");
                    }

                }
                else if (decisao == 6) {
                    redMessage("Saiu da conta\n\n");
                }
                else {
                    redMessage("Opção inválida\n\n");
                }
            }
        }
        else if (permitirAcessoCliente) {
            printf("Bem-vindo(a), %s\n", clienteLogado->nome);

            while (decisao != 4) {
                yellowMessage("Crédito: ");
                printf("%.2f\n\n", clienteLogado->credito);

                blueMessage("1- Comprar produtos\n");
                blueMessage("2- Visualizar produtos comprados\n");
                blueMessage("3- Adicionar crédito\n");
                blueMessage("4- Sair da conta\n");
                scanf("%d", &decisao);
                getchar();

                system(CLEAR_SCREEN);

                if (decisao == 1) {
                    if (totalProdutos > 0) {
                        listarProdutos(produtos, totalProdutos);
                        blueMessage("Cód. produto (-1 para sair): ");
                        scanf("%d", &decisao);
                        getchar();

                        system(CLEAR_SCREEN);

                        if (decisao != -1) {
                            indiceProduto = encontrarIndiceProduto(decisao, produtos, totalProdutos);

                            existeProduto = indiceProduto != -1;

                            if (existeProduto) {

                                precoProduto = produtos[indiceProduto].preco;

                                if (clienteLogado->credito >= precoProduto) {
                                    
                                    permitirAcessoCliente = confirmarComCredenciais(clienteLogado->id, clienteLogado->senha);

                                    if (permitirAcessoCliente) {
                                        novoProduto = copiarProduto(produtos, indiceProduto);
                                        comprarProduto(novoProduto, clienteLogado->produtosComprados);

                                        clienteLogado->credito -= novoProduto.preco;
                                        greenMessage("Produto adquirido\n\n");
                                    }
                                    else {
                                        redMessage("ID ou senha inválidos\n\n");
                                    }
                                }
                                else {
                                    redMessage("Créditos insuficientes\n\n");
                                } 

                            }
                            else {
                                redMessage("ID inválido\n\n");
                            }

                        }
                        else if (decisao == -1) {
                            redMessage("Compra cancelada\n\n");
                        }
                    }
                    else {
                        redMessage("Não há produtos cadastrados\n\n");
                    }
                } 
                else if (decisao == 2) {
                    totalComprados = contarProdutosComprados(clienteLogado->produtosComprados);
                    
                    if (totalComprados > 0) {
                        blueMessage("Produtos comprados\n\n");
                        listarProdutos(clienteLogado->produtosComprados, totalComprados);
                        
                        yellowMessage("Pressione ENTER para voltar\n");
                        getchar();
                        system(CLEAR_SCREEN);
                    }
                    else {
                        redMessage("Você ainda não comprou nenhum produto\n\n");
                    }
                }
                else if (decisao == 3) {
                    system(CLEAR_SCREEN);

                    permitirAcessoCliente = confirmarComCredenciais(clienteLogado->id, clienteLogado->senha);

                    if (permitirAcessoCliente){
                        blueMessage("Adicionar crédito\n\n");

                        blueMessage("Informe valor: ");
                        scanf("%f", &credito);

                        system(CLEAR_SCREEN);

                        if (ehCreditoValido(credito)) {
                            clienteLogado->credito += credito;
                            greenMessage("Crédito adicionado\n\n");
                        }
                        else {
                            redMessage("Valor inválido\n\n");
                        }
                    }
                    else {
                        redMessage("ID ou senha inválidos\n\n");
                    }

                }
                else if (decisao == 4) {
                    redMessage("Saiu da conta\n\n");
                }
                else {
                    redMessage("Opção inválida\n\n");
                }
            }

            decisao = 0;              
        }    
    }
    
    return 0;
}

//funções extras
int ehIdValido(int id) {
    return id > 0;
}


int ehCreditoValido(float valor) {
    return valor >= 0;
}

int confirmarComCredenciais(int idEntrada, char senhaEntrada[]) {
    int idLogin;
    char senhaLogin[30];

    int idValido, senhaValida, permitirAcesso;

    redMessage("Confirme suas credenciais para prosseguir\n\n");

    blueMessage("ID: ");
    scanf("%d", &idLogin);
    getchar();

    blueMessage("Senha: ");
    scanf("%[^\n]", senhaLogin);
    getchar();

    system(CLEAR_SCREEN);
    
    idValido = idLogin == idEntrada;
    senhaValida = strcmp(senhaLogin, senhaEntrada) == 0;
    permitirAcesso = idValido && senhaValida;

    return permitirAcesso;
}

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

void yellowMessage(char message[]){
    printf("\033[1;33m%s\033[0m", message);
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
    
    blueMessage("Id: ");
    scanf("%d", &novoAdm.id);
    getchar();

    blueMessage("Nome: ");
    scanf("%[^\n]", novoAdm.nome);
    getchar();

    blueMessage("Senha: ");
    scanf("%[^\n]", novoAdm.senha);
    getchar();
  
    return novoAdm;
}

Administrador copiarAdm(Administrador adms[], int indice) {
    Administrador admCopia;

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

void listarClientes(Cliente clientes[], int totalClientes) {
    for (int i = 0; i < totalClientes; i++) {
        printf("Id: %d\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        separar();
    }   
}

void visualizarDetalhesCliente(Cliente cliente) {
    int totalComprados;
    totalComprados = contarProdutosComprados(cliente.produtosComprados);

    printf("Id: %d\n", cliente.id);
    printf("Nome: %s\n", cliente.nome);
    printf("Senha: %s\n", cliente.senha);
    printf("Crédito: %.2f\n\n", cliente.credito);
    printf("Comprados (%d):\n\n", totalComprados);
    listarProdutos(cliente.produtosComprados, totalComprados);
}

Cliente criarCliente() {
    Cliente novoCliente;
    
    blueMessage("Id: ");
    scanf("%d", &novoCliente.id);
    getchar();

    blueMessage("Nome: ");
    scanf("%[^\n]", novoCliente.nome);
    getchar();

    blueMessage("Senha: ");
    scanf("%[^\n]", novoCliente.senha);
    getchar();

    novoCliente.credito = 0;
  
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

        clientes[i].id = 0;
        strcpy(clientes[i].nome, "");
        strcpy(clientes[i].senha, "");
        clientes[i].credito = 0;
    }
    else {
        clientes[indice].id = 0;
        strcpy(clientes[indice].nome, "");
        strcpy(clientes[indice].senha, "");
        clientes[indice].credito = 0;
    }
}

Cliente copiarCliente(Cliente clientes[], int indice) {
    Cliente clienteCopia;

    clienteCopia.id = clientes[indice].id;
    strcpy(clienteCopia.nome, clientes[indice].nome);
    strcpy(clienteCopia.senha, clientes[indice].senha);
    clienteCopia.credito = clientes[indice].credito;
    
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

int verificacaoCodigoProduto(int codEntrada, Produto produtos[], int totalProdutos) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalProdutos) && (validacao == FALSE)) {
        if (produtos[i].codigo == codEntrada) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

void listarProdutos(Produto produtos[], int totalProdutos) {
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

    blueMessage("Código: ");
    scanf("%d", &produto.codigo);
    getchar();

    blueMessage("Nome: ");
    scanf("%[^\n]", produto.nome);
    getchar();

    blueMessage("Preço: ");
    scanf("%f", &produto.preco);
    getchar();

    return produto;
}

void separar() {
    for (int i = 0; i < 35; i++) {
        printf(".");
    }
    printf("\n");
}