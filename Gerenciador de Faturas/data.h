struct data
{
    char dia;
    char mes;
    short ano;
};
typedef struct data TData;

int e_bissexto(int ano)
{
    return ano%4 == 0 && (ano%100 != 0 || ano%400 == 0);
}

TData gere_data()
{
    int ndm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    TData dat;
    dat.ano = 2018 + rand()%4;
    if(e_bissexto(dat.ano))
        ndm[2] = 29;
    dat.mes = 1 + rand()%12;
    dat.dia = 1 + rand()%ndm[(int) dat.mes];
    return dat;
}

TData data_do_sistema()
{
    TData data;

    //ponteiro para struct que armazena data e hora
    struct tm *data_hora_atual;

    //variável do tipo time_t para armazenar o tempo em segundos
    time_t segundos;

    //obtendo o tempo em segundos
    time(&segundos);

    //para converter de segundos para o tempo local
    //utilizamos a função localtime
    data_hora_atual = localtime(&segundos);

    data.dia = data_hora_atual->tm_mday;
    data.mes = data_hora_atual->tm_mon+1;
    data.ano = data_hora_atual->tm_year+1900;

    return data;
}

int dataValida(int dia, int mes, int ano)
{
    int ndm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(e_bissexto(ano))
        ndm[2] = 29;
    if(ano < 1900 || mes < 1 || mes > 12 || dia < 1 || dia > ndm[mes])
        return 0;
    return 1;
}

void mostre_data(TData dat)
{
    printf("%02d/%02d/%d", dat.dia, dat.mes, dat.ano);
}

void mais_um_dia(TData *dat)
{
    int ndm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(e_bissexto(dat->ano))
        ndm[2] = 29;
    dat->dia++;
    if(dat->dia > ndm[(int) dat->mes])
    {
        dat->dia = 1;
        dat->mes++;
        if(dat->mes > 12)
        {
            dat->mes = 1;
            dat->ano++;
        }
    }
}

int num_de_dias_desde_1900(TData dat)
{
    int ndm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(e_bissexto(dat.ano))
        ndm[2] = 29;
    int ano, mes, num_dias = 0;
    for(ano=1900; ano<dat.ano; ano++)
        if(e_bissexto(ano))
            num_dias += 366;
        else
            num_dias += 365;
    for(mes=1; mes<dat.mes; mes++)
        num_dias += ndm[mes];
    return num_dias + dat.dia - 1;
}

int dia_da_semana(TData dat)
{
    return num_de_dias_desde_1900(dat)%7;
}

void mostre_data_ext(TData dat)
{
    char ndm[13][21] = {"","janeiro","fevereiro","mar\x87o",
        "abril","maio","junho","julho","agosto","setembro",
        "outubro","novembro","dezembro"};
    char nds[7][21] = {"segunda-feira","ter\x87 \ba-feira"
        ,"quarta-feira","quinta-feira","sexta-feira","s\xa0 \bbado",
        "domingo"};
    printf("%d de %s de %d, %s", dat.dia, ndm[(int)dat.mes],
            dat.ano, nds[dia_da_semana(dat)]);
}

int compare_datas(const void *a, const void *b)
{
    TData *da = (TData *) a;
    TData *db = (TData *) b;
    if(da->ano != db->ano)
        return da->ano - db->ano;
    else
        if(da->mes != db->mes)
            return da->mes - db->mes;
        else
            return da->dia - db->dia;
}






