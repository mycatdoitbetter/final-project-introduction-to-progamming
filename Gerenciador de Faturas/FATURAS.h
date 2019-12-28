#ifndef FATURAS_H_INCLUDED
#define FATURAS_H_INCLUDED


struct fatura{
    unsigned int numero;
    unsigned int cliente;
    TData vencimento;
    TData criacaoDaFatura;
    TData pagamento;
    double valorNominal;
    double valorPago;

};
typedef struct fatura TFatura;

void modificarFaturaNumero(TFatura *fatura) // Função que modifica o número de uma fatura.
{
    printf("\n  Digite novo n\xa3mero de fatura: ");
    fatura->numero = le_inteiro();
}

void modificarFaturaCliente(TFatura *fatura, listaClientes lista) // Função para modificar o codigo na fatura do cliente.
{
    int indice;
    printf("\n  Digite o c\xa2 \bdigo do cliente: ");
    scanf("%d", &indice);
    indice = buscarClienteFatura(lista, indice);
    while(indice == -1){
        printf("\n  C\xa2 \bdigo do cliente n\xc6o encontrado\n  Digitar novamento o c\xa2 \bdigo do cliente");
        indice = buscarClienteCodigo(lista);
    }
    fatura->cliente = lista.clientes[indice].codigo;
}

void modificarFaturaVencimento(TFatura *fatura) // Função para modificar a data de vencimento de uma fatura.
{
    int dia, mes, ano;
    printf("\n  Digite nova data de vencimento (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    while(!dataValida(dia, mes, ano)){
        printf("\n  Data de vencimento inv\xa0lida\n  Digitar novamente a data de vencimento (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
    }
    fatura->vencimento.dia = dia;
    fatura->vencimento.mes = mes;
    fatura->vencimento.ano = ano;
}

void modificarFaturaValorNominal(TFatura *fatura) // Função para modificar o valor nominal de uma fatura.
{
    printf("\n  Digite o novo valor da fatura: ");
    scanf("%lf", &fatura->valorNominal);
}

TFatura criarFatura(listaClientes lista ,unsigned int codigo) // Função para criar uma fatura para um cliente.
{
    int dia, mes, ano;
    TFatura fatura;
    fatura.numero = codigo;

    // Recebendo o código do cliente que receberá a fatura.
    printf("\n  Digite o c\xa2 \bdigo do cliente: ");
    codigo = le_inteiro();
    while(buscarClienteFatura(lista, codigo) == -1){
        printf("  Cliente n\xc6o encontrado\n  Por favor, digite novamente o c\xa2 \bdigo do cliente: ");
        codigo = le_inteiro();
    }
    fatura.cliente = codigo;

    //Recebendo a data de vencimento da fatura e verificando se é valida.
    printf("\n  Digite a data de vencimento (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    while(!dataValida(dia, mes, ano)){
        printf("\n  Data de vencimento inv\xa0lida\n  Digite novamente data de vencimento (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
    }
    fatura.vencimento.dia = dia;
    fatura.vencimento.mes = mes;
    fatura.vencimento.ano = ano;
    printf("\n  Digite valor da fatura: ");
    scanf("%lf", &fatura.valorNominal);
    fatura.valorPago = 0;
    fatura.criacaoDaFatura = data_do_sistema(); // Setando automaticamente a data de criação da fatura com a data do sistema.
    return fatura;
}

TFatura criaFaturaAleatorio(listaClientes lista,unsigned int codigo) // Função para gerar faturas aleatorias para os clientes também aleatorios.
{
    TFatura fatura;
    fatura.numero = codigo;
    fatura.cliente = lista.clientes[rand()%lista.numeroClientes].codigo;
    fatura.criacaoDaFatura = gere_data();
    int dataFatura = num_de_dias_desde_1900(fatura.criacaoDaFatura);
    fatura.vencimento = gere_data();
    int dataVencimento = num_de_dias_desde_1900(fatura.vencimento);

    while(dataFatura - dataVencimento < 0)  // Gera uma fatura com data de vencimento maior do que data de geração da fatura.
    {
        fatura.vencimento = gere_data();
        dataVencimento = num_de_dias_desde_1900(fatura.vencimento);
        fatura.criacaoDaFatura = gere_data();
        dataFatura = num_de_dias_desde_1900(fatura.criacaoDaFatura);
    }
    fatura.valorPago = 0.0;
    fatura.pagamento.dia = 00;
    fatura.pagamento.mes = 00;
    fatura.pagamento.ano = 0000;
    fatura.valorNominal = ((double)(rand()%100000 * ((rand()%5)+1)))/100;
    return fatura;
}

void mostrarFatura(TFatura fatura, listaClientes lista) // Função que mostra fatura nas listas e nos menus de cliente.
{
    int indice;
    indice = buscarClienteFatura(lista, fatura.cliente);
    printaEspcaco(1);
    linhaNota(196, 60);
    printf("\n      FATURA\n");
    printf("\n      Cliente: %s",lista.clientes[indice].nome);
    printf("              C\xa2 \bdigo: %d", lista.clientes[indice].codigo);
    printf("\n      N\xa3mero da fatura : %d\n      Valor: %.2f R$\n", fatura.numero, fatura.valorNominal);
    printf("      Vencimento: ");
    mostre_data(fatura.vencimento);
    printf("\n");
    printaEspcaco(5);
    linhaNota(196, 60);
}


#endif // FATURAS_H_INCLUDED
