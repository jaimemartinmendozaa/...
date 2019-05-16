#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


void presentacion(void);
void ayuda(void);
void controles();
void atacar();
void asistencia();
void informacion();
int azar(int);
void campeon();

typedef struct {

	int vi; //vida restante
	int pd[4];//puntos de daño máximo cada golpe
	int ng[4]; //ng=numero de golpes
	int asistencia;//asistencia posible
	char nombre[30];
	char *ataque[4];


} boxeador;

boxeador Pacquiao;
boxeador mayweather;
int turno = 1;

int main() {

	strcpy(Pacquiao.nombre, "\nPacquiao");//estructura de Pacquiao
	Pacquiao.vi = 100;//puntos de vida iniciales del boxeador
	Pacquiao.ataque[0] = "Puñetazo "; Pacquiao.ataque[1] = "Patada"; Pacquiao.ataque[2] = "Golpe lateral izquierdo"; Pacquiao.ataque[3] = "Golpe lateral derecho";//nombres de ataques 
	Pacquiao.pd[0] = 20; Pacquiao.pd[1] = 40; Pacquiao.pd[2] = 20; Pacquiao.pd[3] = 20;//puntos de vida que quita cada ataque
	Pacquiao.ng[0] = 15; Pacquiao.ng[1] = 2; Pacquiao.ng[2] = 10; Pacquiao.ng[3] = 10;//numero de golpes de cada ataque
	Pacquiao.asistencia = 2;//asistencia de cada boxeador

	strcpy(mayweather.nombre, "\nmayweather");
	mayweather.vi = 100;
	mayweather.ataque[0] = "Puñetazo"; mayweather.ataque[1] = "Patada"; mayweather.ataque[2] = "Golpe lateral derecho"; mayweather.ataque[3] = "Golpe lateral izquierdo";
	mayweather.pd[0] = 30; mayweather.pd[1] = 35; mayweather.pd[2] = 25; mayweather.pd[3] = 25;
	mayweather.ng[0] = 15; mayweather.ng[1] = 2; mayweather.ng[2] = 10; mayweather.ng[3] = 10;
	mayweather.asistencia = 1;

	char comando;//caracter que pulsamos primero para guardarlo en la variable comando

	presentacion();//funcion presentacion
	ayuda();//funcion ayuda

	while (1)
	{

		if (turno == 1)//If-else para decidir el turno de cada uno se alterne, primero Pacquiao y luego Mayweather
			printf("%s ", Pacquiao.nombre);
		else
			printf("%s ", mayweather.nombre);



		printf("\nintroduce la letra correspondiente: ");
		comando = fgetc(stdin);//fgetc comienza a leer desde STDIN, está leyendo una línea completa, que incluye el carácter de nueva línea que terminó esa línea
		while (fgetc(stdin) != '\n');//sirve para borrar el buffer de entrada

		switch (comando)//sirve para cuando pulses una tecla nos lleve a la funcion predeterminada de ese caso.
		{
		case 'm':
			ayuda();
			break;
		case 'c':
			controles();
			break;
		case 'i':
			informacion();
			break;
		case 'a':
			atacar();
			break;
		case 'p':
			asistencia();
			break;
		case 's':
			printf("Se salio del combate\n");
			system("PAUSE");
			exit(0);
		default:
			ayuda();

		}
	}
}

void presentacion()//Presentar el juego
{
	printf("Hola, Bienvenidos al juego de Boxeo mas famoso de la ultima decada\n El juego consta de dos boxeadores de epoca como son el filipino Pacquiao y el estadounidense Floyd Mayweather.\n Ambos lucharan por ver quien es el nuevo campeon del mundo.\n Suerte y a jugar.\n");
	printf("\n");
}

void ayuda()//Menu principal donde podemos ver todas las opciones
{
	printf("m -> Menu Principal\n");
	printf("c -> Controles\n");
	printf("i -> Investigacion sobre la situacion del rival\n");
	printf("a -> Ataca al boxeador rival\n");
	printf("p -> Pedir asistencia medica\n");
	printf("s -> Salir del combate\n");
}

void controles()//Como se juega
{
	printf("\nHay 4 tipos de golpes, cada uno de ellos hace mas o menos daño y tiene un numero limitado de uso. \n Estos son:\n1-Punetazo\n2-Patada\n3-Golpe lateral izquierdo\n4-Golpe lateral derecho\n Para usar cada uno de ellos primero debera pulsar la tecla 'a' para activar la funcion de atacar");
}

