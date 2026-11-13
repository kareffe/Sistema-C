#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//constantes
#define max_clientes 20
#define max_chamados 30
#define status_aberto "Aberto"
#define status_fechado "Fechado"

//estruturas (cliente e chamado)
typedef struct {
    int id;
    char nome[50];
    char telefone[50];
    char email[50];
} Cliente;

typedef struct {
    int id;
    char titulo[50];
    char descricao[200];
    int idCliente;
    char status[10];
} Chamado;

//variaveis globais (Vetores/Arrays)
Cliente clientes[max_clientes];
Chamado chamados[max_chamados];

int totalClientes = 0;
int totalChamados = 0;

//protótipos
void limparTela(void);
void pause(void);
void telaApresentacao(void);
void exibirMenu(void);
void cadastrarCliente(void);
void listarClientes(void);
void abrirChamado(void);
void listarChamados(void);
void listarChamadosPorStatus(void);
void fecharChamado(void);

//função principal
int main(void) {
    int opcao;

    telaApresentacao();

    //menu sendo rodado até o usuário escolher a opcao 0
    do {
        limparTela();   //limpa a tela antes de mostrar o menu
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            opcao = 0;  //entrada invalida ou fim de arquivo = encerra o programa
        } else {
            getchar();  //limpa o \n deixado pelo scanf
        }

        limparTela();

        //definindo as opcoes
        switch (opcao) {
            case 1: cadastrarCliente();        pause(); break;
            case 2: listarClientes();          pause(); break;
            case 3: abrirChamado();            pause(); break;
            case 4: listarChamados();          pause(); break;
            case 5: listarChamadosPorStatus(); pause(); break;
            case 6: fecharChamado();           pause(); break;
            case 0: printf("\nEncerrando o sistema\n"); break;
            default: printf("\nOpcao invalida!\n"); pause();
        }

    } while (opcao != 0);

    return 0;
}

//limpando a tela (poliemnto visual)
void limparTela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//espera o usuario querer dar continuidade depois da apresentacao
void pause(void) {
    printf("\nPressione Enter para continuar...");
    getchar();
}

