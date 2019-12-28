#ifndef MENUS_RELATORIOS_H_INCLUDED
#define MENUS_RELATORIOS_H_INCLUDED

int menuRelatorio() // Função que imprime o menu de relatórios
{
    topoMenu("MENU DE RELAT\xe0RIOS");
    printf("  1 - Relat%crios de Faturas\n", 162);
    printf("  2 - Relat%crios de Clientes\n", 162);
    printf("  3 - Relat%crios de Pagamentos\n", 162);
    printf("  4 - Relat%crio Geral\n", 162);
    printf("  ----------------------\n");
    printf("  0 - Voltar para o menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

int menuRelatorioFaturas() // Função que imprime menu com relatórios de faturas
{
    topoMenu("RELAT\xe0RIO DE FATURAS");
    printf("  1 - Todas as faturas em aberto\n");
    printf("  2 - Faturas em aberto de um cliente\n");
    printf("  3 - Hist%crico de faturas de um cliente\n", 162);
    printf("  4 - Faturas em aberto h%c mais de 30 dias\n", 160);
    printf("  ----------------------\n");
    printf("  0 - Voltar para o menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

int menuRelatorioCliente() // Função que imprime menu com relatórios de cliente
{
    topoMenu("RELAT\xe0RIO DE FATURAS");
    printf("  1 - Clientes com faturas em aberto\n");
    printf("  2 - Clientes com faturas em aberto h%c mais de 30 dias\n", 160);
    printf("  ----------------------\n");
    printf("  0 - Voltar para o menu principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}

int menuRelatorioPagamentos()// Função que imprime menu com relatórios de pagamento
{
    topoMenu("RELAT\xe0RIO DE PAGAMENTO");
    printf("  1 - Nota de Pagamento\n");
    printf("  2 - Recibo de Pagamento\n");
    printf("  ----------------------\n");
    printf("  0 - Voltar para o menu o principal\n");
    printf("\n  Escolha uma op%c%co: ", 135, 198);
    fflush(stdin);
    return getchar();
}


void menuTodasFaturasAbertas(listaFatura listaF, listaClientes listaC)// Função que imprime todas as faturas em aberto
{
    topoMenu("TODAS AS FATURAS EM ABERTO");
    mostrarFaturasAbertas(listaF, listaC);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuFaturasAbertasCliente(listaFatura listaF, listaClientes listaC, int indice)// Função que imprime todas as faturas em aberto de um cliente
{
    topoMenu("FATURAS EM ABERTO");
    if(indice==-1){
        return;
    }
    topoMenu("FATURAS EM ABERTO");
    mostrarFaturasAbertasCliente(listaF, listaC, listaC.clientes[indice].codigo);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuHistoricoFaturasCliente(listaFatura listaF, listaClientes listaC,int indice)// Função que imprime todas as faturas de um cliente
{
    topoMenu("HIST\xe0RICO DE FATURAS");
    if(indice==-1){
        return;
    }
    topoMenu("HIST\xe0RICO DE FATURAS");
    mostraTodasFaturasCliente(listaF, listaC, listaC.clientes[indice].codigo);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuFaturasAbertasAUmMes(listaFatura listaF, listaClientes listaC)// Função que imprime todas as faturas em aberto a mais de um mês.
{
    topoMenu("FATURAS EM ABERTO H\xb5 MAIS DE 30 DIAS");
    mostraFaturasAbertasAMaisDeUmMes(listaF, listaC);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuClientesFaturasAbertas(listaFatura listaF, listaClientes listaC)// Função que imprime todos os clientes com fatura em aberto.
{
    topoMenu("CLIENTE COM FATURAS EM ABERTO");
    mostraClientesFaturasAbertas(listaF, listaC);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuClientesFaturasAbertasMaisDeUmMes(listaFatura listaF, listaClientes listaC) // Função que imprime clientes com fatura em aberto a mais de um mês.
{
    topoMenu("CLIENTE COM FATURAS EM ABERTO h\xb5 MAIS DE UM M\xd2S");
    mostraClientesFaturasAbertasMaisDeUmMes(listaF, listaC);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuNotaFatura(listaFatura listaF, listaClientes listaC)// Função que imprime menu para buscar e mostrar fatura.
{
    int indice;
    topoMenu("NOTA DE FATURA");
    indice = menuAUXtipoDeBuscaFatura(listaF, listaC, "Nota de Fatura");
    while(listaF.faturas[indice].valorPago == 0.0){
        topoMenu("NOTA DE FATURA");
        printf("  Fatura n\xc6o paga.");
        indice = menuAUXtipoDeBuscaFatura(listaF, listaC, "NOTA DE FATURA");
    }
    if(indice == -1){
        return;
    }
    system("cls");
    printf("\n");
    mostraNotaFatura(listaF.faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF.faturas[indice].cliente)]);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void menuReciboFatura(listaFatura listaF, listaClientes listaC)// Função que imprime menu para buscar e mostrar recibo de fatura.
{
    int indice;
    topoMenu("RECIBO DE FATURAS");
    indice = menuAUXtipoDeBuscaFatura(listaF, listaC, "RECIBO DE FATURAS");
    while(listaF.faturas[indice].valorPago == 0.0){
        topoMenu("RECIBO DE FATURAS");
        printf("  Fatura n\xc6o paga.");
        indice = menuAUXtipoDeBuscaFatura(listaF, listaC, "RECIBO DE FATURAS");
    }
    if(indice == -1){
        return;
    }
    system("cls");
    printf("\n");
    mostraReciboFatura(listaF.faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF.faturas[indice].cliente)]);
    printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
    fflush(stdin);
    getchar();
}

void relatorioGerais(listaFatura listaF, listaClientes listaC) // Função que imprime um relatório geral sobre clientes e faturas.
{
    int dataAtual, i, j;
    int quantidadeDeClienteComFaturasEmAberto = 0;
    int quantidadeDeClienteComFaturasEmAbertoAMaisDeUmMes = 0;
    int quantidadeDeClienteComFaturasVencidadas = 0;
    int totalDeFaturasEmAberto = 0;
    int totalDeFaturasEmAbertoAMaisDeUmMes = 0;
    int totalDeFaturasVencidas = 0;

    // captura os dados sobre clientes
    dataAtual = num_de_dias_desde_1900(data_do_sistema());
    for(i = 0; i < listaC.numeroClientes; i++){
        for(j = 0; j < listaF.numeroFaturas; j++){
            if(listaC.clientes[i].codigo == listaF.faturas[j].cliente && listaF.faturas[j].valorPago == 0.0){
            quantidadeDeClienteComFaturasEmAberto++;
            if(dataAtual - num_de_dias_desde_1900(listaF.faturas[j].criacaoDaFatura) >= 30){quantidadeDeClienteComFaturasEmAbertoAMaisDeUmMes++;}
            if(dataAtual > num_de_dias_desde_1900(listaF.faturas[j].vencimento)){quantidadeDeClienteComFaturasVencidadas++;}
            break;
            }
        }
    }

    for(i = 0; i < listaF.numeroFaturas; i++){
        if(listaF.faturas[i].valorPago == 0.0){
                totalDeFaturasEmAberto++;
                if(dataAtual - num_de_dias_desde_1900(listaF.faturas[i].criacaoDaFatura) >= 30){ totalDeFaturasEmAbertoAMaisDeUmMes++; }
                if(dataAtual > num_de_dias_desde_1900(listaF.faturas[i].vencimento)){totalDeFaturasVencidas++;}
        }
    }

topoMenu("RELAT\xe0RIOS GERAIS");
printf("\n---------------------------- CLIENTES ----------------------------\n");
printf("Total de clientes com faturas em aberto: %d", quantidadeDeClienteComFaturasEmAberto);
printf("\nTotal de clientes com fatura em aberto h\xA0 mais de um m\x88s: %d", quantidadeDeClienteComFaturasEmAbertoAMaisDeUmMes);
printf("\nTotal de clientes com fatura vencida: %d", quantidadeDeClienteComFaturasVencidadas);
printf("\n\n---------------------------- FATURAS -----------------------------\n");
printf("Total de faturas em aberto: %d ", totalDeFaturasEmAberto);
printf("\nTotal de faturas em aberto a mais de um m\x88s: %d", totalDeFaturasEmAbertoAMaisDeUmMes);
printf("\nTotal de faturas vencidas: %d", totalDeFaturasVencidas);
printf("\n\nPressione <enter> para voltar ao Menu de Relat%crios de faturas.", 162);
fflush(stdin);
getchar();


}
#endif // MENUS_RELATORIOS_H_INCLUDED
