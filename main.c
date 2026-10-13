
#include <string.h>
#include "raylib.h"
#include "computacao.h"

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(720,720,"TAMAGOTCHI EM C");
    InitAudioDevice();

    int felicidademax=100;
    int felicidade=felicidademax;
    int fomemax=100;
    int fome=0;
    int volume=0;
    int cuidado=0;
    int tipo=sorteio(5,1);
    int mostrar=1;

    double tempo_inicio_aviso;

    char msg[50];
    char pelagem[11];

    Music musica;
    Sound miado = LoadSound("miado.wav");
    Sound perder = LoadSound("perder.wav");
    Sound comer = LoadSound("comer.wav");
    Sound ronronar = LoadSound("ronronar.wav");

    Texture2D gato;
    Color cor_fundo;
    Color cor_quadro;

    switch (tipo)
    {
        case 1:
        strcpy(pelagem,"OREO");
        gato = LoadTexture("oreo.png");
        cor_fundo = CLITERAL(Color){116,118,77,255};
        cor_quadro = CLITERAL(Color){140,142,95,255};
        break;
        case 2:
        strcpy(pelagem,"PANTHERA");
        gato = LoadTexture("panthera.png");
        cor_fundo = CLITERAL(Color){199,166,121,255};
        cor_quadro = CLITERAL(Color){232,196,126,255};
        break;
        case 3:
        strcpy(pelagem,"KITTY");
        gato = LoadTexture("kitty.png");
        cor_fundo = CLITERAL(Color){89,69,91,255};
        cor_quadro = CLITERAL(Color){146,127,152,255};
        break;
        case 4:
        strcpy(pelagem,"MILO");
        gato = LoadTexture("milo.png");
        cor_fundo = CLITERAL(Color){208,143,143,255};
        cor_quadro = CLITERAL(Color){176,114,114,255};
        break;
        case 5:
        strcpy(pelagem,"PEPITO");
        gato = LoadTexture("pepito.png");
        cor_fundo = CLITERAL(Color){115,137,154,255};
        cor_quadro = CLITERAL(Color){77,92,104,255};
        break;
    }

    double tempo_dano=5.0;
    double recarga_acao=2.0;

    SetTargetFPS(60);

    tempo_inicio_aviso = GetTime();
    while (mostrar==1)
    {
        if (mostrar && (GetTime()-tempo_inicio_aviso>=2.0))
        {
            mostrar=0;
        }

        strcpy(msg,"-> BEM VINDO AO TAMAGOTCHI EM C! \n");
        BeginDrawing();
        DrawText(msg, 50,50,20,WHITE);

        strcpy(msg,"-> PARABENS PELO SEU GATINHO \n");
        DrawText(msg,50,70,20,WHITE);

        DrawText(pelagem,50,90,20,WHITE);
        EndDrawing();
        ClearBackground(BLACK);
    }


    do
    {
        if (volume<0 || volume>1)
        {
            strcpy(msg,"\n-> [!] ERRO! VALOR DIGITADO INVALIDO \n");
            BeginDrawing();
            DrawText(msg,450,450,20,WHITE);
            EndDrawing();
        }
        strcpy(msg,"\n-> INFORME O VOLUME DA MUSICA DE FUNDO \n");
        BeginDrawing();
        DrawText(msg,450,450,20,WHITE);
        EndDrawing();
        if (IsKeyPressed(KEY_KP_0)){volume=0;}

        else if (IsKeyPressed(KEY_KP_1)){volume=1;}
    }
    while (volume<0 || volume>1);
    if (volume==0)
    {
        musica = LoadMusicStream("musicavolumebaixo.wav");
    }
    else if (volume==1)
    {
        musica = LoadMusicStream("musicavolumemedio.wav");
    }

    double ultimo_dano_fome = GetTime();
    double ultimo_dano_felicidade = GetTime();
    double ultimo_carinho = GetTime();
    double ultima_comida = GetTime();

    PlayMusicStream(musica);

    PlaySound(miado);
    while (!WindowShouldClose() && felicidade>0 || fome<100)
    {
        double tempo_atual = GetTime();
        UpdateMusicStream(musica);
        BeginDrawing();
        DrawRectangle(150,150,400,400,cor_quadro);
        DrawTexture(gato,190,200,WHITE);
        EndDrawing();
        ClearBackground(cor_fundo);

        if (tempo_atual-ultimo_dano_felicidade>=tempo_dano)
        {
            felicidade-=10;
            ultimo_dano_felicidade=tempo_atual;
        }
        if (tempo_atual-ultimo_dano_fome>=tempo_dano)
        {
            fome+=10;
            ultimo_dano_fome=tempo_atual;
        }


            if (IsKeyPressed(KEY_C) && tempo_atual-ultimo_carinho>=recarga_acao)
            {
                if (felicidade<90)
                {
                    felicidade+=10;
                }
                else {felicidade+=(felicidademax-felicidade);}

                cuidado++;
                PlaySound(miado);
                ultimo_carinho=tempo_atual;
            }
            else if (IsKeyPressed(KEY_F) && tempo_atual-ultimo_carinho>=recarga_acao)
            {
                if (fome>=10)
                {
                    fome-=10;
                }
                else {fome-=fome;}

                cuidado++;
                PlaySound(comer);
                ultima_comida=tempo_atual;
            }
    }

    if (felicidade>0 || fome==100)
    {
       PlaySound(perder);
    }

    UnloadTexture(gato);
    UnloadMusicStream(musica);
    UnloadSound(miado);
    UnloadSound(perder);
    UnloadSound(comer);
    UnloadSound(ronronar);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
