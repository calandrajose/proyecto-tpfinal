#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "gotoxy.h"
#include <string.h>
#include <ctype.h>

///Constantes tipo char y string
const char ARCHIVO_CLIENTES[30]="clientes.bin";
const char ARCHIVO_PRODUCTOS[30]="productos.bin";
const char ARCHIVO_VENTA[30]="ventas.bin";


///Constantes tipo int
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13

typedef struct
{
    int id;
    int dni;
    char nombre[20];
    char apellido[20];
    char telefono[20];
    char domicilio[30];
    char baja; //‘s’ o ‘n’
} CLIENTE;

typedef struct
{
    int id;
    int codigo;
    char producto[20];
    int stock;
    float costo;
    float pvp;
    char baja; //‘s’ o ‘n’
} PRODUCTO;

typedef struct
{
    int id;
    int idCliente;
    int idProducto;
    int cantidad;
    int dia;
    int mes;
    int anio;
    char pagado;
    char anular; //‘a’
} VENTA;

///Prototipos
void menu_principal();
void menu_clientes();
void menu_productos();
void menu_ventas();
int menu_flechas(const char TITULO[],const char OPCIONES[5][30],int validos);

///PROTOTIPOS CLIENTES
void mostrar_cliente(CLIENTE clientes);
CLIENTE buscar_cliente(CLIENTE clientes);
CLIENTE Chequea_DNI();
CLIENTE cargar_clientes(int id);
int cuenta_registro_clientes();
void guardar_cliente();
CLIENTE modifica_cliente_generico(CLIENTE clientes);
void modificar_cliente_determinado();
void baja_de_cliente();
void listado_de_clientes();

///PROTOTIPOS PRODUCTO
void mostrar_producto(PRODUCTO productos);
PRODUCTO cargar_producto(int id);
PRODUCTO buscar_producto(PRODUCTO productos);
int detectar_repetido();
void guardar_producto();
PRODUCTO modifica_PRODUCTO_generico(PRODUCTO productos);
void modificar_PRODUCTO_determinado();
void baja_de_producto();
void listado_de_productos();


int main()
{
    int hide=0;
    SetConsoleTitle("Nombre del programa");
    system("color 4F");
    hidecursor(hide);
    menu_principal();

    return 0;
}

void menu_principal()
{
    int opcion=0;
    const char TITULO[30]="Nombre de la Empresa";
    const char OPCIONES[4][30]= {"Clientes","Productos","Ventas","Salir"};
    int validos=4;

    opcion = menu_flechas(TITULO,OPCIONES,validos);

    switch(opcion)
    {
    case 1:
        menu_clientes();
        break;
    case 2:
        menu_productos();
        break;
    case 3:
        menu_ventas();
        break;
    case 4:
        system("cls");
        gotoxy(33,10);
        printf("Fin del Programa");
        system("pause>null");
        exit(-1);
        break;
    }
}

void menu_clientes()
{
    int opcion=0;

    const char TITULO[30]="Clientes";
    const char OPCIONES[5][30]= {"Alta de Clientes","Baja de Clientes","Modificacion de Clientes",
                                 "Listado de Clientes","Menu Principal"
                                };
    int validos=5;

    opcion=menu_flechas(TITULO,OPCIONES,validos);

    switch(opcion)
    {
    case 1:
        guardar_cliente();
        break;
    case 2:
        baja_de_cliente();
        break;
    case 3:
        modificar_cliente_determinado();
        break;
    case 4:
        listado_de_clientes();
        break;
    case 5:
        menu_principal();
        break;
    }
}

void menu_productos()
{
    int opcion=0;
    const char TITULO[30]="Productos";
    const char OPCIONES[5][30]= {"Alta de Productos","Baja de Productos","Modificacion de Productos",
                                 "Listado de Productos","Menu Principal"
                                };
    int validos=5;

    opcion=menu_flechas(TITULO,OPCIONES,validos);

    switch(opcion)
    {
    case 1:
        guardar_producto();
        break;
    case 2:
        baja_de_producto();
        break;
    case 3:
        modificar_PRODUCTO_determinado();
        break;
    case 4:
        listado_de_productos();
        break;
    case 5:
        menu_principal();
        break;
    }
}

