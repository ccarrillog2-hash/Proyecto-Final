#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct producto {
int codigo;
char nombre [30];
int stock;
float precio;
int ventasAcumuladas;
bool activo;
};

const char* ARCHIVO_PRODUCTOS = "productos.dat";

void mostrarMenu();
void registrarProducto();
void listarProductos();
void buscarPorCodigo();
void buscarPorNombre();

int main() {
    cout << "Nombre del estudiante: Cindy Julissa Carrillo Guarcas\n";
    mostrarMenu();
    return 0;
}
void mostrarMenu(){
        int opcion;

        do{
            cout << "\n== Sistema de gestion de ventas e inventario para tienda ==\n";
            cout << "1. Registrar producto\n";
            cout << "2. Listar productos\n";
            cout << "3. Buscar por codigo\n";
            cout << "4. Buscar por nombre\n";
            cout << "0. Salir\n";
            cout << "\nSelecciona una Opcion: ";
            cin >> opcion;

            switch(opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                listarProductos();
                break;
            case 3:
                buscarPorCodigo();
                break;
            case 4:
                buscarPorNombre();
                break;
            }

        } while(opcion != 0);
}

void registrarProducto(){
    producto p;

    cout << "\n--Registrar Producto --\n";
    cout << "Codigo: ";
    cin >> p.codigo;

    cin.ignore();
    cout << "Nombre: ";
    cin.getline(p.nombre,30);

    cout << "Stock: ";
    cin >> p.stock;

    cout << "Precio: ";
    cin >> p.precio;

    p.ventasAcumuladas = 0;
    p.activo = true;

    ofstream archivo(ARCHIVO_PRODUCTOS, ios::binary | ios::app);
    archivo.write((char*)&p, sizeof(producto));
    archivo.close();

    cout << "Producto guardado correctamente.\n";
}

void listarProductos(){
    producto p;

    ifstream archivo("productos.dat", ios::binary);
    if (!archivo) {
        cout << "No existe productos.\n";
        return;
    }
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(producto))) {
        cout << "\nCodigo: " << p.codigo;
        cout << "\nNombre: " << p.nombre;
        cout << "\nStock: " << p.stock;
        cout << "\nPrecio: Q" << p.precio;
        cout << "\nVentas: " << p.ventasAcumuladas;
        cout << "\nActivo: " << p.activo;
    }
archivo.close();
}

void buscarPorCodigo(){
    producto p;
    int codigo;
    bool encontrado = false;

    cout << "\n--- Busqueda por codigo ---\n";
    cout << "Codigo: ";
    cin >> codigo;

    ifstream archivo(ARCHIVO_PRODUCTOS, ios::binary);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "\nEncontrado:\n";
            cout << "Nombre: " << p.nombre << endl;
            cout << "Stock: " << p.stock << endl;
            cout << "Precio: Q" << p.precio << endl;
            encontrado = true;
            break;
        }
        }
    archivo.close();

    if (!encontrado)
        cout << "No existe codigo\n";
}
void buscarPorNombre(){
    producto p;
    char nombre [30];
    bool encontrado = false;

    cout << "\n--- Busqueda por nombre ---\n";
    cout << "Nombre: ";
    cin.getline(nombre,30);

    ifstream archivo(ARCHIVO_PRODUCTOS, ios::binary);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(producto))) {
        if (p.activo && strstr(p.nombre, nombre)) {
            cout << p.codigo << " - " << p.nombre << endl;
            encontrado = true;
        }
    }

    archivo.close();

    if (!encontrado)
        cout << "No existe producto\n";
}