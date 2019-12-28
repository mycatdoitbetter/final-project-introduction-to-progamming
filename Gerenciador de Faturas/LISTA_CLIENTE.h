#ifndef LISTA_CLIENTE_H_INCLUDED
#define LISTA_CLIENTE_H_INCLUDED
struct listaClientes{
    int capacidade;
    int numeroClientes;
    TCliente *clientes;
};

typedef struct listaClientes listaClientes;

void addClienteLista(listaClientes *lista, TCliente cliente) // Adiciona um cliente a lista de cliente por lista dinâmica
{
    if(lista->capacidade == lista->numeroClientes){
        lista->capacidade += 10;
        lista->clientes = realloc(lista->clientes, lista->capacidade * sizeof(TCliente));
    }
    lista->clientes[lista->numeroClientes] = cliente;
    lista->numeroClientes++;
}

int escolherClienteBusca(listaClientes lista, int j,int indices[j]) // Lista todos os clientes e possibilita o usuário escolher um destes.
{
        int i;
        unsigned int codigo;
        for(i=0;i<j;i++){
            printf("\n  %d) ", i);
            mostrarCliente(lista.clientes[indices[i]]);
            printf("\n\n");
        }
        printf("  Qual o n\xa3mero do cliente que voc\x88 deseja escolher? ");
        codigo = le_inteiro();
        while(codigo > j || codigo < 0){
            printf("  Digite um c\xa2 \bdigo v\xa0lido: ");
            codigo = le_inteiro();
        }
        return indices[codigo];
}

int buscarClienteNome(listaClientes lista) // Função para buscar cliente pelo nome.
{
    int i, j=0;
    int indices[lista.numeroClientes];
    char nomeAux[41];
    printf("  Qual o nome do cliente que voc\x88 deseja  buscar? ");
    fflush(stdin);
    gets(nomeAux);
    for(i=0;i<lista.numeroClientes;i++) // Percorre a lista de clietes comparando o nome capturado com os da lista.
    {
        if(strstr(lista.clientes[i].nome, nomeAux) != 0){
            indices[j] = i;
            j++;
        }
    }
    if(j == 0){
        return -1;
    }
    else if(j ==1){
        return indices[0];
    }
    else{
        return escolherClienteBusca(lista, j,indices);
    }
}

int buscarClienteCodigo(listaClientes lista) //Função para buscar cliente pelo código.
{
    int i, j=0;
    int indices[lista.numeroClientes];
    unsigned int codigoAux;
    printf("  Qual o c\xa2 \bdigo do cliente que voc\x88 deseja buscar? ");
    scanf("%d", &codigoAux);
    for(i=0;i<lista.numeroClientes;i++)// Percorre a lista de clietes comparando o código capturado com os da lista.
        {
        if(lista.clientes[i].codigo == codigoAux){
            indices[j] = i;
            j++;
        }
    }
    if(j == 0){
        return -1;
    }
    else if(j ==1){
        return indices[0];
    }
    else{
        return escolherClienteBusca(lista, j,indices);
    }
}

int buscarClienteFatura(listaClientes lista, unsigned int codigoAux) //Função para buscar cliente pelo codigo da fatura.
{
    int i, indice=0;
    for(i=0;i<lista.numeroClientes;i++){
        if(lista.clientes[i].codigo == codigoAux){
            indice = i;
            return indice;
        }
    }
    return -1;
}


int buscarClienteCPF(listaClientes lista) // Função para buscar cliente pelo CPF.
{
    int i, j=0;
    int indices[lista.numeroClientes];
    char cpfAux[15];
    printf("  Qual o CPF do cliente que voc\x88 deseja buscar? ");
    fflush(stdin);
    gets(cpfAux);
    for(i=0;i<lista.numeroClientes;i++){
        if(strstr(lista.clientes[i].cpf, cpfAux) != 0){
            indices[j] = i;
            j++;
        }
    }
    if(j == 0){
        return -1;
    }
    else if(j ==1){
        return indices[0];
    }
    else{
        return escolherClienteBusca(lista, j, indices);
    }
}

void excluiClienteLista(listaClientes *lista,int indice) // Função para excluir cliente da lista pelo indice
{
    int i;
    for(i=indice;i<lista->numeroClientes;i++){
        lista->clientes[i] = lista->clientes[i+1];
    }
    lista->numeroClientes--;
    if(lista->capacidade - lista->numeroClientes > 50){
        lista->capacidade -= 10;
        lista->clientes = realloc(lista->clientes, lista->capacidade * sizeof(TCliente));
    }
}

listaClientes criarClienteLista() //Função para criar uma lista dinamica de clientes.
{
    listaClientes lista;
    lista.capacidade = 20;
    lista.numeroClientes = 0;
    lista.clientes = malloc(lista.capacidade * sizeof(TCliente));
    return lista;
 }

void criarClienteListaAleatorio(listaClientes *lista, int numero) // Função para alocar o cliente aleatorio na lista.
{
    int p;
    for(p=0;p<numero;p++){ addClienteLista(lista, criarClienteAleatorio(lista->numeroClientes)); }
}

void mostraClienteLista(listaClientes lista) // Função para mostrar os clientes alocados na lista.
{
    int i;
    for(i=0;i<lista.numeroClientes;i++){
        printf("  %.2d)", i);
        mostrarCliente(lista.clientes[i]);
        printf("\n\n");
    }
}






#endif // LISTA_CLIENTE_H_INCLUDED
