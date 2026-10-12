#ifndef EXIBICAO_H_INCLUDED
#define EXIBICAO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>

void gato ();
void gatoaltavida ();
void gatobaixavida ();
void gatodormir();
void raposa ();
void rato ();
void pato ();
void mensagem (char msg[]);
void barradevida (int vida_atual, int vida_max, char nomebarra[]);
void desenharjogo (int felicidade, int felicidademax,int fome, int fomemax);
void gatomorrer();
void encerramento (int segtot);
void musica (int volume);
void sons (int som);

#endif // EXIBICAO_H_INCLUDED
