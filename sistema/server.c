#include "server.h"
/*----------------- Actividades de manejo de archivos -------------- */

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

int registrarNuevoProducto(struct Producto nuevoProducto) 
{
    /* Estado: 1 -> Registrado con exito || 0 -> Producto ya existente */
    int estado = 1;
    FILE *almacenProductos = NULL;
    /* Verificación de existencia de almacen de productos */
    if(!fopen("./productos.dat", "rb")) crearAlmacenProductos();
    almacenProductos = fopen("./productos.dat", "ab");
    printf("ID de nuevo producto: %s\n", nuevoProducto.id);
    if(!validarExistenciaProducto(nuevoProducto.id)){
        fwrite(&nuevoProducto, sizeof(struct Producto), 1, almacenProductos);
        estado = 1;
    } else {
        estado = 0;
    }
    fclose(almacenProductos);
    return estado;
}

struct Producto tomarDatosProducto() 
{
    struct Producto producto;
    puts("Ingresa el ID del producto: ");
    __fpurge(stdin);
    fgets(producto.id, 30, stdin);
    puts("Ingresa el nombre del producto: ");
    __fpurge(stdin);
    fgets(producto.nombre, 100, stdin);
    puts("Ingresa la descripcion del producto: ");
    __fpurge(stdin);
    fgets(producto.descripcion, 100, stdin);
    puts("Ingresa el precio del producto: ");
    __fpurge(stdin);
    scanf("%f", &producto.precio); 
    puts("Ingresa la existencia del producto: ");
    __fpurge(stdin);
    scanf("%d", &producto.existencia); 
    return producto;
}

int validarExistenciaProducto(char *idProducto) 
{
    FILE *almacenProductos = NULL;
    /* Verificación de existencia de almacen de productos */
    if(!fopen("./productos.dat", "rb")) crearAlmacenProductos();
    almacenProductos = fopen("./productos.dat", "rb");
    struct Producto producto;
    fread(&producto, sizeof(struct Producto), 1, almacenProductos);
    while(!feof(almacenProductos))
    {
        if(!strcmp(idProducto, producto.id)) return 1;
        fread(&producto, sizeof(struct Producto), 1, almacenProductos);
    }
    fclose(almacenProductos);
    return 0;
}
char menuModificar()
{
    char opcion;
    do
    {
        printf("\n ¿Que dato desea modificar? \n");
        printf("\n 1. Nombre \n");
        printf("\n 2. Descripcion \n");
        printf("\n 3. Precio \n");
        scanf("%c",&opcion);
    }
    while(opcion!='1' && opcion!='2' && opcion!='3');

    return opcion;
}
int modificarProducto(char *idProducto) 
{
    FILE *modificarProducto;
    int existe=0,estado=1,pos;
    char o;
    struct Producto producto;

    modificarProducto=fopen("./productos.dat","r+b");
    if (modificarProducto==NULL)
        exit(1); 

    fread(&producto, sizeof(struct Producto), 1, modificarProducto);

    while(!feof(modificarProducto))
    {
        if(!strcmp(idProducto,producto.id))
        {
            o=menuModificar();
            switch(o)
            {
                case '1': //Modifica el nombre
                    puts("Ingrese el nuevo nombre del producto: ");
                    __fpurge(stdin);
                    fgets(producto.nombre,100,stdin);
                    pos=ftell(modificarProducto)-sizeof(struct Producto);
                    fseek(modificarProducto,pos,SEEK_SET);
                    fwrite(&producto, sizeof(struct Producto), 1, modificarProducto);
                    printf("Se modifico el nombre del producto con exito.\n");
                    existe=1;
                break;
                case '2': //Modifica la descripcion
                    puts("Ingrese la nueva descripcion: ");
                    __fpurge(stdin);
                    fgets(producto.descripcion,100,stdin);
                    pos=ftell(modificarProducto)-sizeof(struct Producto);
                    fseek(modificarProducto,pos,SEEK_SET);
                    fwrite(&producto, sizeof(struct Producto), 1, modificarProducto);
                    printf("Se modifico la descripcion del producto con exito.\n");
                    existe=1;
                break;
                case '3': //Modifica el precio
                    puts("Ingrese el nuevo precio:");
                    __fpurge(stdin);
                    scanf("%f",&producto.precio);
                    pos=ftell(modificarProducto)-sizeof(struct Producto);
                    fseek(modificarProducto,pos,SEEK_SET);
                    fwrite(&producto, sizeof(struct Producto), 1, modificarProducto);
                    printf("Se modifico el precio del producto con exito.\n");
                    existe=1;
                break;
            }
        }
        fread(&producto, sizeof(struct Producto), 1, modificarProducto);
    }
    if (existe==0)
        printf("No existe un producto con este codigo\n");
    fclose(modificarProducto);

    return estado;
}

int eliminarProducto(char *idProducto) 
{
    FILE *archivo;
	FILE *temporal;
	struct Producto producto;
    int estado=1;
    
    archivo = fopen("productos.dat", "rb");
	temporal = fopen("temporal.dat", "wb");

    if (archivo == NULL || temporal == NULL)
		estado = 0;

    else 
    {
		/* Se copia en el archivo temporal los registros válidos */
		fread(&producto, sizeof(producto), 1, archivo);
		while (!feof(archivo)) 
        {
			if (!strcmp(idProducto,producto.id)) 
            {
			}
            else
                fwrite(&producto, sizeof(producto), 1, temporal);
                
			fread(&producto, sizeof(producto), 1, archivo);
		}
		
		fclose(archivo);
		fclose(temporal);

        system("rm productos.dat");
		system("mv temporal.dat productos.dat");
        
        
    }
    return estado;
}

