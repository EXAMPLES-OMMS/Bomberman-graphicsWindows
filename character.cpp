#include <conio.h>
#include <iostream>
#include <winbgim.h>
#include <time.h>


using namespace std;


    //colores Bomberman
    int rosadoClaro = COLOR(240, 160, 216);
    int rosado= COLOR(248, 56, 104);
    int rosadoOscuro = COLOR(176, 24, 32);
    int casiBlanco = COLOR(248, 248, 248);
    int gris = COLOR(216, 216, 224);
    int grisOscuro = COLOR(168, 160, 168);
    int medioAmarilla = COLOR(248, 184, 0);
    int casiNegro = COLOR(40, 16, 16);
    int azul = COLOR(0, 104, 224);
    int celesteOscuro = COLOR(48, 160, 248);
    int celeste = COLOR(88, 192, 248);
    int negroClaro = COLOR(40, 40, 40);

    //bomba
    int casiCeleste = COLOR(72, 208, 240);
    int casiAzul = COLOR(24, 128, 248);
    int azulOscuro = COLOR(24, 48, 64);
    int parecidoAzul = COLOR(32, 80, 136);
    int amarillo = COLOR(248, 248, 0);
    int rojo = COLOR(232, 32, 16);
    int casiGris = COLOR(160, 152, 152);

