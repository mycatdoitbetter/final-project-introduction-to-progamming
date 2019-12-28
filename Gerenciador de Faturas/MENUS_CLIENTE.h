#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

char menuPrincipal() // Função que imprime o menu principal do sistema de faturas
{
    topoMenu("SISTEMA DE FATURAS");
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

char menuCliente() // Função que imprime o menu do cliente.
{
    topoMenu("MENU DO CLIENTE");
    printf("  1 - Inserir novos clientes\n");
    printf("  2 - Alterar dados de um cliente\n");
    printf("  3 - Excluir um cliente\n");
    printf("  4 - Buscar um cliente\n");
    printf("  5 - Mostrar todos os clientes\n");
    printf("  ----------------------\n");
    printf("  0 - Voltar menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

void menuMostrarTodosClientes(listaClientes lista) // Função que imprime todos os clientes do sistema.
{
    topoMenu("MOSTRAR CLIENTES");
    mostraClienteLista(lista);
    printf("\n\n  Pressione <enter> para voltar ao Menu do Cliente.");
    fflush(stdin);
    getchar();
}


int verificarPermicao(listaClientes listaC, int permicaoUsuario, char* nomeMenu) // Função que verifica o tipo de permisão durante as ações no aplicativo.
{
    int codigo, i, permicao, sla;
    char senha[20];
    if(permicaoUsuario == 1){
        while(1){
            topoMenu(nomeMenu);
            sla=0;
            printc("Voc\x88 n\xc6o tem acesso para essa fun\x87\xc6o.", 66);
            printf("\n");
            printc("Insira a conta de um admistrados para continuar.", 66);
            printf("\n");
            printc("Digite -1 no c\xa2 \bdigo para sair.", 66);
            printf("\n\n    C\xa0 \bdigo: ");
            codigo = le_inteiro();
            if(codigo == -1){
                printf("\n\n");
                printc("SAINDO...", 66);
                Sleep(3000);
                return 0;
            }
            printf("\n    Senha: ");
            fflush(stdin);
            gets(senha);
            for(i=0;i<listaC.numeroClientes;i++){
                if(listaC.clientes[i].codigo == codigo){
                    if(!strcmp(listaC.clientes[i].senha, senha) && listaC.clientes[i].permicao == 2){
                        printf("\n\n    Login realizado.\n    Bem vindo, %s.", listaC.clientes[i].nome);
                        permicao = listaC.clientes[i].permicao;
                        sla=0;
                        Sleep(2000);
                        break;
                    }
                    else{
                        printf("\n\n    Erro no login.\n    Conta ou Permi\x87\xc6o do usu\xa0rio inv\xa0lida.");
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
    }
    return 1;
}

TCliente criarFuncionario_ADM(listaClientes listaC, unsigned int codigo, int permicaoUsuario) // Função que cria um usuário.
{
    TCliente cliente;
    int codigoCliente;
    char senha[20];
    criarUsuario(&cliente, codigo);
    while(1){
        topoMenu("CRIAR USU\xb5RIO");
        printf("\n  Qual a permi\x87\xc6o do usu\xa0rio?\n    0 - Cliente.\n    1 - Funcion\xa0rio.\n    2 - Administrador.\n    C\xa2 \bdigo: ");
        cliente.permicao = le_inteiro();
        while(cliente.permicao < 0 || cliente.permicao > 2){
                printf("\n    C\xa2 \bdigo incorreto. Informe um dos c\xa2 \bdigos acima: ");
                cliente.permicao = le_inteiro();
        }
        if(cliente.permicao !=0){
            if(verificarPermicao(listaC, permicaoUsuario,  "CRIAR USU\xb5RIO")){
                return cliente;
            }
        }
        else{
            return cliente;
        }
    }
}

void menuInserirCliente(listaClientes *lista, int permicaoUsuario) // Função para inserir um cliente
{
    topoMenu("INSERIR CLIENTES");
    TCliente cliente = criarFuncionario_ADM(*lista, lista->numeroClientes, permicaoUsuario);
    if(confirmar()){
        addClienteLista(lista, cliente);
        printf("\n  Cliente criado.\n  Voltando para: Menu do Cliente.");
        Sleep(1000);
    }
    else{
        printf("\n  Cliente cancelado.\n  Voltando para: Menu do Cliente.");
        Sleep(1000);
    }
}

char menuAUXtipoDadoCliente() // Função que imprime menu de busca pelos dados de um cliente
{
    printf("      0 - Sair\n");
    printf("      1 - C\xa2 \bdigo do cliente\n");
    printf("      2 - Nome do Cliente\n");
    printf("      3 - CPF do cliente\n");
    printf("      C\xa2 \bdigo: ");
    fflush(stdin);
    return getchar();
}

int menuAUXtipoDeBuscaCliente(listaClientes lista, const char *nomeMenu) // Função que busca um cliente pelos seus dados
{
    char menu;
    int indice;
    printf("  Que dado deseja utilizar para buscar o cliente?\n");
    while(1){
        menu = menuAUXtipoDadoCliente();
        if(menu == '0'){
            printf("\n  Saindo da busca.\n  Voltando para: Menu do Cliente.");
            Sleep(1000);
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
                topoMenu(nomeMenu);
                printf("  C\xa2 \bdigo inv\xa0lido. Por favor, colocar uma das op\x87\xe5es abaixo:\n");
                continue;
        }
        if(indice == -1){
            topoMenu(nomeMenu);
            printf("  Cliente n%co encontrado. Por favor, selecionar uma das op%c%ces abaixo:\n", 198, 135, 198);
            continue;
        }
        return indice;
    }
}

void menuAlterarDadosCliente(listaClientes *lista, int indice,int permicao) // Função para alteração de dados de um cliente
{
    char menu;
    if(indice == -1){
        return;
    }
    if(!verificarPermicao(*lista, permicao, "ALTERAR DADOS USU\xb5RIO")){
        return;
    }
    TCliente cliente = lista->clientes[indice];
    while(1){
        topoMenu("ALTERAR DADOS DO USU\xb5RIO");
        printf("\n     ");
        mostrarCliente(cliente);
        printf("\n\n  Qual dado deseja alterar?\n");
        while(1){
            menu = menuAUXtipoDadoCliente();
            if(menu == '0'){
                if(confirmar()){
                lista->clientes[indice] = cliente;
                }
                printf("\n  Saindo da altera%c%co.\n  Voltando para: Menu do Cliente.\n", 135, 198);
                Sleep(1000);
                return;
            }
            switch(menu){
                case '1':
                    modificarClienteCodigo(&cliente, permicao);
                    break;
                case '2':
                    modificarClienteNome(&cliente);
                    break;
                case '3':
                    modificarClienteCPF(&cliente);
                    break;
                default:
                    topoMenu("ALTERAR DADOS DO USU\Xb5RIO");
                    printf("\n     ");
                    mostrarCliente(cliente);
                    printf("\n\n  C\xa2 \bdigo n%co encontrado. Selecione um dos c%cdigos abaixo.\n", 198, 162);
                    continue;
            }
            break;
        }
    }
}

void menuExcluirClienteLista(listaClientes *lista) // Função para excluir um cliente
{
    int indice;
    topoMenu("EXCLUIR CLIENTE");
    indice = menuAUXtipoDeBuscaCliente(*lista, "EXCLUIR CLIENTE");
    if(indice == -1){
        return;
    }
    printf("\n     ");
    mostrarCliente(lista->clientes[indice]);
    if(confirmar()){
        excluiClienteLista(lista, indice);
        printf("\n  Exclus%co realizada.\n  Voltando para: Menu do Cliente.", 198);
        Sleep(1000);
    }
    else{
        printf("\n  Exclus%co cancelada.\n  Voltando para: Menu do Cliente.", 198);
        Sleep(1000);
    }
}

void menuBuscarCliente(listaClientes lista) // Função que busca um cliente
{
    topoMenu("BUSCAR CLIENTE");
    int indice;
    indice = menuAUXtipoDeBuscaCliente(lista, "BUSCAR CLIENTE");
    if(indice==-1){
        return;
    }
    topoMenu("BUSCAR CLIENTE");
    printf("     ");
    mostrarCliente(lista.clientes[indice]);
    printf("\n\n  Pressione <enter> para voltar ao Menu do Cliente.");
    fflush(stdin);
    getchar();
}

// MENUS DO CLIENTE

char menuUsuario() // Menu de gerenciamento de dados do cliente
{
    topoMenu("MENU DO USU\xb5RIO");
    printf("  1 - Alterar dados da conta\n");
    printf("  2 - Suas faturas\n");
    printf("  3 - Relat\xa2rio geral da conta\n");
    printf("  4 - Pagamento\n");
    printf("  ----------------------\n");
    printf("  0 - Sair do Aplicativo\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

int menuFaturasUsuario() // Menu de gerenciamento de faturas do cliente
{
    topoMenu("SUAS FATURAS");
    printf("  1 - Hist\xa2rico de faturas\n");
    printf("  2 - Faturas em aberto\n");
    printf("  3 - Faturas Vencidas\n");
    printf("  ----------------------\n");
    printf("  0 - Voltar para o menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

void menuFaturasVencidasUsuario(listaFatura listaF, listaClientes listaC, unsigned int codigoCliente)// Função que exibe as faturas vencidas de um cliente.
{
    topoMenu("FATURAS VENCIDAS");
    int i, j=0,dataAtual = num_de_dias_desde_1900(data_do_sistema());
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].cliente == codigoCliente && listaF.faturas[i].valorPago == 0.0 &&dataAtual > num_de_dias_desde_1900(listaF.faturas[i].vencimento)){
            printf("\n %d) \n    ", j);
            mostrarFatura(listaF.faturas[i], listaC);
            printf("\n");
            j++;
        }
    }
    if(j==0){
        printc("Nenhuma fatura vencida", 66);
    }
    printf("\n\n  Pressione <enter> para voltar ao Menu do Cliente.");
    fflush(stdin);
    getchar();
}

int pegarIndiceUsuario(listaClientes listaC, unsigned int codigoCliente) // Função que captura o indice de um cliente na lista de clientes.
{
    int i;
    for(i=0;i<listaC.numeroClientes;i++){
        if(listaC.clientes[i].codigo == codigoCliente){
            return i;
        }
    }
    return -1;
}

void relatorioGeraisUsuario(listaFatura listaF, unsigned int codigoCliente)// Função que exibe um relatório geral do usuário
{
    topoMenu("REL\XB5TORIO GERAL");
    int totalFaturas=0;
    int faturaAbertas=0;
    int faturasVencidas=0;
    double valorTotalDevido=0;
    int dataAtual = num_de_dias_desde_1900(data_do_sistema());
    int i;
    char numero[sizeof(unsigned long long)];
    double juros, multa;


    for(i=0;i<listaF.numeroFaturas;i++){
        juros=0;
        multa=0;
        if(listaF.faturas[i].cliente == codigoCliente){
            totalFaturas++;
            if(listaF.faturas[i].valorPago == 0.0){
                faturaAbertas++;
                if(dataAtual > num_de_dias_desde_1900(listaF.faturas[i].vencimento)){
                    faturasVencidas++;
                    multa = listaF.faturas[i].valorNominal *0.02;
                    juros = ((((dataAtual - num_de_dias_desde_1900(listaF.faturas[i].vencimento))/30)+1)*0.01) * listaF.faturas[i].valorNominal;
                }
                valorTotalDevido += listaF.faturas[i].valorNominal + juros + multa;
            }
        }
    }

    div_milhar((unsigned long long)valorTotalDevido, numero);
    printf("\n Total de faturas: %d", totalFaturas);
    printf("\n Total de faturas em aberto: %d", faturaAbertas);
    printf("\n Total de faturas vencidas: %d", faturasVencidas);
    printf("\n Valor total devido: %s,%.2d R$", numero, ((int)(valorTotalDevido*100)%100));

    printf("\n\nPressione <enter> para voltar ao Menu de Usu\xa0rio.");
    fflush(stdin);
    getchar();


}


#endif // MENUS_H_INCLUDED
