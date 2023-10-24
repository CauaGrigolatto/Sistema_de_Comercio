/*
    Cauã Grigolatto Domingos
    AQ3022323
    #FreeSoftware
*/

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
    char codigo[30];
    char nome[30];
    float preco;
} Produto;

typedef struct Administrador {
    char id[30];
    char nome[30];
    char senha[30];
} Administrador;


typedef struct Cliente {
    char id[30];
    char nome[30];
    char senha[30];
    int totalComprados;
    Produto produtosComprados[100];
    float credito;
} Cliente;

//funções de interface
void showMainTitle(char title[], char colorTitle[]);
void showSubtitle(char message[], char colorMessage[]);
void showColorfulText(char text[], char color[]);
void redMessage(char message[]);
void greenMessage(char message[]);
void blueMessage(char message[]);
void yellowMessage(char message[]);
void separar();

//funções flags
int confirmarComCredenciais(char idEntrada[], char senhaEntrada[]);
int validarId(char idEntrada[]);
int validarSenha(char senhaEntrada[]);
int ehCreditoValido(float valor);
int compararStrings(char str1[], char str2[]);

//funções de adm
Administrador criarAdministrador();
int verificacaoIdAdm(char idEntrada[], Administrador adms[], int totalAdms);
int verificacaoSenhaAdm(char senhaEntrada[], Administrador adms[], int totalAdms);
int encontrarIndiceAdm(char idEntrada[], Administrador adms[], int totalAdms);

//funções de clientes
Cliente criarCliente();
int verificacaoIdCliente(char idEntrada[], Cliente clientes[], int totalClientes);
int verificacaoSenhaCliente(char senhaEntrada[], Cliente clientes[], int totalClientes);
void removerCliente(Cliente usuarios[], int indice);
void resetarCliente(Cliente *cliente);
void listarClientes(Cliente usuarios[], int totalUsuarios);
void visualizarDetalhesCliente(Cliente cliente);
int encontrarIndiceCliente(char idEntrada[], Cliente clientes[], int totalClientes);

