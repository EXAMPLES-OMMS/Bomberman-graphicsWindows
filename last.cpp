#include <iostream>
#include <winbgim.h>
#include <time.h>

#define M 100
#define P 200
#define C 300
#define T 400
#define E 500

using namespace std;

class Graficos{
    private:
    public:
        void muro(int x,int y,int e,int color){
            e=e/6;
            //rectangle(x+2,y+2,x+e-2,y+e-2);
            //rectangle(x+e/4,y+e/4,x+3*e/4,y+3*e/4);
            setcolor(COLOR(255,81,28));
            setfillstyle(1,COLOR(255,81,28));
            bar(x,y,x+6*e,y+6*e);

            setcolor(COLOR(89,11,11));
            setfillstyle(1,COLOR(89,11,11));
            int g=1;
            for(int i=0;i<6;i++){
               bar(x,(y-g)+i*e,x+6*e,(y+g)+i*e);
               if(i==0 || i==2 || i==4){
                    //0,2,4,6
                    bar((x-g)+2*e,y+i*e,(x+g)+2*e,y+(i+1)*e);
                    bar((x-g)+4*e,y+i*e,(x+g)+4*e,y+(i+1)*e);
               }if(i==1 || i==3 || i==5){
                    //1,3,5
                    bar((x-g)+1*e,y+i*e,(x+g)+1*e,y+(i+1)*e);
                    bar((x-g)+3*e,y+i*e,(x+g)+3*e,y+(i+1)*e);
                    bar((x-g)+5*e,y+i*e,(x+g)+5*e,y+(i+1)*e);

               }
            }
        }

        void heroe(int x,int y,int e,int color){
            e=e/10;
            setcolor(COLOR(15,90,242));
            setfillstyle(1,COLOR(15,90,242));
            int ale[]={x+1*e,y+7*e,x+2*e,y+5*e,x+8*e,y+5*e,x+9*e,y+7*e,x+1*e,y+7*e};
            fillpoly(5,ale);

            setcolor(COLOR(255,102,0));
            setfillstyle(1,COLOR(255,102,0));
            int p[]={x+2*e,y+8.5*e,x+2*e,y+6*e,x+8*e,y+6*e,x+8*e,y+8.5*e,x+6*e,y+8.5*e,x+6*e,y+7*e,x+4*e,y+7*e,x+4*e,y+8.5*e,x+2*e,y+8.5*e};
            fillpoly(9,p);

            setcolor(COLOR(22,139,242));
            setfillstyle(1,COLOR(22,139,242));
            int body[]={x+3*e,y+2*e,x+5*e,y+1.5*e,x+7*e,y+2*e,x+8*e,y+4*e,x+8*e,y+8*e,x+2*e,y+8*e,x+2*e,y+4*e,x+3*e,y+2*e};
            fillpoly(8,body);

            setcolor(COLOR(227,219,219));
            setfillstyle(1,COLOR(227,219,219));
            int body_2[]={x+2*e,y+7*e,x+3*e,y+6*e,x+4*e,y+5.5*e,x+6*e,y+5.5*e,x+7*e,y+6*e,x+8*e,y+7*e,x+8*e,y+8*e,x+2*e,y+8*e,x+2*e,y+7*e};
            fillpoly(9,body_2);

            setcolor(COLOR(255,102,0));
            setfillstyle(1,COLOR(255,102,0));
            int pic[]={x+4*e,y+4*e,x+6*e,y+4*e,x+5*e,y+5*e,x+4*e,y+4*e};
            fillpoly(4,pic);

            setcolor(COLOR(255,255,255));
            setfillstyle(1,COLOR(255,255,255));
            int ojo_1[]={x+3*e,y+4*e,x+4*e,y+3*e,x+4*e,y+4*e,x+3*e,y+4*e};
            fillpoly(4,ojo_1);
            int ojo_2[]={x+6*e,y+3*e,x+6*e,y+4*e,x+7*e,y+4*e,x+6*e,y+3*e};
            fillpoly(4,ojo_2);

            setcolor(COLOR(0,0,0));
            setfillstyle(1,COLOR(0,0,0));
            int ojo_3[]={x+3.5*e,y+4*e,x+4*e,y+3.5*e,x+4*e,y+4*e,x+3.5*e,y+4*e};
            fillpoly(4,ojo_3);
            int ojo_4[]={x+6*e,y+4*e,x+6*e,y+3.5*e,x+6.5*e,y+4*e,x+6*e,y+4*e};
            fillpoly(4,ojo_4);


        }

