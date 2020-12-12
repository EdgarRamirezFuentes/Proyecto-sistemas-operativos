#include "server.h"

int main(void) 
{
    if(!fopen("./productos.dat", "r")){
        crearAlmacenProductos();
    }else {
        printf("Ya estoy perrazo");
    }
    if(!fopen("./ticketsCompra.dat", "r")) crearAlmacenTicketsCompra();
    printf("Funciono\n");
    return 0;
}
