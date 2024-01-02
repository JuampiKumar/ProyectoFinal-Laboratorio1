#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "mensajeria.h"
#include <locale.h>
#include <wchar.h>


int pasarArchivoUsuariosArreglo (stUsuario *arregloUsuarios )
{
    FILE * archivo;
    archivo = fopen("archivoUsuarios.bin", "rb");
    int i = 0, validos;
    stUsuario a;

    validos = ultimoIdUser();

    if(archivo)
    {
        while(i < validos)
        {
            fread(&a, sizeof(stUsuario), 1, archivo);
            arregloUsuarios[i] = a;
            i++;
        }
        fclose(archivo);
    }

    system("pause");
    return validos;
}

void pasarArregloUsuariosArchivo (stUsuario *arregloUsuarios, int validos)
{
    FILE * archivo;
    archivo = fopen("archivoUsuarios.bin", "w+b");
    int i = 0;
    stUsuario a;

    // validos = ultimoIdUser();

    if (archivo)
    {
        while (i < validos)
        {
            fwrite(&arregloUsuarios[i], sizeof(stUsuario), 1, archivo);
            i ++;
        }
        fclose(archivo);
    }
}

stUsuario creacionUnUsuario()
{
    stUsuario a;
    int controlN = -1, controlP = -1, id = -1;
    char password [30];
    char userName [30];
    char cad;
    setlocale(LC_ALL, "");

    printf("\t \t================== CRECION DE USUARIO ================== \n \n");

    do
    {
        system("cls");
        printf("\n \t \t NOMBRE DE USUARIO................: ");
        fflush(stdin);
        gets(userName);
        controlN = verificacionNombreUsuario(userName);
        if(controlN != 0)
        {
            printf("\n \t \t USUARIO EXISTENTE CAPO, INTENTA OTRO. \n");
            cad = getch();
        }
        else
        {
            strcpy(a.userName, userName);
        }
    }
    while (controlN != 0);


    printf("\n \t \t CONTRASEÑA.......................: ");
    fflush(stdin);
    gets(a.password);


    printf("\n \t \t NOMBRE...........................: ");
    fflush(stdin);
    gets(a.nombre);
    printf("\n \t \t APELLIDO.........................: ");
    fflush(stdin);
    gets(a.apellido);
    printf("\n \t \t MAIL.............................: ");
    gets(a.mail);

    id = ultimoIdUser ();

    a.idUsuario = id + 1;
    a.activo = 1;
    a.rol = 0; //1 PARA ADMIN, 0 PARA EL RESTO
    a.nivel = 1;
    a.puntaje = 0;

    return a;
}

stUsuario creacionUnAdmin()
{
    stUsuario a;
    int controlN = -1, controlP = -1, id = -1;
    char password [30];
    char userName [30];
    char cad;

    do
    {
        system("cls");
        printf("\n \t \t NOMBRE DE USUARIO................: ");
        fflush(stdin);
        gets(&userName);
        controlN = verificacionNombreUsuario(userName);
        if(controlN != 0)
        {
            printf("\n \t \t USUARIO EXISTENTE CAPO, INTENTA OTRO. \n");
            cad = getch();
        }
        else
        {
            strcpy(a.userName, userName);
        }
    }
    while (controlN != 0);

    printf("\n \t \t CONTRASEÑA.......................: ");
    fflush(stdin);
    gets(a.password);

    printf("\n \t \t NOMBRE...........................: ");
    fflush(stdin);
    gets(a.nombre);
    printf("\n \t \t APELLIDO.........................: ");
    fflush(stdin);
    gets(a.apellido);
    printf("\n \t \t MAIL.............................: ");
    gets(a.mail);

    id = ultimoIdUser ("archivoUsuarios.bin");

    a.idUsuario = id + 1;
    a.activo = 1;
    a.rol = 1; //1 PARA ADMIN, 0 PARA EL RESTO
    a.nivel = 1;
    a.puntaje = 0;

    return a;
}

int guardarUnUsuarioArreglo (stUsuario arregloUsuarios [], int validos)
{
    int i = 0;

    i = ultimoIdUser() + 1;

    arregloUsuarios[i] = creacionUnUsuario();

    validos = i;

    return validos;
}

