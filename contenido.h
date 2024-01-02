#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    char userName [30]; // GUARDE EL NOMBRE DEL USUARIO QUE CREO EL CONTENIDO
    int idContenido; // auto incremental
    char titulo[30];
    char descripcion[300];
    char categoria[30];
    int idCategoria;
    int likes;
    int puntosPorCompartir;
    int activo;                     // indica 1 o 0 si el contenido está activo
} stContenido;

stContenido cargarContenido(char userName [30]);
int cargaContenidos(stContenido a[], int dimension);

//USA ESTRUCTURA USUARIO PARA TOMAR EL NOMBRE AL MOSTRARLO
void mostrarCont (stContenido b);
void mostrarContenidos(stContenido a[], int validos);
void mostrarContenidosPorCategoria();
int solicitarIdCategoria();
int ultimoIdContenido ();
void guardarUnContenidoArchivo (stContenido contenido);
void mostrarTodosContenidos();
void actualizarPuntajeUsuario(stUsuario *usuario, int incremento);
void actualizarPuntajeContenido(stContenido *contenido, int valor);
int likeContenido(stUsuario *usuario, stContenido *contenido1);
void mostrarContLike(stContenido *b, stUsuario *a);
void mostrarTodosContenidos2(stUsuario *a);
void actualizarContenidoEnArchivo(stContenido *contenido);
