#ifndef AUXILIAR_H_INCLUDED
#define AUXILIAR_H_INCLUDED

int confirmar(){
    /*
    funcao para pedir a confirmacao do usuário
    */

    char confirmar;
    printf("\n  Confirmar (S/N): ");
    fflush(stdin);
    confirmar = getchar();
    //caso confirmar seja diferente de s ou n o while vai ficar pegando valores para confirmar ate uma entrada valida
    while(confirmar != 's' && confirmar != 'S' &&
          confirmar != 'n' && confirmar != 'N'){
        printf("  Por favor, responda S ou N: ");
        confirmar = getchar();
    }
    return(confirmar == 's' || confirmar == 'S' );
}

void caracteres(int nc, char c)
{
    int i;
    for(i=0; i<nc; i++)
        printf("%c", c);
}

void printc(char *s, int tam)
{
    int ne = (tam - strlen(s)) / 2;
    while(ne > 0)
    {
        printf(" ");
        ne--;
    }
    printf(s);
    ne = (tam - strlen(s)) / 2;
    if((tam - strlen(s)) % 2 != 0){
        ne++;
    }
    while(ne > 0)
    {
        printf(" ");
        ne--;
    }
}

void printaEspcaco(int numero){
    int i;
    for(i=0;i<numero;i++){
        printf(" ");
    }
}

void div_milhar(unsigned long long num, char *snum)
{
    int i;
    int np; // número de pontos
    int ts; // tamanho da string
    int pu; // puxador
    sprintf(snum, "%I64u", num);
    ts = strlen(snum);
    np = (ts-1) / 3;
    snum[ts + np] = '\0';
    pu = ts + np - 1;
    while(np > 0) {
        for(i=0; i<3; i++)
        {
            snum[pu] = snum[pu-np];
            pu--;
        }
        snum[pu] = '.';
        if(np > 1)
            pu--;
        np--;
    }
}

int e_inteiro(char *snum)
{
    int i = 0;
    if(snum[i] == '-')
        i++;
    while(snum[i] != '\0')
    {
        if(!isdigit(snum[i]))
            return 0;
        i++;
    }
    return 1;
}

int le_inteiro()
{
    char snum[31];
    fflush(stdin);
    gets(snum);
    while(!e_inteiro(snum) || strlen(snum) == 0)
    {
        printf("  Favor digitar um inteiro: ");
        fflush(stdin);
        gets(snum);
    }
    return atoi(snum);
}

/* Verifica se a string snum pode ser convertida para um real */
int e_real(char *snum)
{
    int i = 0, np = 0;
    if(snum[i] == '-')
        i++;
    while(snum[i] != '\0')
    {
        if(!isdigit(snum[i])) {
            if(snum[i] != '.') {
                return 0;
            }
            else
            {
                np++;
                if(np > 1)
                    return 0;
            }
        }
        i++;
    }
    return 1;
}

float le_real()
{
    char snum[31];
    fflush(stdin);
    gets(snum);
    while(!e_real(snum) || strlen(snum) == 0)
    {
        printf("\n  Favor digitar um real: ");
        fflush(stdin);
        gets(snum);
    }
    return strtod(snum,NULL);
}

void topoMenu(const char *nomeMenu){
    system("cls");
    printf("\n");
    printf("\xc9"); linhaNota(205, 64); printf("\xbb"); printf("\n");

    printf("\xba"); printc(nomeMenu, 64); printf("\xba"); printf("\n");

    printf("\xc8"); linhaNota(205, 64); printf("\xbc"); printf("\n");
}

void porExteso(int numero, char *numeroChar)
{
    strcpy(numeroChar, "");
    int c, d, u;


    char uni[][7] =  {"","um","dois","tr\x88s","quatro",
                      "cinco","seis","sete","oito","nove"};

    char dez[][10] = {"","dez","vinte","trinta","quarenta",
                      "cinquenta","sessenta","setenta",
                      "oitenta","noventa"};

    char cen[][13] = {"","cento","duzentos","trezentos",
                      "quatrocentos","quinhentos","seiscentos",
                      "setecentos","oitocentos","novecentos"};

    char esp[][10] = {"","onze","doze","treze","quatorze",
                      "quinze","dezesseis","dezessete",
                      "dezoito","dezenove"};

    if(numero/1000000 > 0){
        c = numero/100000000;
        d = numero%100000000/10000000;
        u = numero%10000000/1000000;
        if(c==0 && d==0 && u==1){
            strcat(numeroChar, "um milh\xc6o ");
        }

        else{
            if(c > 0){
                strcat(numeroChar, cen[c]);
                if(d > 0 || u > 0)
                {
                    strcat(numeroChar, " e ");
                }
            }

            if(d == 1 && u > 0)
            {
                strcat(numeroChar, esp[u]);
            }

            else{
                if(d > 0)
                {
                    strcat(numeroChar, dez[d]);
                    if(u > 0)
                        strcat(numeroChar, " e ");
                }

                if(u > 0)
                {
                    strcat(numeroChar, uni[u]);
                }
            }
            strcat(numeroChar, " milhoes ");
        }
    }
    numero = numero%1000000;
    if(numero%1000000/1000 > 0){
        c = numero/100000;
        d = numero%100000/10000;
        u = numero%10000/1000;
        if(c ==0 && d==0 && u==1){
            strcat(numeroChar, "mil ");
        }
        else{
            if(c > 0){
                strcat(numeroChar, cen[c]);
                if(d > 0 || u > 0)
                {
                    strcat(numeroChar, " e ");
                }
            }

            if(d == 1 && u > 0)
            {
                strcat(numeroChar, esp[u]);
            }

            else{
                if(d > 0)
                {
                    strcat(numeroChar, dez[d]);
                    if(u > 0)
                        strcat(numeroChar, " e ");
                }

                if(u > 0)
                {
                    strcat(numeroChar, uni[u]);
                }
            }
            strcat(numeroChar, " mil ");
        }
        numero = numero%1000;
    }
    c = numero/100;
    d = numero%100/10;
    u = numero%10;
    if(c > 0){
        strcat(numeroChar, cen[c]);
            if(d > 0 || u > 0)
            {
                strcat(numeroChar, " e ");
            }
    }

    if(d == 1 && u > 0)
    {
        strcat(numeroChar, esp[u]);
    }

    else{
        if(d > 0)
        {
            strcat(numeroChar, dez[d]);
            if(u > 0)
                strcat(numeroChar, " e ");
        }

        if(u > 0)
        {
            strcat(numeroChar, uni[u]);
        }
    }
}




#endif // AUXILIAR_H_INCLUDED
