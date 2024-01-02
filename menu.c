#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "contenido.h"
#include "mensajeria.h"
#include <locale.h>
#include <wchar.h>
#include "menu.h"

int menuInicio ()
{
    int opcion = 0;

    system("cls");
    printf("\n \n \n \n");
    printf("\t \t======================================================== \n");
    printf("\t \t======= BIENVENIDO A LA PEOR RED DE LA HISTORIA ======== \n");
    printf("\t \t======================================================== \n");//MODIFICAR USUARIOS
    printf("\n\n");
    printf("\t \t==================== MENÚ DE INICIO ==================== \n");
    printf("\n \n");
    printf("\t \tINGRESAR ______________________________________ OPCION 1 \n");
    printf("\t \tCREAR USUARIO _________________________________ OPCION 2 \n");
    printf("\t \tSALIR _________________________________________ OPCION 0 \n");
    printf("\n \n");
    scanf("%d", &opcion);

    return opcion;
}

int menuAdmin ()
{
    int opcion = 0;

    system("cls");
    printf("\n \n");
    printf("\t \tBUSCAR USUARIO ________________________________ OPCION 1 \n");
    printf("\t \tMODIFICAR USUARIO _____________________________ OPCION 2 \n");
    printf("\t \tCREAR USUARIO _________________________________ OPCION 3 \n");
    printf("\t \tSALIR _________________________________________ OPCION 4 \n");

    printf("\n \n");
    scanf("%d", &opcion);

    return opcion;
}

int menuBusquedaAdmin ()
{
    int opcion = 0;

    system("cls");
    printf("\n \n \n \n");
    printf("\t \tBUSCAR USUARIO por NOMBRE______________________ OPCION 1 \n");
    printf("\t \tLISTA de USUARIOS _____________________________ OPCION 2 \n");
    printf("\t \tSALIR _________________________________________ OPCION 3 \n");

    printf("\n \n");
    scanf("%d", &opcion);

    return opcion;
}

int menuModificacionAdminInterno ()
{
    int opcion = 0;

    system("cls");
    printf("\n \n \n \n");
    printf("\t \tMODIFICAR NOMBRE ______________________________ OPCION 1 \n");
    printf("\t \tMODIFICAR MAIL ________________________________ OPCION 2 \n");
    printf("\t \tMODIFICAR ROL _________________________________ OPCION 3 \n");
    printf("\t \tMODIFICAR LEVEL _______________________________ OPCION 4 \n");
    printf("\t \tMODIFICAR ACTIVO ______________________________ OPCION 5 \n");
    printf("\t \tSALIR _________________________________________ OPCION 0 \n");

    printf("\n \n");
    scanf("%d", &opcion);

    return opcion;
}



int menuUser (stUsuario a)
{
    int opcion = 0;

    system("cls");
    printf("\n \n \n \n");
    printf("\t \tPUBLICAR CONTENIDO ____________________________ OPCION 1 \n");
    printf("\t \tVER CONTENIDO _________________________________ OPCION 2 \n");
    printf("\t \tENVIAR MENSAJES _______________________________ OPCION 3 \n");
    printf("\t \tVER MENSAJES __________________________________ OPCION 4 \n");
    printf("\t \tVER PERFIL ____________________________________ OPCION 5 \n");
    printf("\t \tSALIR _________________________________________ OPCION 6 \n");

    if(verificarExistenciaMensajes(a) == 1){
        printf("\n \n \t \t============ TENES UN NUEVO MENSAJE PAPU ============= \n");
    }

    printf("\n \n");
    scanf("%d", &opcion);

    return opcion;
}

int menuContenidos ()
{
    int opcion = 0;

    system("cls");
    printf("\n \n \n \n");
    printf("\t \tPUBLICADO _____________________________________ OPCION 1 \n");
    printf("\t \tPOR CATEGORIA _________________________________ OPCION 2 \n");
    printf("\t \tLIKES _________________________________________ OPCION 3 \n");
    printf("\t \tRANDOM ________________________________________ OPCION 4 \n");

    printf("\n \n");
    scanf("%d", &opcion);

    return opcion;
}

void menuCreacionUsuario()
{
    stUsuario a;
    a = creacionUnUsuario();
    guardarUnUsuarioArchivo(a);
    system("cls");
    mostrarUsuario(a);
}

void menuCreacionContenido (char userName[30])
{
    stContenido b;
    char cad;

    b = cargarContenido(userName);
    guardarUnContenidoArchivo(b);
    system("cls");
    mostrarCont(b);
    cad = getch();
}

void menuCreacionMensaje(stUsuario a){

    stMensajeria mensaje;
    char cad;


    mensaje = crearNuevoMensaje(a);
    guardarUnMensajeArchivo(mensaje);
    system("cls");
    mostrarUnMensaje(mensaje);
    cad = getch();
}
