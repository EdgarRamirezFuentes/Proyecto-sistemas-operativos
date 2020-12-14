#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio_ext.h>

/* Structs del sistema */

struct Producto 
{
    char id[30];
    char nombre[100];
    char descripcion[100];
    float precio;
    int existencia;
};

struct ProductoLista {
    char id[30];
    char nombre[100];
    int cantidad;
    float precio;
    float total;
};

struct TicketVenta 
{
    char id[30];
    char fecha[70];
    struct ProductoLista productos[100];
    int cantidadProductos;
    float total;
};

struct TicketCompra
{
    char id[30];
    char fecha[70];
    int cantidadProductos;
    struct ProductoLista productos[100];
    float total;
};


/*----------------- Actividades de manejo de archivos -------------- */

void registrarProductos();
void crearAlmacenProductos(); 
void crearAlmacenTicketsCompra();

/*----------------- Actividades del administrador ------------------ */

    /* Gestión de almacen */
int registrarNuevoProducto(struct Producto);
struct Producto tomarDatosProducto();
int validarExistenciaProducto(char*);
int modificarProducto(char*);
int eliminarProducto(char*);
void mostrarProductos();
void incrementarExistenciaProducto(char*,int);
void decrementarExistenciaProducto(char*,int);
struct Producto buscarProducto(char*);
void imprimirProducto(struct Producto);
    /* Gestión de tickets de compra */
void mostrarTicketsDeCompra();
void modificarTicketCompra(char*);
struct TicketCompra buscarTicketDeCompra(char*);
int registrarTicketDeCompra(struct TicketCompra);
struct TicketCompra tomarDatosTicketDeCompra();
void agregarProductoLista(struct ProductoLista[], int);
void imprimirListaProductos(struct ProductoLista[], int);
int verificarExistenciaTicketDeCompra(char*);
void imprimirTicketDeCompra(struct TicketCompra);
double calcularTotalTicket(struct ProductoLista[], int);
/* Interfaz principal servidor */
void interfazPrincipalServidor();
void seleccionDeOpcion(char);
#endif
