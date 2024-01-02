#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "contenido.h"
#include "mensajeria.h"
#include <locale.h>
#include <wchar.h>
#include <conio.h>

#define ARCHI_USER "archivoUsuarios.bin"

int main()
{
    system("color 60");
    setlocale(LC_ALL, "");
    int opcion = -1, control = -1, salidaMenu = -1, opcionMenu = -1, controlB = 0;
    stUsuario arregloUsuarios [100];
    stContenido arregloContenidos [100];
    stMensajeria arregloMensajeria[100];
    int validosAU = 100; // AU : ARREGLO USUARIOS
    int validosAC = 100; // AC : ARREGLO CONTENIDOS
    int validosAM =100;
    stUsuario a;
    stContenido b;
    char userName[30];
    char cad;

    while(opcion != 0)
    {
        opcion = menuInicio();
        system("cls");
        switch(opcion)
        {
        case 1:
            printf("\t \t==================== MENÚ DE INGRESO =================== \n \n");
            control = logueoUsuario();
            a = buscarUsuarioEstructuraPorID(control);
            strcpy(userName, a.userName);
            if (control != 0)
            {
                while(opcion != 6)
                {
                    opcion = menuUser(a);

                    system("cls");
                    switch (opcion)
                    {
                    case 1:
                        menuCreacionContenido (userName);
                        break;
                    case 2:
                        opcion = menuContenidos ();
                        switch(opcion)
                        {
                        case 1:
                            mostrarTodosContenidos();
                            break;
                        case 2:
                            mostrarContenidosPorCategoria();
                            break;
                        case 3:
                            mostrarTodosContenidos2(&a);
                            break;
                        case 4:
                            //
                            break;
                        }
                        break;
                    case 3:
                        // ENVIAR MENSAJE
                        menuCreacionMensaje(a);
                        break;
                    case 4:
                        // VER MENSAJES RECIBIDOS
                        buscarMensajesArchivo(a);
                        break;
                    case 5:
                        mostrarUsuario(a);
                        break;
                    case 6:
                        break;
                    }
                }
            }
            break;
        case 2:
            menuCreacionUsuario();
            break;
        case 3:
            printf("\t \t===================== MENÚ DE ADMIN ==================== \n \n");
            printf("\t \t============== ESTABAS ESCONDIDO, PICARON =============== \n \n");
            do
            {
                control = logueoAdmin();
                if(control == 1)
                {
                    opcion = menuAdmin();
                    switch(opcion)
                    {
                    case 1:
                        opcionMenu = menuBusquedaAdmin();
                        while(opcionMenu != 3){
                            switch(opcionMenu){
                            case 1:
                                printf("\t \tNOMBRE DE USUARIO: ");
                                fflush(stdin);
                                gets(userName);
                                do{
                                    mostrarUsuario(buscarUsuarioEstructura(userName));
                                    cad = getch();
                                    control = 0;
                                    opcionMenu = 3;
                                }while(control != 0);
                                break;
                            case 2:
                                do{
                                control = mostrarListaUsuarios();
                                opcionMenu = 3;
                                }while(control != 0);
                                break;
                            }
                        }
                    case 2:
                        do{
                            validosAU = pasarArchivoUsuariosArreglo(arregloUsuarios);

                            a = menuModificarUsuarioArchivo();

                            modificarUsuarioEnArreglo(arregloUsuarios, a, validosAU);

                            pasarArregloUsuariosArchivo(arregloUsuarios, validosAU);

                            controlB = 1;
                        }while(controlB == 0);
                        break;
                    case 3:
                        do{
                            creacionUnUsuario();
                            control = 0;
                        }while(control != 0);
                        break;
                    case 4:
                        salidaMenu = 0;
                        break;
                    }
                }
                else break;
            }
            while (control != 1 && salidaMenu != 0);
            break;
        }
    }

    return 0;
}

