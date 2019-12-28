#ifndef LISTA_FATURA_H_INCLUDED
#define LISTA_FATURA_H_INCLUDED

struct listaFatura{
    int capacidade;
    int numeroFaturas;
    TFatura *faturas;
};

typedef struct listaFatura listaFatura;

void addFaturaLista(listaFatura *lista, TFatura fatura) // Adiciona uma fatura a lista dinâmica
{
    if(lista->capacidade == lista->numeroFaturas){
        lista->capacidade += 10;
        lista->faturas = realloc(lista->faturas, lista->capacidade*sizeof(TFatura));
    }
    lista->faturas[lista->numeroFaturas] = fatura;
    lista->numeroFaturas++;
}

void excluiFaturaLista(listaFatura *lista, int indice) // Exclui uma fatura da lista dinâmica
{
    int i;
    for(i=indice; i<lista->numeroFaturas;i++){
        lista->faturas[i] = lista->faturas[i+1];
    }
    lista->numeroFaturas--;
    if(lista->capacidade - lista->numeroFaturas > 50){
        lista->capacidade -= 10;
        lista->faturas = realloc(lista->faturas, lista->capacidade*sizeof(TFatura));
    }
}

listaFatura criarFaturaLista() // Cria uma lista dinâmica de faturas
{
    listaFatura lista;
    lista.capacidade = 20;
    lista.numeroFaturas = 0;
    lista.faturas = malloc(lista.capacidade * sizeof(TCliente));
    return lista;
}

void criaFaturaListaAleatorio(listaFatura *listaF, listaClientes listaC, int numero)// Aloca as faturas geradas aleatoriamente na lista.
{
    int p;
    for(p=0;p<numero;p++){
        addFaturaLista(listaF, criaFaturaAleatorio(listaC, listaF->numeroFaturas));
    }

}

void mostraFaturaLista(listaFatura listaF, listaClientes listaC) // Mostra todas as faturas na lista.
{
    int i;
    for(i=0;i<listaF.numeroFaturas;i++){
        printf("  %.2d)\n", i);
        printaEspcaco(3);
        mostrarFatura(listaF.faturas[i], listaC);
        printf("\n\n");
    }
}

int escolherFaturaBusca(listaFatura listaF, listaClientes listaC,int j, int indices[j]) // Seleciona uma fatura pelo código.
{
        int i;
        unsigned int codigo;
        for(i=0;i<j;i++){
            printf("\n  %d)\n ", i);
            printaEspcaco(3);
            mostrarFatura(listaF.faturas[indices[i]], listaC);
            printf("\n\n");
        }
        printf("  Qual o c\xa2 \bdigo da fatura que voc\x88 deseja escolher? ");
        codigo = le_inteiro();
        while(codigo > j || codigo < 0){
            printf("  Digite um c\xa2 \bdigo v\xa0lido: ");
            codigo = le_inteiro();
        }
        return indices[codigo];
}

int buscarFaturaNumero(listaFatura listaF, listaClientes listaC) // Busca fatura pelo número.
{
    int i, j=0;
    int indices[listaF.numeroFaturas];
    unsigned int  numeroAux;
    printf("  Qual o n\xa3mero da fatura que voc\x88 deseja buscar? ");
    scanf("%d", &numeroAux);
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].numero == numeroAux){
            indices[j] = i;
            j++;
        }
    }
    if(j==0){
        return -1;
    }
    else if(j==1){
        return indices[0];
    }
    else{
        return escolherFaturaBusca(listaF, listaC,j, indices);
    }
}

int buscarFaturaCliente(listaFatura listaF, listaClientes listaC, unsigned int codigoClinte) // Busca fatura pelo codigo do cliente.
{
    int i, j=0;
    int indices[listaF.numeroFaturas];
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].cliente == codigoClinte){
            indices[j] = i;
            j++;
        }
    }
    if(j==0){
        return -1;
    }
    else if(j==1){
        return indices[0];
    }
    else{
        return escolherFaturaBusca(listaF, listaC,j, indices);
    }
}

