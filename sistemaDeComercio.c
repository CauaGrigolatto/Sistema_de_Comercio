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

//funções usuários

void removerUsuario(Usuario usuarios[], int indice);
Usuario copiarUsuario(Usuario usuarios[], int indice);
Usuario criarUsuario();
void cadastrarUsuario(Usuario usuarios[], int indice);
void visualizarUsuarios(Usuario usuarios[], int totalUsuarios);

//funções produtos
void removerProduto(Produto produtos[], int indice);
Produto copiarProduto(Produto produtos[], int indice);
void visualizarProdutos(Produto produtos[], int totalProdutos);
void cadastrarProduto(Produto produtos[], int indice, Produto produto);
Produto criarProduto();
void separar();

int main() {
    Usuario usuarios[100];
    int totalUsuarios = 0;
    
    while (totalUsuarios < 2) {
        cadastrarUsuario(usuarios, totalUsuarios);
        totalUsuarios++;
        separar();
    }
        
    visualizarUsuarios(usuarios, totalUsuarios);
    removerUsuario(usuarios, 0);
    totalUsuarios--;

    printf("Usuário removido\n");
    visualizarUsuarios(usuarios, totalUsuarios);

    return 0;
}

void visualizarUsuarios(Usuario usuarios[], int totalUsuarios) {
    for (int i = 0; i < totalUsuarios; i++) {
        printf("Adm: %d\n", usuarios[i].administrador);
        printf("Id: %d\n", usuarios[i].id);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Senha: %s\n", usuarios[i].senha);
        separar();
    }
    
}

void cadastrarUsuario(Usuario usuarios[], int indice) {
    Usuario novoUsuario = criarUsuario();
    usuarios[indice] = novoUsuario;
}

Usuario criarUsuario() {
    Usuario novoUsuario;
    
    printf("Id: ");
    scanf("%d", &novoUsuario.id);
    getchar();

    printf("Nome: ");
    scanf("%[^\n]", novoUsuario.nome);
    getchar();

    printf("Senha: ");
    scanf("%[^\n]", novoUsuario.senha);
    getchar();

    char isAdm;
    printf("Cadastrar como administrador? (s/n): ");
    scanf("%c", &isAdm);
    getchar();
  
    if (isAdm == 's') {
        novoUsuario.administrador = TRUE;
    }
    else {
        novoUsuario.administrador = FALSE;
    }

    return novoUsuario;
}

void removerUsuario(Usuario usuarios[], int indice) {
    Usuario usuarioCopia;
    int i = indice + 1;

    while (usuarios[i].nome[0] != '\0') {
        usuarioCopia = copiarUsuario(usuarios, i);
        usuarios[i-1] = usuarioCopia;
        i++;
    }
    
    usuarios[i].administrador = 0;
    usuarios[i].id = 0;
    strcpy(usuarios[i].nome, "");
    strcpy(usuarios[i].senha, "");
}

Usuario copiarUsuario(Usuario usuarios[], int indice) {
    Usuario usuarioCopia;

    usuarioCopia.administrador = usuarios[indice].administrador;
    usuarioCopia.id = usuarios[indice].id;
    strcpy(usuarioCopia.nome, usuarios[indice].nome);
    strcpy(usuarioCopia.senha, usuarios[indice].senha);
    
    return usuarioCopia;
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