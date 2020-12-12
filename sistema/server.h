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

/* Structs del sistema */

struct Producto 
{
    char id[30];
    char nombre[100];
    char descripcion[100];
    float precio;
    int existencia;
};

struct Ticket_venta 
{
    char id[30];
    char fecha[70];
    struct Producto productos[100];
    float total;
};

struct Ticket_compra
{
    char id[30];
    char fecha[70];
    struct Producto productos[100];
    float total;
};

/*----------------- Actividades de manejo de archivos -------------- */

void registrarProductos();
void crearAlmacenProductos(); 
void crearAlmacenTicketCompra();

/*----------------- Actividades del administrador ------------------ */

    /* Gestión de almacen */
void registrarNuevoProducto(struct Producto);
void modificarProducto(char*);
void eliminarProducto(char*);
void mostrarProductos();
void incrementarExistenciaProducto(char*);
void decrementarExistenciaProducto(char*);
    /* Gestión de tickets de compra */
void mostrarTicketsDeCompra();
void buscarTicketDeCompra(char*);
void generarTicketDeCompra(struct Ticket_compra);

#endif
