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
  
  void crearAlmacenTicketsCompra()
  {   
    FILE *historialTicketsCompra = NULL;
    historialTicketsCompra  = fopen("./ticketsCompra.dat", "wb+");
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
    FILE *modificarProducto;
    int existe=0;
    char opcion;
    struct Producto producto;

    modificarProducto=fopen("./productos.dat","r+b");
    if (modificarProducto==NULL)
        exit(1); 

    fread(&producto, sizeof(struct Producto), 1, modificarProducto);

    while(!feof(modificarProducto))
    {
        if (idProducto==producto.id)
        {
           while(opcion!='1' || opcion!='2' || opcion!='3')
           { 
                system("clear");
                printf("\n ¿Que dato desea modificar? \n");
                printf("\n 1. Nombre \n");
                printf("\n 2. Descripcion \n");
                printf("\n 3. Precio \n");
                scanf("%c",&opcion);
           }
           if(opcion==1)
           {
               printf("\n Ingrese el nuevo nombre del producto:\n");
               gets(producto.nombre);
               int pos=ftell(modificarProducto)-sizeof(struct Producto);
               fseek(modificarProducto,pos,SEEK_SET);
               fwrite(&producto.nombre, sizeof(struct Producto), 1, modificarProducto);
               printf("\n Se modifico el nombre del producto.\n");
               existe=1;
               break;
           }
           else if(opcion==2)
           {
               printf("\n Ingrese el nuevo precio del producto:\n");
               gets(producto.descripcion);
               int pos=ftell(modificarProducto)-sizeof(struct Producto);
               fseek(modificarProducto,pos,SEEK_SET);
               fwrite(&producto.descripcion, sizeof(struct Producto), 1, modificarProducto);
               printf("\n Se modifico la descripcion del producto.\n");
               existe=1;
               break;
           }
           else if(opcion==3)
           {
               printf("\n Ingrese el nuevo precio del producto:\n");
               scanf("%f",&producto.precio);
               int pos=ftell(modificarProducto)-sizeof(struct Producto);
               fseek(modificarProducto,pos,SEEK_SET);
               fwrite(&producto.precio, sizeof(struct Producto), 1, modificarProducto);
               printf("\n Se modifico el precio del producto.\n");
               existe=1;
               break;
           }
        }
        fread(&producto, sizeof(struct Producto), 1, modificarProducto);
    }
    if (existe==0)
        printf("No existe un producto con este codigo\n");
    fclose(modificarProducto);


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

