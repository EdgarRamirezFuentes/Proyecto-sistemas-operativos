#include "server.h"
/*----------------- Actividades de manejo de archivos -------------- */
  
  void registrarProductos()
  {
    FILE *almacenProductos = NULL;
  }
  
  void crearAlmacenProductos()
  {
    FILE *almacenProductos = NULL;
    almacenProductos = fopen("./productos.dat", "wb+");
    if(!almacenProductos) exit(1);
    fclose(almacenProductos);
 }
  
  void crearAlmacenTicketCompra()
  {   
    FILE *historialTicketsCompra = NULL;
    almacenProductos = fopen("./ticketsCompra.dat", "wb+");
    if(!historialTicketsCompra) exit(1);
    fclose(historialTicketsCompra);
  }

/* Administrador */
    /* Gestión de almacen */
void registrarNuevoProducto(struct Producto producto) 
{

}

void modificarProducto(char *idProducto) 
{

}

void eliminarProducto(char *idProducto) 
{

}

void mostrarProductos() 
{

}

void incrementarExistenciaProducto(char *idProducto) 
{

}

void decrementarExistenciaProducto(char *idProducto) 
{

}

    /* Gestión de tickets de compra */
void mostrarTicketsDeCompra()
{

}


void buscarTicketDeCompra(char *idTicketCompra) 
{

}

void generarTicketDeCompra(struct Ticket_compra ticket) 
{

}