void bombermanFrente(int x,int y,float e,int color){
    {//gorrito
        setcolor(rosadoClaro);
        setfillstyle(1, rosadoClaro);
        bar(x+23*e,y+4*e, x+26*e,y+8*e);

        setcolor(rosado);
        setfillstyle(1, rosado);
        bar(x+26*e,y+4*e, x+30*e,y+8*e);

        setcolor(rosadoOscuro);
        setfillstyle(1,rosadoOscuro);
        bar(x+30*e,y+4*e, x+33*e,y+8*e);
    }

    //cabeza
    {
        setcolor(casiBlanco);
        setfillstyle(1, casiBlanco);
        //de arriba - abajo, izquierda - derecha
        int cabeza[]={x+14*e,y+11*e, x+14*e,y+15*e, x+7*e,y+15*e, x+7*e,y+18*e, x+4*e,y+18*e, x+4*e,y+39*e, x+7*e,y+39*e,
                        x+7*e,y+42*e, x+14*e,y+42*e, x+14*e,y+46*e, x+39*e,y+46*e, x+39*e,y+42*e, x+46*e,y+42*e, x+46*e,y+39*e,
                        x+49*e,y+39*e, x+49*e,y+18*e, x+46*e,y+18*e, x+46*e,y+15*e, x+39*e,y+15*e, x+39*e,y+11*e, x+14*e,y+11*e};
        fillpoly(21, cabeza);
    }

    //cabeza detalles claro
    {
        setcolor(gris);
        setfillstyle(1, gris);
        bar(x+17*e,y+11*e, x+36*e,y+15*e); bar(x+7*e,y+15*e, x+10*e,y+18*e); bar(x+33*e,y+15*e, x+42*e,y+18*e);
        bar(x+4*e,y+18*e, x+7*e,y+22*e); bar(x+36*e,y+18*e, x+46*e,y+22*e); bar(x+42*e,y+22*e, x+46*e,y+39*e);
        bar(x+4*e,y+35*e, x+7*e,y+39*e); bar(x+7*e,y+39*e, x+10*e,y+42*e); bar(x+39*e,y+39*e, x+42*e,y+42*e);
        bar(x+17*e,y+42*e, x+20*e,y+46*e); bar(x+33*e,y+42*e, x+36*e,y+46*e);
    }

    //cabeza detalles oscuro
    {
        setcolor(grisOscuro);
        setfillstyle(1, grisOscuro);
        bar(x+14*e,y+11*e, x+17*e,y+15*e); bar(x+36*e,y+11*e, x+39*e,y+15*e); bar(x+42*e,y+15*e, x+46*e,y+18*e);
        bar(x+46*e,y+18*e, x+49*e,y+39*e); bar(x+42*e,y+39*e, x+46*e,y+42*e); bar(x+14*e,y+42*e, x+17*e,y+46*e);
        bar(x+36*e,y+42*e, x+39*e,y+46*e);
    }

    //cara interior
    {
        setcolor(medioAmarilla);
        setfillstyle(1, medioAmarilla);
        bar(x+14*e,y+25*e, x+39*e,y+39*e);
    }

    //ojos
    {
        setcolor(casiNegro);
        setfillstyle(1, casiNegro);
        bar(x+17*e,y+25*e, x+20*e,y+39*e); bar(x+33*e,y+25*e, x+36*e,y+39*e);
    }

    //cara exterior
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+11*e,y+22*e, x+42*e,y+25*e); bar(x+11*e,y+25*e, x+14*e,y+39*e); bar(x+39*e,y+25*e, x+42*e,y+39*e);
    bar(x+14*e,y+39*e, x+39*e,y+42*e);

    //cuerpo exterior
    setcolor(azul);
    setfillstyle(1, azul);
    int cuerpo[]={x+14*e,y+49*e, x+14*e,y+66*e, x+23*e,y+66*e, x+23*e,y+70*e, x+30*e,y+70*e, x+30*e,y+66*e, x+39*e,y+66*e,
                    x+39*e,y+49*e, x+14*e,y+49*e};
    fillpoly(9, cuerpo);

    //cuerpo interior oscuro
    setcolor(celesteOscuro);
    setfillstyle(1, celesteOscuro);
    bar(x+17*e,y+49*e, x+20*e,y+52*e); bar(x+23*e,y+49*e, x+30*e,y+52*e); bar(x+26*e,y+52*e, x+33*e,y+56*e);
    bar(x+26*e,y+59*e, x+33*e,y+63*e); bar(x+20*e,y+63*e, x+30*e,y+66*e);

    //cuerpo interior claro
    setcolor(celeste);
    setfillstyle(1, celeste);
    bar(x+20*e,y+49*e, x+23*e,y+52*e); bar(x+20*e,y+52*e, x+26*e,y+56*e); bar(x+17*e,y+59*e, x+26*e,y+63*e);

    //brillo interior
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+17*e,y+52*e, x+20*e,y+56*e);

    //correa
    setcolor(negroClaro);
    setfillstyle(1, negroClaro);
    bar(x+14*e,y+56*e, x+39*e,y+59*e);

    //hebilla
    setcolor(medioAmarilla);
    setfillstyle(1, medioAmarilla);
    bar(x+23*e,y+56*e, x+30*e,y+59*e);

    //brazo derecho
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+10*e,y+49*e, x+14*e,y+52*e); bar(x+7*e,y+52*e, x+10*e,y+56*e);

    //mano derecha
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+4*e,y+56*e, x+10*e,y+63*e);

    //brazo izquierdo
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+39*e,y+49*e, x+42*e,y+52*e); bar(x+42*e,y+52*e, x+46*e,y+56*e);

    //mano izquierda
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+42*e,y+56*e, x+49*e,y+63*e);

    //sombra manos
    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+7*e,y+59*e, x+10*e,y+63*e); bar(x+46*e,y+59*e, x+49*e,y+63*e);

    //pierna derecha
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+14*e,y+66*e, x+23*e,y+73*e);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+20*e,y+66*e, x+23*e,y+73*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+14*e,y+70*e, x+17*e,y+73*e);

    //pierna izquierda
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+30*e,y+66*e, x+39*e,y+73*e);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+30*e,y+66*e, x+33*e,y+73*e); bar(x+36*e,y+66*e, x+39*e,y+70*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+33*e,y+70*e, x+36*e,y+73*e);

    //pie derecho
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+10*e,y+73*e, x+23*e,y+80*e);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+10*e,y+73*e, x+14*e,y+76*e); bar(x+20*e,y+73*e, x+23*e,y+80*e); bar(x+7*e,y+76*e, x+10*e,y+80*e);

    setcolor(rosadoClaro);
    setfillstyle(1, rosadoClaro);
    bar(x+14*e,y+73*e, x+17*e,y+76*e); bar(x+10*e,y+76*e, x+14*e,y+80*e);

    //pie izquierdo
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+30*e,y+73*e, x+42*e,y+80*e);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+30*e,y+73*e, x+33*e,y+80*e); bar(x+39*e,y+73*e, x+42*e,y+80*e); bar(x+42*e,y+76*e, x+46*e,y+80*e);

    setcolor(rosadoClaro);
    setfillstyle(1, rosadoClaro);
    bar(x+33*e,y+73*e, x+36*e,y+76*e);

    //bordes
    setcolor(casiNegro);
    setfillstyle(1, casiNegro);
    bar(x+23*e,y+1*e, x+33*e,y+4*e); bar(x+20*e,y+4*e, x+23*e,y+8*e); bar(x+33*e,y+4*e, x+36*e,y+8*e);
    bar(x+14*e,y+8*e, x+39*e,y+11*e); bar(x+7*e,y+11*e, x+14*e,y+15*e); bar(x+39*e,y+11*e, x+46*e,y+15*e);
    bar(x+4*e,y+15*e, x+7*e,y+18*e); bar(x+46*e,y+15*e, x+49*e,y+18*e); bar(x+1*e,y+18*e, x+4*e,y+39*e);
    bar(x+49*e,y+18*e, x+52*e,y+39*e); bar(x+4*e,y+39*e, x+7*e,y+42*e); bar(x+46*e,y+39*e, x+49*e,y+42*e);
    bar(x+7*e,y+42*e, x+14*e,y+46*e); bar(x+39*e,y+42*e, x+46*e,y+46*e); bar(x+10*e,y+46*e, x+42*e,y+49*e);

    bar(x+7*e,y+49*e, x+10*e,y+52*e); bar(x+42*e,y+49*e, x+46*e,y+52*e); bar(x+4*e,y+52*e, x+7*e,y+56*e);
    bar(x+10*e,y+52*e, x+14*e,y+73*e); bar(x+39*e,y+52*e, x+42*e,y+73*e); bar(x+46*e,y+52*e, x+49*e,y+56*e);
    bar(x+1*e,y+56*e, x+4*e,y+63*e); bar(x+49*e,y+56*e, x+52*e,y+63*e); bar(x+4*e,y+63*e, x+10*e,y+66*e);
    bar(x+42*e,y+63*e, x+49*e,y+66*e); bar(x+7*e,y+70*e, x+10*e,y+76*e); bar(x+42*e,y+70*e, x+46*e,y+76*e);
    bar(x+4*e,y+73*e, x+7*e,y+80*e); bar(x+46*e,y+73*e, x+49*e,y+80*e); bar(x+23*e,y+70*e, x+30*e,y+80*e);
    bar(x+7*e,y+80*e, x+46*e,y+83*e);
}

