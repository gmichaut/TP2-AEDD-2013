/* GRUPO NRO 5
 INTEGRANTES:
 GABRIEL MICHAUT
 gmichaut@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include "admin.h"

#define randomize (srand(time(NULL)))
#define random(num) (rand()%(num))
#define MAXSALA 1500
#define MAXPELI 20
#define MAXNOMBRE 50
#define ANYOACTUAL 2013

/* Estructura Peliculas */
struct Peliculas {
	char nombre[MAXNOMBRE];
	int anyo;
	char genero;
	int mce;
	char fac[12];
	int marcaBaja;
};

/* Sinonimo tipo de dato */
typedef struct Peliculas peliculas;

/* Estructura Salas */
struct Salas {
	char nombreSala[20];
	char generoSala;
	int capacidad;
	peliculas enCartelera[10];
	int asignadas;
};

/* Sinonimo tipo de dato */
typedef struct Salas salas;

/* Prototipo Funciones */
void inicio();
void autenticar(usuario pu[]);
void gestionPeliculas(peliculas *pp, int *indice);
void altaManual(peliculas *pp, int *indice);
void altaMasiva(peliculas *pp, int *indice);
void bajaPeli(peliculas *pp, int *indice);
void modificarPeli(peliculas *pp, int *indice);
void listado(peliculas *pp, int *indice);
void renovarCartelera(salas *ps, peliculas *pp, int *indice);
void gestionSalas(salas *ps, int *indice);
void fechaActual();
void noPeli();
int validoFecha(char *fecha);
/* Emulamos la funcion getch de la libreria conio.h */
int getch();

