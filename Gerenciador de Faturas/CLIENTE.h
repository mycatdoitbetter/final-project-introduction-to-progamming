#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

struct cliente{
    unsigned int codigo;
    int permicao;
    char senha[20];
    char nome[41];
    char cpf[15];
};

typedef struct cliente TCliente;

void modificarClienteCodigo(TCliente *cliente, int permicao) // Função que permite modificar o código do cliente.
{
    if(!permicao){
        printf("\n  Voc\x88 n\xc6o possui permi\x87\xc6o essa a\x87\xc6o.");
        Sleep(2000);
    }
    else{
        printf("\n  Digitar novo c\xa2 \bdigo: ");
        cliente->codigo = le_inteiro();
    }
}

void modificarClienteNome(TCliente *cliente) // Função que permite modificar o nome do cliente.
{
    printf("\n  Digite um novo nome: ");
    fflush(stdin);
    gets(cliente->nome);
}

void modificarClienteSenha(TCliente *cliente) // Função que permite modificar a senha de um cliente.
{
    printf("\n  Digite uma nova senha: ");
    fflush(stdin);
    gets(cliente->senha);
}

void modificarUsuarioPermicao(TCliente *cliente) // Função que permite modificar a permição de um usuário.
{
    int aux;
    printf("\n  Digite uma nova permi\x87\xc6o.\n    0 - Cliente.\n    1 - Funcion\xa0rio.\n    2 - Administrador.\n    C\xa2 \bdigo: ");
    aux = le_inteiro();
    while(aux<0 || aux>2){
        printf("\n    C\xa2 \bdigo incorreto. Informe um dos c\xa2 \bdigos acima: ");
        aux = le_inteiro();
    }
}


void modificarClienteCPF(TCliente *cliente) // Função que permite modificar o CPF de um cliente
{
    char aux[15];
    printf("\n  Digite um novo CPF(XXX.XXX.XXX-YY): ");
    fflush(stdin);
    gets(aux);
    while(!verificaCPF(aux)){ //A função verificaCPF é utilizada para confimar o formato padrão.
        printf("\n  CPF inv\xa0lido.\n  Por favor, insira novamente o CPF: ");
        fflush(stdin);
        gets(aux);
    }
    strcpy(cliente->cpf, aux);
}

void criarUsuario(TCliente *cliente, unsigned int codigo) // A função adiciona um novo usuário com todos seus dados na lista de clientes.
{
    char aux[20];
    cliente->codigo = codigo;
    printf("\n  Nome Usu\xa0rio: ");
    fflush(stdin);
    gets(cliente->nome);
    printf("\n  CPF Usu\xa0rio(XXX.XXX.XXX-YY): ");
    fflush(stdin);
    gets(aux);
    while(!verificaCPF(aux)){
        printf("\n  CPF inv\xa0lido.\n  Por favor, insira novamente o CPF: ");
        fflush(stdin);
        gets(aux);
    }
    strcpy(cliente->cpf, aux);
    printf("\n  Senha:");
    fflush(stdin);
    gets(aux);
    strcpy(cliente->senha, aux);
}

TCliente criarCliente(unsigned int codigo) // Utiliza a função acima e insere a permissão (1) para identificar o usuário como cliente.
{
    TCliente cliente;
    criarUsuario(&cliente, codigo);
    cliente.permicao = 0;
    return cliente;
}

void mostrarCliente(TCliente cliente) // Mostra todos os usuários da plataforma, incluindo Admnistrador e funcionário.
{
    printf("\n\n");
    printaEspcaco(3);
    linhaNota(196, 60);

    // As condicionais abaixo organizam o nome acima do relatório de usuário.
    if(cliente.permicao == 0){
        printf("\n       Cliente\n"); // caso a permissão de usuário seja 0, o usuário é classificado na lista como cliente.
    }
    else if(cliente.permicao == 1){
        printf("\n       Funcion\xa0rio\n"); // caso a permissão de usuário seja 1, o usuário é classificado na lista como funcionário.
    }
    else{
        printf("\n       Admistrador\n"); // caso a permissão de usuário seja 2, o usuário é classificado na lista como admin.
    }

    printf("\n       C\xa2 \bdigo: %d\n       Nome: %s\n       CPF: %s\n", cliente.codigo, cliente.nome, cliente.cpf);//Imprime todos os dados do usuário.
    printaEspcaco(3);
    linhaNota(196, 60);
    printf("\n");
}

