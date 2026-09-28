#include <stdio.h>
#include <string.h>

//Constantes 

#define max_clientes 20
#define max_chamados 30
#define status_aberto "Aberto"
#define status_fechado "Fechado"

//Estruturas 

typedef struct {
    int id;
    char nome[50];
    char telefone[50];
    char email[50];
}Cliente; 

typedef struct {
    int id;
    char titulo[50];
    char descricao[200];
    int idCliente;
    char status[10];
} Chamado;

//Variaveis Globais (Vetores/Arrays)

Cliente clientes[max_clientes];
Chamado chamados[max_chamados];

int totalClientes = 0;
int totalChamados = 0;
    
//Protótipos

void exibirMenu(void);
void cadastrarCliente(void);
void listarClientes(void);
void abrirChamado(void);
void listarChamados(void);
void listarChamadosPorStatus(void);
void fecharChamado(void);
    
//Função principal 
int main(void) {
    int opcao;
    
    //menu sendo rodado até o usuário escolher a opcao 0 
    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1){
            opcao = 0;  //entradas invalidas ou fim de arquivo = encerra o programa 
        }else {
            getchar(); //limpa o \n deixado pelo scanf
        }
        
        //definindo as opcoes
        switch (opcao){
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: abrirChamado(); break;
            case 4: listarChamados(); break;
            case 5: listarChamadosPorStatus(); break;
            case 6: fecharChamado(); break;
            case 0: printf("\nEncerrando o sistema\n"); break;
        }
        
    }while (opcao != 0);
    
    return 0;
}
//fazendo o menu
void exibirMenu(void) {
    printf("\n===================================\n");
    printf("           Menu principal\n");
    printf("===================================\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Listar clientes\n");
    printf("3 - Abrir chamado\n");
    printf("4 - Listar chamados\n");
    printf("5 - Filtrar chamados por status\n");
    printf("6 - Fechar chamado\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

void cadastrarCliente(void) {
    
    if (totalClientes >= max_clientes){
        printf("\nTotal de clientes atingido!\n");
    }else {
        Cliente novo;
        novo.id = totalClientes + 1;
        
        printf("\nNome do CLiente: ");
        fgets(novo.nome, sizeof(novo.nome), stdin);
        novo.nome[strcspn(novo.nome, "\n")] = '\0';
        
        printf("\nTelefone: ");
        fgets(novo.telefone, sizeof(novo.telefone), stdin);
        novo.telefone[strcspn(novo.telefone, "\n")] = '\0';
        
        printf("\nEmail: ");
        fgets(novo.email, sizeof(novo.email), stdin);
        novo.email[strcspn(novo.email, "\n")] = '\0';
        
        clientes[totalClientes] = novo;
        totalClientes++;
        
        printf("\nCliente cadastrado com sucesso! (ID %d)\n", novo.id);
    }
}

void listarClientes(void) {
    
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }
    
    printf("\n Lista clientes\n");
    
    for (int i = 0; i < totalClientes; i++){
        printf("ID %d | Nome: %-20s | Tel: %-15s | E-mail: %s\n",
              clientes[i].id, clientes[i].nome,
              clientes[i].telefone, clientes[i].email);    
       
    }
}

//Chamados

void abrirChamado(void) {
    
    
    if (totalClientes == 0){
        printf("\nCadastre um cliente antes de abrir um chamado. \n");
        return;
    }
    if (totalChamados >= max_chamados) {
        printf("\nLimite de chamados atingido!\n");
        return;
    }
    
    listarClientes();
    
    int idCliente;
    printf("\nDigite o ID do cliente para este chamado: ");
    scanf("%d", &idCliente);
    getchar();
    
    if (idCliente < 1 || idCliente > totalClientes){
        printf("\nCliente invalido!\n");
        return;
    }
    
    Chamado novo;
    novo.id = totalChamados +1;
    novo.idCliente = idCliente;
    strcpy(novo.status, status_aberto);

    printf("\nTitulo do chamado: ");
    fgets(novo.titulo, sizeof(novo.titulo), stdin);
    novo.titulo[strcspn(novo.titulo, "\n")] = '\0';

    printf("\nDescreva o problema: ");
    fgets(novo.descricao, sizeof(novo.descricao),stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    chamados[totalChamados] = novo; //Armazenando o chamado no array de chamados
    totalChamados++;

    printf("\nChamado aberto com sucesso! (ID %d)\n", novo.id);
}   

void listarChamados(void) {

    if (totalChamados == 0){
        printf("\nNenhum chamado cadastrado.\n");
        return;
    }

    printf("\nLista de chamados\n");

    int i = 0;
    while (i < totalChamados){
        Cliente dono = clientes[chamados[i].idCliente - 1]; //Acessando o cliente dono do chamado
        printf("ID %d | Cliente: %-15s | Titulo: %-20s | Status: %s\n",
            chamados[i].id, dono.nome, chamados[i].titulo, chamados[i].status);
            i++;
    }
}

void listarChamadosPorStatus(void){
    if (totalChamados == 0){
        printf("\nNenhum chamado cadastrado.\n");
        return;
    }

    int opcaoStatus;
    printf("\n1 - Ver chamados abertos\n2 - Ver chamados fechados\nEscolha: ");
    scanf("%d", &opcaoStatus);
    getchar(); //limpando o \n deixado pelo scanf

    char statusFiltro[10];

    if (opcaoStatus == 1){
        strcpy(statusFiltro, status_aberto);
    }else if (opcaoStatus == 2){
        strcpy(statusFiltro, status_fechado);
    }else {
        printf("\nOpção invalida!\n");
        return;
    }

    int encontrados = 0;
    printf("\nChamados %s \n", statusFiltro);

    for (int i = 0; i < totalChamados; i++){
        if (strcmp(chamados[i].status, statusFiltro) == 0){
            printf("ID %d | Titulo: %s\n", chamados[i].id, chamados[i].titulo);
            encontrados++;
        }
    }
    if (encontrados == 0){
        printf("\nNenhum chamado com esse status.\n");
    }
}

void fecharChamado(void){
    if (totalChamados == 0){
        printf("\nNenhum chamado cadastrado.\n");
        return;
    }

    listarChamados();

    int id;
    printf("\nDigite o ID do chamado que deseja fechar: ");
    scanf("%d", &id);
    getchar();

    int encontrado = 0;

    for (int i = 0; i < totalChamados; i++){
        if (chamados[i].id == id){
            strcpy(chamados[i].status, status_fechado);
            encontrado = 1;
            break;
        }
    }

    if (encontrado){
        printf("\nChamado %d fechado com sucessoi!\n", id);
    }else{
        printf("\nChamado não encontrado.\n");
    }
}