void menu_ventas()
{
    int opcion=0;
    const char TITULO[30]="Ventas";
    const char OPCIONES[6][30]= {"Alta de Ventas","Anulacion de Ventas","Listado de Ventas por Cliente",
                                 "Listado de Ventas del Mes","Promedio de Ventas del Mes","Menu Principal"
                                };
    int validos=6;


    opcion=menu_flechas(TITULO,OPCIONES,validos);


    switch(opcion)
    {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;

    case 5:

        break;
    case 6:
        menu_principal();
        break;
    }
}


int menu_flechas(const char TITULO[],const char OPCIONES[5][30],int validos_principal)
{
    int opcionSeleccionada=1;
    int tecla;
    int flag=0;
    int i;

    do
    {
        system("cls");
        gotoxy(25,9 + opcionSeleccionada);
        printf(">>");
        gotoxy(30,5);
        printf("%s",TITULO);

        for(i=0; i<validos_principal; i++)
        {
            gotoxy(30,10+i);
            printf("%s",OPCIONES[i]);
        }
        do
        {
            tecla=getch();
        }
        while(tecla!=TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=TECLA_ENTER);

        switch(tecla)
        {
        case TECLA_ARRIBA:
            opcionSeleccionada--;
            if(opcionSeleccionada<1)
            {
                opcionSeleccionada=validos_principal;
            }
            break;
        case TECLA_ABAJO:
            opcionSeleccionada++;
            if(opcionSeleccionada>validos_principal)
            {
                opcionSeleccionada=1;
            }
            break;
        case TECLA_ENTER:
            flag=1;
            break;
        }

    }
    while(flag==0);


    return opcionSeleccionada;
}

void mostrar_cliente(CLIENTE clientes)
{
    printf("\n.......................................................\n");
    printf("ID: %d\n",clientes.id);
    printf("DNI: %d\n",clientes.dni);
    printf("Nombre: %s\n",clientes.nombre);
    printf("Apellido: %s\n",clientes.apellido);
    printf("Telefono: %s\n",clientes.telefono);
    printf("Domicilio: %s\n",clientes.domicilio);
    printf(".......................................................\n");
}

CLIENTE buscar_cliente(CLIENTE clientes)
{
    CLIENTE flag;
    flag.dni=-1;

    FILE *file=fopen(ARCHIVO_CLIENTES,"rb");

    CLIENTE auxclientes;
    auxclientes.dni=0;

    if(ARCHIVO_CLIENTES!=NULL)
    {
        while(fread(&auxclientes,sizeof(CLIENTE),1,file)>0 && flag.dni!=clientes.dni)
        {
            if(auxclientes.dni==clientes.dni)
            {
                flag=clientes;
                //pos =(ftell(file) - (sizeof(CLIENTE)));             ///OJO QUE USO FSEEK ACA Y ABAJO
                //fseek(file,pos,SEEK_SET);
            }
        }
        fclose(file);
    }


    return flag;
}

///Detectar repetido

CLIENTE Chequea_DNI()
{
    CLIENTE flag;
    CLIENTE clientes;
    FILE *file=fopen(ARCHIVO_CLIENTES,"r+b");

    if(file!=NULL)
    {
        do
        {
            printf("DNI:\n");
            fflush(stdin);
            scanf("%d",&clientes.dni);
            flag=buscar_cliente(clientes);
            if(flag.dni!=-1)
            {

                printf("\nEl cliente ya existe en la base de datos, por favor ingrese otro DNI\n");
                system("pause>null");
                system("cls");
            }

        }
        while(flag.dni!=-1);
        fclose(file);
    }

    return clientes;
}

///Cargar y guardar clientes

CLIENTE cargar_clientes(int id)
{
    CLIENTE clientes;
    FILE *file=fopen(ARCHIVO_CLIENTES,"ab");

    if(file!=NULL)
    {
        system("cls");
        printf("%50s\n\n","Cliente");
        fflush(stdin);

        clientes = Chequea_DNI();

        printf("Apellido:\n");
        fflush(stdin);
        strupr(gets(clientes.apellido));
        printf("Nombre:\n");
        fflush(stdin);
        strupr(gets(clientes.nombre));
        printf("Telefono:\n");
        fflush(stdin);
        gets(clientes.telefono);
        printf("Domicilio:\n");
        fflush(stdin);
        strupr(gets(clientes.domicilio));
        clientes.baja='n';
        clientes.id=id;

        fwrite(&clientes,sizeof(CLIENTE),1,file);
        fclose(file);
    }

    return clientes;
}