void guardarUnUsuarioArchivo (stUsuario usuario)
{
    FILE * archivo;
    archivo = fopen("archivoUsuarios.bin", "ab");
    if (archivo)
    {
        fwrite(&usuario, sizeof(stUsuario), 1, archivo);
        fclose(archivo);
    }
}

int verificacionNombreUsuario (char userName[])
{
    int id = 0;
    FILE * archivo;
    stUsuario a;

    archivo = fopen ("archivoUsuarios.bin", "rb");

    if (archivo)
    {
        while (id == 0 && fread(&a, sizeof (stUsuario), 1, archivo) > 0)
        {
            if (strcmp(a.userName, userName) == 0)
            {
                id = a.idUsuario;
            }
        }
        fclose(archivo);
    }

    return id;
}

int verificacionNombreUsuarioArreglo (stUsuario arregloUsuarios [], int validos, char userName [])
{
    int i = 0, control = 0;
    stUsuario unUsuario;

    for (i = 0; i > validos; i ++)
    {
        unUsuario = arregloUsuarios[i];
        if (strcmp(unUsuario.userName, userName) == 0)
        {
            control = 1;
        }
    }

    return control;
}


int verificacionContrasenia(int id, char userName [], char password [])
{
    int control = 0;
    FILE * archivo;
    stUsuario a;

    archivo = fopen ("archivoUsuarios.bin", "rb");

    if (archivo)
    {
        while(fread(&a, sizeof (stUsuario), 1, archivo) > 0){
            if(strcmp(a.userName, userName) == 0 && strcmp(a.password, password) == 0){
                control = 1;
            }
        }
        fclose(archivo);
    }
    return control;
}

int verificacionContraseniaArreglo (stUsuario arregloUsuarios[], int validos, int id, char password [])
{
    stUsuario unUsuario;
    int control = 0;

    unUsuario = arregloUsuarios[id - 1]; //EL ID SIEMPRE SERÁ 1 MÁS QUE EL SUB-INDICE (ARRANCA EN 0 CUANDO LOS ID´S ARRANCAN EN 1)

    if (strcmp(unUsuario.password, password) == 0)
    {
        control = 1;
    }

    return control;
}

int ultimoIdUser ()
{
    FILE * archivo;
    stUsuario a;
    int id = 0;

    archivo = fopen("archivoUsuarios.bin", "rb");

    if(archivo)
    {
        fseek(archivo, -1 * sizeof(stUsuario), SEEK_END);
        if (fread(&a, sizeof(stUsuario), 1, archivo))
        {
            id = a.idUsuario;
        }
        fclose(archivo);
    }
    return id;
}

int logueoUsuario()
{
    char userName[30];
    char password[30];
    char salir = '\0';
    int controlN = 0, controlP = 0, controlV = 0, pos = 0; //exito = 0;
    char cad;

    do
    {
        printf("\t\tINGRESE NOMBRE DE USUARIO.......: ");
        fflush(stdin);
        gets(userName);

        controlN = verificacionNombreUsuario(userName);

        pos = controlN - 1;

        printf("\n\t\tINGRESE CONTRASEÑA..............: ");
        fflush(stdin);
        gets(password);

        controlP = verificacionContrasenia(pos, userName, password);

        controlV = verificarActivo (userName);

        if (controlN == 0 || controlP == 0 || controlV == 0)
        {
            system("cls");
            printf("\t \t======================================================== \n");
            printf("\t \t============ USUARIO O CONTRASEÑA INCORRECTO =========== \n");
            printf("\t \t======================================================== \n");
            printf("\t \t================== INTENTE NUEVAMENTE ================== \n");
            printf("\t \t==================   ESC PARA SALIR   ================== \n");
            printf("\t \t======================================================== \n");
            salir = getch();
            system("cls");
            printf("\t \t==================== MENÚ DE INGRESO =================== \n \n");
        }
        else
        {
            //exito = 1;
            salir =  27;
            system("cls");
            printf("\t \t==================== MENÚ DE INGRESO =================== \n \n");
            printf("\t \t======================================================== \n");
            printf("\t \t=============== ENTRASTE PAPA, SOS GROSO =============== \n");
            printf("\t \t======================================================== \n");
            cad = getch();
        }

    }
    while (salir!=27);

    return controlN;
}

