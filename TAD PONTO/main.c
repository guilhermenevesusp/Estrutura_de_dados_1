#include <stdio.h>
#include <stdio.h>
#include "Ponto.h"

int main(){

    float d;
    Ponto *p, *q;
    float x1, x2, y1, y2;

    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    p = Ponto_cria(x1,y1);
    q = Ponto_cria(x2,y2);
    
    d = Ponto_distancia(p, q);

    printf("%.2f\n", d);

    Ponto_libera(q);
    Ponto_libera(p);

    return 0;
}