int cuenta_registro_clientes()
{
    int cantidadRegistros=0;
    FILE *file=fopen(ARCHIVO_CLIENTES,"rb");

    if(file!=NULL)
    {
        fseek(file,0,SEEK_END);
        cantidadRegistros=ftell(file)/sizeof(CLIENTE);
        fclose(file);
    }

    return cantidadRegistros;
}

void guardar_cliente()
{
    char control;
    CLIENTE clientes;
    int id=cuenta_registro_clientes();
    FILE *file=fopen(ARCHIVO_CLIENTES,"ab");

    if(file==NULL)
    {
        fwrite(&clientes,sizeof(CLIENTE),1,file);
        printf("El archivo aun esta vacio\n");
    }
    else
    {
        do
        {
            //fopen(ARCHIVO_CLIENTES,"ab");
            id++;                                           ///SI ABRO Y CIERRO DENTRO DEL CICLO FUNCIONA NO CARGAR REPETIDOS
            clientes=cargar_clientes(id);                   ///Esta hecho implicitamente en la funcion cargarcliente
            system("pause>null");
            //fwrite(&clientes,sizeof(CLIENTE),1,file);
            printf("Cliente agregado con exito\n");
            mostrar_cliente(clientes);
            printf("\nDesea ingresar otro cliente?(s/n)\n");
            fflush(stdin);
            control=toupper(getch());
            system("cls");
            // fclose(file);
        }
        while(control=='S');
        fclose(file);
    }
    menu_clientes();
}

///Modificacion de clientes

CLIENTE modifica_cliente_generico(CLIENTE clientes)
{
    int opcion;
    CLIENTE AUXclientes=clientes;

    printf("Seleccione los datos a modificar:\n\n");
    printf("1.DNI\n");
    printf("2.Nombre\n");
    printf("3.Apellido\n");
    printf("4.Telefono\n");
    printf("5.Domicilio\n");
    printf("6.Volver al menu principal\n");
    fflush(stdin);
    scanf("%i", &opcion);

    switch(opcion)
    {
    case 1:
        printf("DNI:\n");
        fflush(stdin);
        scanf("%d", &AUXclientes.dni);
        break;

    case 2:
        printf("Nombre:\n");
        fflush(stdin);
        strupr(gets(AUXclientes.nombre));
        break;
    case 3:
        printf("Apellido:\n");
        fflush(stdin);
        strupr(gets(AUXclientes.apellido));
        break;
    case 4:
        printf("Telefono:\n");
        fflush(stdin);
        gets(AUXclientes.telefono);
        break;
    case 5:
        printf("Domicilio:\n");
        fflush(stdin);
        strupr(gets(AUXclientes.domicilio));
        break;
    case 6:
        menu_clientes();
        break;
    }

    system("cls");
    return AUXclientes;
}


void modificar_cliente_determinado()
{
    system("cls");
    int id;
    int existe=0;
    int pos;
    char control;

    CLIENTE clientes;

    FILE *file=fopen(ARCHIVO_CLIENTES,"r+b");

    if (file!=NULL)
    {
        system("cls");
        printf("Ingrese el ID del cliente:");
        fflush(stdin);
        scanf("%d",&id);

        while(fread(&clientes, sizeof(CLIENTE), 1, file)>0 && existe!=1)         ///busca dni para saber si existe el CLIENTE
        {
            if (id==clientes.id&& clientes.baja!='s')
            {
                mostrar_cliente(clientes);
                existe=1;
                pos =(ftell(file) - (sizeof(CLIENTE)));             ///OJO QUE USO FSEEK ACA Y ABAJO
                fseek(file,pos,SEEK_SET);
            }
        }

        if(existe==0)
        {
            printf("\nEl cliente no existe en la base de datos o ya esta dado de baja\n");
            system("pause>null");
            menu_clientes();
        }
        do
        {
            pos =(ftell(file) - (sizeof(CLIENTE)));                     ///MODIFICA DATOS
            fseek(file,pos,SEEK_SET);
            clientes=modifica_cliente_generico(clientes);
            mostrar_cliente(clientes);
            printf("Desea modificar algun otro dato?(s/n)");
            fflush(stdin);
            scanf("%c", &control);
            fwrite(&clientes,sizeof(CLIENTE),1, file);
        }
        while(control=='s'||control=='S');
        fclose(file);
    }

    menu_clientes();
}