        void eliminado(int x,int y,int e){
            setfillstyle(1,4);
            setcolor(4);
            sector(x+e/2,y+e/2,0,360,e/3,e/3);
        }
        void vacio(int x,int y,int e){
            setfillstyle(1,0);
            setcolor(0);
            //sector(x+e/2,y+e/2,0,360,e/3,e/3);
            bar(x,y,x+e,y+e);
        }

        void comida(int x,int y,int e,int color){
            setcolor(COLOR(226,6,44));
            setfillstyle(1,COLOR(226,6,44));
            e=e/6;
            int pX_1[]={x+1*e,y+2*e,x+2*e,y+1.5*e,x+3*e,y+2*e,x+4*e,y+1.5*e,x+5*e,y+2*e,x+5*e,y+4*e,x+4*e,y+5*e,x+3*e,y+4.5*e,x+2*e,y+5*e,x+1*e,y+4*e,x+1*e,y+2*e};
            fillpoly(11,pX_1);

            setcolor(COLOR(255,181,182));
            setfillstyle(1,COLOR(255,181,182));
            int pX_2[]={x+4*e,y+2*e,x+4.5*e,y+2.5*e,x+4*e,y+3*e,x+3.5*e,y+2.5*e,x+4*e,y+2*e};
            fillpoly(5,pX_2);

            setcolor(COLOR(140,95,69));
            setfillstyle(1,COLOR(140,95,69));
            int pX_3[]={x+3*e,y+0.5*e,x+3*e,y+2*e,x+2.5*e,y+0.5*e,x+3*e,y+0.5*e};
            fillpoly(4,pX_3);

            setcolor(COLOR(127,166,45));
            setfillstyle(1,COLOR(127,166,45));
            int pX_4[]={x+3*e,y+1.5*e,x+4*e,y+0.5*e,x+4*e,y+1.5*e,x+3*e,y+1.5*e};
            fillpoly(4,pX_4);
        }

        void bomba(int x,int y,int e,int color){
            e=e/10;

            setcolor(COLOR(200,200,200));
            setfillstyle(1,COLOR(200,200,200));
            int cir_2[]={x+4.5*e,y+3*e,x+4.5*e,y+2*e,x+5.5*e,y+1*e,x+7*e,y+1*e,x+7*e,y+2*e,x+6.5*e,y+2*e,x+6.5*e,y+1.5*e,x+6*e,y+1.5*e,x+5.5*e,y+2*e,x+5.5*e,y+4*e,x+4.5*e,y+3*e};
            fillpoly(11,cir_2);

            setcolor(COLOR(217,17,54));
            setfillstyle(1,COLOR(217,17,54));
            int cir_3[]={x+6.5*e,y+2*e,x+7*e,y+2*e,x+7*e,y+2.5*e,x+6.5*e,y+2.5*e,x+6.5*e,y+2*e};
            fillpoly(5,cir_3);

            setcolor(COLOR(44,44,44));
            setfillstyle(1,COLOR(44,44,44));
            int cir_1[]={x+4*e,y+2.5*e,x+6*e,y+2.5*e,x+6*e,y+4*e,x+4*e,y+4*e,x+4*e,y+2.5*e};
            fillpoly(5,cir_1);

            setcolor(COLOR(66,66,66));
            setfillstyle(1,COLOR(66,66,66));
            int cir[]={x+5*e,y+3*e,x+7*e,y+4*e,x+8*e,y+6*e,x+7*e,y+8*e,x+5*e,y+9*e,x+3*e,y+8*e,x+2*e,y+6*e,x+3*e,y+4*e,x+5*e,y+3*e};
            fillpoly(9,cir);

            setcolor(COLOR(200,200,200));
            setfillstyle(1,COLOR(200,200,200));
            int cir_4[]={x+3*e,y+5*e,x+4*e,y+4*e,x+4*e,y+5*e,x+3*e,y+5*e};
            fillpoly(4,cir_4);
        }
        void V(int x,int y,int e){
            setfillstyle(1,0);
            bar(x,y,x+e,y+e);
        }
};

