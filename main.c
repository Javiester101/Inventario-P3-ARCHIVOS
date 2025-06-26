#include <stdio.h>
#include "funciones.h"
#define MAX_PRODUCTOS 5

int main (int argc, char *argv[]) {
    
    struct Producto productos[5];
    struct Ventas ventas[5];
    int opc;
    int numVentas = 0;
    do
    {
        opc = menu();
        switch (opc)
        {
            case 1:
                inicializarProductos(productos);
                printf("Productos inicializados correctamente.\n");
                break;
            case 2:
                imprimirProductos(productos);
                break;
            case 3:
                realizarVenta(productos);
                break;
            case 4:
                leerVentasPool(ventas, &numVentas,MAX_PRODUCTOS );
                if (numVentas > 0) {
                    listarVentas(ventas, numVentas);
                }else {
                    printf("No hay ventas registradas.\n");
                }
                break;
            case 5:
                buscarVentaXCedula();
                printf("Busqueda de venta por cedula completada.\n");
                break;
            case 6:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida, intente de nuevo.\n");
        }
    } while (opc!= 6);
    
    return 0;
}