void baja_de_cliente()
{
    char opcion;
    int id;
    int existe=0;
    int pos;
    CLIENTE clientes;

    FILE *file=fopen(ARCHIVO_CLIENTES,"r+b");

    system("cls");
    if (file==NULL)
    {
        printf("El archivo aun esta vacio\n");
        system("pause>null");
    }
    else
    {
        printf("Ingrese el ID del cliente:");
        scanf("%d",&id);

        while(fread(&clientes, sizeof(CLIENTE), 1, file)>0)
        {
            if (id==clientes.id && clientes.baja!='s')
            {
                mostrar_cliente(clientes);
                printf("\nSeguro que desea dar de baja el cliente?(s/n)\n");
                fflush(stdin);
                opcion=toupper(getch());
                if(opcion=='S')
                {
                    pos =ftell(file) - sizeof(CLIENTE);
                    fseek(file,pos,SEEK_SET);
                    printf("\nBaja de Cliente:\n");
                    clientes.baja='s';
                    printf("\nSe dio de baja el cliente con exito.\n");
                    fwrite(&clientes, sizeof(CLIENTE), 1, file);
                    existe=1;
                    system("pause>null");
                }
                else
                {
                    printf("Baja de cliente abortada\n");
                    system("pause>null");
                    menu_clientes();
                }
                break;
            }
        }
        if (existe==0)
        {
            printf("El cliente no existe en la base de datos o ya esta dado de baja\n");
            system("pause>null");
        }
        fclose(file);
    }
    menu_clientes();
}

void listado_de_clientes()
{
    int i=6;

    system("cls");
    CLIENTE clientes;
    FILE *file=fopen(ARCHIVO_CLIENTES,"rb");

    if(file==NULL)
    {
        fwrite(&clientes,sizeof(CLIENTE),1,file);
        printf("El archivo aun esta vacio\n");
        system("pause>null");
    }
    else
    {
        gotoxy(35,2);
        printf("Clientes");
        gotoxy(1,4);
        printf("ID");
        gotoxy(16,4);
        printf("DNI");
        gotoxy(31,4);
        printf("Nombre");
        gotoxy(46,4);
        printf("Apellido");
        gotoxy(61,4);
        printf("Telefono");
        gotoxy(76,4);
        printf("Domicilio");

        while((fread(&clientes,sizeof(CLIENTE),1,file)>0))
        {
            if(clientes.baja!='s')
            {
                gotoxy(1,i);
                printf("%d",clientes.id);
                gotoxy(16,i);
                printf("%d",clientes.dni);
                gotoxy(31,i);
                printf("%s",clientes.nombre);
                gotoxy(46,i);
                printf("%s",clientes.apellido);
                gotoxy(61,i);
                printf("%s",clientes.telefono);
                gotoxy(76,i);
                printf("%s",clientes.domicilio);
                i++;
            }
        }
        fclose(file);
        system("pause>null");
    }
    menu_clientes();
}

/// EMPIEZA PRODUCTO

void mostrar_producto(PRODUCTO productos)
{
    printf("\n.......................................................\n");
    printf("ID: %i\n",productos.id);
    printf("Codigo: %i\n",productos.codigo);
    printf("Nombre: %s\n",productos.producto);
    printf("Stock: %i\n",productos.stock);
    printf("Costo: %.2f\n",productos.costo);
    printf("Precio de Venta al Publico: %.2f\n",productos.pvp);
    printf(".......................................................\n");
}

PRODUCTO buscar_producto(PRODUCTO productos)
{
    PRODUCTO flag;
    flag.codigo=-1;

    FILE *file=fopen(ARCHIVO_PRODUCTOS,"rb");

    PRODUCTO auxproductos;
    auxproductos.codigo=0;

    if(ARCHIVO_PRODUCTOS!=NULL)
    {
        while(fread(&auxproductos,sizeof(PRODUCTO),1,file)>0 && flag.codigo!=productos.codigo)
        {
            if(auxproductos.codigo==productos.codigo)
            {
                flag=productos;
                //pos =(ftell(file) - (sizeof(CLIENTE)));             ///OJO QUE USO FSEEK ACA Y ABAJO
                //fseek(file,pos,SEEK_SET);
            }
        }
        fclose(file);
    }


    return flag;
}