int buscarFaturaClienteAbertas(listaFatura listaF, listaClientes listaC, unsigned int codigoClinte) // Busca fatura em aberto pelo código do cliente.
{
    int i, j=0;
    int indices[listaF.numeroFaturas];
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].cliente == codigoClinte && listaF.faturas[i].valorPago == 0.0){
            indices[j] = i;
            j++;
        }
    }
    if(j==0){
        return -1;
    }
    else if(j==1){
        return indices[0];
    }
    else{
        return escolherFaturaBusca(listaF, listaC,j, indices);
    }
}

void mostraTodasFaturasCliente(listaFatura listaF, listaClientes listaC,unsigned int codigoCliente) // Imprime todas as faturas de um cliente.
{
    int i, j=0;
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].cliente == codigoCliente){
            printf("\n %d)\n ", j);
            printaEspcaco(3);
            mostrarFatura(listaF.faturas[i], listaC);
            printf("\n");
            j++;
        }
    }
}

void mostrarFaturasAbertas(listaFatura listaF, listaClientes listaC) // Imprime todas as faturas em aberto da lista de faturas.
{
    int i;
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].valorPago == 0.0){
            printf("\n %d) ", i);
            printaEspcaco(3);
            mostrarFatura(listaF.faturas[i], listaC);
            printf("\n");
        }
    }
}

void mostrarFaturasAbertasCliente(listaFatura listaF, listaClientes listaC,unsigned int codigoCliente) // Mostra todas as faturas em aberto de um cliente.
{
    int i, j=0;
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].cliente == codigoCliente && listaF.faturas[i].valorPago == 0.0){
            printf("\n %d) \n ", j);
            printaEspcaco(3);
            mostrarFatura(listaF.faturas[i], listaC);
            printf("\n");
            j++;
        }
    }
    if(j==0){
        printc("Nenhuma fatura em aberto", 66);

    }
}

void mostraFaturasAbertasAMaisDeUmMes(listaFatura listaF, listaClientes listaC) // Mostra todas as faturas em aberto a mais de um mês
{
    int i, j=0, dataFatura;
    int dataAtual = num_de_dias_desde_1900(data_do_sistema());
    for(i=0;i<listaF.numeroFaturas;i++){
        dataFatura = num_de_dias_desde_1900(listaF.faturas[i].criacaoDaFatura);
        if( dataAtual - dataFatura >= 30){
            printf("\n %d) ", j);
            printaEspcaco(3);
            mostrarFatura(listaF.faturas[i], listaC);
            printf("\n");
            j++;
        }
    }
}

int buscarFaturaVencimento(listaFatura listaF, listaClientes listaC) // Busca fatura pelo vencimento.
{
    int i, j=0;
    int indices[listaF.numeroFaturas];
    int dia, mes, ano;
    printf("  Qual o vencimento da fatura que voc\x88 deseja buscar? ");
    scanf("%d/%d/%d", &dia, &mes, &ano);
    for(i=0;i<listaF.numeroFaturas;i++){
        if(listaF.faturas[i].vencimento.dia == dia &&
           listaF.faturas[i].vencimento.mes == mes &&
           listaF.faturas[i].vencimento.ano == ano){

            indices[j] = i;
            j++;
        }
    }
    if(j==0){
        return -1;
    }
    else if(j==1){
        return indices[0];
    }
    else{
        return escolherFaturaBusca(listaF, listaC,j, indices);
    }
}

void mostraClientesFaturasAbertas(listaFatura listaF, listaClientes listaC) // Mostra uma lista de clientes com faturas em aberto.
{
    int i, j, k=0;
    for(i=0;i<listaC.numeroClientes;i++){
        for(j=0;j<listaF.numeroFaturas;j++){
            if(listaF.faturas[j].cliente == listaC.clientes[i].codigo &&
               listaF.faturas[j].valorPago == 0.0){
                printf(" %d) ", k);
                mostrarCliente(listaC.clientes[i]);
                printf("\n");
                k++;
                break;
               }
        }
    }
}

