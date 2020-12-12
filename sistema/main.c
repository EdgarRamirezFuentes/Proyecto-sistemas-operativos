#include "server.h"

int main(void) 
{
    struct Producto producto;
    __fpurge(stdin);
    fgets(&producto.id, 30, stdin);
    __fpurge(stdin);
    fgets(&producto.nombre, 100, stdin);
    __fpurge(stdin);
    fgets(&producto.descripcion, 100, stdin);
    __fpurge(stdin);
    scanf("%f", &producto.precio); 
    __fpurge(stdin);
    scanf("%d", &producto.existencia); 
    registrarNuevoProducto(producto);
    mostrarProductos();
    return 0;
}
