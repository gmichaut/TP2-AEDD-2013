//
//  admin.h
//  TP1
//
//  GRUPO NRO 5
//  INTEGRANTES:
//  GABRIEL MICHAUT
//  gmichaut@gmail.com

#ifndef TP1_admin_h
#define TP1_admin_h

#define NOMBREMAX 50

/* Estructuras */
struct Usuario {
	char nombreUsuario[NOMBREMAX];
	char password[5];
};

typedef struct Usuario usuario;

/* Declaro un array de 10 usuarios y lo inicializo */
usuario User[10];
usuario User[] = {
    {"el secreto de sus ojos\n", "2009"},
    {"un novio para mi mujer\n", "2008"},
    {"el abrazo partido\n", "2004"},
    {"nueve reinas\n", "2000"},
    {"mundo grua\n", "1999"},
    {"dias de pesca\n", "2012"},
    {"el cielo elegido\n", "2012"},
    {"escuela normal\n", "2012"},
    {"un lugar en el mundo\n", "1992"},
    {"la historia oficial\n", "1985"}
};
/* FIN ADMIN.H */

#endif
