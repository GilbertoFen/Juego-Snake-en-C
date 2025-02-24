#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

/*
	Dimensiones de la pantalla
	x = 639 255, 132, 51 
	y = 479
*/

int colorF= RGB(255, 132, 51  );
int colorF2= RGB(114, 235, 246);
int colorM=RGB(255, 72, 51 );
typedef struct nodo
{
	int x;
	int y;
	struct nodo *sig;
}movimiento;

void agregarMovimiento(movimiento **nodo, int x, int y);
void traerMovimiento(movimiento *nodo, int *x, int *y );

void crearSerpiente(int *x, int *y);
void borrarSerpiente(movimiento **cola);

void crearFruta(int *xf, int *yf);
void comerFruta(int *x, int *y ,int *xf, int *yf, int *contador, movimiento **cola);

void direccion(int *x, int *y);
bool perder(int x, int y, int movX, int movY);
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
	// Movimiento en x & y
	movimiento *cola = NULL;
	int x = 50, y = 50, xf = 0, yf = 0, contador=0, velocidad = 150;
    int movimientoX = 25, movimientoY = 0;
    char tecla;
    
    char puntaje[50];
	// Posicion aleatoria de la "comida"
	setcolor(colorF2);
 	setfillstyle(1,colorF2);
 	rectangle(0,0,getmaxx(), getmaxy());
 	floodfill(1,1,colorF2);
 	
    setcolor(colorF);
    setfillstyle(1,colorF);
    rectangle(0,0,getmaxx(), 20);
    floodfill(1,1,colorF);
    
	crearFruta(&xf, &yf);
    
    do
    {
    	setcolor(WHITE);
    	sprintf(puntaje, "Puntaje: %d", contador);
        outtextxy(400, 2, puntaje);

        // Dibujar el cuadrado inicial    
        crearSerpiente(&x, &y);
        
        comerFruta(&x, &y, &xf, &yf, &contador, &cola);
        agregarMovimiento(&cola, x, y);
        delay(velocidad-(2*contador));
        borrarSerpiente(&cola);
		// Cambiar la direccion del cuadrado 
        x += movimientoX;
        y += movimientoY;
        
        if (kbhit())
        {
            direccion(&movimientoX, &movimientoY);
        }
        if(perder(x,y,movimientoX, movimientoY))
		{
			break;
		}
    }
    while(!(x < 0 || x > (getmaxx() -25) || y < 20 || y > (getmaxy() - 25)));
	cleardevice();
    settextstyle(1, 0, 4);
    outtextxy(150, getmaxy() / 2, "GAME OVER");
    settextstyle(1, 0, 2);
    outtextxy(250, getmaxy() / 2+100, puntaje);
    getch();
    printf("x= %d  \n y= %d", getmaxx(), getmaxy());
    closegraph();
    return 0;
}

///////////// FUNCIONES DE COLA
void agregarMovimiento(movimiento **nodo, int x, int y)
{
	movimiento *nuevo = (movimiento *) malloc(sizeof(movimiento));
	nuevo->x = x;
	nuevo->y = y;
	nuevo->sig = NULL;
	if(*nodo==NULL){
		*nodo = nuevo;
	}
	else{
		agregarMovimiento(&(*nodo)->sig, x,y);	
	}
}
void traerMovimiento(movimiento ***nodo, int *x, int *y )
{
	printf("\n%d", (**nodo)->sig);
	*x = (**nodo)->x;
	*y = (**nodo)->y;
	(**nodo)= (**nodo)->sig;
}
///////////////// FUNCIONES DE COLA

void crearSerpiente(int *x, int *y)
{	setcolor(GREEN);
	setfillstyle(1,GREEN);
	circle(*x+13,*y+13, 13);
	floodfill(*x+13, *y+13 ,GREEN);
	setcolor(WHITE);
		
}

void borrarSerpiente(movimiento **cola)
{
	int x = 0, y = 0;
	traerMovimiento(&cola, &x, &y);
	setcolor(colorF2);
	setfillstyle(1,colorF2);
	circle(x+13,y+13, 13);
	floodfill(x+13, y+13 ,colorF2);
	setcolor(WHITE);
}

void crearFruta(int *xf, int *yf)
{
	do{
		srand(time(NULL));
		// Posicion aleatoria de la "comida"
	    *xf = ((rand() % (getmaxx() - 25)) /25 * 25) + 5;
	    *yf = ((rand() % (getmaxy() - 50)) /25 * 25) + 5 + 25;
	}
	while(getpixel(*xf, *yf) == GREEN);
	setcolor(colorM);
	setfillstyle(1,colorM);
	circle(*xf+8,*yf+8, 8);
	arc(*xf+4, *yf+4,0,270, 6 );
	arc(*xf+10, *yf+4,180,120, 6 );
	floodfill(*xf+3,*yf+3, colorM);
	floodfill(*xf+8,*yf+8, colorM);
	floodfill(*xf+10,*yf+4, colorM);
	setcolor(WHITE);
}
 
void comerFruta(int *x, int *y, int *xf, int *yf, int *contador, movimiento **cola)
{	
	if( (*y+25 > *yf && *y < *yf+8)&&(*x < *xf+8 && *x+25 > *xf))
    {
    	agregarMovimiento(cola, getmaxx()+50, getmaxy()+50);
    	setcolor(GREEN);
		setfillstyle(1,GREEN);
		circle(*xf+8,*yf+8, 8);
		floodfill(*xf+8,*yf+8, GREEN);
       	crearFruta(xf, yf);
        (*contador)++;
        setcolor(WHITE);
    }
}
void direccion(int *movimientoX, int *movimientoY)
{
	char tecla = getch();
	int xProx = 0, yProx = 0;
	if ((tecla == 'w'||tecla == 'W' || tecla == 72) && *movimientoY !=25)
	{
		*movimientoX = 0;
		*movimientoY = -25;
	}
    else if ((tecla == 'a'||tecla == 'A' || tecla == 75) && *movimientoX !=25)
    {
        *movimientoX = -25;
        *movimientoY = 0;
    }
    else if ((tecla == 's'||tecla == 'S' || tecla == 80)&& *movimientoY !=-25)
    {
        *movimientoX = 0;
        *movimientoY = 25;
    }
    else if ((tecla == 'd'||tecla == 'D' || tecla == 77) && *movimientoX !=-25)
    {
        *movimientoX = 25;
        *movimientoY = 0;
    }
}
bool perder(int x, int y, int movX, int movY)
{
	if(movX == 0)
	{
		y+=movY+10;
		x += 10;
	}
	else if(movY == 0)
	{
		x += movX + 10;
		y += 10;
	}
	return getpixel(x,y) == GREEN;				
}