///Detectar repetido

PRODUCTO chequea_codigo()
{
    PRODUCTO flag;
    PRODUCTO productos;
    FILE *file=fopen(ARCHIVO_PRODUCTOS,"r+b");

    if(file!=NULL)
    {
        do
        {
            printf("Codigo:\n");
            fflush(stdin);
            scanf("%d",&productos.codigo);
            flag=buscar_producto(productos);
            if(flag.codigo!=-1)
            {

                printf("\nEl producto ya existe en la base de datos, por favor ingrese otro codigo\n");
                system("pause>null");
                system("cls");
            }

        }
        while(flag.codigo!=-1);
        fclose(file);
    }

    return productos;
}


///Cargar y guardar productos

PRODUCTO cargar_producto(int id)
{
    PRODUCTO productos;
    FILE *file=fopen(ARCHIVO_PRODUCTOS,"ab");

    if(file!=NULL)
    {
        system("cls");
        gotoxy(35,2);
        printf("Producto\n\n");
        fflush(stdin);

        productos = chequea_codigo();

        printf("Nombre:\n");
        fflush(stdin);
        strupr(gets(productos.producto));
        printf("Stock:\n");
        fflush(stdin);
        scanf("%d",&productos.stock);
        printf("Costo:\n");
        fflush(stdin);
        scanf("%f",&productos.costo);
        printf("Precio de Venta al Publico:\n");
        fflush(stdin);
        scanf("%f",&productos.pvp);
        productos.baja='n';
        productos.id=id;

        fwrite(&productos,sizeof(PRODUCTO),1,file);
        fclose(file);
    }

    return productos;
}

int cuenta_registro_productos()
{
    int cantidadRegistros=0;
    FILE *file=fopen(ARCHIVO_PRODUCTOS,"rb");

    if(file!=NULL)
    {
        fseek(file,0,SEEK_END);
        cantidadRegistros=ftell(file)/sizeof(PRODUCTO);
        fclose(file);
    }


    return cantidadRegistros;
}

void guardar_producto()
{
    char control;
    PRODUCTO productos;
    int id=cuenta_registro_productos();
    FILE *file=fopen(ARCHIVO_PRODUCTOS,"ab");

    if(file==NULL)
    {
        fwrite(&productos,sizeof(PRODUCTO),1,file);
        printf("El archivo aun esta vacio\n");
        system("pause>null");
    }
    else
    {
        do
        {
            id++;
            productos=cargar_producto(id);
            system("pause>null");
            printf("Producto agregado con exito\n");
            mostrar_producto(productos);
            printf("\nDesea ingresar otro producto?(s/n)\n");
            fflush(stdin);
            control=toupper(getch());
            system("cls");
        }
        while(control=='S');
        fclose(file);
    }
    menu_productos();
}

///Modificacion de productos

PRODUCTO modifica_PRODUCTO_generico(PRODUCTO productos)
{
    int opcion;
    PRODUCTO AUXproductos=productos;

    printf("\nSeleccione los datos a modificar:\n\n");
    printf("1.Codigo\n");
    printf("2.Nombre\n");
    printf("3.Stock\n");
    printf("4.Costo\n");
    printf("5.Precio de venta al Publico\n");
    printf("6.Volver al menu principal\n");
    fflush(stdin);
    scanf("%i", &opcion);

    if(opcion>0 && opcion<7)
    {
        switch(opcion)
        {
        case 1:
            printf("Codigo: \n");
            fflush(stdin);
            scanf("%d", &AUXproductos.codigo);
            break;
        case 2:
            printf("Nombre: \n");
            fflush(stdin);
            strupr(gets(AUXproductos.producto));
            break;
        case 3:
            printf("Stock: \n");
            fflush(stdin);
            scanf("%d", &AUXproductos.stock);
            break;
        case 4:
            printf("Costo: \n");
            fflush(stdin);
            scanf("%f", &AUXproductos.costo);
            break;
        case 5:
            printf("Precio de Venta al Publico:\n");
            fflush(stdin);
            scanf("%f", &AUXproductos.pvp);
            break;
        case 6:
            menu_productos();
            break;
        }
    }
    else
    {
        system("cls");
        printf("Seleccione una opcion valida\n");
        system("pause>null");
    }

    system("cls");

    return AUXproductos;
}