void atacar()
{
	int dano;
	char ataque;

	printf("\nDecide el ataque que vas a utilizar [1-4]\n");

	ataque = fgetc(stdin);//sirve para leer un caracter del archivo asociado al puntero 
	while (fgetc(stdin) != '\n');//Sirve para borrar el buffer de entrada

	if (turno == 1) //si le toca a Pacquiao
	{
		switch (ataque)
		{
		case '1':// si elijo 1
			if (Pacquiao.ng[0] == 0)// si te quedan 0 golpes de un ataque se salta el turno al otro boxeador	
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 2;
				break;
			}
			dano = azar(Pacquiao.pd[0]);
			printf("%s uso %s\n", Pacquiao.nombre, Pacquiao.ataque[0]);// ataque que ha usado
			Pacquiao.ng[0]--;// el contador de golpe baja 1
			printf("Le has quitado %d puntos de vida\n", dano);
			mayweather.vi -= dano;//puntos de vida que quito al boxeador rival

			if (mayweather.vi <= 0)// si la vida de Mayweather es menor que 0 el campeon es Pacquiao
				campeon();
			turno = 2;
			break;
		case '2':
			if (Pacquiao.ng[1] == 0)
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 2;
				break;
			}
			dano = azar(Pacquiao.pd[1]);
			printf("%s uso %s\n", Pacquiao.nombre, Pacquiao.ataque[1]);
			Pacquiao.ng[1]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			mayweather.vi -= dano;
			if (mayweather.vi <= 0)
				campeon();
			turno = 2;
			break;
		case '3':
			if (Pacquiao.ng[2] == 0)
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 2;
				break;
			}
			dano = azar(Pacquiao.pd[2]);
			printf("%s uso %s\n", Pacquiao.nombre, Pacquiao.ataque[2]);
			Pacquiao.ng[2]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			mayweather.vi -= dano;
			if (mayweather.vi <= 0)
				campeon();
			turno = 2;
			break;
		case '4':
			if (Pacquiao.ng[3] == 0)
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 2;
				break;
			}
			dano = azar(Pacquiao.pd[3]);
			printf("%s uso %s\n", Pacquiao.nombre, Pacquiao.ataque[3]);
			Pacquiao.ng[3]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			mayweather.vi -= dano;
			if (mayweather.vi <= 0)
				campeon();
			turno = 2;
			break;
		default:
			printf("Escoja un numero entre el 1 y el 4\n");
			turno = 1;
			break;
		}

	}

	else
	{
		switch (ataque)
		{
		case '1':
			if (mayweather.ng[0] == 0)
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 1;
				break;
			}
			dano = azar(mayweather.pd[0]);
			printf("%s uso %s\n", mayweather.nombre, mayweather.ataque[0]);
			mayweather.ng[0]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			Pacquiao.vi -= dano;
			if (Pacquiao.vi <= 0)
				campeon();
			turno = 1;
			break;
		case '2':
			if (mayweather.ng[1] == 0)
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 1;
				break;
			}
			dano = azar(mayweather.pd[1]);
			printf("%s uso %s\n", mayweather.nombre, mayweather.ataque[1]);
			mayweather.ng[1]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			Pacquiao.vi -= dano;
			if (Pacquiao.vi <= 0)
				campeon();
			turno = 1;
			break;
		case '3':
			if (mayweather.ng[2] == 0)
			{
				printf("0 numero de golpes de este ataque\n");
				turno = 1;
				break;
			}
			dano = azar(mayweather.pd[2]);
			printf("%s uso %s\n", mayweather.nombre, mayweather.ataque[2]);
			mayweather.ng[2]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			Pacquiao.vi -= dano;
			if (Pacquiao.vi <= 0)
				campeon();
			turno = 1;
			break;
		case '4':
			if (mayweather.ng[3] == 0)
			{
				printf("9\n");
				turno = 1;
				break;
			}
			dano = azar(mayweather.pd[3]);
			printf("%s uso %s\n", mayweather.nombre, mayweather.ataque[3]);
			mayweather.ng[3]--;
			printf("Le has quitado %d puntos de vida\n", dano);
			Pacquiao.vi -= dano;
			if (Pacquiao.vi <= 0)
				campeon();
			turno = 2;
			break;
		default:
			printf("Escoja un numero entre el 1 y el 4\n");
			turno = 2;
			break;
		}

	}
}