void bombermanArriba(int x,int y, float e,int color){
    //53x84
    //gorrito

    setcolor(rosadoOscuro);
    setfillstyle(1,rosadoOscuro);
    bar(x+23*e,y+4*e, x+33*e,y+14*e);

    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+23*e,y+4*e, x+30*e,y+11*e);

    setcolor(rosadoClaro);
    setfillstyle(1, rosadoClaro);
    bar(x+23*e,y+4*e, x+27*e,y+8*e);

    //cabeza
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    //de arriba - abajo, izquierda - derecha
    int cabeza[]={x+14*e,y+11*e, x+14*e,y+14*e, x+7*e,y+14*e, x+7*e,y+18*e, x+4*e,y+18*e, x+4*e,y+38*e, x+7*e,y+38*e,
                    x+7*e,y+42*e, x+14*e,y+42*e, x+14*e,y+45*e, x+39*e,y+45*e, x+39*e,y+42*e, x+46*e,y+42*e, x+46*e,y+38*e,
                    x+49*e,y+38*e, x+49*e,y+18*e, x+20*e,y+18*e, x+20*e,y+11*e, x+14*e,y+11*e};
    fillpoly(19, cabeza);

    //cabeza detalles claro
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+17*e,y+11*e, x+20*e,y+14*e); bar(x+7*e,y+14*e, x+11*e,y+18*e); bar(x+20*e,y+14*e, x+23*e,y+18*e);
    bar(x+30*e,y+14*e, x+46*e,y+21*e); bar(x+4*e,y+18*e, x+7*e,y+21*e); bar(x+36*e,y+21*e, x+46*e,y+25*e);
    bar(x+39*e,y+25*e, x+46*e,y+42*e); bar(x+4*e,y+35*e, x+7*e,y+38*e); bar(x+7*e,y+38*e, x+11*e,y+42*e); 
    bar(x+36*e,y+38*e, x+39*e,y+42*e); bar(x+17*e,y+42*e, x+20*e,y+45*e); bar(x+33*e,y+42*e, x+36*e,y+45*e);

    //cabeza detalles oscuro
    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+14*e,y+11*e, x+17*e,y+14*e); bar(x+36*e,y+11*e, x+39*e,y+14*e); bar(x+33*e,y+14*e, x+36*e,y+18*e);
    bar(x+43*e,y+14*e, x+46*e,y+18*e); bar(x+46*e,y+18*e, x+49*e,y+38*e); bar(x+43*e,y+38*e, x+46*e,y+42*e);
    bar(x+14*e,y+42*e, x+17*e,y+45*e); bar(x+36*e,y+42*e, x+39*e,y+45*e);

    //cuerpo exterior
    setcolor(azul);
    setfillstyle(1, azul);
    int cuerpo[]={x+14*e,y+49*e, x+14*e,y+66*e, x+23*e,y+66*e, x+23*e,y+69*e, x+30*e,y+69*e, x+30*e,y+66*e, x+39*e,y+66*e,
                    x+39*e,y+49*e, x+14*e,y+49*e};
    fillpoly(9, cuerpo);

    //cuerpo interior claro
    setcolor(celeste);
    setfillstyle(1, celeste);
    bar(x+17*e,y+49*e, x+30*e,y+62*e);

    //cuerpo interior oscuro
    setcolor(celesteOscuro);
    setfillstyle(1, celesteOscuro);
    bar(x+17*e,y+49*e, x+20*e,y+52*e); bar(x+23*e,y+49*e, x+30*e,y+52*e); bar(x+27*e,y+52*e, x+33*e,y+56*e);
    bar(x+30*e,y+59*e, x+33*e,y+62*e); bar(x+20*e,y+62*e, x+30*e,y+66*e);    

    //brillo interior
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+17*e,y+52*e, x+20*e,y+56*e);

    //correa
    setcolor(negroClaro);
    setfillstyle(1, negroClaro);
    bar(x+14*e,y+56*e, x+39*e,y+59*e);

    //brazo derecho
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+39*e,y+49*e, x+43*e,y+52*e); bar(x+43*e,y+52*e, x+46*e,y+56*e);

    //mano derecha
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+43*e,y+56*e, x+49*e,y+62*e);

    //brazo izquierdo
    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+11*e,y+49*e, x+14*e,y+52*e); bar(x+7*e,y+52*e, x+11*e,y+56*e);

    //mano izquierda
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+4*e,y+56*e, x+11*e,y+62*e);

    //sombra manos
    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+7*e,y+59*e, x+11*e,y+62*e); bar(x+46*e,y+59*e, x+49*e,y+62*e);

    //pierna derecha
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+30*e,y+66*e, x+39*e,y+73*e);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+30*e,y+66*e, x+33*e,y+73*e); bar(x+36*e,y+66*e, x+39*e,y+69*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+33*e,y+69*e, x+36*e,y+73*e);

    //pierna izquierda
    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+14*e,y+66*e, x+20*e,y+73*e);

    setcolor(grisOscuro);
    setfillstyle(1, grisOscuro);
    bar(x+20*e,y+66*e, x+23*e,y+73*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+14*e,y+69*e, x+17*e,y+73*e);

    //pie derecho
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+33*e,y+73*e, x+39*e,y+80*e);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+30*e,y+73*e, x+33*e,y+80*e); bar(x+39*e,y+73*e, x+43*e,y+76*e); bar(x+36*e,y+76*e, x+39*e,y+80*e);

    //pie izquierdo
    setcolor(rosado);
    setfillstyle(1, rosado);
    bar(x+14*e,y+73*e, x+20*e,y+80*e);

    setcolor(rosadoOscuro);
    setfillstyle(1, rosadoOscuro);
    bar(x+11*e,y+73*e, x+14*e,y+76*e); bar(x+20*e,y+73*e, x+23*e,y+80*e); bar(x+14*e,y+76*e, x+17*e,y+80*e);

    //bordes
    setcolor(casiNegro);
    setfillstyle(1, casiNegro);
    bar(x+23*e,y+1*e, x+33*e,y+4*e); bar(x+20*e,y+4*e, x+23*e,y+14*e); bar(x+33*e,y+4*e, x+36*e,y+14*e);
    bar(x+14*e,y+8*e, x+20*e,y+11*e); bar(x+36*e,y+8*e, x+39*e,y+11*e); bar(x+7*e,y+11*e, x+14*e,y+14*e);
    bar(x+39*e,y+11*e, x+46*e,y+14*e); bar(x+4*e,y+14*e, x+7*e,y+18*e); bar(x+23*e,y+14*e, x+33*e,y+18*e);
    bar(x+46*e,y+14*e, x+49*e,y+18*e); bar(x+1*e,y+18*e, x+4*e,y+38*e); bar(x+49*e,y+18*e, x+52*e,y+38*e);
    bar(x+4*e,y+38*e, x+7*e,y+42*e); bar(x+46*e,y+38*e, x+49*e,y+42*e); bar(x+7*e,y+42*e, x+14*e,y+45*e);
    bar(x+39*e,y+42*e, x+46*e,y+45*e); bar(x+11*e,y+45*e, x+43*e,y+49*e); 
    
    bar(x+7*e,y+49*e, x+11*e,y+52*e); bar(x+43*e,y+49*e, x+46*e,y+52*e); bar(x+4*e,y+52*e, x+7*e,y+56*e); 
    bar(x+11*e,y+52*e, x+14*e,y+73*e); bar(x+39*e,y+52*e, x+43*e,y+73*e); bar(x+46*e,y+52*e, x+49*e,y+56*e);
    bar(x+1*e,y+56*e, x+4*e,y+62*e); bar(x+49*e,y+56*e, x+52*e,y+62*e); bar(x+4*e,y+62*e, x+11*e,y+66*e);
    bar(x+43*e,y+62*e, x+49*e,y+66*e); bar(x+7*e,y+69*e, x+11*e,y+83*e); bar(x+43*e,y+69*e, x+46*e,y+83*e);
    bar(x+4*e,y+73*e, x+7*e,y+80*e); bar(x+46*e,y+73*e, x+49*e,y+80*e); bar(x+11*e,y+76*e, x+14*e,y+80*e);
    bar(x+39*e,y+76*e, x+43*e,y+80*e); bar(x+7*e,y+80*e, x+46*e,y+83*e); bar(x+23*e,y+69*e, x+30*e,y+80*e);

    //punto negro en gorro
    setcolor(negroClaro);
    setfillstyle(1, negroClaro);
    bar(x+27*e,y+18*e, x+30*e,y+21*e); 
}

