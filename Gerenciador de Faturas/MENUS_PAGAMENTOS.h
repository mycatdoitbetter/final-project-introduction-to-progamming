#ifndef MENUS_PAGAMENTOS_H_INCLUDED
#define MENUS_PAGAMENTOS_H_INCLUDED

void menuPagamentos(listaFatura *listaF, listaClientes listaC) // Função que imprime menu para gerenciar pagamentos
{
    int indice;
    char aux;
    float multa=0.0, juros=0.0;
    topoMenu("PAGAMENTOS");
    indice = menuAUXtipoDeBuscaFatura(*listaF, listaC, "PAGAMENTOS");
    if(indice == -1){
        return;
    }
    while(listaF->faturas[indice].valorPago!= 0.0){
        topoMenu("PAGAMENTOS");
        printf("  Fatura j\xa0 paga.");
        indice = menuAUXtipoDeBuscaFatura(*listaF, listaC, "PAGAMENTOS");
    }
    if(!confirmar()){
        printf("\n Pagamento n\xc6o realizado. Voltando ao menu: Sistema de faturas");
        Sleep(2000);
        return;
    }
    int dataVencimento = num_de_dias_desde_1900(listaF->faturas[indice].vencimento);
    int dataAtual = num_de_dias_desde_1900(data_do_sistema());
    int dataDiferenca = dataAtual - dataVencimento;
    listaF->faturas[indice].pagamento = data_do_sistema();
    if(dataDiferenca > 0){
        multa = listaF->faturas[indice].valorNominal *0.02;
        juros = ((((dataDiferenca)/30)+1)*0.01) * listaF->faturas[indice].valorNominal;
    }
    listaF->faturas[indice].valorPago = listaF->faturas[indice].valorNominal + multa + juros;
    while(1){
        topoMenu("PAGAMENTOS");
        mostraBoletoFatura(listaF->faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF->faturas[indice].cliente)]);
        printf("  1 - Emitir nota da Fatura\n");
        printf("  2 - Emitir recibo da fatura\n");
        printf("  ----------------------\n");
        printf("  0 - Voltar menu principal\n");
        printf("\n  Escolha uma op%c%co: ", 135, 198);
        fflush(stdin);
        aux = getchar();
        if(aux=='0'){
            return;
        }

        if(aux=='1'){
            topoMenu("PAGAMENTOS");
            mostraNotaFatura(listaF->faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF->faturas[indice].cliente)]);
            printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de Pagamento.", 162);
            fflush(stdin);
            getchar();
            break;
        }
        else if(aux=='2'){
            topoMenu("PAGAMENTOS");
            mostraReciboFatura(listaF->faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF->faturas[indice].cliente)]);
            printf("\n\n  Pressione <enter> para voltar ao Menu de Relat%crios de Pagamento.", 162);
            fflush(stdin);
            getchar();
            break;
        }
        else{
            printf("  C\xa2 \bigo inv\xa0lido\n");
            Sleep(1000);
        }
    }

}

void menuPagamentosUsuario(listaFatura *listaF, listaClientes listaC, unsigned int codigoCliente)// Função que imprime aba de pagamento de um usuário.
{
    int indice;
    char aux;
    float multa=0.0, juros=0.0;
    topoMenu("PAGAMENTOS");
    indice = buscarFaturaClienteAbertas(*listaF, listaC, codigoCliente);
    if(indice == -1){
        printf("\n    Nenhuma fatura em aberto encontrada.\n    Saindo menu de pagamento");
        Sleep(2000);
        return;
    }
    while(listaF->faturas[indice].valorPago!= 0.0){
        topoMenu("PAGAMENTOS");
        printf("  Fatura j\xa0 paga.");
        indice = buscarFaturaClienteAbertas(*listaF, listaC, codigoCliente);
    }
    topoMenu("PAGAMENTOS");
    printf("    ");
    mostrarFatura(listaF->faturas[indice], listaC);
    if(!confirmar()){
        printf("\n Pagamento n\xc6o realizado.\n Voltando ao menu: Sistema de faturas");
        Sleep(2000);
        return;
    }
    int dataVencimento = num_de_dias_desde_1900(listaF->faturas[indice].vencimento);
    int dataAtual = num_de_dias_desde_1900(data_do_sistema());
    int dataDiferenca = dataAtual - dataVencimento;
    listaF->faturas[indice].pagamento = data_do_sistema();
    if(dataDiferenca > 0){
        multa = listaF->faturas[indice].valorNominal *0.02;
        juros = ((((dataDiferenca)/30)+1)*0.01) * listaF->faturas[indice].valorNominal;
    }
    listaF->faturas[indice].valorPago = listaF->faturas[indice].valorNominal + multa + juros;
    while(1){
        topoMenu("PAGAMENTOS");
        mostraBoletoFatura(listaF->faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF->faturas[indice].cliente)]);
        printf("  1 - Emitir nota da Fatura\n");
        printf("  2 - Emitir recibo da fatura\n");
        printf("  ----------------------\n");
        printf("  0 - Voltar menu principal\n");
        printf("\n  Escolha uma op%c%co: ", 135, 198);
        fflush(stdin);
        aux = getchar();
        if(aux=='0'){
            return;
        }

        if(aux=='1'){
            topoMenu("PAGAMENTOS");
            mostraNotaFatura(listaF->faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF->faturas[indice].cliente)]);
            printf("\n\n  Pressione <enter> para voltar ao Menu de Usu\xa0rio.");
            fflush(stdin);
            getchar();
            break;
        }
        else if(aux=='2'){
            topoMenu("PAGAMENTOS");
            mostraReciboFatura(listaF->faturas[indice], listaC.clientes[buscarClienteFatura(listaC, listaF->faturas[indice].cliente)]);
            printf("\n\n  Pressione <enter> para voltar ao Menu de Usu\xa0rio.");
            fflush(stdin);
            getchar();
            break;
        }
        else{
            printf("  C\xa2 \bdigo inv\xa0lido\n");
            Sleep(1000);
        }
    }

}



#endif // MENUS_PAGAMENTOS_H_INCLUDED
