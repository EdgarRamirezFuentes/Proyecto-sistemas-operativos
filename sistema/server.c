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

void incrementarExistenciaProducto(char *idProducto,int cantidad) 
{
   FILE *incrementar;
   int pos;
   struct Producto producto;

    incrementar=fopen("./productos.dat","r+b");
    if (incrementar==NULL)
        exit(1); 

    fread(&producto, sizeof(struct Producto), 1, incrementar);

    while(!feof(incrementar))
    {
        if(!strcmp(idProducto,producto.id))
        {
            producto.existencia=producto.existencia+cantidad;
            pos=ftell(incrementar)-sizeof(struct Producto);
            fseek(incrementar,pos,SEEK_SET);
            fwrite(&producto, sizeof(struct Producto), 1, incrementar);
            break;
        }
        fread(&producto, sizeof(struct Producto), 1, incrementar);
    }
    
    fclose(incrementar);

}

void decrementarExistenciaProducto(char *idProducto,int cantidad) 
{
   FILE *decrementar;
   int pos;
   struct Producto producto;

    decrementar=fopen("./productos.dat","r+b");
    if (decrementar==NULL)
        exit(1); 

    fread(&producto, sizeof(struct Producto), 1, decrementar);

    while(!feof(decrementar))
    {
        if(!strcmp(idProducto,producto.id))
        {
            producto.existencia=producto.existencia-cantidad;
            pos=ftell(decrementar)-sizeof(struct Producto);
            fseek(decrementar,pos,SEEK_SET);
            fwrite(&producto, sizeof(struct Producto), 1, decrementar);
            break;
        }
        fread(&producto, sizeof(struct Producto), 1, decrementar);
    }
    
    fclose(decrementar);
}

    /* Gestión de tickets de compra */

void mostrarTicketsDeCompra()
{
    FILE *historialTicketsDeCompra = NULL;
    if(!fopen("./ticketsCompra.dat", "rb")) crearAlmacenTicketsCompra();
    historialTicketsDeCompra = fopen("./ticketsCompra.dat", "rb");
    struct TicketCompra ticket;
    fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    while(!feof(historialTicketsDeCompra))
    {
        imprimirTicketDeCompra(ticket);
        fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    }
    fclose(historialTicketsDeCompra);
}


struct TicketCompra buscarTicketDeCompra(char *idTicketCompra) 
{
    FILE *historialTicketsDeCompra = NULL;
    if(!fopen("./ticketsCompra.dat", "rb"))crearAlmacenTicketsCompra();
    historialTicketsDeCompra = fopen("./ticketsCompra.dat", "rb");
    struct TicketCompra ticket;
    fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    while(!feof(historialTicketsDeCompra))
    {
        if(!strcmp(idTicketCompra, ticket.id)) break;
        fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    }
    fclose(historialTicketsDeCompra);
    return ticket;
}

int registrarTicketDeCompra(struct TicketCompra ticket) 
{
    FILE *historialTicketsDeCompra = NULL;
    int estado = 1;
    if(!fopen("./ticketsCompra.dat", "rb")) crearAlmacenTicketsCompra();
    historialTicketsDeCompra = fopen("./ticketsCompra.dat", "ab");
    if(!verificarExistenciaTicketDeCompra(ticket.id)) {
        fwrite(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
        estado = 1;
    }else {
        estado = 0;
    }
    fclose(historialTicketsDeCompra);
    return estado;
}

struct TicketCompra tomarDatosTicketDeCompra()
{
    struct TicketCompra nuevoTicket;
    puts("Ingresa el id del ticket de compra: ");
    __fpurge(stdin);
    fgets(nuevoTicket.id, 30, stdin);
    puts("Ingresa la fecha del ticket de compra: ");
    __fpurge(stdin);
    fgets(nuevoTicket.fecha, 70, stdin);
    do
    {
        puts("Ingresa la cantidad de productos diferentes comprados del ticket de compra: [1-100]");
        __fpurge(stdin);
        scanf("%d", &nuevoTicket.cantidadProductos);
    } while (nuevoTicket.cantidadProductos < 0 && nuevoTicket.cantidadProductos > 100);
    for(int i = 0; i < nuevoTicket.cantidadProductos; i++)
    {
        agregarProductoLista(nuevoTicket.productos, i);
    }
    return nuevoTicket;
}

void agregarProductoLista(struct ProductoLista lista[], int posicion)
{
    char idProducto[30];
    struct Producto productoAlmacen;
    int existe = 1;
    do
    {
        system("clear");
        puts("El id del producto a agregar ya debe estar registrado en el almacen");
        puts("Ingresa el id del producto: ");
        __fpurge(stdin);
        fgets(idProducto, 100, stdin);
        existe = validarExistenciaProducto(idProducto);
        if(!existe) 
        {
            puts("El id ingresado no se encuentra en el almacen");
            sleep(5);
        }
        
    } while (!existe);
    productoAlmacen = buscarProducto(idProducto);
    strcpy(lista[posicion].id, productoAlmacen.id);
    strcpy(lista[posicion].nombre, productoAlmacen.nombre);
    puts("Ingresa la cantidad del producto: ");
    __fpurge(stdin);
    scanf("%d", &lista[posicion].cantidad);
    incrementarExistenciaProducto(idProducto,lista[posicion].cantidad);
    puts("Ingresa el precio del producto: ");
    __fpurge(stdin);
    scanf("%f", &lista[posicion].precio);
    lista[posicion].total = lista[posicion].precio * lista[posicion].cantidad;
}

void imprimirListaProductos(struct ProductoLista lista[], int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("ID del producto: %s", lista[i].id);
        printf("Nombre del producto: %s", lista[i].nombre);
        printf("Cantidad del producto: %d\n", lista[i].cantidad);
        printf("Precio del producto: %.2f\n", lista[i].precio);
        printf("Total del producto: %.2f\n", lista[i].total);
        puts("\n");
    }
    
}