int buscarUsuario (char userName [])
{
    int id = 0, flag = -1;
    FILE * archivo;
    stUsuario a;

    archivo = fopen("archivoUsuarios.bin", "rb");

    if(archivo)
    {
        while (fread(&a, sizeof(stUsuario), 1, archivo) > 0 && flag != 0)
        {
            if (strcmp(a.userName, userName))
            {
                flag = 0;
                id = a.idUsuario;
            }
        }
        fclose(archivo);
    }

    return id - 1;
}

int buscarUsuarioArreglo (stUsuario arregloUsuario [], int validos, char userName [])
{
    int i = 0, control = 1;
    stUsuario unUsuario;

    for (i = 0; i > validos; i ++)
    {
        unUsuario = arregloUsuario[i];
        if (strcmp(unUsuario.userName, userName) == 0)
        {
            control = 1;
        }
    }

    return control;
}

void mostrarUsuario (stUsuario unUsuario)
{
    char cad;

    printf("\t \t======================================================== \n");
    printf("\t \tNOMBRE de USUARIO...............: %s \n", unUsuario.userName);
    printf("\t \tID de USUARIO...................: %.3d \n", unUsuario.idUsuario);
    printf("\t \t======================================================== \n");
    printf("\t \tNOMBRE..........................: %s \n", unUsuario.nombre);
    printf("\t \tAPELLIDO........................: %s \n", unUsuario.apellido);
    printf("\t \tMAIL............................: %s \n", unUsuario.mail);
    printf("\t \t======================================================== \n");
    printf("\t \tPUNTAJE.........................: %d \n", unUsuario.puntaje);
    printf("\t \tNIVEL...........................: %d \n", unUsuario.nivel);
    printf("\t \t======================================================== \n");
    printf("\t \tROL.............................: %d \n", unUsuario.rol);
    printf("\t \t======================================================== \n");

    cad = getch();
}


int mostrarListaUsuarios ()
{
    int flag = 0, control = 1;
    FILE * archivo;
    stUsuario a;

    archivo = fopen("archivoUsuarios.bin", "rb");

    control = ultimoIdUser();

    if (archivo){
        while(control != 0 && fread(&a, sizeof(stUsuario), 1, archivo) > 0){
            mostrarUsuario(a);
            system("cls");
            control --;
            printf("%d", control);
            system("pause");
        }
        fclose(archivo);
    }

    return control;
}

// BUSCA CON FULTROS DE INT: ID, LEVEL, ROL, ACTIVO.
void mostrarListaUsuariosLevelMayor (stUsuario arregloUsuarios [], int validos, int filtro)
{
    int i = 0;
    stUsuario unUsuario;

    for (i = 0; i > validos; i ++)
    {
        unUsuario = arregloUsuarios[i];
        if(unUsuario.nivel >= filtro)
        {
            mostrarUsuario(unUsuario);
        }
    }

}

void mostrarListaUsuariosLevelMenor (stUsuario arregloUsuarios [], int validos, int filtro)
{
    int i = 0;
    stUsuario unUsuario;

    for (i = 0; i > validos; i ++)
    {
        unUsuario = arregloUsuarios[i];
        if(unUsuario.nivel <= filtro)
        {
            mostrarUsuario(unUsuario);
        }
    }
}

void darBajaUsuarioArreglo (stUsuario arregloUsuarios [], int validos, int id)
{
    int i = 0, control = 0;
    stUsuario unUsuario;

    while (i > validos && control == 0)
    {
        unUsuario = arregloUsuarios[i - 1];
        if (unUsuario.idUsuario == id)
        {
            unUsuario.activo = 0;
            control = 1;
        }
    }
}

void eliminarUsuarioDefinitivoArreglo (stUsuario arregloUsuarios [], int validos, int id)
{
    int i = id - 1;
    stUsuario unUsuario;

    for (; i > validos; i ++)
    {
        arregloUsuarios[i] = arregloUsuarios [i + 1];
    }
}

