#ifndef MENUS_FATURA_H_INCLUDED
#define MENUS_FATURA_H_INCLUDED

int menuFatura()// Função que imprime menu para gerenciar a aba de faturas
{
    topoMenu("Menu de faturas");
    printf("  1 - Inserir novas faturas\n");
    printf("  2 - Alterar dados de uma fatura\n");
    printf("  3 - Excluir uma fatura\n");
    printf("  4 - Buscar uma fatura\n");
    printf("  5 - Mostrar todas as faturas\n");
    printf("  ----------------------\n");
    printf("  0 - Voltar menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

void menuMostrarTodasFaturas(listaFatura listaF,listaClientes listaC) // Função que imprime todas as faturas
{
    topoMenu("MOSTRAR FATURAS");
    mostraFaturaLista(listaF, listaC);
    printf("\n\n  Pressione <enter> para voltar ao Menu de faturas.");
    fflush(stdin);
    getchar();
}

void menuInserirFatura(listaFatura *listaF, listaClientes listaC)// Função para inserir uma fatura na lista
{
    topoMenu("INSERIR FATURA");
    TFatura fatura = criarFatura(listaC, listaF->numeroFaturas);
    if(confirmar()){
        addFaturaLista(listaF, fatura);
        printf("\n  Fatura criada com sucesso ");
        Sleep(1000);
    }
    else{
        printf("\n  Cancelando... ");
        Sleep(1000);
    }
}

char menuAUXtipoDadoBuscaFatura() // Função que imprime um menu auxiliar para buscar fatura
{
    printf("      0 - Sair\n");
    printf("      1 - N%cmero da fatura\n", 163);
    printf("      2 - C\xa2 \bdigo do cliente\n");
    printf("      3 - Vencimento da fatura\n");
    printf("      C\xa2 \bdigo: ");
    fflush(stdin);
    return getchar();
}

char menuAUXtipoDadoFatura() // Função que imprime um menu auxiliar para buscar fatura
{
    printf("      0 - Sair\n");
    printf("      1 - N%cmero da fatura\n", 163);
    printf("      2 - C\xa2 \bdigo do cliente\n");
    printf("      3 - Vencimento da fatura\n");
    printf("      4 - Valor da fatura\n");
    printf("      C\xa2 \bdigo: ");
    fflush(stdin);
    return getchar();
}

int menuAUXtipoDeBuscaFatura(listaFatura listaF, listaClientes listaC, const char *nomeMenu) // Função que imprime um menu auxiliar para buscar fatura
{
    char menu;
    int indice;
    unsigned int codigoAux;
    topoMenu(nomeMenu);
    printf("  Que dado deseja utilizar para buscar a fatura?\n");
    while(1){
        menu = menuAUXtipoDadoBuscaFatura();
        if(menu == '0'){
            printf("\n  Saindo da busca.\n  Voltando para: Menu de faturas.");
            Sleep(1000);
            return -1;
        }
        switch(menu){
            case '1':
                indice = buscarFaturaNumero(listaF, listaC);
                break;
            case '2':
                printf("  Qual o c\xa2 \bdigo do cliente que voc\x88 deseja buscar? ");
                scanf("%d", &codigoAux);
                indice = buscarFaturaCliente(listaF, listaC, codigoAux);
                break;
            case '3':
                indice = buscarFaturaVencimento(listaF, listaC);
                break;
            default:
                topoMenu(nomeMenu);
                printf("  C\xa2 \bdigo inv%clido. Por favor, colocar uma das opc%ces abaixo:\n", 160, 228);
                continue;
        }
        if(indice == -1){
            topoMenu(nomeMenu);
            printf("  Fatura n%co encontrada.\n Por favor, selecionar uma das op%c%ces abaixo:\n", 162, 145, 228);
            continue;
        }
        return indice;
    }
}

void menuAlterarDadosFatura(listaFatura *listaF, listaClientes listaC, int permicaoUsuario)// Função que imprime um menu para alterar dados de uma fatura
{
    int indice;
    char menu;
    topoMenu("ALTERAR DADOS DE UMA FATURA");
    if(!verificarPermicao(listaC, permicaoUsuario, "ALTERAR DADOS DE UMA FATURA")){
        return;
    }
    indice = menuAUXtipoDeBuscaFatura(*listaF, listaC,"ALTERAR DADOS DE UMA FATURA");
    if(indice == -1){
        return;
    }
    TFatura fatura = listaF->faturas[indice];
    while(1){
        topoMenu("ALTERAR DADOS DE UMA FATURA");
        printf("    ");
        mostrarFatura(fatura, listaC);
        printf("\n\n  Qual dado voc%c deseja alterar?\n", 136);
        while(1){
            menu = menuAUXtipoDadoFatura();
            if(menu == '0'){
                if(confirmar()){
                    listaF->faturas[indice] = fatura;
                }
                printf("\n  Saindo da altera%c%co.\n  Voltando para: Menu de fatura.\n", 135, 198);
                Sleep(1000);
                return;
            }
            switch(menu){
                case '1':
                    modificarFaturaNumero(&fatura);
                    break;
                case '2':
                    modificarFaturaCliente(&fatura, listaC);
                    break;
                case '3':
                    modificarFaturaVencimento(&fatura);
                    break;
                case '4':
                    modificarFaturaValorNominal(&fatura);
                    break;
                default:
                    topoMenu("ALTERAR DADOS DE UMA FATURA");
                    mostrarFatura(fatura, listaC);
                    printf("\n\n  C\xa2 \bdigo n%co encontrado. Selecione um dos c%cdigos abaixo.\n", 198, 162);
                    continue;
            }
            break;
        }
    }
}

void menuExcluirFaturaLista(listaFatura *listaF, listaClientes listaC) // Função que exclui uma fatura da lista
{
    int indice;
    topoMenu("EXCLUIR UMA FATURA");
    indice = menuAUXtipoDeBuscaFatura(*listaF, listaC,"EXCLUIR UMA FATURA");
    if(indice == -1){
        return;
    }
    printf("\n     ");
    mostrarFatura(listaF->faturas[indice], listaC);
    if(confirmar()){
        excluiFaturaLista(listaF, indice);
        printf("\n  Exclus%co realizada.\n  Voltando para: Menu de faturas.", 198);
        Sleep(1000);
    }
    else{
        printf("\n  Exclus%co cancelada.\n  Voltando para: Menu de faturas.", 198);
        Sleep(1000);
    }
}

void menuBuscarFatura(listaFatura listaF, listaClientes listaC) // Função que busca uma fatura da lista
{
    topoMenu("BUSCAR UMA FATURA");
    int indice;
    indice = menuAUXtipoDeBuscaFatura(listaF, listaC,"BUSCAR UMA FATURA");
    if(indice ==-1){
        return;
    }
    topoMenu("BUSCAR UMA FATURA");
    printf("    ");
    mostrarFatura(listaF.faturas[indice], listaC);
    printf("\n\n  Pressione <enter> para voltar ao Menu de faturas.");
    fflush(stdin);
    getchar();
}


#endif // MENUS_FATURA_H_INCLUDED
