#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idUsuario;                 // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int listadoIdsContenidosGuardados[50];
    int validosContenidos;
    int puntaje;
    int nivel;
    int contenidosFavoritos [10]; // GUARDA IDS DE LOS CONTENIDOS FAVS
    int rol;                      // 1: es admin - 0: es comun
    int activo;                   // indica 1 o 0 si el usuario está activo
} stUsuario;



//PROTOTIPADO
int pasarArchivoUsuariosArreglo (stUsuario arregloUsuarios []); //ARCHIVO TO ARREGLO

void pasarArregloUsuariosArchivo (stUsuario arregloUsuarios [], int validos); //ARREGLO TO ARCHIVO

stUsuario creacionUnUsuario();

stUsuario creacionUnAdmin();

int guardarUnUsuarioArreglo (stUsuario arregloUsuarios [], int validos);

void guardarUnUsarioArchivo (stUsuario usuario);

int verificacionNombreUsuario (char userName[]);

int verificacionNombreUsuarioArreglo (stUsuario arregloUsuarios [], int validos, char userName []);

int verificacionMail (char mail[]);

int verificacionContrasenia(int id, char userName [], char password []);

int verificacionContraseniaArreglo (stUsuario arregloUsuarios[], int validos, int id, char password []);

int ultimoIdUser ();

int logueoUsuario ();

int buscarUsuario (char userName []);

int buscarUsuarioArreglo (stUsuario arregloUsuario [], int validos, char userName []);

void mostrarUsuario (stUsuario unUsuario);

int mostrarListaUsuarios ();

void mostrarListaUsuariosLevelMayor (stUsuario arregloUsuarios [], int validos, int filtro); //DESDE ARREGLO

void mostrarListaUsuariosLevelMenor (stUsuario arregloUsuarios [], int validos, int filtro); //DESDE ARREGLO

void darBajaUsuarioArreglo (stUsuario arregloUsuarios [], int validos, int id);

void eliminarUsuarioDefinitivoArreglo (stUsuario arregloUsuarios [], int validos, int id);

stUsuario buscarUsuarioEstructura (char userName []); //USADO PARA CREAR ADMIN

int verificarAdmin (char userName []); //VERIFICA SI ES USUARIO

int logueoAdmin (); //INGRESO DE ADMIN

// void modificarUsuarioArchivo; //MODIFICAR USUARIOS

int menuModificacionAdminInterno (); //MODIFICAR USUARIOS - MENU INTERNO PARA ADMIN

void modificarUsuario(stUsuario a);

stUsuario buscarUsuarioEstructuraPorID(int id);

void reemplazarNombreUsuario (char userName, int posUser);

void modificarUsuarioEnArreglo(stUsuario * arregloUsuarios, stUsuario a, int validos);

stUsuario menuModificarUsuarioArchivo ();

void mostrarArreglo (stUsuario *arregloUsuarios, int validos);

int verificarActivo (char userName []);
