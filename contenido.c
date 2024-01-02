#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "contenido.h"
#include "mensajeria.h"
#include <locale.h>
#include <wchar.h>
#include <conio.h>

///---------- FUNCION CARGA CONTENIDO ----------
stContenido cargarContenido(char userName [30])
{
    int flag=0, opcion = -1;
    stContenido b;

    strcpy(b.userName, userName);

    b.idContenido = ultimoIdContenido () + 1;

    printf("\n \t \t TITULO DE LA PUBLICACION.........: ");
    fflush(stdin);
    gets(b.titulo);

    printf("\n \t \t QUE NOS CONTAS HOY, PAPU?........: \n");
    printf("\n \t \t TENES 300 CARACTERES PARA HACERLO. ");
    fflush(stdin);
    gets(b.descripcion);

    while(flag==0)
    {
        printf("\n \t \t EN QUE CATEGORIA LO PUBLICAS?.....: \n");
        printf("\n \t \t DEPORTE = 1 ");
        printf("\n \t \t COCINA = 2  ");
        printf("\n \t \t OTROS = 3 ");
        printf("\n \n");
        scanf("%d", &opcion);

        if(opcion == 1)
        {
            strcpy(b.categoria, "DEPORTES");
            b.idCategoria = 1;
            flag=1;
        }
        else if(opcion == 2)
        {
            strcpy(b.categoria, "COCINA");
            b.idCategoria = 2;
            flag=1;
        }
        else
        {
            strcpy(b.categoria, "OTROS");
            b.idCategoria = 3;
            flag=1;
        }
    }

    b.activo = 1;
    b.likes = 0;
    b.puntosPorCompartir = 0;

    return b;
}

///----------------- ARREGLO DE CONTENIDOS -------------------
/*
int cargaContenidos(stContenido a[], int dimension)
{
    int validos = 0;
    char control = 's';

    while(control=='s' && validos<dimension)
    {
        a[validos] = cargarContenido();
        printf("\nDesea seguir agregando Contenido? s/n.");
        fflush(stdin);
        control = getch();
        validos++;
    }
    return validos;
}
*/

void mostrarContenidos(stContenido a[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        printf("\n---------------------------\n");
        printf("\nId Id.............: %d", a[i].idContenido);
        printf("\nTitulo.................: %s", a[i].titulo);
        printf("\nDescripcion...................: %s", a[i].descripcion);
        printf("\nCategoria..............: %s", a[i].categoria);
        printf("\nLikes..............: %d", a[i].likes);
        printf("\n---------------------------\n");
    }
}

void mostrarCont (stContenido b)
{
    char cad;
    system("cls");
    printf("\t \t======================================================== \n");
    printf("\t \tNOMBRE de USUARIO...............: %s \n", b.userName);
    printf("\t \tID de PUBLICACION...............: %.3d \n", b.idContenido);
    printf("\t \t======================================================== \n");
    printf("\t \tTITULO..........................: %s \n", b.titulo);
    printf("\t \tCATEGORIA.......................: %s \n", b.categoria);
    printf("\t \t======================================================== \n");
    printf("\t \tMENSAJE.........................: %s \n", b.descripcion);
    printf("\t \t======================================================== \n");
    printf("\t \tLIKES...........................: %d \n", b.likes);
    printf("\t \t======================================================== \n");
    cad = getch();
}


void mostrarTodosContenidos()
{
    FILE * archivo;
    stContenido b;
    int id = 0, cont = 0;
    char cad;

    system("cls");

    printf("\t \t======================================================== \n");
    printf("\t \t====================== PUBLICACIONES =================== \n");
    printf("\t \t======================================================== \n");
    printf("\t \t======================================================== \n");

    archivo = fopen("archivoContenido.bin", "rb");

    if(archivo)
    {
        while(fread(&b, sizeof(stContenido), 1, archivo) > 0)
        {
            mostrarCont(b);

            /*scanf("%d", &opcion);

            if (opcion == 1){
                agregarFavorito(b);
            }else if (opcion == 2){
                ponerLikeContenido(b);
            }*/

            cont ++; //VARIABLE PARA LIMPIAR LA PANTALLA
            if (cont % 2 == 0)
            {
                system("cls");
            }
        }
        fclose(archivo);
    }

    cad = getch();
}



/* void agregarFavorito (stContenido b){
    int id = -1;
    stUsuario a;

    id = buscarIdFavoritos(a);

    a.contenidosFavoritos[id + 1] = b.idContenido;


}

void ponerLikeContenidop (stContenido){

} */

void mostrarContenidosPorCategoria()
{
    FILE * archivo;
    stContenido b;
    int id = 0, idCategoria;
    char cad;

    idCategoria = solicitarIdCategoria();

    archivo = fopen("archivoContenido.bin", "rb");

    if(archivo)
    {
        while(fread(&b, sizeof(stContenido), 1, archivo) > 0)
        {
            if(b.idCategoria == idCategoria)
            {
                mostrarCont(b);
            }
        }
        fclose(archivo);
    }

    cad = getch();
}