stUsuario buscarUsuarioEstructura (char userName [])
{
    int flag = 0;
    FILE * archivo;
    stUsuario a;

    archivo = fopen("archivoUsuarios.bin", "rb");

    if(archivo)
    {
        while (flag != 1 && fread(&a, sizeof(stUsuario), 1, archivo) > 0)
        {
            if (strcmp(a.userName, userName) == 0)
            {
                flag = 1;
            }
        }
        fclose(archivo);
    }
    mostrarUsuario(a);
    return a;
}

int verificarAdmin (char userName [])
{
    int control = 0, pos = 0;
    FILE * archivo;
    stUsuario a;

    archivo = fopen ("archivoUsuarios.bin", "rb");

    pos = verificacionNombreUsuario(userName) - 1;

    if (archivo)
    {
        fseek(archivo, pos * sizeof(stUsuario), SEEK_SET);
        fread(&a, sizeof (stUsuario), 1, archivo);
        if (a.rol == 1)
        {
            control = 1;
        }
        fclose(archivo);
    }
    return control;
}

int logueoAdmin ()  //DEVUELVE TRUE 1 O FALSE 0.
{
    char userName [30];
    char password [30];
    int controlN = 0, controlP = 0, controlA = 0, pos = 0; //exito = 0;
    char salir;

    do
    {
        printf("\t\tINGRESE NOMBRE DE USUARIO.......: ");
        fflush(stdin);
        gets(userName);
        controlN = verificacionNombreUsuario(userName);

        pos = controlN;

        printf("\n\t\tINGRESE CONTRASEÑA..............: ");
        fflush(stdin);
        gets(password);
        controlP = verificacionContrasenia(pos, userName, password);

        controlA = verificarAdmin(userName);


        if (controlN == 0 || controlP == 0 || controlA == 0)
        {
            printf("\t \t======================================================== \n");
            printf("\t \t============ USUARIO O CONTRASEÑA INCORRECTO =========== \n");
            printf("\t \t======================================================== \n");
            printf("\t \t================== INTENTE NUEVAMENTE ================== \n");
            printf("\t \t==================   ESC PARA SALIR   ================== \n");
            printf("\t \t======================================================== \n");
            salir = getch();
            system("cls");
            printf("\t \t==================== MENÚ DE INGRESO =================== \n \n");
        }
        else
        {
            //exito = 1;
            salir =  27;
            printf("\n \t \tENTRASTE PAPÁ, SOS GROSO. \n");
        }

    }
    while (salir!=27);

    system("cls");

    return controlA;
}

stUsuario buscarUsuarioEstructuraPorID(int id)
{
    int flag = -1;
    FILE * archivo;
    stUsuario a;

    archivo = fopen("archivoUsuarios.bin", "rb");

    if(archivo)
    {
        while (flag != 0 && fread(&a, sizeof(stUsuario), 1, archivo) > 0)
        {
            if (a.idUsuario == id)
            {
                flag = 0;
            }
        }
        fclose(archivo);
    }

    return a;
}

void reemplazarNombreUsuario (char userName, int posUser){
    FILE * archivo;
    int flag = -1;
    stUsuario a;

    archivo = fopen("archivoUsuarios.bin", "wb");

    if(archivo)
    {
        while (flag != 0 && fread(&a, sizeof(stUsuario), 1, archivo) > 0)
        {
            if (a.idUsuario == posUser)
            {
                strcpy(a.nombre, userName);
                flag = 0;
            }
        }
        fclose(archivo);
    }
}
 /*
void modificarUsuario(stUsuario a) {
    stUsuario b;
    int flag = 0;
    FILE * archivo;
    archivo = fopen("archivoUsuarios.bin", "+b");

    if (archivo) {
        while (fread(&b.idUsuario, sizeof(stUsuario), 1, archivo > 0 && flag != 1)) {
            if (strcmp(b.idUsuario, a.idUsuario) == 0) {
               strcpy(b.nombre, a.nombre);
               strcpy(b.mail, a.mail);
               b.rol = a.rol;
               b.nivel = a.nivel;
               mostrarUsuario(b);

               flag = 1;
            }
        }
        fclose(archivo);
    }
} */

