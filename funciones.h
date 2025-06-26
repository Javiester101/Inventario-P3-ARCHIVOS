struct Cliente 
{
    char nombre[30];
    int cedula;
};

struct Producto 
{
    char nombre[20];
    float precio;
};

struct Ventas 
{
    struct Cliente cliente;
    int NumProductos;
    struct Producto productos[5];
    float totalVenta;
};
int menu();
void Leercadena(char *cadena, int num);
void inicializarProductos(struct Producto productos[5]);
void imprimirProductos(struct Producto productos[5]);
void guardarProductos(struct Producto *productos);
int leerProductos(struct Producto *productos);
void realizarVenta(struct Producto productos[5]);
void guardarVenta(struct Ventas venta);
void leerVentasPool(struct Ventas *ventas, int *numVentas,int num);
void leerVEntas1x1(struct Ventas *ventas, int *numVentas);
void listarVentas(struct Ventas *ventas, int numVentas);
void buscarVentaXCedula();
void imprimirVenta(struct Ventas venta);