void mostraClientesFaturasAbertasMaisDeUmMes(listaFatura listaF, listaClientes listaC)//Mostra uma lista de clientes com faturas em aberto a mais de um mês.
{
    int i, j, k=0;
    int dataAtual = num_de_dias_desde_1900(data_do_sistema());
    int dataFatura;
    for(i=0;i<listaC.numeroClientes;i++){
        for(j=0;j<listaF.numeroFaturas;j++){
             dataFatura = num_de_dias_desde_1900(listaF.faturas[j].criacaoDaFatura);
            if(listaF.faturas[j].cliente == listaC.clientes[i].codigo &&
               listaF.faturas[j].valorPago == 0.0 &&
               dataAtual - dataFatura > 30){
                printf(" %d) ", k);
                mostrarCliente(listaC.clientes[i]);
                printf("\n");
                k++;
                break;
               }
        }
    }
}

void vazioNota() // Função para criar estrutura da nota.
{
    printf("%c", 179);
    printaEspcaco(64);
    printf("%c\n", 179);
}

void linhaNota(int simbolo,int vezes) // Função cria estrutura de linha
{
    int i;
    for(i=0;i<vezes;i++){
        printf("%c", simbolo);
    }
}

void mostraNotaFatura(TFatura fatura, TCliente cliente) // Função que estrutura a nota e a fatura do cliente e exibe as mesmas.
{
    int dataPagamento = num_de_dias_desde_1900(fatura.pagamento);
    int dataVencimento = num_de_dias_desde_1900(fatura.vencimento);
    char numero[sizeof(unsigned long long)];
    float multa=0.0, juros=0.0, valorTotal = fatura.valorNominal;

    if(dataPagamento > dataVencimento){
        multa = fatura.valorNominal *0.02;
        juros = ((((dataPagamento - dataVencimento)/30)+1)*0.01) * fatura.valorNominal;
        valorTotal += multa + juros;
    }

    printf("%c", 218);
    linhaNota(196, 64);
    printf("%c\n", 191);

    printf("%c %c", 179, 201);
    linhaNota(205, 60);
    printf("%c %c\n", 187, 179);

    printf("%c %c", 179, 186);
    printaEspcaco(24);
    printf("TOPO DO NOTA");
    printaEspcaco(24);
    printf("%c %c\n", 186, 179);

    printf("%c %c", 179, 200);
    linhaNota(205, 60);
    printf("%c %c\n", 188, 179);

    vazioNota();

    printf("%c %c", 179, 201);
    linhaNota(205, 60);
    printf("%c %c\n", 187, 179);

    printf("%c %c", 179, 186);
    printaEspcaco(20);
    printf("%c NOTA DE PAGAMENTO %c", 219, 219);
    printaEspcaco(19);
    printf("%c %c\n", 186, 179);

    printf("%c %c", 179, 200);
    linhaNota(205, 60);
    printf("%c %c\n", 188, 179);

    vazioNota();

    printf("%c %c", 179, 218);
    linhaNota(196, 14);
    printf("%c", 194);
    linhaNota(196, 24);
    printf("%c", 194);
    linhaNota(196, 20);
    printf("%c %c\n", 191, 179);

    printf("%c %c", 179, 179);
    printf(" Fatura: %.4d ", fatura.numero);
    printf("%c", 179);
    printf(" Vencimento: ");
    mostre_data(fatura.vencimento);
    printf(" %c", 179);
    div_milhar((unsigned long long)fatura.valorNominal, numero);
    printf(" Valor: R$ %6s,%.2d", numero, ((int)(fatura.valorNominal*100)%100));
    printf("%c %c\n", 179, 179);

    printf("%c %c", 179, 192);
    linhaNota(196, 14);
    printf("%c", 193);
    linhaNota(196, 24);
    printf("%c", 193);
    linhaNota(196, 20);
    printf("%c %c\n", 217, 179);

    vazioNota();

    printf("%c %c", 179, 218);
    linhaNota(196, 39);
    printf("%c", 194);
    linhaNota(196, 20);
    printf("%c %c\n", 191, 179);

    printf("%c %c", 179, 179);
    printf("         Data de pagamento: ");
    mostre_data(fatura.vencimento);
    printf(" %c", 179);
    printf(" Multa: R$ %9.2f", multa);
    printf("%c %c\n", 179, 179);

    printf("%c %c", 179, 192);
    linhaNota(196, 39);
    printf("%c", 180);
    printf(" Juros: R$ %9.2f", juros);
    printf("%c %c\n", 179, 179);

    printf("%c", 179);
    linhaNota(255, 41);
    printf("%c", 179);
    div_milhar((unsigned long long)fatura.valorNominal, numero);
    printf(" Total: R$ %6s,%.2d", numero, (int)(valorTotal*100)%100);
    printf("%c %c\n", 179, 179);

    printf("%c", 179);
    linhaNota(255, 41);
    printf("%c", 192);
    linhaNota(196, 20);
    printf("%c %c\n", 217, 179);

    vazioNota();

    printf("%c", 192);
    linhaNota(196, 64);
    printf("%c\n", 217);

}

