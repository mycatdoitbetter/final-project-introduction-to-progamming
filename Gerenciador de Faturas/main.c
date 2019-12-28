#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "AUXILIAR.h"
#include "data.h"
#include "CLIENTE.h"
#include "LISTA_CLIENTE.h"
#include "FATURAS.h"
#include "LISTA_FATURA.h"
#include "MENUS_CLIENTE.h"
#include "MENUS_FATURA.h"
#include "MENUS_RELATORIOS.h"
#include "MENUS_PAGAMENTOS.h"

int main()
{
    srand(time(NULL));
    listaClientes listaC = criarClienteLista(); //Criando lista de clientes aleatórios para inicializar o arquivo para salvamento.
    listaFatura listaF = criarFaturaLista(); //Criando lista de faturas aleatórias para inicializar o arquivo para salvamento.
    TCliente cliente;
    TFatura fatura;


    FILE *arquivo; // adicionando variável arquivo para salvamento de dados

    // Alocando dados dos usuários no arquivo "ARQ_USUARIOS".
    arquivo = fopen("ARQ_USUARIOS", "rb");
    while(fread(&cliente, sizeof(TCliente), 1, arquivo)){ addClienteLista(&listaC, cliente); }
    fclose(arquivo);

    // Alocando dados de faturas no arquivo "ARQ_FATURAS".
    arquivo = fopen("ARQ_FATURAS", "rb");
    while(fread(&fatura, sizeof(TFatura), 1, arquivo)){ addFaturaLista(&listaF, fatura); }
    fclose(arquivo);

    // Variáveis de controle do menu.
    int codigo, i, sla, permicao;
    char senha[20], menu;

    // Menu principal.
    while(1){
        while(1){
            sla=0;

            // Menu de Login
            topoMenu("LOGIN DE USU\xb5RIO");
            printc("Bem vindo. Por favor, entre com sua conta.", 66);
            printf("\n");
            printc("Caso n\xc6o possua uma conta digite (-2) no c\xa2 \bdigo para criar uma.", 66);
            printf("\n");
            printc("Digite (-1) no c\xa2 \bdigo para sair.", 66);
            printf("\n\n    C\xa2 \bdigo: ");
            codigo = le_inteiro();

            // Condicionais para identificação de permissão (Administrador, funcionário e cliente)..
            if(codigo == -1){
                printf("\n\n");
                if(confirmar()){
                    arquivo = fopen("ARQ_USUARIOS", "wb");
                    for(i=0;i<listaC.numeroClientes;i++){
                        fwrite(&listaC.clientes[i], sizeof(TCliente), 1, arquivo);
                    }
                    fclose(arquivo);

                    arquivo = fopen("ARQ_FATURAS", "wb");
                    for(i=0;i<listaF.numeroFaturas;i++){
                        fwrite(&listaF.faturas[i], sizeof(TFatura), 1, arquivo);
                    }
                    fclose(arquivo);
                }
                printc("Saindo do aplicativo...", 66);
                Sleep(3000);
                return 0;
            }
            if(codigo == -2){
                addClienteLista(&listaC, criarCliente(listaC.numeroClientes));
                printf("\n  Seu c\xa2 \bdigo de login \x82: %d", listaC.numeroClientes-1);
                Sleep(2000);
                continue;
            }
            printf("\n    Senha: ");
            fflush(stdin);
            gets(senha);

            // Bloco para comparar código e senha do usuário e realizar login.
            for(i=0;i<listaC.numeroClientes;i++){
                if(listaC.clientes[i].codigo == codigo){
                    if(!strcmp(listaC.clientes[i].senha, senha)){
                        printf("\n\n");
                        printc("Login realizado com sucesso!", 66);
                        printf("\n");
                        printc("Bem vindo!", 66);
                        printf("\n");
                        printc(listaC.clientes[i].nome, 66);
                        permicao = listaC.clientes[i].permicao;
                        sla=0;
                        Sleep(2000);
                        break;
                    }
                    else{
                        printf("\n\n    Erro no login.\n    Usu\xa0rio ou senha incorretos.");
                        sla=1;
                        Sleep(2000);
                        continue;
                    }
                }
                if(sla){
                    break;
                }
            }
            if(!sla){
                break;
            }
        }

        // Menus de usuário para Administrador (permissão 2) e funcionário (permissão 1).
        if(permicao == 1 || permicao == 2){
            while(1){
                menu = menuPrincipal(); // variável menu vai gerir as ações dentro do menu principal.
                if(menu == '0'){
                    printf("\n  Saindo de Sistema de faturas.\n  Voltando para: Login.");
                    Sleep(3000);
                    break;
                }
                switch(menu){
                    case '1':
                        while(1){
                            menu = menuCliente(); // variável menu vai gerir as ações dentro do menu do cliente.
                            if(menu == '0'){
                                printf("\n  Saindo do Menu do Cliente.\n  Voltando para: Menu Principal.");
                                Sleep(1000);
                                break;
                            }
                            switch(menu){
                                case '1':
                                    menuInserirCliente(&listaC, permicao); // Função que gera um menu para inserir um novo cliente.
                                    break;
                                case '2':
                                    menuAlterarDadosCliente(&listaC, menuAUXtipoDeBuscaCliente(listaC, "ALTERAR DADOS"), permicao);  /* Função que gera
                                    menu para alteração de dados do cliente.
                                    */
                                    break;
                                case '3':
                                    menuExcluirClienteLista(&listaC); // Função que gera menu para excluir um cliente da lista de clientes.
                                    break;
                                case '4':
                                    menuBuscarCliente(listaC); // Função que gera menu para buscar um cliente a partir de seus dados.
                                    break;
                                case '5':
                                    menuMostrarTodosClientes(listaC); // Função que gera uma lista com todos os clientes e seus dados.
                                    break;
                                default:
                                    printf("\n  C\xa2 \bdigo incorreto", 162);
                            }
                        }
                        break;

                    case '2':
                        while(1){
                            menu = menuFatura(); // variável menu vai gerir as ações dentro do menu de fatura.
                            if(menu == '0'){
                                printf("\n  Saindo do Menu de faturas.\n  Voltando para: Menu Principal.");
                                Sleep(1000);
                                break;
                            }
                            switch(menu){
                                case '1':
                                    menuInserirFatura(&listaF, listaC); // Função que gera menu para inserir uma fatura.
                                    break;
                                case '2':
                                    menuAlterarDadosFatura(&listaF, listaC, permicao); // Função que gera menu para alterar dados de uma fatura.
                                    break;
                                case '3':
                                    menuExcluirFaturaLista(&listaF, listaC); // Função que gera menu para excluir uma fatura.
                                    break;
                                case '4':
                                    menuBuscarFatura(listaF, listaC); // Função que gera menu para buscar uma fatura.
                                    break;
                                case '5':
                                    menuMostrarTodasFaturas(listaF, listaC); // Função que gera uma lista com todas as faturas e seus dados.
                                    break;
                                default:
                                    printf("\n  C\xa2 \bdigo incorreto", 162);
                            }
                        }
                        break;

                    case '3':
                        while(1){
                            menu = menuRelatorio(); // Variável menu vai gerir as ações dentro do menu de relatórios.
                            if(menu == '0'){
                                printf("\n  Saindo do Menu de Relat%crios.\n  Voltando para: Menu Principal.", 162);
                                Sleep(1000);
                                break;
                            }
                            switch(menu){
                                case '1':
                                    while(1){
                                        menu = menuRelatorioFaturas(); // Variável menu vai gerir as ações dentro do relatório de faturas.
                                        if(menu == '0'){
                                            printf("\n  Saindo do Menu de Relat%crios Fatura.\n  Voltando para: Menu de Relat%crios.", 162, 162);
                                            Sleep(1000);
                                            break;
                                        }
                                        switch(menu){
                                            case '1':
                                                menuTodasFaturasAbertas(listaF, listaC); // Função que gera uma lista com todas as faturas em aberto
                                                break;
                                            case '2':
                                                menuFaturasAbertasCliente(listaF, listaC, menuAUXtipoDeBuscaCliente(listaC, "FATURAS EM ABERTO")); /* Função
                                                que gera uma lista com todas as faturas em aberto de um cliente em específico */
                                                break;
                                            case '3':
                                                menuHistoricoFaturasCliente(listaF, listaC, menuAUXtipoDeBuscaCliente(listaC, "HIST\xe0RICO DE FATURAS")); /* Função
                                                que gera uma histórioco de faturas de um cliente em especifico*/
                                                break;
                                            case '4':
                                                menuFaturasAbertasAUmMes(listaF, listaC); // Gera lista com todas as faturas em aberto a mais de um mês.
                                                break;
                                            default:
                                                printf("\n  C\xa2 \bdigo incorreto", 162);
                                        }

                                    }
                                    break;
                                case '2':
                                    while(1){
                                        menu = menuRelatorioCliente(); // Variável menu vai gerir as ações dentro do relatório do cliente.
                                        if(menu == '0'){
                                            printf("\n  Saindo do Menu de Relat%crios de Cliente.\n  Voltando para: Menu de Relat%crios.", 162, 162);
                                            Sleep(1000);
                                            break;
                                        }
                                        switch(menu){
                                            case '1':
                                                menuClientesFaturasAbertas(listaF, listaC); //Lista de clientes com faturas em aberto.
                                                break;
                                            case '2':
                                                menuClientesFaturasAbertasMaisDeUmMes(listaF, listaC); /* Lista de clientes com faturas em aberto a
                                                mais de um mês.
                                                */
                                                break;
                                            default:
                                                printf("\n  C\xa2 \bdigo incorreto");
                                        }
                                    }
                                    break;
                                case '3':
                                    while(1){
                                        menu = menuRelatorioPagamentos(); // Variável menu vai gerir as ações dentro do relatório de pagamentos.
                                        if(menu == '0'){
                                            printf("\n  Saindo do Menu de Relat%crios de Pagamento.\n  Voltando para: Menu de Relat%crios.", 162, 162);
                                            Sleep(1000);
                                            break;
                                        }
                                        switch(menu){
                                            case '1':
                                                menuNotaFatura(listaF, listaC); //Mostra nota de pagamento a partir dos dados de uma fatura.
                                                break;
                                            case '2':
                                                menuReciboFatura(listaF, listaC); // Mostra o recibo de pagamento a partir dos dados de uma fatura.
                                                break;
                                            default:
                                                printf("\n  C\xa2 \bdigo incorreto", 162);
                                        }
                                    }
                                case '4':
                                    relatorioGerais(listaF, listaC); // Gera uma lista com uma relatório geral sobre os clientes e as faturas.
                                    Sleep(500);
                                    break;
                                default:
                                    printf("\n  C\xa2 \bdigo incorreto", 162);
                            }
                        }
                        break;

                    case '4':
                        menuPagamentos(&listaF, listaC); // Menu para pagamento de faturas.
                        break;

                    default:
                        printf("C\xa2 \bdigo inv\xa0lido", 162);
                }
            }
        }
        else if(permicao == 0){
            while(1){
                menu = menuUsuario(); // Variável menu vai gerir as ações dentro do menu do usuário.
                if(menu == '0'){
                    printf("\n  Saindo do Menu de Menu de Usu\xa0rio.\n  Voltando para: Login.");
                    Sleep(1000);
                    break;
                }
                switch(menu){
                    case '1':
                        menuAlterarDadosCliente(&listaC, pegarIndiceUsuario(listaC, codigo), permicao); // Função que permite o cliente alterar seus dados.
                        break;

                    case '2':
                        while(1){
                            menu = menuFaturasUsuario(); // Variável menu vai gerir as ações dentro do menu de faturas do usuário.
                            if(menu == '0'){
                                printf("\n  Saindo do Menu de Faturas.\n  Voltando para: Menu de Usu\xa0rio.");
                                Sleep(1000);
                                break;
                            }
                            switch(menu){
                                case '1':
                                    menuHistoricoFaturasCliente(listaF, listaC, pegarIndiceUsuario(listaC, codigo));// Gera lista de faturas de um cliente.
                                    break;

                                case '2':
                                    menuFaturasAbertasCliente(listaF, listaC, pegarIndiceUsuario(listaC, codigo)); /* Gera lista de faturas em aberto
                                    de um cliente.
                                    */
                                    break;

                                case '3':
                                    menuFaturasVencidasUsuario(listaF, listaC,codigo); // Gera lista de faturas vencidas de um cliente.
                                    break;
                                default:
                                    printf("C\xa2 \bdigo inv\xa0lido");
                            }
                        }
                        break;

                        case '3':
                            relatorioGeraisUsuario(listaF, codigo); // Gera um relatório geral de um cliente
                            break;

                        case '4':
                            menuPagamentosUsuario(&listaF, listaC, codigo); // Aba para pagamento de faturas do cliente.
                            break;

                        default:
                            printf("C\xa2 \bdigo inv\xa0lido", 162);
                }
            }
        }
    }
    return 0;
}