void geraCPF(char *cpf) // Função para criar o número do CPF dos clientes gerados automaticamente.
{
    char geradorCPF[15]= "";
    char aux[2];
    short digito;
    int digitoIdentificadorUm=0;
    int digitoIdentificadorDois=0;
    int i;
    for(i=0;i<9;i++){
        digito = rand()%10;
        sprintf(aux, "%d", digito);
        strcat(geradorCPF, aux);
        if((i+1)%3==0 && i!= 0 && i!= 8){
            strcat(geradorCPF, ".");
        }
        digitoIdentificadorUm += digito*(10-i);
        digitoIdentificadorDois += digito*(11-i);
    }
    strcat(geradorCPF, "-");
    digitoIdentificadorUm = digitoIdentificadorUm%11;
    if(digitoIdentificadorUm <2){
        strcat(geradorCPF, "0");
    }
    else{
        digito = 11-digitoIdentificadorUm;
        sprintf(aux, "%d", digito);
        strcat(geradorCPF, aux);
    }
    digitoIdentificadorDois += digitoIdentificadorUm*2;
    digitoIdentificadorDois = digitoIdentificadorDois%11;
    if(digitoIdentificadorDois <2){
        strcat(geradorCPF, "0");
    }
    else{
        digito = 11-digitoIdentificadorDois;
        sprintf(aux, "%d", digito);
        strcat(geradorCPF, aux);
    }
    strcpy(cpf, geradorCPF);
}

void gere_nome(char *n) // Função para criar nomes aleatorios para os clientes.
{
    int ps, ss;
    char nomes[][16] = {"Aline", "Ana", "Beatriz", "Bernardo", "Bruno", "Camila", "Carlos", "Cec\xa1lia",
             "Davi", "Eduardo", "Felipe", "Francisco", "Gabriel", "G\x82rson", "Heitor", "Henrique",
             "Ingrid", "Isabela", "J\xa3lia", "Larissa", "Laura", "Leonardo", "Lorena", "Marcelo",
             "M\xa0rcia", "Marcos", "Mariana", "Milena", "Patr\xa1\x63ia", "Pedro", "Priscila", "Renato",
             "Ricardo", "Rodrigo", "Ronaldo", "Samuel", "S\x82rgio", "Sofia", "Tiago", "Vin\xa1\x63ius"};
    char sobres[][16] = {"Abreu", "Albuquerque", "Almeida", "Alencar", "Alves", "Amaral", "Amorim",
                  "Andrade", "Antunes", "Arantes", "Ara\xa3jo", "Arruda", "Azevedo", "Barros",
                  "Bastos", "Batista", "Bezerra", "Brand\xc6o", "Brito", "Cabral", "Campos",
                  "Cardoso", "Carneiro", "Carvalho", "Castro", "Cavalcante", "Chagas", "Chaves",
                  "Correia", "Costa", "Cruz", "Dantas", "Diniz", "Duarte", "Esteves", "Fagundes",
                  "Fernandes", "Ferraz", "Ferreira", "Figueiredo", "Fonseca", "Franco", "Freire",
                  "Freitas", "Furtado", "Gomes", "Gon\x87\x61lves", "Guedes", "Guerra", "Guimar\xc6\x65s",
                  "Liberato", "Marinho", "Marques", "Martins", "Medeiros", "Melo", "Menezes",
                  "Monteiro", "Montenegro", "Moraes", "Moreira", "Moura", "Nogueira", "Noronha",
                  "Novaes", "Oliveira", "Pereira", "Pinto", "Resende", "Ribeiro", "Rios",
                  "Sampaio", "Santana", "Santos", "Torres", "Trindade", "Vasconcelos", "Vargas"};
    strcpy(n,nomes[rand()%40]); // captura um dos nomes da lista nomes
    strcat(n, " ");
    ps = rand()%78;
    ss = rand()%78;
    while(ps == ss) // busca um segundo sobrenome diferente do primeiro.
        ss = rand()%78;
    strcat(n, sobres[ps]); // adiciona o primeiro sobrenome ao nome
    strcat(n, " ");
    strcat(n, sobres[ss]); // adiciona o segundo sobrenome ao nome
}

TCliente criarClienteAleatorio(unsigned int codigo) // Função que cria um cliente aleatorio com base no geraCPF e gera_nome
{
    TCliente cliente;
    cliente.codigo = codigo;
    cliente.permicao = 0;
    itoa(codigo, cliente.senha, 10);
    gere_nome(cliente.nome);
    geraCPF(cliente.cpf);
    return cliente;

}

int verificaCPF(char *cpf) // Função para verificar CPF
{
    int i, g=0, p=0, aux, soma1=0, soma2=0;

    while(cpf[g]) // Loop para verificar cada digito do CPF
    {
        g++;
    }
    if(g < 14)  // Condicional para para o loop de verificação do CPF
    {
        return 0;
    }

    // Loops para modelar os digitos do CPF
    for(i=0;i<11;i++){
        if(isdigit(cpf[i])){
            aux = cpf[i] - '0';
            soma1 += aux*(10-p);
            soma2 += aux*(11-p);
            p++;
        }
    }

    aux = soma1%11;
    if(aux < 2){
        if(cpf[13]-'0' != 0){
            return 0;
        }
        aux = 0;
    }
    else{
        if(cpf[12]-'0' != 11-aux){
            return 0;
        }
        aux=11-aux;
    }
    soma2 += aux*2;
    aux = soma2%11;
    if(aux < 2){
        if(cpf[13]-'0' != 0){
            return 0;
        }
        aux = 0;
    }
    else{
        if(cpf[13]-'0' != 11-aux){
            return 0;
        }
        aux=11-aux;
    }
    return 1;
}
#endif // CLIENTE_H_INCLUDED