class Matriz{
    private:
        int juego[200][200];
        int filas;
        int columnas;
    public:
        Matriz(){

        }
        void SetMatriz(int f,int c){
            //cout<<"Inicializa matriz";
            filas=f;
            columnas=c;
            /*juego=new int[filas];
            for(int i=0;i<filas;i++){
                juego[i]=new int[columnas];
            }*/

            for(int i=0;i<filas;i++){
                for(int j=0;j<columnas;j++){
                    juego[i][j]=C;
                }
            }

            for(int i=0;i<columnas;i++){
                juego[0][i]=M;
                juego[filas-1][i]=M;
            }

            for(int i=0;i<filas;i++){
                juego[i][0]=M;
                juego[i][columnas-1]=M;
            }

            srand(time(NULL));
            for(int i=0;i<35;i++){
                ponerMuro();
            }
        }
        void ponerMuro(){
            int i=rand()%(filas-2)+1;
            int j=rand()%(columnas-2)+1;
            juego[i][j]=M;
            juego[i][j+1]=M;
            juego[i+1][j+1]=M;
        }
        int getFilas(){
            return filas;
        }
        int getColumas(){
            return columnas;
        }
        int getValor(int i,int j){
            return juego[i][j];
        }
        void setValorMatriz(int i,int j,int v){
            juego[i][j]=v;
        }
};

class Juego{
    private:
        int filas;
        int columnas;
        int xini;
        int yini;
        int escala;
        Graficos g;
        Matriz m;

        int persona_i;
        int persona_j;