void asistencia() //la funcion se utiliza cuando accionamos la tecla p para pedir asistencia
{
	if (turno == 1)//si el turno es de Pacquiao
	{
		turno = 2;
		if (Pacquiao.asistencia == 0)//si el contador de tus asistencias es igual a 0 no puedes pedir más 
		{
			printf("no puedes pedir asistencia medica, has gastado toda tu asistencia medica\n");
		}
		else // si puedes pedir asistencia médica, tu contador baja uno y suma 45 a tus puntos de vida
		{
			Pacquiao.asistencia -= 1;
			Pacquiao.vi += 45;
			if (Pacquiao.vi > 100) Pacquiao.vi = 100;// si con asistencia medica tu vida sube mas de cien tu vida sigue siendo cien
			printf("Acabas de recibir asistencia medica, ahora tu vida es de %d\n", Pacquiao.vi);
		}
	}
	else //si el turno es de Mayweather
	{
		turno = 1;
		if (mayweather.asistencia == 0) {

			printf("no puedes pedir asistencia medica, has gastado toda tu asistencia medica\n");

		}
		else {

			mayweather.asistencia -= 1;
			mayweather.vi += 60;
			if (mayweather.vi > 100) mayweather.vi = 100;
			printf("Acabas de recibir asistencia médica, ahora tu vida es de %d\n", mayweather.vi);
		}
	}
}

void informacion() //Funcion que se abre para dar informacion a cerca del combate
{
	if (turno == 1) {
		printf("/////\n");
		printf("%s\n", Pacquiao.nombre);
		printf("Tus puntos de vida son:%d\n", Pacquiao.vi);
		printf("\t- . -TUS ATAQUES- . -\n");
		printf("\t%s numero de golpes restantes:%d\n", Pacquiao.ataque[0], Pacquiao.ng[0]);
		printf("\t%s numero de golpes restantes:%d\n", Pacquiao.ataque[1], Pacquiao.ng[1]);
		printf("\t%s numero de golpes restantes:%d\n", Pacquiao.ataque[2], Pacquiao.ng[2]);
		printf("\t%s numero de golpes restantes:%d\n", Pacquiao.ataque[3], Pacquiao.ng[3]);
		printf("\t-.-.-.-.-.-.-.-.-\n");
		printf("Asistencia medica posible:%d\n", Pacquiao.asistencia);
		printf("Los puntos de vida de Mayweather son:%d\n", mayweather.vi);
		printf("/////\n");
	}

	if (turno == 2) {
		printf("/////\n");
		printf("%s\n", mayweather.nombre);
		printf("Tus puntos de vida son:%d\n", mayweather.vi);
		printf("- . -TUS ATAQUES- . -\n");
		printf("\t%s numero de golpes restantes:%d\n", mayweather.ataque[0], mayweather.ng[0]);
		printf("\t%s numero de golpes restantes:%d\n", mayweather.ataque[1], mayweather.ng[1]);
		printf("\t%s numero de golpes restantes:%d\n", mayweather.ataque[2], mayweather.ng[2]);
		printf("\t%s numero de golpes restantes:%d\n", mayweather.ataque[3], mayweather.ng[3]);
		printf("\t-.-.-.-.-.-.-.-.-\n");
		printf("Asistencia medica posible:%d\n", mayweather.asistencia);
		printf("Los puntos de vida de Pacquiao son:%d\n", Pacquiao.vi);
		printf("/////\n");
	}
}

int azar(int maximo) //Sirve para crear numeros aleatorios que luego usamos en la funcion atacar para quitar los diferentes puntos de vida.
{
	srand(time(NULL));//Instrucción que inicializa el generador de números aleatorios
	return rand() % (maximo);//Guarda el numero random en la variable maximo
}

void campeon()//Esta funcion se activa cuando los puntos de vida de uno son 0
{
	if (turno == 1)
	{
		printf("////////////////////////*/\n");
		printf("/ %s es el nuevo campeon del mundo de boxeo /\n", Pacquiao.nombre);
		printf("////////////////////////*/\n");
		system("PAUSE");
		exit(0);
	}
	else
	{
		printf("////////////////////////*/\n");
		printf("/ %s es el nuevo campeon del mundo de boxeo /\n", mayweather.nombre);
		printf("////////////////////////*/\n");
		system("PAUSE");
		exit(0);
	}
}