#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto; 


Ponto* Ponto_cria (float x, float y); //cria um novo ponto

void Ponto_libera(Ponto*p); //libera um ponto

int Ponto_acessa(Ponto *p, float* x, float* y); //acessa os valores de "x" e "y";

int Ponto_atribui (Ponto*p, float x, float y); //atribui valores "x" e "y" a dois pontos

float Ponto_distancia(Ponto *p1, Ponto *p2); // calcula a distância entre dois pontos

#endif //PONTO_H