//tela inicial com a apresentação do grupo
void telaApresentacao(void) {
    limparTela();
    printf("\n=====================================\n");
    printf("     Apresentação do grupo:\n");
    printf("=====================================\n");
    printf("Lider do Projeto:  - Site do Sistema(Front-End e Documentação)\n");
    printf("Graziele Silva de Lima Sampaio - Site do sistema (Front-End)\n");
    printf("Matheus Henrique Silva Nunes - Sistema em C\n");
    printf("Kauan Reis Fernandes - Sistema em C\n");
    printf("Manoella Assenza de Santana - Modelagem do Banco De Dados\n");
    printf("Laura da Silva Brandão - Desenvolvimento do Banco de Dados (Scripts SQL)\n");
    printf("Guilherme da Silva dos Santos - Criação do Pitch (Apresentação do projeto)\n");
    pause();
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

//função para cadastro de cliente
void cadastrarCliente(void) {

    //caso o limite seja atingido
    if (totalClientes >= max_clientes) {
        printf("\nTotal de clientes atingido!\n");
    } else {
        //caso o limite nao seja atingido = cadastre
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

        clientes[totalClientes] = novo; //inserindo o cliente no array dos clientes
        totalClientes++;

        printf("\nCliente cadastrado com sucesso! (ID %d)\n", novo.id);
    }
}

//função para listar os clientes cadastrados
void listarClientes(void) {

    //caso nenhum cliente esteja cadastrado
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    //mostrando os clientes no sistema
    printf("\n Lista clientes\n");

    for (int i = 0; i < totalClientes; i++) {
        printf("ID %d | Nome: %-20s | Tel: %-15s | E-mail: %s\n",
               clientes[i].id, clientes[i].nome,
               clientes[i].telefone, clientes[i].email);
    }
}

//abrir um chamado no sistema
void abrirChamado(void) {

    //informando ao usuario para cadastrar um cliente antes de abrir algum chamado
    if (totalClientes == 0) {
        printf("\nCadastre um cliente antes de abrir um chamado. \n");
        return;
    }
    //caso o limite de chamados seja atingido
    if (totalChamados >= max_chamados) {
        printf("\nLimite de chamados atingido!\n");
        return;
    }

    //chamando a função de listar os clientes
    listarClientes();

    //pedindo as informações (ID) do cliente responsável pelo chamado
    int idCliente;
    printf("\nDigite o ID do cliente para este chamado: ");
    scanf("%d", &idCliente);
    getchar();

    //caso o ID seja inválido ou 0, o sistema barra a consulta
    if (idCliente < 1 || idCliente > totalClientes) {
        printf("\nCliente invalido!\n");
        return;
    }

    //abrindo o chamado
    Chamado novo;
    novo.id = totalChamados + 1;
    novo.idCliente = idCliente;
    strcpy(novo.status, status_aberto);

    //informando as informações do chamado
    printf("\nTitulo do chamado: ");
    fgets(novo.titulo, sizeof(novo.titulo), stdin);
    novo.titulo[strcspn(novo.titulo, "\n")] = '\0';

    printf("\nDescreva o problema: ");
    fgets(novo.descricao, sizeof(novo.descricao), stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    chamados[totalChamados] = novo; //armazenando o chamado no array de chamados
    totalChamados++;

    //chamado aberto/armazenado no sistema
    printf("\nChamado aberto com sucesso! (ID %d)\n", novo.id);
}

//exibe todos os chamados registrados no sistema
void listarChamados(void) {

    //caso não haja nenhum chamado cadastrado
    if (totalChamados == 0) {
        printf("\nNenhum chamado cadastrado.\n");
        return;
    }

    //mostrando a lista dos chamados
    printf("\nLista de chamados\n");

    //buscando o dono do chamado e informando sobre o chamado
    int i = 0;
    while (i < totalChamados) {
        Cliente dono = clientes[chamados[i].idCliente - 1]; //acessando o cliente dono do chamado
        printf("ID %d | Cliente: %-15s | Titulo: %-20s | Status: %s\n",
               chamados[i].id, dono.nome, chamados[i].titulo, chamados[i].status);
        i++;
    }
}

//exibe os chamados filtrados pelo status (aberto ou fechado)
void listarChamadosPorStatus(void) {
    if (totalChamados == 0) {
        printf("\nNenhum chamado cadastrado.\n");
        return;
    }

    //mostrando ao usuario caso ele queira ver os chamados ativos ou que ja foram fechados
    int opcaoStatus;
    printf("\n1 - Ver chamados abertos\n2 - Ver chamados fechados\nEscolha: ");
    scanf("%d", &opcaoStatus);
    getchar();

    char statusFiltro[10];

    //filtrando pela opção do usuario
    if (opcaoStatus == 1) {
        strcpy(statusFiltro, status_aberto);
    } else if (opcaoStatus == 2) {
        strcpy(statusFiltro, status_fechado);
    } else {
        printf("\nOpção invalida!\n");
        return;
    }

    int encontrados = 0;
    printf("\nChamados %s \n", statusFiltro);

    //percorrendo o array de chamados para conferir pela opção, quais os chamados o usuario decidiu ver
    for (int i = 0; i < totalChamados; i++) {
        if (strcmp(chamados[i].status, statusFiltro) == 0) {
            printf("ID %d | Titulo: %s\n", chamados[i].id, chamados[i].titulo);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("\nNenhum chamado com esse status.\n");
    }
}

//fechando um chamado no sistema
void fecharChamado(void) {
    if (totalChamados == 0) {
        printf("\nNenhum chamado cadastrado.\n");
        return;
    }

    //chama a função para listar os chamados para o usuario conseguir saber qual ira fechar
    listarChamados();

    //usuario escolhe qual ele quer fechar
    int id;
    printf("\nDigite o ID do chamado que deseja fechar: ");
    scanf("%d", &id);
    getchar();

    int encontrado = 0;

    //define o status do chamado como fechado atraves do ID
    for (int i = 0; i < totalChamados; i++) {
        if (chamados[i].id == id) {
            strcpy(chamados[i].status, status_fechado);
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        printf("\nChamado %d fechado com sucessoi!\n", id);
    } else {
        printf("\nChamado não encontrado.\n");
    }
}