void modificarUsuario(stUsuario a) {
    stUsuario b;
    int flag = 0;
    FILE *archivo;
    archivo = fopen("archivoUsuarios.bin", "r+b");

    if (archivo) {
        while (fread(&b, sizeof(stUsuario), 1, archivo) > 0 && flag != 1) {
            if (strcmp(b.idUsuario, a.idUsuario) == 0) {
                strcpy(b.nombre, a.nombre);
                strcpy(b.mail, a.mail);
                b.rol = a.rol;
                b.nivel = a.nivel;

                fseek(archivo, -sizeof(stUsuario), SEEK_CUR);

                fwrite(&b, sizeof(stUsuario), 1, archivo);

                printf("\n \n \t \tUSUARIO MODIFICADO EXITOSAMENTE.");
                flag = 1;
            }
        }
        fclose(archivo);
    }
}

stUsuario menuModificarUsuarioArchivo ()
{
    int posUser = 0, opcion = -1, salir = 0;
    stUsuario a;
    char mail [30];
    char userName [30];

    do{
        system("cls");
        printf("\n \n \t \tNOMBRE DE USUARIO: ");
        fflush(stdin);
        gets(userName);
        posUser = verificacionNombreUsuario(userName);

        if(posUser != 0){
            salir =  27;
        }else{
            printf("\t \t======================================================== \n");
            printf("\t \t================== USUARIO INCORRECTO ================== \n");
            printf("\t \t======================================================== \n");
            printf("\t \t================== INTENTE NUEVAMENTE ================== \n");
            printf("\t \t==================   ESC PARA SALIR   ================== \n");
            printf("\t \t======================================================== \n");
            salir = getch();
            system("cls");
            printf("\t \t==================== MENÚ DE INGRESO =================== \n \n");
        }
    }while(salir != 27);

    a = buscarUsuarioEstructuraPorID(posUser);

    do
    {
        opcion = menuModificacionAdminInterno();
        system("cls");
        switch(opcion)
        {
        case 1:
            printf("\n \n \t \tNUEVO NOMBRE: ");
            fflush(stdin);
            gets(userName);

            strcpy(a.nombre, userName);
            printf("\n");
            mostrarUsuario(a);
            break;
        case 2:
            printf("\n \n \t \tNUEVO MAIL: ");
            fflush(stdin);
            gets(mail);
            printf("\n");
            strcpy(a.mail, mail);

            mostrarUsuario(a);
            break;
        case 3:
            printf("\n \n \t \tMODIFICAR ROL - 1 PARA ADMIN - 0 PARA USUARIO: ");
            scanf("%d", &a.rol);

            printf("\n");
            mostrarUsuario(a);
            break;
        case 4:
            printf("\n \n \t \tMODIFICAR NIVEL: ");
            scanf("%d", &a.nivel);

            printf("\n");
            mostrarUsuario(a);
            break;
        case 5:
            printf("\n \n \t \tMODIFICAR ESTATUS - 1 ACTIVO - 0 PARA DAR DE BAJA: ");
            scanf("%d", &a.activo);

            printf("\n");
            mostrarUsuario(a);
            break;
        case 0:
            break;
        }
    }while (opcion != 0);

    return a;
}

void modificarUsuarioEnArreglo(stUsuario * arregloUsuarios, stUsuario a, int validos){
    int i = 0, control = 0;
    stUsuario b;

    while(i < validos && control != 1){
        b = arregloUsuarios[i];

        if(b.idUsuario == a.idUsuario){
            strcpy(b.nombre, a.userName);
            strcpy(b.mail, a.mail);
            b.rol = a.rol;
            b.nivel = a.nivel;
            b.activo = a.activo;
            control = 1;
            arregloUsuarios[i] = b;
        }
        i++;
    }
}

void mostrarArreglo (stUsuario *arregloUsuarios, int validos){
    int i = 0;
    stUsuario a;

    while(i < validos){
        a = arregloUsuarios[i];
        mostrarUsuario(a);
        i++;
    }
}

int verificarActivo (char userName []){
    int control = 0;
    stUsuario a;

    a = buscarUsuarioEstructura(userName);

    if(a.activo == 1){
        control = 1;
    }

    return control;
}