void mostrarProductos() 
{
    FILE *almacenProductos = NULL;
    if(!fopen("./productos.dat", "rb")) crearAlmacenProductos();
    almacenProductos = fopen("./productos.dat", "rb");
    struct Producto producto;
    fread(&producto, sizeof(struct Producto), 1, almacenProductos);
    while(!feof(almacenProductos))
    {
        imprimirProducto(producto);
        fread(&producto, sizeof(struct Producto), 1, almacenProductos);
    }
    fclose(almacenProductos);
    getc(stdin);
}

struct Producto buscarProducto(char *idProducto)
{
    FILE *almacenProductos = NULL;
    if(!fopen("./productos.dat", "rb")) crearAlmacenProductos();
    almacenProductos = fopen("./productos.dat", "rb");
    struct Producto producto;
    fread(&producto, sizeof(struct Producto), 1, almacenProductos);
    while(!feof(almacenProductos))
    {
        if(!strcmp(idProducto, producto.id)) break;
        fread(&producto, sizeof(struct Producto), 1, almacenProductos);
    }
    fclose(almacenProductos);
    return producto;
}

void imprimirProducto(struct Producto producto)
{
    printf("ID Producto: %s\n", producto.id);
    printf("Nombre: %s\n", producto.nombre);
    printf("Descripcion:\n %s \n", producto.descripcion);
    printf("Precio: %.2f\n", producto.precio);
    printf("Existencia: %d\n", producto.existencia);
    puts("\n\n-------------------------------------------------------------------------\n\n");
}

void incrementarExistenciaProducto(char *idProducto, struct Producto* producto) 
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

/* -----------------------------Interfaz principal servidor ------------------------ */

void interfazPrincipalServidor () 
{
    char opcion, repetir;
    do
    {
        system("clear");
        puts("========= Bienvenido al menu principal del servidor =========\n\n");
        puts("1.- Agregar nuevo producto al almacen");
        puts("2.- Modificar datos de un producto");
        puts("3.- Buscar datos de un producto");
        puts("4.- Eliminar registro de un producto del almacen");
        puts("5.- Incrementar la existencia de un producto");
        puts("6.- Decrementar la existencia de un producto");
        puts("7.- Mostrar listado del almacen");
        puts("8.- Salir del sistema");
        puts("¿Que accion deseas realizar? ");
        __fpurge(stdin);
        opcion = getc(stdin);
        seleccionDeOpcion(opcion);
        puts("Ingresa 1 para volver al menu principal o ingresa 0 para salir del sistema");
        __fpurge(stdin);
        repetir = getc(stdin);
    } while (repetir != '0');
}

void seleccionDeOpcion (char opcion)
{
    char idProducto[30], nombreProducto[100], descripcion[100];
    float precioProducto;
    int existenciaProducto;
    switch (opcion)
    {
    case '1':
        /* Agrega nuevo producto al almacen */
        system("clear");
        if(registrarNuevoProducto(tomarDatosProducto()))
        {
            system("clear");
            puts("Producto agregado exitosamente");
        }else{
            system("clear");
            puts("El ID ingresado ya se encuentra registrado en el almacen");
        }
        break;
    case '2':
        /* Modificar datos de un producto */
        puts("Ingresa el ID producto a modificar: ");
        __fpurge(stdin);
        fgets(idProducto, 30, stdin);
        if(modificarProducto(idProducto))
        {
            puts("\n");
        }
        else
        {
            puts("\n Error al modificar producto\n");
        }
        break;
    case '3':
        /* Buscar datos de un producto */
        system("clear");
        puts("Ingresa el ID producto a buscar: ");
        __fpurge(stdin);
        fgets(idProducto, 30, stdin);
        if(validarExistenciaProducto(idProducto))
        {
            system("clear");
            puts("Datos del producto solicitado");
            imprimirProducto(buscarProducto(idProducto));
        }else{
            system("clear");
            puts("No existe producto en el almacen con el ID ingresado");
        }
        break;
    case '4':
        /*Elimina un producto*/
        puts("Ingresa el ID producto a modificar: ");
        __fpurge(stdin);
        fgets(idProducto, 30, stdin);
        if(validarExistenciaProducto(idProducto))
        {
            puts("Datos del producto a eliminar\n ");
            imprimirProducto(buscarProducto(idProducto));

            if(eliminarProducto(idProducto))
            {
                sleep(2);
                puts("\n Producto eliminado con exito\n");
            }
                
        }
        else
        {
            system("clear");
            puts("No existe producto en el almacen con el ID ingresado");
        }
        break;
    case '5':

        break;
    case '6':
        break;
    case '7':
        /* Mostrar listado del almacen */
        system("clear");
        puts("===== Lista de productos en almacen ====\n\n");
        mostrarProductos();
        break;
    case '8':
        /* Salir del sistema */
        exit(EXIT_SUCCESS);
        break;
    default:
        puts("La opcion ingresada no es valida");
        break;
    }
}