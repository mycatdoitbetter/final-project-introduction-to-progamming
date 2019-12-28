#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include <stdlib.h>

char menuPrincipal() // Função para imprimir as opções do menu principal
{
    system("cls");
    printf("\n");
    caracteres(66, '='); printf("\n");
    printc("SISTEMA DE FATURAS", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    printf("  1 - Aba do cliente\n");
    printf("  2 - Aba de Faturas\n");
    printf("  3 - Emiss%co de relat%crios\n", 198, 162);
    printf("  4 - Pagamento\n");
    printf("  ----------------------\n");
    printf("  0 - Sair do Aplicativo\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

char menuCliente()// Função para imprimir as opções do menu do cliente.
{
    system("cls");
    printf("\n");
    caracteres(66, '='); printf("\n");
    printc("MENU DO CLIENTE", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    printf("  1 - Inserir novos clientes\n");
    printf("  2 - Alterar dados de um cliente\n");
    printf("  3 - Excluir um cliente\n");
    printf("  4 - Buscar um cliente\n");
    printf("  ----------------------\n");
    printf("  0 - Voltar menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

void menuInserirCliente(listaClientes *lista) // Função para imprimir as opções do menu inserir cliente
{
    system("cls");
    printf("\n");
    caracteres(66, '='); printf("\n");
    printc("Inserir Cliente", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    addClienteLista(lista, criarCliente());
}

char menuAUXtipoDadoCliente() // Função para imprimir as opções do menu de busca com dados do cliente.
{
    printf("      0 - Sair\n");
    printf("      1 - C\xa2 \bdigo do cliente\n");
    printf("      2 - Nome do Cliente\n");
    printf("      3 - CPF do cliente\n");
    printf("      C\xa2 \bdigo: ");
    fflush(stdin);
    return getchar();
}

int menuAUXtipoDeBusca(listaClientes lista, const char *nomeMenu)// Função para imprimir as opções do menu de busca do cliente
{
    char menu;
    int indice;
    printf("  Que dado deseja utilizar para buscar o cliente?\n");
    while(1){
        menu = menuAUXtipoDadoCliente();
        printf("\n");
        if(menu == '0'){
            printf("  Saindo da busca.\n  Voltando para: Menu do Cliente.");
            Sleep(4000);
            return -1;
        }
        switch(menu){
            case '1':
                indice = buscarClienteCodigo(lista);
                break;
            case '2':
                indice = buscarClienteNome(lista);
                break;
            case '3':
                indice = buscarClienteCPF(lista);
                break;
            default:
                system("cls");
                caracteres(66, '='); printf("\n");
                printc(nomeMenu, 66);  printf("\n");
                caracteres(66, '='); printf("\n");
                printf("  C\xa2 \bdigo invalido.\n Por favor, coloque uma das op\xe4 \bes abaixo:\n");
                continue;
        }
        if(indice == -1){
            system("cls");
            caracteres(66, '='); printf("\n");
            printc(nomeMenu, 66);  printf("\n");
            caracteres(66, '='); printf("\n");
            printf("  Cliente n\xc6o encontrado.\n Por favor recelecionar uma das op\xe4 \bes abaixo:\n");
            continue;
        }
        return indice;
    }
}

void menuAlterarDadosCliente(listaClientes *lista)// Função para imprimir as opções de alteração de dados e alterar os dados do cliente.
{
    int indice;
    char menu;
    printf("\n");
    system("cls");
    caracteres(66, '='); printf("\n");
    printc("ALTERAR DADOS DO CLIENTE", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    indice = menuAUXtipoDeBusca(*lista, "ALTERAR DADOS DO CLIENTE");
    if(indice == -1){
        return;
    }
    while(1){
        system("cls");
        caracteres(66, '='); printf("\n");
        printc("ALTERAR DADOS DO CLIENTE", 66);  printf("\n");
        caracteres(66, '='); printf("\n");
        printf("\n     ");
        mostrarCliente(lista->clientes[indice]);
        printf("\n");
        printf("  Que dado voc\x88 deseja alterar do cliente?\n");
        menu = menuAUXtipoDadoCliente();
        if(menu == '0'){
            printf("  Saindo da altera%c%co.\n  Voltando para: Menu do Cliente.\n", 135, 198);
            Sleep(4000);
            break;
        }
        switch(menu){
            case '1':
                modificarCodigo(&lista->clientes[indice]);
                break;
            case '2':
                modificarNome(&lista->clientes[indice]);
                break;
            case '3':
                modificarCPF(&lista->clientes[indice]);
                break;
            default:
                printf("  C\xa2 \bdigo n%co encontrado\n", 198);
                continue;
        }
    }
}

void menuExcluirClienteLista(listaClientes *lista) // Função para imprimir menu de exclusão e excluir um cliente
{
    int indice;
    system("cls");
    caracteres(66, '='); printf("\n");
    printc("EXCLUIR UM CLIENTE", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    indice = menuAUXtipoDeBusca(*lista, "EXCLUIR UM CLIENTE");
    if(indice == -1){
        return;
    }
    excluiClienteLista(lista, indice);
    printf("\n  Exclus%co realizada. Voltando para: Menu do Cliente.", 198);
    Sleep(4000);
}

void menuBuscarCliente(listaClientes lista) // Função que gera menu de busca de um cliente.
{
    int indice;
    system("cls");
    caracteres(66, '='); printf("\n");
    printc("BUSCANDO UM CLIENTE", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    indice = menuAUXtipoDeBusca(lista, "BUSCANDO UM CLIENTE");
    system("cls");
    caracteres(66, '='); printf("\n");
    printc("BUSCANDO UM CLIENTE", 66);  printf("\n");
    caracteres(66, '='); printf("\n");
    printf("     ");
    mostrarCliente(lista.clientes[indice]);
    printf("\n\n  Pressione <enter> para voltar ao Menu do Cliente.");
    fflush(stdin);
    getchar();
}





#endif // MENUS_H_INCLUDED