int main() {
	/* Array de estructuras */
	peliculas Peli[MAXPELI];
	salas Sala[3];
	
	/* Puntero a estructura */
	peliculas *ptrPeli;
	ptrPeli = Peli;
	
	salas *ptrSala;
	ptrSala = Sala;
	
	usuario *ptrUser;
	ptrUser = User;
	
	/* Reserva espacio almacenamiento puntero */
	ptrPeli = malloc(sizeof(Peli)*2);
	ptrSala = malloc(sizeof(Sala)*2);
	ptrUser = malloc(sizeof(User));
	
	/* Indice cantidad peliculas cargadas */
	int indice = 0;
	int *ptrIndice;
	ptrIndice = &indice;
	
	/* Autenticamos el usuario */
	autenticar(User);
	
	int opcion = 0;
    char buffer[256];
	inicio();
	do {
		system("clear");
		inicio();
		printf("\ninicio\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n             1. Gestion de Peliculas | 2. Renovar Cartelera | 3. Gestion de Salas | 4. Salir del Sistema\n\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("-> ");
        
		scanf("%s",buffer);
        /* Previene que falle al ingresar cualquier caracter que no sea un digito */
        opcion = atoi(buffer);
        
		switch (opcion) {
			case 0:
				break;
                
			case 1: gestionPeliculas(ptrPeli, ptrIndice);
				opcion = 0;
                break;
                
            case 2: renovarCartelera(ptrSala, ptrPeli, ptrIndice);
                opcion = 0;
				break;
                
            case 3: gestionSalas(ptrSala, ptrIndice);
                opcion = 0;
				break;
                
            case 4:
                system("clear");
                inicio();
                printf("\nsalir\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("\n                                               GRACIAS POR UTILIZAR CINAMON\n\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
				break;
                
            default:
                opcion = 0;
				break;
		}
	} while(opcion == 0);
	
	/* Libera espacio reservado en memoria */
	free(ptrPeli);
	free(ptrSala);
	free(ptrUser);
	return 0;
}

void gestionPeliculas(peliculas *pp, int *indice) {
	int opcion;
    char buffer[256];
	
	system("clear");
	inicio();
	do {
		getchar();
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n             1. Alta Manual | 2. Alta Masiva | 3. Baja | 4. Modificacion | 5. Listado | 9. Menu anterior\n\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("-> ");
        
		scanf("%s",buffer);
        /* Previene que falle al ingresar cualquier caracter que no sea un digito */
        opcion = atoi(buffer);
		
        switch (opcion) {
			case 0:
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("\n                                                OPCION INCORRECTA\n\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                getchar();
                break;
                
            case 1: altaManual(pp, indice);
                opcion = 0;
				break;
                
            case 2: altaMasiva(pp, indice);
                opcion = 0;
				break;
                
            case 3: bajaPeli(pp, indice);
                opcion = 0;
				break;
                
            case 4: modificarPeli(pp, indice);
                opcion = 0;
				break;
                
            case 5: listado(pp, indice);
                opcion = 0;
				break;
                
            case 9:
				break;
                
            default:
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("\n                                                OPCION INCORRECTA\n\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                getchar();
                opcion = 0;
				break;
		}
	} while(opcion == 0);
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void altaManual(peliculas *pp, int *indice) {
	char opcion, n_genero, nombrePeli[MAXNOMBRE], buffer[256], bufferexp[256];
    int anyop, cantexp, h, k;
    peliculas temp;
	
	/* Verifica si se alcanzo el limite de peliculas */
	if(*indice == MAXPELI){
        system("clear");
        inicio();
        printf("\ninicio >> gestion de peliculas >> alta manual\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n                                            NO SE PUEDEN CARGAR MAS PELICULAS\n\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	else {
		do {
			getchar();
			fflush(stdin);
			system("clear");
			inicio();
			printf("\ninicio >> gestion de peliculas >> alta manual\n");
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("INGRESE EL NOMBRE DE LA PELICULA: ");
			fgets(nombrePeli,MAXNOMBRE,stdin);
            strncpy(pp[*indice].nombre, nombrePeli, strlen(nombrePeli)-1);
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			do {
				printf("INGRESE EL AÑO DE ESTRENO: ");
				scanf("%s",buffer);
                anyop = atoi(buffer);
                fflush(stdin);
			} while((anyop > ANYOACTUAL) || (anyop < 1900));
            pp[*indice].anyo = anyop;
            
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			do {
				fflush(stdin);
				getchar();
				printf("SELECCIONE EL GENERO (A)CCION - (C)OMEDIA - (D)RAMA - (S)USPENSO - (T)ERROR : ");
				scanf("%c",&n_genero);
				switch (n_genero) {
					case 'A':
					case 'a':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'C':
					case 'c':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'D':
					case 'd':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'S':
					case 's':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'T':
					case 't':
						pp[*indice].genero = toupper(n_genero);
						break;
					default: n_genero = -1;
						break;
				}
			} while(n_genero == -1);
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			do {
				printf("INGRESE LA CANTIDAD EXPECTADORES QUE SE ESPERAN: ");
				scanf("%s",bufferexp);
                cantexp = atoi(bufferexp);
                fflush(stdin);
			} while((cantexp > MAXSALA) || (cantexp < 1));
            pp[*indice].mce = cantexp;
            
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			
			/* Pelicula se carga con estado "Vigente" */
			pp[*indice].marcaBaja = 0;
			
			/* Incrementa en 1 indice de peliculas cargadas */
			*indice += 1;
			
            /* Ordena las peliculas en orden descendente a medida que se van cargando */
            for (h = 0; h < *indice; h++){
                for (k = h + 1; k < *indice; k++) {
                    if (strcmp(pp[h].nombre, pp[k].nombre) > 0) {
                        temp = pp[h];
                        pp[h] = pp[k];
                        pp[k] = temp;
                    }
                    
                }
            }
            
			system("clear");
			inicio();
			printf("\ninicio >> gestion de peliculas >> alta manual\n");
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n                                           CANTIDAD PELICULAS CARGADAS: %d\n\n", *indice);
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("DESEA CARGAR MAS PELICULAS? (S)I - (N)O: ");
			scanf("%c",&opcion);
		} while (opcion == 's' || opcion == 'S');
	}
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void altaMasiva(peliculas *pp, int *indice) {
	int i, j, k;
	char ch, gen[] = {'A','C','D','S','T'};
    peliculas temp;
	
	randomize;
	
	if(*indice == MAXPELI){
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> alta masiva\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n                                           NO SE PUEDEN CARGAR MAS PELICULAS\n\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	else {
		for (i = *indice; i < MAXPELI; i++) {
			for(j = 0; j < MAXNOMBRE; j++){
				/* Genera 50 caracteres aleatorios a-z */
				ch = 'a' + rand() % (('z'-'a') + 1);
				pp[*indice].nombre[j] = ch;
			}
			/* Genera Años entre 1900 y 2013 */
			pp[*indice].anyo = 1900 + (rand() % (int)(ANYOACTUAL - 1900 + 1));
			
			/* Genera MCE */
			pp[*indice].mce = random(MAXSALA+1);
			
			/* Inicializa FAC en blanco */
			strcpy(pp[*indice].fac, "");
			
			/* Asigna el genero aleatorio */
			pp[*indice].genero = gen[random(5)];
			
			/* Se asigna marcaBaja en 0. significa que estan vigentes */
			pp[*indice].marcaBaja = 0;
			
			/* incremento el indice de peliculas */
			*indice += 1;
		}
        /* Ordena las peliculas descendentemente */
        for (i = 0; i < *indice; i++){
            for (k = i + 1; k < *indice; k++) {
                if (strcmp(pp[i].nombre, pp[k].nombre) > 0) {
                    temp = pp[i];
                    pp[i] = pp[k];
                    pp[k] = temp;
                }
                
            }
        }
        
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> alta masiva\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\n                                           CANTIDAD PELICULAS CARGADAS: %d\n\n",*indice);
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void bajaPeli(peliculas *pp, int *indice) {
	/* marcaBaja = 0 : VIGENTE
     marcaBaja = 1 : DADA DE BAJA */
	
	int i, j, h, num, aux, bandera = -1, pos[MAXPELI];
	char opcion, nombrePeli[MAXNOMBRE];
	char *ptr;
	
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
        system("clear");
        inicio();
        printf("\ninicio >> gestion de peliculas >> baja\n");
		noPeli();
	}
	else {
        
		system("clear");
		inicio();
		
		printf("\ninicio >> gestion de peliculas >> baja\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("INGRESE EL NOMBRE O PARTE DEL NOMBRE A BUSCAR: ");
		getchar();
		
		scanf("%s", nombrePeli);
		i = j = 0;
		printf("\n");
        printf("\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
		printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
        while(i < *indice){
			ptr = strstr(pp[i].nombre, nombrePeli);
			/* Verifica que la busqueda haya arrojado resultados */
			if(ptr != NULL) {
				if (j < 9)
                    printf("%d.  ",j+1);
                else
                    printf("%d. ",j+1);
                printf("%s", pp[i].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (h = 0; h < (MAXNOMBRE - strlen(pp[i].nombre)); h++)
                    printf(" ");
                printf(" | %d ", pp[i].anyo);
                switch (pp[i].genero) {
                    case 'A':
                        printf("|  ACCION  ");
                        break;
                    case 'C':
                        printf("|  COMEDIA ");
                        break;
                    case 'D':
                        printf("|  DRAMA   ");
                        break;
                    case 'S':
                        printf("| SUSPENSO ");
                        break;
                    case 'T':
                        printf("|  TERROR  ");
                        break;
                }
                if (pp[i].mce < 10)
                    printf("|   %d   ", pp[i].mce);
                else if (pp[i].mce < 100)
                    printf("|  %d   ", pp[i].mce);
                else if (pp[i].mce < 1000)
                    printf("|  %d  ", pp[i].mce);
                else
                    printf("|  %d ", pp[i].mce);
                
                /* Deja espacio en blanco si no hay fecha asignada */
                if(strlen(pp[i].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", pp[i].fac);
                printf("| %s\n", ((pp[i].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
                printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
				pos[j] = i;
				j++;
				bandera = 0;
			}
			i++;
		}
		printf("CANTIDAD PELICULAS ENCONTRADAS: %d\n",j);
        
		/* Si no encuentra peliculas muestra msj y vuelve al menu anterior */
		if(bandera != 0){
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n                                            NO SE ENCONTRO NINGUNA PELICULA\n\n");
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("\nPRESIONE ENTER PARA CONTINUAR..");
			getchar();
		}
		else {
			do {
                printf("\nNUMERO DE PELICULA A DAR DE BAJA: ");
                scanf("%d",&num);
			} while(num < 0 || num >= j+1);
            
			do {
				getchar();
				printf("\nCONFIRMA LOS CAMBIOS? (S)I - (N)O: ");
				scanf("%c",&opcion);
                
				switch (opcion) {
					case 'S':
					case 's':
						aux = pos[num-1];
						pp[aux].marcaBaja = 1;
						system("clear");
						inicio();
						printf("\nSE HA DADO DE BAJA LA SIGUIENTE PELICULA:\n");
						printf("------------------------------------------------------------------------------------------------------------------------\n");
						printf("\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
                        printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
                        if (aux < 9)
                            printf("%d.  ",aux+1);
                        else
                            printf("%d. ",aux+1);
                        printf("%s", pp[aux].nombre);
                        /* Formatea el nombre para mostrar en tabla */
                        for (j = 0; j < (MAXNOMBRE - strlen(pp[aux].nombre)); j++)
                            printf(" ");
                        printf(" | %d ", pp[aux].anyo);
                        switch (pp[aux].genero) {
                            case 'A':
                                printf("|  ACCION  ");
                                break;
                            case 'C':
                                printf("|  COMEDIA ");
                                break;
                            case 'D':
                                printf("|  DRAMA   ");
                                break;
                            case 'S':
                                printf("| SUSPENSO ");
                                break;
                            case 'T':
                                printf("|  TERROR  ");
                                break;
                        }
                        if (pp[aux].mce < 10)
                            printf("|   %d   ", pp[aux].mce);
                        else if (pp[aux].mce < 100)
                            printf("|  %d   ", pp[aux].mce);
                        else if (pp[aux].mce < 1000)
                            printf("|  %d  ", pp[aux].mce);
                        else
                            printf("|  %d ", pp[aux].mce);
                        
                        /* Deja espacio en blanco si no hay fecha asignada */
                        if(strlen(pp[aux].fac) == 0)
                            printf("|            ");
                        else
                            printf("| %s ", pp[aux].fac);
                        printf("| %s\n", ((pp[aux].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
                        printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
						printf("\nPRESIONE ENTER PARA CONTINUAR..");
						getchar();
						break;
					case 'N':
					case 'n':
						printf("------------------------------------------------------------------------------------------------------------------------\n");
						printf("\n                                                NO SE REALIZARON CAMBIOS\n\n");
						printf("------------------------------------------------------------------------------------------------------------------------\n");
						printf("\nPRESIONE ENTER PARA CONTINUAR..");
						getchar();
						break;
					default: opcion = -1;
						break;
				}
			} while(opcion == -1);
		}
	}
	
	/* Vuelve bandera a su estado inicial */
	bandera = -1;
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void modificarPeli(peliculas *pp, int *indice) {
	int i, j, k, num, aux, bandera = -1, opcion, n_anyo, n_mce, pos[MAXPELI];
	char n_genero, nombrePeli[MAXNOMBRE];
	char *ptr;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
        system("clear");
        inicio();
        printf("\ninicio >> gestion de peliculas >> modificar\n");
		noPeli();
	}
	else {
		getchar();
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> modificar\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\nNOMBRE O PARTE DEL NOMBRE A BUSCAR: ");
		
		scanf("%s", nombrePeli);
		printf("\n");
        printf("\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
		printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
		i = j = 0;
		while(i < *indice){
			/* Compara la subcadena con el nombre de pelicula */
			ptr = strstr(pp[i].nombre, nombrePeli);
			/* Verifica que la busqueda haya arrojado resultados */
			if(ptr != NULL) {
				if (j < 9)
                    printf("%d.  ",j+1);
                else
                    printf("%d. ",j+1);
                printf("%s", pp[i].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (k = 0; k < (MAXNOMBRE - strlen(pp[i].nombre)); k++)
                    printf(" ");
                printf(" | %d ", pp[i].anyo);
                switch (pp[i].genero) {
                    case 'A':
                        printf("|  ACCION  ");
                        break;
                    case 'C':
                        printf("|  COMEDIA ");
                        break;
                    case 'D':
                        printf("|  DRAMA   ");
                        break;
                    case 'S':
                        printf("| SUSPENSO ");
                        break;
                    case 'T':
                        printf("|  TERROR  ");
                        break;
                }
                if (pp[i].mce < 10)
                    printf("|   %d   ", pp[i].mce);
                else if (pp[i].mce < 100)
                    printf("|  %d   ", pp[i].mce);
                else if (pp[i].mce < 1000)
                    printf("|  %d  ", pp[i].mce);
                else
                    printf("|  %d ", pp[i].mce);
                
                /* Deja espacio en blanco si no hay fecha asignada */
                if(strlen(pp[i].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", pp[i].fac);
                printf("| %s\n", ((pp[i].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
                printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
				pos[j] = i;
				j++;
				bandera = 0;
			}
			i++;
		}
		printf("CANTIDAD PELICULAS ENCONTRADAS: %d\n",j);
        
		/* Si no encuentra peliculas muestra msj y vuelve al menu anterior */
		if(bandera != 0) {
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\n                                     NO SE ENCONTRO NINGUNA PELICULA\n\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nPRESIONE ENTER PARA CONTINUAR..");
			getchar();
		}
		else {
			do {
                printf("\nNUMERO DE PELICULA A MODIFICAR: ");
                scanf("%d",&num);
			} while(num < 0 || num >= j+1);
			
			/* Almacena la posicion de la pelicula de la estructura */
			aux = pos[num-1];
			
			do {
				fflush(stdin);
				system("clear");
				inicio();
				printf("\nPELICULA A MODIFICAR:\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
                printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
                if (aux < 9)
                    printf("%d.  ",aux+1);
                else
                    printf("%d. ",aux+1);
                printf("%s", pp[aux].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (k = 0; k < (MAXNOMBRE - strlen(pp[aux].nombre)); k++)
                    printf(" ");
                printf(" | %d ", pp[aux].anyo);
                switch (pp[aux].genero) {
                    case 'A':
                        printf("|  ACCION  ");
                        break;
                    case 'C':
                        printf("|  COMEDIA ");
                        break;
                    case 'D':
                        printf("|  DRAMA   ");
                        break;
                    case 'S':
                        printf("| SUSPENSO ");
                        break;
                    case 'T':
                        printf("|  TERROR  ");
                        break;
                }
                if (pp[aux].mce < 10)
                    printf("|   %d   ", pp[aux].mce);
                else if (pp[aux].mce < 100)
                    printf("|  %d   ", pp[aux].mce);
                else if (pp[aux].mce < 1000)
                    printf("|  %d  ", pp[aux].mce);
                else
                    printf("|  %d ", pp[aux].mce);
                
                /* Deja espacio en blanco si no hay fecha asignada */
                if(strlen(pp[aux].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", pp[aux].fac);
                printf("| %s\n", ((pp[aux].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
                printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
				printf("\n\nSELECCIONE LA MODIFICACION A REALIZAR:\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("                                 1. Año | 2. Genero | 3. MCE | 4. Volvel al menu anterior\n");
				printf("------------------------------------------------------------------------------------------------------------------------\n");
				printf("-> ");
				scanf("%d", &opcion);
				switch (opcion) {
					case 1: do {
                        getchar();
                        printf("\nINGRESE EL NUEVO ANYO: ");
                        scanf("%d",&n_anyo);
                    } while(n_anyo < 1900 || n_anyo > ANYOACTUAL);
                        pp[aux].anyo = n_anyo;
						break;
					case 2:	do {
                        fflush(stdin);
                        getchar();
                        printf("\nINGRESE EL NUEVO GENERO: ");
                        scanf("%c",&n_genero);
                        switch (n_genero) {
                            case 'A':
                            case 'a':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'C':
                            case 'c':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'D':
                            case 'd':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'S':
                            case 's':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'T':
                            case 't':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            default: n_genero = -1;
                                break;
                        }
                    } while(n_genero == -1);
						break;
					case 3: do {
                        getchar();
                        printf("\nINGRESE EL NUEVO MCE: ");
                        scanf("%d",&n_mce);
                    } while(n_mce < 0 || n_mce > MAXSALA);
                        pp[aux].mce = n_mce;
						break;
					case 4:
						break;
					default: opcion = -1;
						break;
				}
			} while(opcion == -1);
            
            system("clear");
            inicio();
            printf("\nSE HA MODIFICADO LA SIGUIENTE PELICULA:\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
            printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
            if (aux < 9)
                printf("%d.  ",aux+1);
            else
                printf("%d. ",aux+1);
			printf("%s", pp[aux].nombre);
            /* Formatea el nombre para mostrar en tabla */
            for (j = 0; j < (MAXNOMBRE - strlen(pp[aux].nombre)); j++)
                printf(" ");
            printf(" | %d ", pp[aux].anyo);
            switch (pp[aux].genero) {
                case 'A':
                    printf("|  ACCION  ");
                    break;
                case 'C':
                    printf("|  COMEDIA ");
                    break;
                case 'D':
                    printf("|  DRAMA   ");
                    break;
                case 'S':
                    printf("| SUSPENSO ");
                    break;
                case 'T':
                    printf("|  TERROR  ");
                    break;
            }
            if (pp[aux].mce < 10)
                printf("|   %d   ", pp[aux].mce);
            else if (pp[aux].mce < 100)
                printf("|  %d   ", pp[aux].mce);
            else if (pp[aux].mce < 1000)
                printf("|  %d  ", pp[aux].mce);
            else
                printf("|  %d ", pp[aux].mce);
            
            /* Deja espacio en blanco si no hay fecha asignada */
            if(strlen(pp[aux].fac) == 0)
                printf("|            ");
            else
                printf("| %s ", pp[aux].fac);
            printf("| %s\n", ((pp[aux].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
            printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
            printf("\nPRESIONE ENTER PARA CONTINUAR..");
            getchar();
		}
	}
	/* Vuelve bandera a su estado inicial */
	bandera = -1;
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void listado(peliculas *pp, int *indice) {
	int i, j;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
        system("clear");
        inicio();
        printf("\ninicio >> gestion de peliculas >> listado\n");
		noPeli();
	}
	else {
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> listado\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
		printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
		for(i = 0; i < *indice; i++) {
            if (i < 9)
                printf("%d.  ",i+1);
            else
                printf("%d. ",i+1);
            printf("%s", pp[i].nombre);
            
            /* Formatea el nombre para mostrar en tabla */
            for (j = 0; j < (MAXNOMBRE - strlen(pp[i].nombre)); j++)
                printf(" ");
            printf(" | %d ", pp[i].anyo);
            switch (pp[i].genero) {
                case 'A':
                    printf("|  ACCION  ");
                    break;
                case 'C':
                    printf("|  COMEDIA ");
                    break;
                case 'D':
                    printf("|  DRAMA   ");
                    break;
                case 'S':
                    printf("| SUSPENSO ");
                    break;
                case 'T':
                    printf("|  TERROR  ");
                    break;
            }
            
            if (pp[i].mce < 10)
                printf("|   %d   ", pp[i].mce);
            else if (pp[i].mce < 100)
                printf("|  %d   ", pp[i].mce);
            else if (pp[i].mce < 1000)
                printf("|  %d  ", pp[i].mce);
            else
                printf("|  %d ", pp[i].mce);
            
            /* Deja espacio en blanco si no hay fecha asignada */
            if(strlen(pp[i].fac) == 0)
                printf("|            ");
            else
                printf("| %s ", pp[i].fac);
            printf("| %s\n", ((pp[i].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
            printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
		}
		printf("\n");
	}
	/* Limpia buffer y vuelve al menu anterior */
	printf("PRESIONE ENTER PARA CONTINUAR..");
	getchar();
	fflush(stdin);
}

void renovarCartelera(salas *ps, peliculas *pp, int *indice) {
	int i, j, k, h, n, genSala, fechaOK = 0, indiceGen = 4;
	char gen[] = {'A','C','D','S','T'};
	char fechahoy[12];
	
	fechaActual(fechahoy);
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
        inicio();
        printf("\ninicio >> renovar cartelera\n");
        noPeli();
	}
	else {
		
		/* Inicializo las salas con su respectivo nombre y capacidad */
		strcpy(ps[0].nombreSala, "Aleandro");
		ps[0].capacidad = 1500;
		strcpy(ps[1].nombreSala, "Zorrilla");
		ps[1].capacidad = 200;
		strcpy(ps[2].nombreSala, "Nu");
		ps[2].capacidad = 525;
		strcpy(ps[3].nombreSala, "Eve");
		ps[3].capacidad = 525;
		
		for(i = 0; i < 4; i++){
			fflush(stdin);
			getchar();
			system("clear");
			inicio();
			printf("\ninicio >> renovar cartelera\n");
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("\nSELECCIONE EL GENERO PARA LA SALA \"%s\":\t Accion - Comedia - Drama - Suspenso - Terror\n\n", ps[i].nombreSala);
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("GENEROS DISPONIBLES: ");
			
			/* Muestra los generos disponibles */
			for(j = 0; j <= indiceGen; j++) {
                switch (gen[j]) {
                    case 'A':
                        printf("| %d. ACCION ",j+1);
                        break;
                    case 'C':
                        printf("| %d. COMEDIA ",j+1);
                        break;
                    case 'D':
                        printf("| %d. DRAMA ",j+1);
                        break;
                    case 'S':
                        printf("| %d. SUSPENSO ",j+1);
                        break;
                    case 'T':
                        printf("| %d. TERROR ",j+1);
                        break;
                }
            }
			
			/* Verifica que el numero ingresado este dentro del rango */
			do {
				printf("\nINGRESE EL NUMERO CORRESPONDIENTE: ");
				scanf("%d",&genSala);
			} while((genSala > j) || (genSala < 0));
			
			/* Asigna e imprime el genero seleccionado a la sala */
			ps[i].generoSala = gen[genSala-1];
			
			/* Elimina de la lista de generos disponibles al genero seleccionado */
			for(k = genSala-1; k <= indiceGen; k++)
				gen[k] = gen[k+1];
			
			/* Busca y asigna las peliculas a la sala de acuerdo al genero seleccionado */
			for(h = 0, n = 0; h < *indice; h++){
				
				/* Verifica la FAC con la fecha actual. En caso de haber pasado mas de 7 dias da el OK. -2604 y 8897 num magicos que indican dif 7 dias */
				if((validoFecha(pp[h].fac) - validoFecha(fechahoy) >= -2604) || (validoFecha(pp[h].fac) - validoFecha(fechahoy) <= 8897))
					fechaOK = 1;
				
				/* Verifica los criterios para que la pelicula pueda ser asignada a la sala */
				if((pp[h].genero == ps[i].generoSala) && (pp[h].mce <= ps[i].capacidad) && (pp[h].marcaBaja == 0) && fechaOK == 1) {
					strcpy(ps[i].enCartelera[n].nombre, pp[h].nombre);
					strcpy(ps[i].enCartelera[n].fac, fechahoy);
					strcpy(pp[h].fac, fechahoy);
					ps[i].enCartelera[n].anyo = pp[h].anyo;
                    ps[i].enCartelera[n].mce = pp[h].mce;
					ps[i].enCartelera[n].genero = pp[h].genero;
					/* Contador de peliculas asignadas a la sala correspondiente */
                    ps[i].asignadas = n+1;
					n++;
				}
			}
			indiceGen--;
		}
	}
	
	fechaOK = 0;
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
	getchar();
}

void gestionSalas(salas *ps, int *indice) {
	int i, j, h;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
        inicio();
        printf("\ninicio >> gestion de salas\n");
        noPeli();
	}
	
	else {
		/* Muestra el listado de peliculas asignadas a las correspondientes salas */
		system("clear");
		inicio();
		printf("\ninicio >> gestion de salas\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		for(i = 0; i < 4; i++){
			printf("\nPELICULAS ASIGNADAS A LA SALA \"%s\" (%d)", ps[i].nombreSala, ps[i].asignadas);
			printf("\n\n    NOMBRE PELICULA                                      AÑO     GENERO     MCE       FAC         ESTADO\n");
            printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
			for(j = 0; j < ps[i].asignadas; j++) {
				if (j < 9)
                    printf("%d.  ",j+1);
                else
                    printf("%d. ",j+1);
                printf("%s", ps[i].enCartelera[j].nombre);
                
                /* Formatea el nombre para mostrar en tabla */
                for (h = 0; h < (MAXNOMBRE - strlen(ps[i].enCartelera[j].nombre)); h++)
                    printf(" ");
                printf(" | %d ", ps[i].enCartelera[j].anyo);
                switch (ps[i].enCartelera[j].genero) {
                    case 'A':
                        printf("|  ACCION  ");
                        break;
                    case 'C':
                        printf("|  COMEDIA ");
                        break;
                    case 'D':
                        printf("|  DRAMA   ");
                        break;
                    case 'S':
                        printf("| SUSPENSO ");
                        break;
                    case 'T':
                        printf("|  TERROR  ");
                        break;
                }
                if (ps[i].enCartelera[j].mce < 10)
                    printf("|   %d   ", ps[i].enCartelera[j].mce);
                else if (ps[i].enCartelera[j].mce < 100)
                    printf("|  %d   ", ps[i].enCartelera[j].mce);
                else if (ps[i].enCartelera[j].mce < 1000)
                    printf("|  %d  ", ps[i].enCartelera[j].mce);
                else
                    printf("|  %d ", ps[i].enCartelera[j].mce);
                
                /* Deja espacio en blanco si no hay fecha asignada */
                if(strlen(ps[i].enCartelera[j].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", ps[i].enCartelera[j].fac);
                printf("| %s\n", ((ps[i].enCartelera[j].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
                printf("--+----------------------------------------------------+------+----------+-------+------------+--------------+----------\n");
            }
			printf("\n\n");
        }
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	getchar();
}

void autenticar(usuario pu[]) {
	int i, j=0, ch, userOK = 0, auth, pos;
	char usuario[MAXNOMBRE], pword[5];
	
	do {
		system("clear");
		puts("\n\n");
		puts("                                                                **");
		puts("                                                   *** ****  ********");
		puts("                                                  *       ****      **");
		puts("                                                 **        **        *");
		puts("                                                 **        **        *");
		puts("                                                  *       ***        *");
		puts("                                                   **   ********  ***   **");
		puts("                                                   **           ** *** **");
		puts("                                                   **            *     **");
		puts("                                                   **                  **");
		puts("                                                   **                  **");
		puts("                                                    *            * **  **");
		puts("                                                        *   *          **");
		puts("                                                       *** * *");
		puts("                                                       **  ** *");
		puts("                                                      *    * **");
		puts("                                                     * *   *  **");
		puts("                                                    * *    *  * *");
		puts("                                                     *     *   * *");
		puts("\n                                                   BIENVENIDO A CINAMON");
		fflush(stdin);
		
		printf("\n\n                                                   USUARIO: ");
		fgets(usuario,50,stdin);
		
		for(i= 0; i < 10; i++) {
			auth = strcmp(pu[i].nombreUsuario, usuario);
			/* Valida el usuario */
			if(auth == 0) {
				pos = i;
				userOK = 1;
			}
		}
		
		printf("                                                   CONTRASENIA: ");
        fflush(stdout);
		while ((ch = getch()) != EOF && ch != '\n' && ch != '\r' && j < sizeof(pword) - 1) {
            if (ch == '\b' && j > 0)
            {
                printf("\b \b");
                fflush(stdin);
                j--;
                pword[j] = '\0';
            }
            else if (isalnum(ch))
            {
                putchar('*');
                pword[j++] = (char)ch;
            }
        }
        
        
		
		/* Verifica que el usuario y contraseña coincidan */
		if((strcmp(pu[pos].password,pword) == 0) && userOK == 1)
			auth = 1;
		
		else {
			auth = 0;
			printf("\n------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n                                             USUARIO O CONTRASENIA INCORRECTOS\n\n");
			printf("------------------------------------------------------------------------------------------------------------------------\n");
			printf("\nPRESIONE ENTER PARA CONTINUAR..");
		}
		getchar();
	} while (auth == 0);
	
	printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n                                                   INGRESO SATISFACTORIO\n\n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\nPRESIONE ENTER PARA CONTINUAR..");
	getchar();
}

void fechaActual(char *fecha) {
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	strftime(fecha,12,"%d/%m/%Y",tlocal);
}

int validoFecha(char *fecha) {
    int a = (int)strtol(fecha, &fecha, 10);
    int m = (int)strtol(++fecha, &fecha, 10);
    int d = (int)strtol(++fecha, &fecha, 10);
    return (a*12+m)*31+d;
}

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void noPeli() {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n                                          NO SE PUEDEN CARGAR MAS PELICULAS\n\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nPRESIONE ENTER PARA CONTINUAR..");
    getchar();
}

void inicio() {
	char ltime[12];
	fechaActual(ltime);
	printf("%s\n",ltime);
	puts("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
    puts("MMMMMMMMMMMMDNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMMMMMMMMMNDDDDDMMMMMMDDDDD8MMMMMMMMDD8DNMMMMMMMMMMMMMMMMMMMMMMMMMM");
	puts("MMMM           ZMM        MN     ~MMM       ,MMMMM=     MMMMMMM       MMMM       MMMMM          OMMM8     ?MMM       ~MM");
	puts("MMM            OMM        MM       MM        MMMMM       MMMMMM:       ND        MMM=             MMM       MM       ,MM");
	puts("MM             DMMM     MMMM::      MMM,   MMMMMM,       MMMMMMMM              NMMM8     :OM$     ,MM::      MMM    MMMM");
	puts("MZ     MMMM    DMMM     MMMMMM       MM:   MMMMMM    Z    MMMMMMM              NMMM:    DMMMMM     MMMO       MM    MMMM");
	puts("M,    DMMMMMMMMMMMM     MMMMMM        =~   MMMMMD    M    DMMMMMM    M    Z    NMMM     MMMMMM     MMMO        $    MMMM");
	puts("M,    DMMMMMMMMMMMM     MMMMMM             MMMMM           MMMMMM    MD,,NM    DMMM     MMMMMM     MMMO             MMMM");
	puts("MO     MMMMMZMMMMMM     MMMMMM    M,       MMMMM           ZMMMMM    MMMMMM    DMMM~    +MMMMM     MMM8    M,       MMMM");
	puts("MM            NMMMM     MMMMMM    MM:      MMMMM   ,MMM,    MMMMM    MMMMMM    DMMMN      ,:,     ~MMM8    MM:      MMMM");
	puts("MMM            8MM        ZM        M      MMM       M+       M,       MM.       NMM?            ,MMM       :M      MMMM");
    puts("MMMM?,        MMMM        7M        MMI    MMM       $Z.      M=       MM.       $MMMM          8MMMM        MM     MMMM");
    puts("MMMMMMMNDDDMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNMMMMDDNNNNMMMDNDNMMMMMMMNDNDDMMMNNNNNNMMMMMMMMMDDDDNMMMMMMMMMMMMMMMMMMNNNMMMMM");
    puts("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
}