void modificar_PRODUCTO_determinado()
{
    system("cls");
    int id;
    int existe=0;
    int pos;
    char control;

    PRODUCTO productos;

    FILE *file=fopen(ARCHIVO_PRODUCTOS,"r+b");

    if (file!=NULL)
    {
        system("cls");
        printf("\nIngrese el ID del producto:");
        fflush(stdin);
        scanf("%d",&id);

        while(fread(&productos, sizeof(PRODUCTO), 1, file)>0 && existe!=1)
        {
            if (id==productos.id && productos.baja!='s')
            {
                mostrar_producto(productos);
                existe=1;
                pos =(ftell(file) - (sizeof(PRODUCTO)));
                fseek(file,pos,SEEK_SET);
            }
        }

        if(existe==0)
        {
            printf("\nEl producto no existe en la base de datos o esta dado de baja\n");
            system("pause>null");
            menu_productos();
        }
        do
        {
            pos =(ftell(file) - (sizeof(PRODUCTO)));
            fseek(file,pos,SEEK_SET);
            productos=modifica_PRODUCTO_generico(productos);
            mostrar_producto(productos);
            printf("Desea modificar algun otro dato?(s/n)");
            fflush(stdin);
            control=getch();
            fwrite(&productos,sizeof(PRODUCTO),1, file);
        }
        while(control=='s'||control=='S');
        fclose(file);
    }
    menu_productos();
}

void baja_de_producto()
{
    char opcion;
    int id;
    int existe=0;
    int pos;
    PRODUCTO productos;

    FILE *file=fopen(ARCHIVO_PRODUCTOS,"r+b");

    system("cls");
    if (file==NULL)
    {
        printf("El archivo aun esta vacio\n");
        system("pause>null");
    }
    else
    {
        printf("Ingrese el ID del producto: ");
        scanf("%d",&id);

        while(fread(&productos, sizeof(PRODUCTO), 1, file)>0)
        {
            if (id==productos.id && productos.baja!='s')
            {
                mostrar_producto(productos);
                printf("\nSeguro que desea dar de baja el producto?(s/n)\n");
                fflush(stdin);
                opcion=toupper(getch());
                if(opcion=='S')
                {
                    pos =ftell(file) - sizeof(PRODUCTO);
                    fseek(file,pos,SEEK_SET);
                    printf("\nBaja de Producto:\n");
                    productos.baja='s';
                    printf("\nSe dio de baja el producto con exito.\n");
                    fwrite(&productos, sizeof(PRODUCTO), 1, file);
                    existe=1;
                }
                else
                {
                    printf("Baja de producto abortada\n");
                    system("pause>null");
                    menu_productos();
                }
                break;
            }
        }
        if (existe==0)
        {
            printf("El producto no existe en la base de datos o ya esta dado de baja\n");
            system("pause>null");
        }
        fclose(file);
    }
    menu_productos();
}

void listado_de_productos()
{
    int i=6;

    system("cls");
    PRODUCTO productos;
    FILE *file=fopen(ARCHIVO_PRODUCTOS,"rb");

    if(file==NULL)
    {
        printf("El archivo aun esta vacio\n");
        system("pause>null");
    }
    else
    {
        gotoxy(35,2);
        printf("Productos");
        gotoxy(1,4);
        printf("ID");
        gotoxy(16,4);
        printf("Codigo");
        gotoxy(31,4);
        printf("Nombre");
        gotoxy(46,4);
        printf("Stock");
        gotoxy(61,4);
        printf("Costo");
        gotoxy(76,4);
        printf("PvP");

        while((fread(&productos,sizeof(PRODUCTO),1,file)>0))
        {
            if(productos.baja!='s')
            {
                gotoxy(1,i);
                printf("%d",productos.id);
                gotoxy(16,i);
                printf("%d",productos.codigo);
                gotoxy(31,i);
                printf("%s",productos.producto);
                gotoxy(46,i);
                printf("%d",productos.stock);
                gotoxy(61,i);
                printf("%.2f",productos.costo);
                gotoxy(76,i);
                printf("%.2f",productos.pvp);
                i++;
            }
        }
        fclose(file);
        system("pause>null");
    }
    menu_productos();
}