//funções produtos
Produto criarProduto();
void comprarProduto(Produto produto, Produto produtosComprados[], int indice);
void removerProduto(Produto produtos[], int indice);
void resetarProduto(Produto *produto);
int encontrarIndiceProduto(char codEntrada[], Produto produtos[], int totalProdutos);
void listarProdutos(Produto produtos[], int totalProdutos);
int ehCodigoExistente(char codEntrada[], Produto produtos[], int totalProdutos);
void cadastrarProduto(Produto produtos[], int indice, Produto produto);

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

    char idLogin[30];
    char senhaLogin[30];
    char idEntrada[30];
    char codCompra[30];

    int indiceAdm;
    int indiceCliente;
    int indiceProduto;

    float precoProduto;
    float credito;
    
    char message[50];
    char colorMessage[10]; 
    strcpy(message, "");
    strcpy(colorMessage, "blue");

    //Flags
    int existeAdm; 
    int existeCliente;
    int existeProduto;

    int idValido;
    int senhaValida; 

    int permitirAcessoAdm;
    int permitirAcessoCliente;

    while (decisao != 3) {            
        idValido = senhaValida = FALSE;
        permitirAcessoAdm = permitirAcessoCliente = FALSE;

        showMainTitle("Sistema de Comércio", "blue");
        showSubtitle(message, colorMessage);

        blueMessage("[1] "); printf("Cadastrar\n");
        blueMessage("[2] "); printf("Entrar\n");
        blueMessage("[3] "); printf("Sair\n\n");

        scanf("%d", &decisao);
        strcpy(message, "");

        
        system(CLEAR_SCREEN);
 
        if (decisao == 1) {

            showMainTitle("Cadastrar", "blue");
            showSubtitle("Escolha uma opção de cadastro", "blue");

            blueMessage("[1] "); printf("Cadastrar administrador\n");
            blueMessage("[2] "); printf("Cadastrar cliente\n\n");
            
            scanf("%d", &decisao);
            getchar();
            strcpy(message, "");

            system(CLEAR_SCREEN);

            if (decisao == 1) {
                showMainTitle("Cadastrar adminstrador", "blue");
                showSubtitle("Preencha os campos e cadastre um ADM", "blue");

                novoAdm = criarAdministrador();
                existeAdm = verificacaoIdAdm(novoAdm.id, administradores, totalAdms);

                system(CLEAR_SCREEN);

                if (existeAdm == FALSE) {
                    administradores[totalAdms] = novoAdm;
                    totalAdms++;

                    strcpy(message, "Administrador cadastrado com sucesso!");
                    strcpy(colorMessage, "green"); 
                }
                else {
                    strcpy(message, "ID inválido!");
                    strcpy(colorMessage, "red");
                }
            }
            else if (decisao == 2) {
                showMainTitle("Cadastrar cliente", "blue");
                showSubtitle("Preencha os campos e cadastre um cliente", "blue");

                novoCliente = criarCliente();
                existeCliente = verificacaoIdCliente(novoCliente.id, clientes, totalClientes);

                system(CLEAR_SCREEN);

                if (existeCliente == FALSE) {

                    clientes[totalClientes] = novoCliente;
                    totalClientes++;

                    strcpy(message, "Cliente cadastrado!");
                    strcpy(colorMessage, "green");
                }
                else {
                    strcpy(message, "ID inválido!");
                    strcpy(colorMessage, "red");
                }
            }
            else {
                strcpy(message, "Opção inválida!");
                strcpy(colorMessage, "red");
                decisao = 0;
            }
        }
        else if (decisao == 2) {
            existeAdm = totalAdms != 0; 
            existeCliente = totalClientes != 0;
            
            if (existeAdm || existeCliente) {
                showMainTitle("Entrar", "blue");
                showSubtitle("Escolha uma opção de entrada", "blue");
                
                blueMessage("[1] "); printf("Entrar como ADM\n");
                blueMessage("[2] "); printf("Entrar como cliente\n\n");
                
                scanf("%d", &decisao);
                getchar();
                strcpy(message, "");

                system(CLEAR_SCREEN);

                if ((decisao == 1) && existeAdm) {
                    showMainTitle("Entrar como ADM", "blue");
                    showSubtitle("Preencha os campos para entrar como ADM", "blue");

                    blueMessage("ID: ");
                    scanf("%[^\n]", idLogin);
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

                        strcpy(message, "Entrou como ADM!");
                        strcpy(colorMessage, "green");
                    }
                    else {
                        strcpy(message, "ID ou senha inválidos!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if ((decisao == 2) && existeCliente) {
                    showMainTitle("Entrar como cliente", "blue");
                    showSubtitle("Preencha os campos para entrar como cliente", "blue");

                    blueMessage("ID: ");
                    scanf("%[^\n]", idLogin);
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

                        strcpy(message, "Entrou como cliente!");
                        strcpy(colorMessage, "green");
                    }
                    else {
                        strcpy(message, "ID ou senha inválidos!");
                        strcpy(colorMessage, "red");
                    }

                }
                else {
                    strcpy(message, "Não há cadastros!");
                    strcpy(colorMessage, "red");
                    decisao = 0;
                }
            }
            else {
                strcpy(message, "Não há cadastros!");
                strcpy(colorMessage, "red");
            }
        }
        else if (decisao == 3) {
            system(CLEAR_SCREEN);
            blueMessage("Bye\n");
        }
        else {
            strcpy(message, "Opção inválida!");
            strcpy(colorMessage, "red");
        }

        if (permitirAcessoAdm) {
            while (decisao != 6) {

                showMainTitle("Administrador", "blue");
                showSubtitle(admLogado->nome, "blue");
                showSubtitle(message, colorMessage);

                blueMessage("[1] "); printf("Cadastrar produto\n");
                blueMessage("[2] "); printf("Visualizar produtuos\n");
                blueMessage("[3] "); printf("Excluir produto\n");
                blueMessage("[4] "); printf("Visualizar clientes\n");
                blueMessage("[5] "); printf("Excluir cliente\n");
                blueMessage("[6] "); printf("Sair da conta\n\n");

                scanf("%d", &decisao);
                getchar();
                strcpy(message, "");

                system(CLEAR_SCREEN);

                if (decisao == 1) {
                    showMainTitle("Cadastrar produto", "blue");

                    novoProduto = criarProduto();
                    existeProduto = ehCodigoExistente(novoProduto.codigo, produtos, totalProdutos);

                    system(CLEAR_SCREEN);

                    if (existeProduto == FALSE) {
                        cadastrarProduto(produtos, totalProdutos, novoProduto);
                        totalProdutos++;

                        strcpy(message, "Produto cadastrado!");
                        strcpy(colorMessage, "green");
                    }
                    else {
                        strcpy(message, "Código inválido!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if (decisao == 2) {
                    if (totalProdutos > 0) {
                        showMainTitle("Produtos cadastrados", "blue");
                        listarProdutos(produtos, totalProdutos);
                        yellowMessage("Pressione ENTER para voltar\n");
                        getchar();
                        system(CLEAR_SCREEN);
                    }
                    else {
                        strcpy(message, "Não há produtos cadastrados!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if (decisao == 3) {
                    if (totalProdutos > 0) {
                        showMainTitle("Excluir produto", "red");
                        listarProdutos(produtos, totalProdutos);
                        blueMessage("Cód. produto: ");
                        scanf("%[^\n]", idEntrada);
                        strcpy(message, "");
                        getchar();

                        system(CLEAR_SCREEN);

                        indiceProduto = encontrarIndiceProduto(idEntrada, produtos, totalProdutos);
                        existeProduto = indiceProduto != -1;

                        if (existeProduto) {
                            permitirAcessoAdm = confirmarComCredenciais(admLogado->id, admLogado->senha);

                            if (permitirAcessoAdm) {
                                removerProduto(produtos, indiceProduto);
                                totalProdutos--;    
                                
                                strcpy(message, "Produto excluído!");
                                strcpy(colorMessage, "green");
                            }
                            else {
                                strcpy(message, "ID ou senha inválidos!");
                                strcpy(colorMessage, "red");
                            }
                        }
                        else {
                            strcpy(message, "Código inválido!");
                            strcpy(colorMessage, "red");
                        }
                    }
                    else {
                        strcpy(message, "Não há produtos cadastrados!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if (decisao == 4) {
                    if (totalClientes > 0){
                        showMainTitle("Visualizar clientes", "blue");
                        listarClientes(clientes, totalClientes);

                        blueMessage("[1] "); printf("Visualizar cliente com detalhes\n");
                        blueMessage("[2] "); printf("Voltar\n\n");

                        scanf("%d", &decisao);
                        getchar();
                        strcpy(message, "");

                        system(CLEAR_SCREEN);

                        if (decisao == 1) {
                            showMainTitle("Visualizar com detalhes", "blue");
                            showSubtitle("Informe o ID da conta para ver detalhes", "blue");
                            listarClientes(clientes, totalClientes);
                            
                            blueMessage("ID Cliente: ");
                            scanf("%[^\n]", idEntrada);
                            getchar();

                            system(CLEAR_SCREEN);

                            indiceCliente = encontrarIndiceCliente(idEntrada, clientes, totalClientes);
                            existeCliente = indiceCliente != -1;

                            if (existeCliente) {
                                showMainTitle("Detalhes da conta", "blue");
                                visualizarDetalhesCliente(clientes[indiceCliente]);

                                yellowMessage("Pressione ENTER para voltar\n");
                                getchar();
                                system(CLEAR_SCREEN);
                            }
                            else {
                                strcpy(message, "ID inválido!");
                                strcpy(colorMessage, "red");
                            }
                        }
                        else if (decisao != 2){
                            strcpy(message, "Opção inválida!");
                            strcpy(colorMessage, "red");
                        }   
                    }
                    else {
                        strcpy(message, "Não há clientes cadastrados!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if (decisao == 5) {
                    
                    if (totalClientes > 0) {
                        showMainTitle("Excluir cliente", "red");
                        listarClientes(clientes, totalClientes);

                        blueMessage("ID Cliente: ");
                        scanf("%[^\n]", idEntrada);
                        getchar();

                        system(CLEAR_SCREEN);

                        indiceCliente = encontrarIndiceCliente(idEntrada, clientes, totalClientes);
                        existeCliente = indiceCliente != -1;

                        if (existeCliente) {
                            permitirAcessoAdm = confirmarComCredenciais(admLogado->id, admLogado->senha);

                            if (permitirAcessoAdm) {
                                removerCliente(clientes, indiceCliente);
                                totalClientes--;
                                
                                strcpy(message, "Cliente removido!");
                                strcpy(colorMessage, "green");
                            }
                            else {
                                strcpy(message, "ID ou senha inválidos!");
                                strcpy(colorMessage, "red");
                            }
                        }
                        else {
                            strcpy(message, "ID inválido!");
                            strcpy(colorMessage, "red");
                        }
                    }
                    else {
                        strcpy(message, "Não há clientes cadastrados!");
                        strcpy(colorMessage, "red");
                    }

                }
                else if (decisao == 6) {
                    strcpy(message, "Saiu da conta!");
                    strcpy(colorMessage, "red");
                }
                else {
                    strcpy(message, "Opção inválida!");
                    strcpy(colorMessage, "red");
                }
            }
        }
        else if (permitirAcessoCliente) {

            while (decisao != 4) {
                showMainTitle("Cliente", "blue");
                showSubtitle(clienteLogado->nome, "blue");
                showSubtitle(message, colorMessage);

                blueMessage("[1] "); printf("Comprar produtos\n");
                blueMessage("[2] "); printf("Meus pedidos\n");
                blueMessage("[3] "); printf("Adicionar créditos\n");
                blueMessage("[4] "); printf("Sair da conta\n\n");

                yellowMessage("Crédito: ");
                printf("%.2f\n\n", clienteLogado->credito);

                scanf("%d", &decisao);
                strcpy(message, "");
                getchar();

                system(CLEAR_SCREEN);

                if (decisao == 1) {
                    if (totalProdutos > 0) {
                        showMainTitle("Comprar produtos", "blue");
                        listarProdutos(produtos, totalProdutos);
                        blueMessage("Cód. produto (-1 para sair): ");
                        scanf("%[^\n]", codCompra);
                        strcpy(message, "");
                        getchar();

                        system(CLEAR_SCREEN);

                        if (decisao != -1) {
                            indiceProduto = encontrarIndiceProduto(codCompra, produtos, totalProdutos);
                            existeProduto = indiceProduto != -1;

                            if (existeProduto) {
                                precoProduto = produtos[indiceProduto].preco;

                                if (clienteLogado->credito >= precoProduto) {
                                    permitirAcessoCliente = confirmarComCredenciais(clienteLogado->id, clienteLogado->senha);

                                    if (permitirAcessoCliente) {
                                        novoProduto = produtos[indiceProduto];

                                        comprarProduto(novoProduto, clienteLogado->produtosComprados, clienteLogado->totalComprados);
                                        clienteLogado->totalComprados += 1;


                                        clienteLogado->credito -= novoProduto.preco;
                                        
                                        strcpy(message, "Produto adquirido!");
                                        strcpy(colorMessage, "green");
                                    }
                                    else {
                                        strcpy(message, "ID ou senha inválidos!");
                                        strcpy(colorMessage, "red");
                                    }
                                }
                                else {
                                    strcpy(message, "Créditos insuficientes!");
                                    strcpy(colorMessage, "red");
                                } 
                            }
                            else {
                                strcpy(message, "ID inválido!");
                                strcpy(colorMessage, "red");
                            }
                        }
                        else if (decisao == -1) {
                            strcpy(message, "Compra cancelada!");
                            strcpy(colorMessage, "red");
                        }
                    }
                    else {
                        strcpy(message, "Não há produtos cadastrados!");
                        strcpy(colorMessage, "red");
                    }
                } 
                else if (decisao == 2) {
                    if (clienteLogado->totalComprados > 0) {
                        showMainTitle("Produtos comprados", "blue");
                        listarProdutos(clienteLogado->produtosComprados, clienteLogado->totalComprados);
                        
                        yellowMessage("Pressione ENTER para voltar\n");
                        getchar();
                        system(CLEAR_SCREEN);
                    }
                    else {
                        strcpy(message, "Nenhum produto comprado!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if (decisao == 3) {
                    system(CLEAR_SCREEN);

                    permitirAcessoCliente = confirmarComCredenciais(clienteLogado->id, clienteLogado->senha);

                    if (permitirAcessoCliente){
                        showMainTitle("Adiconar créditos", "blue");
                        showSubtitle("Adicione créditos realizar compras", "blue");

                        blueMessage("Informe valor: ");
                        scanf("%f", &credito);
                        strcpy(message, "");

                        system(CLEAR_SCREEN);

                        if (ehCreditoValido(credito)) {
                            clienteLogado->credito += credito;

                            strcpy(message, "Crédito adicionado!");
                            strcpy(colorMessage, "green");
                        }
                        else {
                            strcpy(message, "Valor inválido!");
                            strcpy(colorMessage, "red");
                        }
                    }
                    else {
                        strcpy(message, "ID ou senha inválidos!");
                        strcpy(colorMessage, "red");
                    }
                }
                else if (decisao == 4) {
                    strcpy(message, "Saiu da conta!");
                    strcpy(colorMessage, "red");
                }
                else {
                    strcpy(message, "Opção inválida!");
                    strcpy(colorMessage, "red");
                }
            }

            decisao = 0;              
        }    
    }
    
    return 0;
}

//funções de interface
void showMainTitle(char title[], char titleColor[]) {
    printf("---------------------------------------------\n\n");
    showColorfulText(title, titleColor);
    printf("\n---------------------------------------------\n");
}

void showSubtitle(char message[], char colorMessage[]) {
    showColorfulText(message, colorMessage);
    printf("---------------------------------------------\n");
}

void showColorfulText(char text[], char color[]) {
    if (strcmp(color, "red") == 0) {
        printf("\033[31m%s\033[0m\n", text);
    }
    else if (strcmp(color, "green") == 0) {
        printf("\033[32m%s\033[0m\n", text);
    }
    else if (strcmp(color, "blue") == 0) {
        printf("\033[34m%s\033[0m\n", text);
    }
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

void separar() {
    printf("---------------------------------------------\n");
}

//funções flags
int confirmarComCredenciais(char idEntrada[], char senhaEntrada[]) {
    int idValido, senhaValida, permitirAcesso;

    showMainTitle("Confirmar credenciais", "blue");
        
    idValido = validarId(idEntrada);
    senhaValida = validarSenha(senhaEntrada);
    
    permitirAcesso = idValido && senhaValida;
    
    system(CLEAR_SCREEN);

    return permitirAcesso;
}

int validarId(char idEntrada[]) {
    char idLogin[30];

    blueMessage("ID: ");
    scanf("%[^\n]", idLogin);
    getchar();

    return compararStrings(idEntrada, idLogin);
}

int validarSenha(char senhaEntrada[]) {
    char senhaLogin[30];

    blueMessage("Senha: ");
    scanf("%[^\n]", senhaLogin);
    getchar();

    return compararStrings(senhaEntrada, senhaLogin);
}

int ehCreditoValido(float valor) {
    return valor >= 0;
}

int compararStrings(char str1[], char str2[]) {
    return strcmp(str1, str2) == 0;
}

//funções de adm
Administrador criarAdministrador() {
    Administrador novoAdm;
    
    blueMessage("Id: ");
    scanf("%[^\n]", novoAdm.id);
    getchar();

    blueMessage("Nome: ");
    scanf("%[^\n]", novoAdm.nome);
    getchar();

    blueMessage("Senha: ");
    scanf("%[^\n]", novoAdm.senha);
    getchar();
  
    return novoAdm;
}

int verificacaoIdAdm(char idEntrada[], Administrador adms[], int totalAdms) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalAdms) && (validacao == FALSE)) {
        if (compararStrings(adms[i].id, idEntrada)) {
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
        if (compararStrings(adms[i].senha, senhaEntrada)) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

int encontrarIndiceAdm(char idEntrada[], Administrador adms[], int totalAdms) {
    int indice = -1;
    int i = 0;

    while ((i < totalAdms) && (indice == -1)) {
        if (compararStrings(adms[i].id, idEntrada)) {
            indice = i;
        }
        i++;
    }
    
    return indice;
}

//funções de clientes
Cliente criarCliente() {
    Cliente novoCliente;
    
    blueMessage("Id: ");
    scanf("%[^\n]", novoCliente.id);
    getchar();

    blueMessage("Nome: ");
    scanf("%[^\n]", novoCliente.nome);
    getchar();

    blueMessage("Senha: ");
    scanf("%[^\n]", novoCliente.senha);
    getchar();

    novoCliente.credito = 0;
    novoCliente.totalComprados = 0;
  
    return novoCliente;
}

int verificacaoIdCliente(char idEntrada[], Cliente clientes[], int totalClientes) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalClientes) && (validacao == FALSE)) {
        if (compararStrings(clientes[i].id, idEntrada)) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

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

void removerCliente(Cliente clientes[], int indice) {
    Cliente clienteCopia;
    int i = indice + 1;

    if (clientes[i].nome[0] != '\0') {
        while (clientes[i].nome[0] != '\0') {
            clienteCopia = clientes[i];
            clientes[i-1] = clienteCopia;
            i++;
        }

        resetarCliente(&clientes[i]);
    }
    else {
        resetarCliente(&clientes[indice]);
    }
}

void resetarCliente(Cliente *cliente) {
    strcpy(cliente->id, "\0");
    strcpy(cliente->nome, "\0");
    strcpy(cliente->senha, "\0");
    cliente->credito = 0;
}

void listarClientes(Cliente clientes[], int totalClientes) {
    for (int i = 0; i < totalClientes; i++) {
        printf("Id: %s\n", clientes[i].id);
        printf("Nome: %s\n", clientes[i].nome);
        separar();
    }   
}

void visualizarDetalhesCliente(Cliente cliente) {
    printf("Id: %s\n", cliente.id);
    printf("Nome: %s\n", cliente.nome);
    printf("Senha: %s\n", cliente.senha);
    printf("Crédito: %.2f\n\n", cliente.credito);
    printf("Comprados (%d):\n\n", cliente.totalComprados);
    listarProdutos(cliente.produtosComprados, cliente.totalComprados);
}

int encontrarIndiceCliente(char idEntrada[], Cliente clientes[], int totalClientes) {
    int indiceCliente = -1;
    int i = 0;

    while ((i < totalClientes) && (indiceCliente == -1)) {
        if (compararStrings(clientes[i].id, idEntrada)) {
            indiceCliente = i;
        }
        i++;
    }
    
    return indiceCliente;
}

//funções produtos
Produto criarProduto() {
    Produto produto;

    blueMessage("Código: ");
    scanf("%[^\n]", produto.codigo);
    getchar();

    blueMessage("Nome: ");
    scanf("%[^\n]", produto.nome);
    getchar();

    blueMessage("Preço: ");
    scanf("%f", &produto.preco);
    getchar();

    return produto;
}

//melhorar função
void comprarProduto(Produto produto, Produto produtosComprados[], int indice) {
    produtosComprados[indice] = produto;
}

void removerProduto(Produto produtos[], int indice) {
    Produto copiaProduto;
    int i = indice + 1;

    if (produtos[i].nome[0] != '\0') {
        while (produtos[i].nome[0] != '\0') {
            copiaProduto = produtos[i];
            produtos[i-1] = copiaProduto;
            i++;
        }

        resetarProduto(&produtos[i]);
    }
    else {
        resetarProduto(&produtos[indice]);
    }       
}

void resetarProduto(Produto *produto) {
    strcpy(produto->codigo, "\0");
    strcpy(produto->nome, "\0");
    produto->preco = 0.0;
}

int encontrarIndiceProduto(char codEntrada[], Produto produtos[], int totalProdutos) {
    int indice = -1;
    int i = 0;

    while ((i < totalProdutos) && (indice == -1)) {
        if (compararStrings(produtos[i].codigo, codEntrada)) {
            indice = i;
        }
        i++;
    }
    
    return indice;
}

void listarProdutos(Produto produtos[], int totalProdutos) {
    for (int i = 0; i < totalProdutos; i++) {
        printf("Código: %s\n", produtos[i].codigo);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preço: %.2f\n", produtos[i].preco);
        separar();
    }
    
}

int ehCodigoExistente(char codEntrada[], Produto produtos[], int totalProdutos) {
    int validacao = FALSE;
    int i = 0;
    while ((i < totalProdutos) && (validacao == FALSE)) {
        if (compararStrings(produtos[i].codigo, codEntrada)) {
            validacao = TRUE;
        }

        i++;
    }

    return validacao;
}

void cadastrarProduto(Produto produtos[], int indice, Produto produto) {
    produtos[indice] = produto;
}