        int bomba_i;
        int bomba_j;
    public:
        Juego(){

        }
        void setFilas(int f){
            filas=f;
        }
        void setColumnas(int c){
            columnas=c;
        }
        void setPosJuego(int x,int y){
            xini=x;
            yini=y;
        }
        void setEscala(int e){
            escala=e;
        }
        void crearMatriz(){
            m.SetMatriz(filas,columnas);
        }
        void mostrarJuego(){
            for(int i=0;i<m.getFilas();i++){
                for(int j=0;j<m.getColumas();j++){
                    g.V(xini+j*escala,yini+i*escala,escala);
                    if(m.getValor(i,j)==M){
                        g.muro(xini+j*escala,yini+i*escala,escala,COLOR(0,0,255));
                    }
                    if(m.getValor(i,j)==P){
                        g.heroe(xini+j*escala,yini+i*escala,escala,COLOR(255,0,255));
                    }
                    if(m.getValor(i,j)==E){
                        g.eliminado(xini+j*escala,yini+i*escala,escala);
                    }
                    if(m.getValor(i,j)==C){
                        g.comida(xini+j*escala,yini+i*escala,escala,COLOR(255,0,0));
                        //draw_manza(xini+j*e,yini+i*e,e);
                    }
                    if(m.getValor(i,j)==T){
                        g.bomba(xini+j*escala,yini+i*escala,escala,COLOR(0,255,0));
                    }
                }
            }
        }
        void poner_trampa(int&i,int&j){
            srand(time(NULL));
            do{
                //filas=15  5   15
                i=getAleatorio(persona_i-1,persona_i+1);
                j=getAleatorio(persona_j-2,persona_j+2);
                if(m.getValor(i,j)==C || m.getValor(i,j)==0 || m.getValor(i,j)==P){
                    //mat[i][j]=T;
                    m.setValorMatriz(i,j,T);
                    return;
                }
            }while(true);
        }
        int getAleatorio(int minimo,int maximo){
            return rand()%(maximo-minimo)+minimo;
        }
        void enJuego(){
            persona_i=1;
            persona_j=1;

            bomba_i=0;
            bomba_j=0;

            m.setValorMatriz(persona_i,persona_j,P);

            mostrarJuego();

            int paredes_r=0;
            int tecla=0;
            int comidas;
            bool perdiste;

            while(tecla!=13){
                tecla=getch();
                //cout<<tecla<<endl;
                //cleardevice();
                //mat[persona_i][persona_j]=0;
                m.setValorMatriz(persona_i,persona_j,0);

                //g.heroe(xini+persona_j*50,yini+persona_i*50,50,0);

                if(comidas%5==0 && tecla!=0){
                    cout<<"Bomba puesta";
                    poner_trampa(bomba_i,bomba_j);
                    g.vacio(xini+bomba_j*escala,yini+bomba_i*escala,escala);
                    g.bomba(xini+bomba_j*escala,yini+bomba_i*escala,escala,0);
                    //dib_matriz(50,50,50,mat,10,10);
                    //--->mostrarJuego();
                }
                /***********/
                if(tecla==77){
                    if(m.getValor(persona_i,persona_j+1)!=M){
                        g.vacio(xini+persona_j*escala,yini+persona_i*escala,escala);
                        persona_j++;
                        g.heroe(xini+persona_j*escala,yini+persona_i*escala,escala,COLOR(255,0,255));
                    }
                }
                if(tecla==75){
                    if(m.getValor(persona_i,persona_j-1)!=M){
                        g.vacio(xini+persona_j*escala,yini+persona_i*escala,escala);
                        persona_j--;
                        g.heroe(xini+persona_j*escala,yini+persona_i*escala,escala,COLOR(255,0,255));
                    }
                }
                if(tecla==72){
                    if(m.getValor(persona_i-1,persona_j)!=M){
                        g.vacio(xini+persona_j*escala,yini+persona_i*escala,escala);
                        persona_i--;
                        g.heroe(xini+persona_j*escala,yini+persona_i*escala,escala,COLOR(255,0,255));
                    }
                }
                if(tecla==80){
                    if(m.getValor(persona_i+1,persona_j)!=M){
                        g.vacio(xini+persona_j*escala,yini+persona_i*escala,escala);
                        persona_i++;
                        g.heroe(xini+persona_j*escala,yini+persona_i*escala,escala,COLOR(255,0,255));
                    }
                }
                /***********/
                if(tecla=='w' && paredes_r<5){
                    m.setValorMatriz(persona_i-1,persona_j,0);
                    g.vacio(xini+persona_j*escala,yini+(persona_i-1)*escala,escala);
                    paredes_r++;
                }
                if(tecla=='s' && paredes_r<5){
                    m.setValorMatriz(persona_i+1,persona_j,0);
                    g.vacio(xini+persona_j*escala,yini+(persona_i+1)*escala,escala);
                    paredes_r++;
                }
                if(tecla=='a' && paredes_r<5){
                    m.setValorMatriz(persona_i,persona_j-1,0);
                    g.vacio(xini+(persona_j-1)*escala,yini+persona_i*escala,escala);
                    paredes_r++;
                }
                if(tecla=='d' && paredes_r<5){
                    m.setValorMatriz(persona_i,persona_j+1,0);
                    g.vacio(xini+(persona_j+1)*escala,yini+persona_i*escala,escala);
                    paredes_r++;
                }
                if(m.getValor(persona_i,persona_j)==C){
                    comidas++;
                    //cout<<comidas<<endl;
                }
                if(m.getValor(persona_i,persona_j)==T){
                    m.setValorMatriz(persona_i,persona_j,E);
                    g.vacio(xini+persona_j*escala,yini+persona_i*escala,escala);
                    g.eliminado(xini+persona_j*escala,yini+persona_i*escala,escala);
                    //--->mostrarJuego();
                    perdiste=true;
                    tecla=13;
                    getch();
                    getch();
                    getch();
                }
                m.setValorMatriz(persona_i,persona_j,P);

                //--->mostrarJuego();

                //mat[persona_i][persona_j]=P;
                //dib_matriz(50,50,50,mat,10,10);
            }
        }
};

int main()
{
    initwindow(1200,600);

    while(true){
        Juego j;
        j.setFilas(15);
        j.setColumnas(25);
        j.setPosJuego(10,10);
        j.setEscala(30);
        j.crearMatriz();
        //--->j.mostrarJuego();
        j.enJuego();
    }



    getch();
    getch();
    return 0;
}