void bomba(int x, int y, float e, int color){
    //55x53
    //de fuera para dentro arriba - abajo, izquierda- derecha
    //bomba exterior
    setcolor(azulOscuro);
    setfillstyle(1, azulOscuro);
    //de arriba - abajo, izquierda - derecha
    int bombaExterior[]={x+30*e,y+7*e, x+4*e,y+31*e, x+4*e,y+37*e, x+6*e,y+37*e, x+6*e,y+43*e, x+11*e,y+43*e, x+11*e,y+48*e,
                    x+16*e,y+48*e, x+16*e,y+50*e, x+35*e,y+50*e, x+40*e,y+45*e, x+49*e,y+45*e, x+49*e,y+21*e, x+43*e,y+21*e,
                    x+43*e,y+7*e, x+30*e,y+7*e};
    fillpoly(16, bombaExterior);
    
    //bomba medio
    setcolor(parecidoAzul);
    setfillstyle(1, parecidoAzul);
    int bombaMedio[]={x+17*e,y+7*e, x+17*e,y+11*e, x+11*e,y+11*e, x+11*e,y+14*e, x+7*e,y+14*e, x+7*e,y+18*e, x+4*e,y+18*e,
                    x+4*e,y+31*e, x+7*e,y+31*e, x+7*e,y+35*e, x+11*e,y+35*e, x+11*e,y+38*e, x+17*e,y+38*e, x+17*e,y+42*e,
                    x+30*e,y+42*e, x+30*e,y+38*e, x+36*e,y+38*e, x+36*e,y+35*e, x+39*e,y+35*e, x+39*e,y+28*e, x+33*e,y+28*e,                    
                    x+33*e,y+25*e, x+30*e,y+25*e, x+30*e,y+21*e, x+27*e,y+21*e, x+27*e,y+11*e, x+30*e,y+11*e, x+30*e,y+7*e,
                    x+17*e,y+7*e};
    fillpoly(29, bombaMedio);

    //brillo
    setcolor(casiBlanco);
    setfillstyle(1,casiBlanco);
    bar(x+20*e,y+11*e, x+23*e,y+14*e); bar(x+11*e,y+18*e, x+17*e,y+25*e);
    
    setcolor(casiCeleste);
    setfillstyle(1, casiCeleste);
    bar(x+17*e,y+11*e, x+20*e,y+14*e); bar(x+7*e,y+18*e, x+11*e,y+25*e); bar(x+17*e,y+18*e, x+20*e,y+25*e);
    bar(x+11*e,y+25*e, x+17*e,y+28*e);

    setcolor(casiAzul);
    setfillstyle(1, casiAzul);
    bar(x+20*e,y+7*e, x+23*e,y+11*e); bar(x+23*e,y+11*e, x+27*e,y+14*e); bar(x+11*e,y+14*e, x+17*e,y+18*e);
    bar(x+20*e,y+14*e, x+23*e,y+18*e); bar(x+7*e,y+25*e, x+11*e,y+28*e); bar(x+17*e,y+25*e, x+20*e,y+28*e);
    bar(x+11*e,y+28*e, x+17*e,y+31*e);

    //mecha
    setcolor(rojo);
    setfillstyle(1, rojo);
    bar(x+46*e,y+1*e, x+49*e,y+4*e); bar(x+43*e,y+4*e, x+46*e,y+11*e); bar(x+49*e,y+4*e, x+52*e,y+11*e);

    setcolor(amarillo);
    setfillstyle(1, amarillo);
    bar(x+46*e,y+4*e, x+49*e,y+11*e);

    setcolor(casiGris);
    setfillstyle(1, casiGris);
    bar(x+30*e,y+11*e, x+33*e,y+14*e); bar(x+43*e,y+11*e, x+46*e,y+14*e); bar(x+36*e,y+14*e, x+43*e,y+18*e);
    bar(x+43*e,y+18*e, x+46*e,y+21*e); bar(x+33*e,y+21*e, x+36*e,y+25*e); bar(x+39*e,y+21*e, x+43*e,y+25*e);

    setcolor(gris);
    setfillstyle(1, gris);
    bar(x+33*e,y+11*e, x+36*e,y+14*e); bar(x+39*e,y+11*e, x+43*e,y+14*e); bar(x+30*e,y+18*e, x+36*e,y+21*e);
    bar(x+36*e,y+21*e, x+39*e,y+25*e);

    setcolor(casiNegro);
    setfillstyle(1, casiNegro);
    bar(x+36*e,y+11*e, x+39*e,y+14*e); bar(x+33*e,y+14*e, x+36*e,y+18*e); bar(x+43*e,y+14*e, x+46*e,y+18*e);
    bar(x+36*e,y+18*e, x+43*e,y+21*e);

    setcolor(casiBlanco);
    setfillstyle(1, casiBlanco);
    bar(x+30*e,y+14*e, x+33*e,y+18*e);

    //bombaExterior
    setcolor(casiNegro);
    setfillstyle(1,casiNegro);
    bar(x+17*e,y+4*e, x+36*e,y+7*e); bar(x+11*e,y+7*e, x+17*e,y+11*e); bar(x+36*e,y+7*e, x+43*e,y+11*e);
    bar(x+7*e,y+11*e, x+11*e,y+14*e); bar(x+46*e,y+11*e, x+49*e,y+21*e); bar(x+4*e,y+14*e, x+7*e,y+18*e);
    bar(x+1*e,y+18*e, x+4*e,y+38*e); bar(x+49*e,y+21*e, x+52*e,y+38*e); bar(x+4*e,y+35*e, x+7*e,y+45*e);
    bar(x+46*e,y+35*e, x+49*e,y+45*e); bar(x+7*e,y+42*e, x+11*e,y+49*e); bar(x+43*e,y+42*e, x+46*e,y+49*e);
    bar(x+11*e,y+45*e, x+17*e,y+49*e); bar(x+36*e,y+45*e, x+46*e,y+49*e); bar(x+14*e,y+49*e, x+39*e,y+52*e);
}



//class Graficos
//class Matriz
//class Juego
int main(){
    initwindow(800,800);
    setfillstyle(1, COLOR(255, 255, 255)); // Establecer el estilo y color de relleno
    floodfill(0, 0, 1);
    //trampa(50, 50, 30, 5);
    bombermanFrente(0, 0, 1, 5);
    bomba(410, 248, 3, 1);
    bombermanArriba(200, 0, 1, 5);
    //muro1(50, 0, 50, 5);
    

    getch();
    getch();
    closegraph();
}