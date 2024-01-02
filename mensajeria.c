#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "contenido.h"
#include "mensajeria.h"
#include <locale.h>
#include <wchar.h>
#include "menu.h"

///EL ID DE LA PUBLICACION APARECE CUANDO SE MUESTRA CONTENIDOS, HACEMOS QUE LO ANOTE O SE ACUERDE Y LO MANDE?
//Martin: Yo diría que los ID solo aparezcan en modo admin. Para el usuario no es dato de relevancia




stMensajeria crearNuevoMensaje(stUsuario a)//stContenido b)
{
    stMensajeria nuevoMensaje;
    char userNameReceptor[20];
    stUsuario receptor;

    printf("=============MENSAJE NUEVO=============\n");
    nuevoMensaje.idUsuarioEmisor = a.idUsuario;                     //"a"=estructura de tipo usuario que se carga con los datos del usuario cuando inicio sesion

    printf("Ingrese el NOMBRE del usuario al que desea enviar el mensaje:\n");

    fflush(stdin);
    gets(userNameReceptor);

    receptor = buscarUsuarioEstructura(userNameReceptor);
    nuevoMensaje.idUsuarioReceptor = receptor.idUsuario;

    //nuevoMensaje.idUsuarioReceptor = buscarUsuario(userNameReceptor);

    printf("Mensaje:\n");
    fflush(stdin);

    gets(nuevoMensaje.mensaje);

    nuevoMensaje.leido = 0;

    return nuevoMensaje;
}

void buscarMensajesArchivo(stUsuario a)
{

    FILE *archivo=fopen("mensajes.dat", "rb");
    stMensajeria unMensaje;
    char cad;

    if(archivo!=NULL)
    {
        while(fread(&unMensaje, sizeof(stMensajeria), 1, archivo)>0)
        {
            if(unMensaje.idUsuarioReceptor==a.idUsuario && unMensaje.leido==0)
            {
                mostrarUnMensajeRecibido(unMensaje);
                //fwrite(&unMensaje, sizeof(stMensajeria),1,archivo);
            }
        }
        fclose(archivo);
    }
    cad = getch();
}

int verificarExistenciaMensajes (stUsuario a)
{
    int control = 0;
    stMensajeria unMensaje;
    FILE * archivo;
    archivo = fopen("mensajes.dat", "rb");
    char cad;

    if(archivo!=NULL)
    {
        while(fread(&unMensaje, sizeof(stMensajeria), 1, archivo)>0)
        {
            if(unMensaje.idUsuarioReceptor==a.idUsuario && unMensaje.leido==0)
            {
                control = 1;
                unMensaje.leido = 1;
            }
        }
        fclose(archivo);
    }
    cad = getch();

    return control;
}

void mostrarUnMensajeRecibido(stMensajeria unMensaje)
{
    stUsuario a;
    char cad;
    a = buscarUsuarioEstructuraPorID(unMensaje.idUsuarioEmisor);

    printf("\n \n \n \n");
    printf("\t \t======================================================== \n");
    printf("\t \t================ NUEVO MENSAJE RECIBIDO ================ \n");
    printf("\t \t======================================================== \n ");
    printf("ENVIADO POR.............: %s \n", a.nombre);
    printf("MENSAJE.................: %s \n", unMensaje.mensaje);
    //unMensaje.leido=1;

    cad = getch();
}
void mostrarTodosMensajesArchivo(stUsuario a)
{
    FILE *archivo=fopen("mensajes.dat", "rb");
    stMensajeria unMensaje;
    char cad;
    if(archivo!=NULL)
    {
        while(fread(&unMensaje, sizeof(stMensajeria), 1, archivo)>0)
        {
            mostrarUnMensajeRecibido(unMensaje);

        }
        fclose(archivo);
    }
    cad = getch();
}
void guardarUnMensajeArchivo (stMensajeria unMensaje)
{
    FILE * archivo;
    archivo = fopen("mensajes.dat", "ab");
    if (archivo)
    {
        fwrite(&unMensaje, sizeof(stMensajeria), 1, archivo);
        fclose(archivo);
    }
}
void mostrarUnMensaje(stMensajeria unMensaje)
{
    stUsuario a;
    a = buscarUsuarioEstructuraPorID(unMensaje.idUsuarioReceptor);

    printf("=============NUEVO MENSAJE ENVIADO=============\n\n");
    printf("Enviado a.............: %s\n", a.nombre);
    //void (funcion para mostrar contenido)
    printf("Mensaje: %s\n", unMensaje.mensaje);
    unMensaje.leido=1;
}