void mostraReciboFatura(TFatura fatura, TCliente cliente) // Função que estrutura o recibo da fatura e mostra a mesma.
{
    int dataPagamento = num_de_dias_desde_1900(fatura.pagamento);
    int dataVencimento = num_de_dias_desde_1900(fatura.vencimento);
    int nAux=0, i;
    char numero[sizeof(unsigned long long)];
    char numeroChar[200];
    char aux[200];
    strcpy(aux, "");
    porExteso((int)(fatura.valorPago*100)/100 , numeroChar);
    porExteso((int)(fatura.valorPago*100)%100, aux);
    strcat(numeroChar, " Reais");

    if(strcmp(aux, "")){
        strcat(numeroChar, " e ");
        strcat(numeroChar, aux);
        strcat(numeroChar, " Centavos");
    }
    while(numeroChar[nAux]){
        nAux++;
    }
    float multa=0.0, juros=0.0, valorTotal = fatura.valorNominal;

    if(dataPagamento > dataVencimento){
        multa = fatura.valorNominal *0.02;
        juros = ((((dataPagamento - dataVencimento)/30)+1)*0.01) * fatura.valorNominal;
        valorTotal += multa + juros;
    }

    printf("%c", 218);
    linhaNota(196, 64);
    printf("%c\n", 191);

    printf("%c %c", 179, 201);
    linhaNota(205, 60);
    printf("%c %c\n", 187, 179);

    printf("%c %c", 179, 186);
    printaEspcaco(24);
    printf("TOPO DO NOTA");
    printaEspcaco(24);
    printf("%c %c\n", 186, 179);

    printf("%c %c", 179, 200);
    linhaNota(205, 60);
    printf("%c %c\n", 188, 179);

    vazioNota();

    printf("%c %c", 179, 201);
    linhaNota(205, 60);
    printf("%c %c\n", 187, 179);

    printf("%c %c", 179, 186);
    printaEspcaco(19);
    printf("%c RECIBO DE PAGAMENTO %c", 219, 219);
    printaEspcaco(18);
    printf("%c %c\n", 186, 179);

    printf("%c %c", 179, 200);
    linhaNota(205, 60);
    printf("%c %c\n", 188, 179);

    vazioNota();

    printf("%c %c", 179, 218);
    linhaNota(196, 60);
    printf("%c %c\n", 191, 179);

    printf("%c %c", 179, 179);
    printf(" RECEBI DE: %-48s", cliente.nome);
    printf("%c %c\n",179, 179);

    div_milhar((unsigned long long)fatura.valorPago, numero);
    printf("%c %c", 179, 179);
    printf(" A QUANTIA DE R$ %11s,%-2d", numero, (int)(fatura.valorPago*100)%100);
    linhaNota(255, 29);
    printf("%c %c\n",179, 179);

    printf("%c %c", 179, 179);
    int pulouLinha = 0;
    int algo=0;
    printf(" (");
    if(nAux > 57){
        for(i=0;i<nAux;i++){
            if(i>46 && !pulouLinha && numeroChar[i]==' '){
                linhaNota(255, 58-i);
                printf("%c %c\n",179, 179);
                printf("%c %c", 179, 179);
                pulouLinha = 1;
            }
            else if(pulouLinha){
                algo++;
            }
            printf("%c", numeroChar[i]);
        }
        printf(")");
        linhaNota(255, 58-algo);
    }
    else{
        printf("%-57s)", numeroChar);
    }
    printf("%c %c\n",179, 179);
    printf("%c %c", 179, 179);
    printf(" REFERENTE AO PAGAMENTO DA FATURA N\xe9MERO: %.4d", fatura.numero);
    linhaNota(255, 14);
    printf("%c %c\n",179, 179);

    printf("%c %c", 179, 192);
    linhaNota(196, 60);
    printf("%c %c\n",217, 179);

    printf("%c", 192);
    linhaNota(196, 64);
    printf("%c\n", 217);

}

