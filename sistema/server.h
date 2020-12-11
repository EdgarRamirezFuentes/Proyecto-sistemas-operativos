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

struct Producto {
    char id[30];
    char nombre[100];
    char descripcion[100];
    float precio;
    int existencia;
};

struct Ticket_venta {
    char id[30];
    char fecha[70];
    struct Producto productos[100];
    float total;
};

struct Ticket_compra{
    char id[30];
    char fecha[70];
    struct Producto productos[100];
    float total;
};


/*----------------- Actividades del administrador ------------------ */

    /* Gestión de almacen */
void *registrarNuevoProducto(void*);
void *modificarProducto(void*);
void *eliminarProducto(void*);
void *mostrarProductos(void*);
void *incrementarExistenciaProducto(void*);
void *decrementarExistenciaProducto(void*);
    /* Gestión de tickets de venta */
void *mostrarTicketsDeVenta(void*);
void *buscarTicketDeVenta(void*);
void *generarTicketDeVenta(void*);
    /* Gestión de tickets de compra */
void *mostrarTicketsDeCompra(void*);
void *buscarTicketDeCompra(void*);
void *generarTicketDeCompra(void*);

/*----------------- Actividades del vendedor ------------------ */

    /* Gestión de ventas */
void *agregarVenta(void*);
void *agregarProductoDeVenta(void*);
void *quitarProductoDeventa(void*);

#endif