int solicitarIdCategoria ()
{
    int idCategoria = 0, flag = 0, opcion = -1;

    while(flag==0)
    {
        printf("\n \t \t QUE CATEGORIA QUERES VER?....: \n");
        printf("\n \t \t DEPORTE = 1 ");
        printf("\n \t \t COCINA = 2  ");
        printf("\n \t \t OTROS = 3 ");
        printf("\n \n");
        scanf("%d", &opcion);

        if(opcion == 1)
        {
            idCategoria = 1;
            flag=1;
        }
        else if(opcion == 2)
        {
            idCategoria = 2;
            flag=1;
        }
        else
        {
            idCategoria = 3;
            flag=1;
        }
    }


    return idCategoria;
}

int ultimoIdContenido ()
{
    FILE * archivo;
    stContenido b;
    int id = 0;

    archivo = fopen("archivoContenido.bin", "rb");

    if(archivo)
    {
        fseek(archivo, -1 * sizeof(stContenido), SEEK_END);
        if (fread(&b, sizeof(stContenido), 1, archivo))
        {
            id = b.idContenido;
        }
        fclose(archivo);
    }
    return id;
}

void guardarUnContenidoArchivo (stContenido contenido)
{
    FILE * archivo;
    archivo = fopen("archivoContenido.bin", "ab");
    if (archivo)
    {
        fwrite(&contenido, sizeof(stContenido), 1, archivo);
        fclose(archivo);
    }
}

// Likes

long buscarPosicionPorId(int idContenido)
{
    FILE *archivo = fopen("archivoContenido.bin", "rb");
    if (archivo)
    {
        stContenido contenido;
        long posicion = 0;
        while (fread(&contenido, sizeof(stContenido), 1, archivo) > 0)
        {
            if (contenido.idContenido == idContenido)
            {
                fclose(archivo);
                return posicion;
            }
            posicion++;
        }
        fclose(archivo);
    }
    return -1; // Si no se encuentra el registro, se devuelve -1
}

void actualizarContenidoEnArchivo(stContenido *contenido)
{
    long posicion = buscarPosicionPorId(contenido->idContenido);
    if (posicion != -1)
    {
        FILE *archivo = fopen("archivoContenido.bin", "r+b");
        if (archivo)
        {
            fseek(archivo, sizeof(stContenido) * posicion, SEEK_SET);
            fwrite(contenido, sizeof(stContenido), 1, archivo);
            fclose(archivo);
        }
    }
}

void actualizarPuntajeUsuario(stUsuario *usuario, int incremento)
{
    usuario->puntaje += incremento;
}

void actualizarPuntajeContenido(stContenido *contenido, int valor)
{
    contenido->likes += valor;
    actualizarContenidoEnArchivo(contenido);
}

int likeContenido(stUsuario *usuario, stContenido *contenido1)
{
    int accion = getch() - '0';  // Obtener el valor numérico de la tecla presionada
    if (accion == 1)
    {

        if (contenido1->likes == 0)
        {
            actualizarPuntajeContenido(contenido1, 1);
            actualizarPuntajeUsuario(usuario, 1);
        }
    }
    else if (accion == 2)
    {
        if (contenido1->likes == 1)
        {
            actualizarPuntajeContenido(contenido1, -1);
            actualizarPuntajeUsuario(usuario, -1);
        }
    }
    return accion;
}

void mostrarContLike(stContenido *b, stUsuario *a)
{
    int cad;
    do {
        system("cls");
        printf("\t \t======================================================== \n");
        printf("\t \tNOMBRE de USUARIO...............: %s \n", b->userName);
        printf("\t \tID de PUBLICACION...............: %.3d \n", b->idContenido);
        printf("\t \t======================================================== \n");
        printf("\t \tTITULO..........................: %s \n", b->titulo);
        printf("\t \tCATEGORIA.......................: %s \n", b->categoria);
        printf("\t \t======================================================== \n");
        printf("\t \tMENSAJE.........................: %s \n", b->descripcion);
        printf("\t \t======================================================== \n");
        printf("\t \tLIKES...........................: %d \n", b->likes);
        printf("\t \t======================================================== \n");
        printf("Presiona '1' para dar like a un contenido.\n");
        printf("Presiona '2' para quitar el like a un contenido.\n");
        printf("Presiona cualquier otra tecla para continuar.\n");
        cad = likeContenido(a, b);
    } while (cad == 1 || cad == 2);
}

void mostrarTodosContenidos2(stUsuario *a)
{
    FILE *archivo;
    stContenido b;
    int cad;

    system("cls");

    printf("\t \t======================================================== \n");
    printf("\t \t====================== PUBLICACIONES =================== \n");
    printf("\t \t======================================================== \n");
    printf("\t \t======================================================== \n");

    archivo = fopen("archivoContenido.bin", "rb");

    if (archivo)
    {
        while (fread(&b, sizeof(stContenido), 1, archivo) > 0)
        {
            mostrarContLike(&b, a);
        }
        fclose(archivo);
    }
    cad = getch();
}

