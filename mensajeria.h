#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idUsuarioEmisor;
    int idUsuarioReceptor;
    int idContenidoEnviado;
    char mensaje[300];
    int leido;                      // 1:si 0:no
} stMensajeria;

stMensajeria crearNuevoMensaje(stUsuario a);
void mostrarUnMensaje(stMensajeria unMensaje);
void guardarUnMensajeArchivo (stMensajeria unMensaje);
void buscarMensajesArchivo(stUsuario a);
void mostrarUnMensajeRecibido(stMensajeria unMensaje);
void mostrarTodosMensajesArchivo(stUsuario a);
