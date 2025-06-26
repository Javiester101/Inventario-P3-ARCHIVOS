#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu(){
    int opc;
    printf("\tBienvenido al sistema de ventas\n");
    printf("Seleccione una opcion:\n");
    printf("1.Inicializar productos\n");
    printf("2.Imprimir productos\n");
    printf("3.Realizar venta\n");
    printf("4.Listar ventas\n");
    printf("5.Buscar venta\n");
    printf("6.Salir\n");
    printf("Ingrese la opcion: ");
    scanf("%d", &opc);
    return opc;
}

void Leercadena(char *cadena, int num) {
    fflush(stdin);
    fgets(cadena, num, stdin);
    int len = strlen(cadena) - 1; 
    cadena[len] = '\0';
} 

void inicializarProductos(struct Producto productos[5]) {
    strcpy(productos[0].nombre,"Camiseta");
    productos[0].precio = 8;
    strcpy(productos[1].nombre,"Camisa");
    productos[1].precio = 15;
    strcpy(productos[2].nombre,"Pantalon");
    productos[2].precio = 25;
    strcpy(productos[3].nombre,"Zapatos");
    productos[3].precio = 40;
    strcpy(productos[4].nombre,"Gorra");
    productos[4].precio = 15;
    guardarProductos(productos);
}

void imprimirProductos(struct Producto productos[5]) {
    if (leerProductos(productos) == 1)
    {
         printf("#\t\tLista de productos\n");
         printf("#\t\tNombre\t\tPrecio\n");
         for (int i = 0; i < 5; i++) 
         {
         printf("%d\t\t%s\t\t%.2f\n", i , productos[i].nombre, 
                                         productos[i].precio);
       }
    }
}

void guardarProductos(struct Producto *productos) {
    FILE *f;
    f=fopen("productos.dat", "wb+");
    fwrite(productos, sizeof(struct Producto), 5, f);
    fclose(f);
}

int leerProductos(struct Producto *productos) {
    FILE *f;
    f=fopen("productos.dat", "rb+");
    if (f == NULL) {
        printf("No se encontro el archivo\n");
        return 0;
    }
    fread(productos, sizeof(struct Producto), 5, f);
    fclose(f);
    return 1;
}

void realizarVenta(struct Producto productos[5]) {
    struct Ventas venta;
    int numProductos;
    printf("Productos disponibles:\n");
    imprimirProductos(productos);
    
    printf("Ingrese el nombre del cliente: ");
    Leercadena(venta.cliente.nombre, 30);
    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &venta.cliente.cedula);

    printf("Ingrese el numero de productos a vender (maximo 5): ");
    scanf("%d", &numProductos);
    if (numProductos < 1 || numProductos > 5) {
        printf("Numero de productos invalido. Debe ser entre 1 y 5.\n");
        return;
    }
    venta.NumProductos = numProductos;
    venta.totalVenta = 0.0;
    int numP=0;
    for (int i = 0; i < numProductos; i++)
    {
        
        printf("Ingrese el numero de productos que desea comprar %d (0-4): ", i + 1);
        scanf("%d", &numP);
        strcpy(venta.productos[i].nombre, productos[numP].nombre);
        venta.productos[i].precio = productos[numP].precio;
        venta.totalVenta += productos[numP].precio;
    }
    guardarVenta(venta);
    printf("Venta realizada correctamente.\n");
}

void guardarVenta(struct Ventas venta) {
    FILE *f;
    f = fopen("ventas.dat", "ab+");
    if (f == NULL) {
        printf("No se pudo abrir el archivo de ventas.\n");
        return;
    }
    fwrite(&venta, sizeof(struct Ventas), 1, f);
    fclose(f);
    printf("Venta guardada correctamente.\n");
}

void leerVentasPool(struct Ventas *ventas, int *numVentas,int num) {
    FILE *f;
    f = fopen("ventas.dat", "rb+");
    if (f == NULL) {
        printf("No se pudo abrir el archivo de ventas.\n");
        *numVentas = 0;
        return;
    }
    *numVentas = fread(ventas, sizeof(struct Ventas), num, f);
    fclose(f);
}

void listarVentas(struct Ventas *ventas, int numVentas) {
    if (numVentas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }
    printf("#\tCliente\t\tCedula\n");
    for (int i = 0; i < numVentas; i++) {
        printf("%d\t%s\t%d\t", i + 1, ventas[i].cliente.nombre, ventas[i].cliente.cedula);
        for (int j = 0; j < ventas[i].NumProductos; j++) {
            printf("Prodcutos:\n");
            printf("Nombre: %s \n ", ventas[i].productos[j].nombre);
            printf("Precio: %.2f \n", ventas[i].productos[j].precio);
        }
        printf("\t%.2f\n", ventas[i].totalVenta);
    }
}

void buscarVentaXCedula() {
    int cedulaBuscar;
    int numVentas;
    int f=0;
    printf("Ingrese el numero de cedula del cliente a buscar: ");
    scanf("%d", &cedulaBuscar);
    struct Ventas venta[5];
    leerVentasPool(venta, &numVentas, 5);
    for (int i = 0; i < numVentas; i++) {
        if (venta[i].cliente.cedula == cedulaBuscar)
         {
            imprimirVenta(venta[i]);
            f=1;
        }
    }
    if ( f == 0) 
    {
        printf("No se encontraron ventas para la cedula %d.\n", cedulaBuscar);
    }
    
}

void imprimirVenta(struct Ventas venta) {
    printf("Cliente: %s\n", venta.cliente.nombre);
    printf("Cedula: %d\n", venta.cliente.cedula);
    printf("Productos:\n");
    for (int i = 0; i < venta.NumProductos; i++) {
        printf("Nombre: %s, Precio: %.2f\n", venta.productos[i].nombre, venta.productos[i].precio);
    }
    printf("Total de la venta: %.2f\n", venta.totalVenta);
}