int verificarExistenciaTicketDeCompra(char *idticketCompra)
{
    FILE *historialTicketsDeCompra = NULL;
    if(!fopen("./ticketsCompra.dat", "rb")) crearAlmacenTicketsCompra();
    historialTicketsDeCompra = fopen("./ticketsCompra.dat", "rb");
    struct TicketCompra ticket;
    fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    while(!feof(historialTicketsDeCompra))
    {
        if(!strcmp(idticketCompra, ticket.id)) return 1;
        fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    }
    fclose(historialTicketsDeCompra);
    return 0;
}

void imprimirTicketDeCompra(struct TicketCompra ticket)
{
    printf("ID ticket de compra: %s", ticket.id);
    printf("Fecha ticket de compra: %s", ticket.fecha);
    puts("Productos del ticket");
    imprimirListaProductos(ticket.productos, ticket.cantidadProductos);
    printf("Total: $ %.2lf\n", calcularTotalTicket(ticket.productos, ticket.cantidadProductos));
    puts("\n\n-------------------------------------------------------------------------\n\n");
}

double calcularTotalTicket(struct ProductoLista lista[], int cantidad)
{
    double total = 0;
    for (int i = 0; i < cantidad; i++)
    {
        total += lista[i].total;
    }
    return total;
}

void modificarTicketCompra(char *idticketCompra)
{
    FILE *historialTicketsDeCompra;
    char opcion;
    int existe=0,pos;
    struct TicketCompra ticket,tc;


    historialTicketsDeCompra = fopen("./ticketsCompra.dat", "r+b");
    fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    while(!feof(historialTicketsDeCompra))
    {
        if(!strcmp(idticketCompra, ticket.id))
        {
            puts("Ingrese la fecha nueva del ticket: ");
            __fpurge(stdin);
            fgets(ticket.fecha,70,stdin);
            pos=ftell(historialTicketsDeCompra)-sizeof(struct TicketCompra);
            fseek(historialTicketsDeCompra,pos,SEEK_SET);
            fwrite(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
            printf("Se modifico la fecha con exito.\n");
            existe=1;
        }
        fread(&ticket, sizeof(struct TicketCompra), 1, historialTicketsDeCompra);
    }
    fclose(historialTicketsDeCompra);
}



/* -----------------------------Interfaz principal servidor ------------------------ */

void interfazPrincipalServidor () 
{
    int opcion, repetir;
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
        puts("8.- Agregar nuevo ticket de compra");
        puts("9.- Buscar ticket de compra");
        puts("10.- Mostrar listado de tickets de compra");
        puts("11.- Modificar fecha de un ticket");
        puts("12.- Salir del sistema");
        puts("¿Que accion deseas realizar? ");
        __fpurge(stdin);
        scanf("%d", &opcion);
        seleccionDeOpcion(opcion);
        puts("Ingresa 1 para volver al menu principal o ingresa 0 para salir del sistema");
        __fpurge(stdin);
        scanf("%d", &repetir);
    } while (repetir);
}

void seleccionDeOpcion (char opcion)
{
    char idProducto[30], idTicketCompra[30];
    switch (opcion)
    {
    case 1:
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
    case 2:
        system("clear");
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
    case 3:
        /* Buscar datos de un producto */
        system("clear");
        puts("Ingresa el ID producto a buscar: ");
        __fpurge(stdin);
        fgets(idProducto, 30, stdin);
        if(validarExistenciaProducto(idProducto))
        {
            system("clear");
            puts("Datos del producto solicitado\n\n");
            imprimirProducto(buscarProducto(idProducto));
        }else{
            system("clear");
            puts("No existe producto en el almacen con el ID ingresado");
        }
        break;
    case 4:
        /*Elimina un producto*/
        system("clear");
        puts("Ingresa el ID producto: ");
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
    case 5:

        break;
    case 6:

        break;
    case 7:
        /* Mostrar listado del almacen */
        system("clear");
        puts("===== Lista de productos en almacen ====\n\n");
        mostrarProductos();
        break;
    case 8:
        system("clear");
        if(registrarTicketDeCompra(tomarDatosTicketDeCompra()))
        {
            puts("Ticket de compra registrado exitosamente");
        }else {
            puts("Ya existe un ticket de compra con el ID ingresado");
        }
        break;
    case 9:
        system("clear");
        puts("Ingresa el ID del ticket de compra a buscar: ");
        __fpurge(stdin);
        fgets(idTicketCompra, 30, stdin);
        if(verificarExistenciaTicketDeCompra(idTicketCompra))
        {
            system("clear");
            puts("Datos del producto solicitado\n\n");
            imprimirTicketDeCompra(buscarTicketDeCompra(idTicketCompra));
        }else{
            system("clear");
            puts("No existe producto en el almacen con el ID ingresado");
        }
        break;
    case 10:
        system("clear");
        puts("==== Lista de tickets de compra ====\n\n");
        mostrarTicketsDeCompra();
        break;
    case 11: /*Modifica algun dato del ticket*/
        system("clear");
        puts("Ingresa el ID del ticket a modificar: ");
        __fpurge(stdin);
        fgets(idTicketCompra, 30, stdin);
        if(verificarExistenciaTicketDeCompra(idTicketCompra))
        {
            modificarTicketCompra(idTicketCompra);    
        }
        else
        {
            puts("No existe producto en el almacen con el ID ingresado");
        }
        break;
    case 12:
        /* Salir del sistema */
        exit(EXIT_SUCCESS);
        break;
    default:
        puts("La opcion ingresada no es valida");
        break;
    }
}