void mostraBoletoFatura(TFatura fatura, TCliente cliente) // Função para mostrar o boleto referente a uma fatura.
{
    int dataPagamento = num_de_dias_desde_1900(fatura.pagamento);
    int dataVencimento = num_de_dias_desde_1900(fatura.vencimento);
    char numero[sizeof(unsigned long long)];
    float multa=0.0, juros=0.0, valorTotal = fatura.valorNominal;

    if(dataPagamento > dataVencimento){
        multa = fatura.valorNominal *0.02;
        juros = ((((dataPagamento - dataVencimento)/30)+1)*0.01) * fatura.valorNominal;
        valorTotal += multa + juros;
    }

    printf("%c", 218);
    linhaNota(196, 64);
    printf("%c\n", 191);

    printf("%c %c", 179, 201);
    linhaNota(205, 60);
    printf("%c %c\n", 187, 179);

    printf("%c %c", 179, 186);
    printaEspcaco(24);
    printf("TOPO DO NOTA");
    printaEspcaco(24);
    printf("%c %c\n", 186, 179);

    printf("%c %c", 179, 200);
    linhaNota(205, 60);
    printf("%c %c\n", 188, 179);

    vazioNota();

    printf("%c %c", 179, 201);
    linhaNota(205, 60);
    printf("%c %c\n", 187, 179);

    printf("%c %c", 179, 186);
    printaEspcaco(25);
    printf("%c BOLETO %c", 219, 219);
    printaEspcaco(25);
    printf("%c %c\n", 186, 179);

    printf("%c %c", 179, 200);
    linhaNota(205, 60);
    printf("%c %c\n", 188, 179);

    vazioNota();

    printf("%c %c", 179, 218);
    linhaNota(196, 60);
    printf("%c %c\n", 191, 179);

    printf("%c %c", 179, 179);
    printf(" CLIENTE: (%.4d) %-41s  ", cliente.codigo, cliente.nome);
    printf("%c %c\n", 179, 179);

    printf("%c %c", 179, 179);
    printf(" CPF: %s", cliente.cpf);
    linhaNota(255, 40);
    printf("%c %c\n", 179, 179);

    printf("%c %c", 179, 192);
    linhaNota(196, 60);
    printf("%c %c\n", 217, 179);

    vazioNota();

    printf("%c %c", 179, 218);
    linhaNota(196, 14);
    printf("%c", 194);
    linhaNota(196, 24);
    printf("%c", 194);
    linhaNota(196, 20);
    printf("%c %c\n", 191, 179);

    printf("%c %c", 179, 179);
    printf(" Fatura: %.4d ", fatura.numero);
    printf("%c", 179);
    printf(" Vencimento: ");
    mostre_data(fatura.vencimento);
    printf(" %c", 179);
    printf(" Multa: R$ %9.2f", multa);
    printf("%c %c\n", 179, 179);

    printf("%c %c", 179, 192);
    linhaNota(196, 14);
    printf("%c", 193);
    linhaNota(196, 24);
    printf("%c", 180);
    printf(" Juros: R$ %9.2f", juros);
    printf("%c %c\n", 179, 179);

    printf("%c", 179);
    linhaNota(255, 41);
    printf("%c", 179);
    div_milhar((unsigned long long)valorTotal, numero);
    printf(" Total: R$ %6s,%.2d", numero, (int)(valorTotal*100)%100);
    printf("%c %c\n", 179, 179);

    printf("%c", 179);
    linhaNota(255, 41);
    printf("%c", 192);
    linhaNota(196, 20);
    printf("%c %c\n", 217, 179);

    vazioNota();

    printf("%c", 192);
    linhaNota(196, 64);
    printf("%c\n", 217);

}
#endif // LISTA_FATURA_H_INCLUDED
