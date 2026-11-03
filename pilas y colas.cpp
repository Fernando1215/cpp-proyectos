#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

// ================== PILA ==================
void push(Nodo*& tope, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = tope;
    tope = nuevo;
}

void pop(Nodo*& tope) {
    if (tope == NULL) {
        cout << "La pila esta vacia\n";
        return;
    }
    Nodo* temp = tope;
    cout << "Eliminado de la pila: " << temp->dato << endl;
    tope = tope->siguiente;
    delete temp;
}

void mostrarPila(Nodo* tope) {
    if (tope == NULL) {
        cout << "La pila esta vacia\n";
        return;
    }
    cout << "Pila: ";
    while (tope != NULL) {
        cout << tope->dato << " ";
        tope = tope->siguiente;
    }
    cout << endl;
}

// ================== COLA ==================
void enqueue(Nodo*& frente, Nodo*& fin, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    if (frente == NULL) {
        frente = nuevo;
    } else {
        fin->siguiente = nuevo;
    }
    fin = nuevo;
}

void dequeue(Nodo*& frente, Nodo*& fin) {
    if (frente == NULL) {
        cout << "La cola esta vacia\n";
        return;
    }
    Nodo* temp = frente;
    cout << "Eliminado de la cola: " << temp->dato << endl;
    frente = frente->siguiente;
    if (frente == NULL) {
        fin = NULL; // cola vacía
    }
    delete temp;
}

void mostrarCola(Nodo* frente) {
    if (frente == NULL) {
        cout << "La cola esta vacia\n";
        return;
    }
    cout << "Cola: ";
    while (frente != NULL) {
        cout << frente->dato << " ";
        frente = frente->siguiente;
    }
    cout << endl;
}

// ================== MENU PRINCIPAL ==================
int main() {
    Nodo* pila = NULL;        // Tope de la pila
    Nodo* frente = NULL;      // Frente de la cola
    Nodo* fin = NULL;         // Final de la cola

    int opcion, valor;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Insertar en Pila\n";
        cout << "2. Eliminar de Pila\n";
        cout << "3. Mostrar Pila\n";
        cout << "4. Insertar en Cola\n";
        cout << "5. Eliminar de Cola\n";
        cout << "6. Mostrar Cola\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Digite un valor: ";
                cin >> valor;
                push(pila, valor);
                break;
            case 2:
                pop(pila);
                break;
            case 3:
                mostrarPila(pila);
                break;
            case 4:
                cout << "Digite un valor: ";
                cin >> valor;
                enqueue(frente, fin, valor);
                break;
            case 5:
                dequeue(frente, fin);
                break;
            case 6:
                mostrarCola(frente);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while (opcion != 0);

    return 0;
}

