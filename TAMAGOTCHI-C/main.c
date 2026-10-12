
#include "exibicao.h"
#include "computacao.h"

int main()
{
    int felicidademax=100;
    int felicidade=felicidademax;
    int fomemax=100;
    int fome=0;
    int volume=0;
    int cuidado=0;
    int tipo=sorteio(5,1);

    char msg[50];
    char pelagem[11];

    switch (tipo)
    {
        case 1:
        strcpy(pelagem,"OREO");
        break;
        case 2:
        strcpy(pelagem,"PANTHERA");
        break;
        case 3:
        strcpy(pelagem,"KITTY");
        break;
        case 4:
        strcpy(pelagem,"MILO");
        break;
        case 5:
        strcpy(pelagem,"PEPITO");
        break;
    }

    double tempo_dano=5.0;
    double recarga_acao=2.0;


    strcpy(msg,"-> BEM VINDO AO TAMAGOTCHI EM C! \n");
    mensagem(msg);
    strcpy(msg,"-> PARABENS PELO SEU GATINHO \n\n");
    mensagem(msg);
    mensagem(pelagem);
    gato();
    sons(1);

    do
    {
        if (volume<0 || volume>2)
        {
            strcpy(msg,"\n-> [!] ERRO! VALOR DIGITADO INVALIDO \n");
            mensagem(msg);
        }
        strcpy(msg,"\n-> INFORME O VOLUME DA MUSICA DE FUNDO \n");
        mensagem(msg);
        scanf("%i",&volume);
    }
    while (volume<0 || volume>2);
    musica(volume);

    clock_t tempo_inicial_felicidade=clock();
    clock_t tempo_inicial_fome=clock();

    clock_t ultimo_carinho = clock();
    clock_t ultima_comida = clock();

    desenharjogo(felicidade,felicidademax,fome,fomemax);
    while (felicidade>0 || fome==100)
    {
        clock_t tempo_atual_felicidade=clock();
        double tempo_passado_felicidade=(double)(tempo_atual_felicidade-tempo_inicial_felicidade)/CLOCKS_PER_SEC;

        clock_t tempo_atual_fome=clock();
        double tempo_passado_fome=(double)(tempo_atual_fome-tempo_inicial_fome)/CLOCKS_PER_SEC;

        if (tempo_passado_felicidade>=tempo_dano)
        {
            felicidade-=10;
            tempo_inicial_felicidade=tempo_atual_felicidade;
            desenharjogo(felicidade,felicidademax,fome,fomemax);
        }
        if (tempo_passado_fome>=tempo_dano)
        {
            fome+=10;
            tempo_inicial_fome=tempo_atual_fome;
            desenharjogo(felicidade,felicidademax,fome,fomemax);
        }

        clock_t tempo_carinho = (tempo_atual_felicidade-ultimo_carinho)/CLOCKS_PER_SEC;
        clock_t tempo_comida = (tempo_atual_fome-ultima_comida)/CLOCKS_PER_SEC;

        if (kbhit())
        {
            char tecla = getch();
            if ((tecla=='c' || tecla=='C') && tempo_carinho>=recarga_acao)
            {
                if (felicidade<90)
                {
                    felicidade+=10;
                }
                else {felicidade+=(felicidademax-felicidade);}

                cuidado++;
                sons(1);
                Sleep(1000);
                musica(volume);
                ultimo_carinho=tempo_atual_felicidade;
                tempo_inicial_felicidade=tempo_atual_felicidade;
                desenharjogo(felicidade,felicidademax,fome,fomemax);
            }
            else if ((tecla=='f' || tecla=='F') && tempo_comida>=recarga_acao)
            {
                if (fome>=10)
                {
                    fome-=10;
                }
                else {fome-=fome;}

                cuidado++;
                sons(4);
                Sleep(700);
                musica(volume);
                ultima_comida=tempo_atual_fome;
                tempo_inicial_fome=tempo_atual_fome;
                desenharjogo(felicidade,felicidademax,fome,fomemax);
            }
        }
        if (cuidado==2)
        {
            strcpy(msg,"\n-> SEU PET VEIO TE VISITAR!\n");
            mensagem(msg);
            sons(1);
            Sleep(1000);
            musica(volume);

            switch (tipo)
            {
                case 1:
                system("start oreo.png");
                break;
                case 2:
                system("start panthera.png");
                break;
                case 3:
                system("start kitty.png");
                break;
                case 4:
                system("start milo.png");
                break;
                case 5:
                system("start pepito.png");
                break;
            }
            cuidado=0;
        }
        Sleep(100);
    }

    if (felicidade>0 || fome==100)
    {
        sons(2);
    }
    encerramento(3);

    return 0;
}
