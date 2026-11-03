#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct NodoISBN {
    string ISBN;
    string titulo;
    string autor;
    string genero;
    bool estado;
    NodoISBN* izq;
    NodoISBN* der;
};

struct Libro {
    string titulo;
    string autor;
    string ISBN;
    bool estado;
    Libro* siguiente;
};

struct Genero {
    string nombre;
    Genero* sig;
    Libro* listaLibros;
};

struct Prestamo {
    string titulo;
    string autor;
    string ISBN;
    string genero;
    Prestamo* sig;
};

// Inserta en ABB. Si ISBN ya existe, lo informa y no inserta.
void InsertarABB(NodoISBN*& raiz, Libro* libro, const string& genero) {
    if (raiz == nullptr) {
        raiz = new NodoISBN{
            libro->ISBN,
            libro->titulo,
            libro->autor,
            genero,
            libro->estado,
            nullptr,
            nullptr
        };
        return;
    }
    if (libro->ISBN < raiz->ISBN) {
        InsertarABB(raiz->izq, libro, genero);
    } else if (libro->ISBN > raiz->ISBN) {
        InsertarABB(raiz->der, libro, genero);
    } else {
        cout << "El ISBN " << libro->ISBN << " ya existe en el ABB. No se inserta duplicado.\n";
    }
}

int BuscarABB(NodoISBN* raiz, const string& isbn, int& saltos) {
    if (raiz == nullptr) {
        return 0;
    }
    saltos++;
    if (isbn == raiz->ISBN) {
        cout << "Libro encontrado en ABB\n";
        cout << "Titulo: " << raiz->titulo << endl;
        cout << "Autor: " << raiz->autor << endl;
        cout << "Genero: " << raiz->genero << endl;
        cout << "Estado: " << (raiz->estado ? "Disponible" : "Prestado") << endl;
        return 1;
    }
    if (isbn < raiz->ISBN)
        return BuscarABB(raiz->izq, isbn, saltos);
    else
        return BuscarABB(raiz->der, isbn, saltos);
}

void InordenABB(NodoISBN* raiz) {
    if (raiz != nullptr) {
        InordenABB(raiz->izq);
        cout << raiz->ISBN << " - " << raiz->titulo << " (" << raiz->genero << ")\n";
        InordenABB(raiz->der);
    }
}

// Inserta un nuevo genero al final; evita duplicados
void Insertar_Genero(const string& nombre, Genero*& cab) {
    for (Genero* temporal = cab; temporal != nullptr; temporal = temporal->sig) {
        if (temporal->nombre == nombre) {
            cout << "El genero " << nombre << " ya existe" << endl;
            return;
        }
    }
    Genero* nuevo = new Genero{nombre, nullptr, nullptr};
    if (cab == nullptr)
        cab = nuevo;
    else {
        Genero* temporal = cab;
        while (temporal->sig != nullptr)
            temporal = temporal->sig;
        temporal->sig = nuevo;
    }
    cout << "Genero '" << nombre << "' agregado correctamente.\n";
}

Genero* BuscarGenero(const string& nombre, Genero* cab) {
    Genero* temporal = cab;
    while (temporal != nullptr) {
        if (temporal->nombre == nombre)
            return temporal;
        temporal = temporal->sig;
    }
    return nullptr;
}

// Ahora retorna el puntero al nuevo Libro o nullptr si no se inserta (duplicado)
Libro* Insertar_Libro(const string& titulo, const string& id, const string& autor, bool estado, Libro*& cab) {
    // Verificar duplicados
    for (Libro* t = cab; t != nullptr; t = t->siguiente) {
        if (t->ISBN == id) {
            cout << "El ISBN ingresado ya existe" << endl;
            return nullptr;
        }
        if (t->titulo == titulo && t->autor == autor) {
            cout << "El titulo y el autor ya existen" << endl;
            return nullptr;
        }
    }
    // Crear y anexar
    Libro* nuevo = new Libro{titulo, autor, id, estado, nullptr};
    if (cab == nullptr) {
        cab = nuevo;
    } else {
        Libro* temporal = cab;
        while (temporal->siguiente != nullptr)
            temporal = temporal->siguiente;
        temporal->siguiente = nuevo;
    }
    cout << "Libro " << titulo << " agregado correctamente" << endl;
    return nuevo;
}

void Insertar_LibroEnGenero(const string& generoBuscado, const string& titulo, const string& id, const string& autor, bool estado, Genero*& cabGenero, NodoISBN*& raizABB) {
    Genero* gen = BuscarGenero(generoBuscado, cabGenero);
    if (gen == nullptr) {
        cout << "El genero no existe, no se puede insertar el libro" << endl;
        return;
    }
    // Insertar libro y obtener el puntero al nuevo nodo
    Libro* nuevoLibro = Insertar_Libro(titulo, id, autor, estado, gen->listaLibros);
    if (nuevoLibro == nullptr) {
        // no se insertó (duplicado u otro) -> no insertar en ABB
        return;
    }
    // Insertar en ABB usando el libro recién creado
    InsertarABB(raizABB, nuevoLibro, gen->nombre);
}

void MostrarBiblioteca(Genero* cab) {
    Genero* auxGenero = cab;
    if (auxGenero == nullptr) {
        cout << "No hay generos registrados" << endl;
        return;
    }
    while (auxGenero != nullptr) {
        cout << "Genero: " << auxGenero->nombre << endl;
        Libro* auxLibro = auxGenero->listaLibros;
        if (auxLibro == nullptr)
            cout << "No hay libros registrados en este genero" << endl;
        else {
            while (auxLibro != nullptr) {
                cout << "titulo: " << auxLibro->titulo << endl;
                cout << "autor: " << auxLibro->autor << endl;
                cout << "ISBN: " << auxLibro->ISBN << endl;
                cout << "estado: " << (auxLibro->estado ? "Disponible" : "Prestado") << endl;
                auxLibro = auxLibro->siguiente;
            }
        }
        auxGenero = auxGenero->sig;
    }
}

void BuscarLibroISBN(const string& id, Genero* cabGenero) {
    Genero* g = cabGenero;
    while (g != nullptr) {
        Libro* l = g->listaLibros;
        while (l != nullptr) {
            if (l->ISBN == id) {
                cout << "Libro encontrado en el genero " << g->nombre << endl;
                cout << "titulo: " << l->titulo << endl;
                cout << "autor: " << l->autor << endl;
                cout << "ISBN: " << l->ISBN << endl;
                cout << "estado: " << (l->estado ? "Disponible" : "Prestado") << endl;
                return;
            }
            l = l->siguiente;
        }
        g = g->sig;
    }
    cout << "No se encontro ningun libro con el ISBN " << id << endl;
}

void DevolverLibro(const string& id, Genero* cabGenero) {
    Genero* g = cabGenero;
    while (g != nullptr) {
        Libro* l = g->listaLibros;
        while (l != nullptr) {
            if (l->ISBN == id) {
                if (!l->estado) {
                    l->estado = true;
                    cout << "El libro con ISBN " << id << " ha sido devuelto" << endl;
                } else {
                    cout << "El libro con ISBN " << id << " ya estaba disponible" << endl;
                }
                return;
            }
            l = l->siguiente;
        }
        g = g->sig;
    }
    cout << "No se encontro ningún libro con el ISBN " << id << endl;
}

void EliminarLibroID(const string& id, Genero* cabGenero) {
    Genero* g = cabGenero;
    while (g != nullptr) {
        Libro* actual = g->listaLibros;
        Libro* anterior = nullptr;
        while (actual != nullptr && actual->ISBN != id) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (actual != nullptr) {
            if (anterior == nullptr)
                g->listaLibros = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;
            delete actual;
            cout << "Libro con ISBN " << id << " eliminado correctamente del genero " << g->nombre << endl;
            return;
        }
        g = g->sig;
    }
    cout << "No se encontro ningun libro con ese ISBN.\n";
}

void MostrarLibrosAutor(const string& autorBuscado, Genero* cabGenero) {
    bool encontrado = false;
    for (Genero* g = cabGenero; g != nullptr; g = g->sig) {
        for (Libro* l = g->listaLibros; l != nullptr; l = l->siguiente) {
            if (l->autor == autorBuscado) {
                if (!encontrado) {
                    cout << "Libros del autor " << autorBuscado << endl;
                    encontrado = true;
                }
                cout << "Titulo: " << l->titulo << " genero: " << g->nombre << endl;
            }
        }
    }
    if (!encontrado)
        cout << "No se encontraron libros del autor " << autorBuscado << endl;
}

void RegistrarPrestamo(Libro* libro, const string& genero, Prestamo*& historial) {
    Prestamo* nuevo = new Prestamo{libro->titulo, libro->autor, libro->ISBN, genero, historial};
    historial = nuevo;
}

void PrestarLibro(const string& id, Genero* cabGenero, Prestamo*& historial) {
    for (Genero* g = cabGenero; g != nullptr; g = g->sig) {
        for (Libro* l = g->listaLibros; l != nullptr; l = l->siguiente) {
            if (l->ISBN == id) {
                if (l->estado) {
                    l->estado = false;
                    RegistrarPrestamo(l, g->nombre, historial);
                    cout << "El libro con ISBN " << id << " ha sido prestado" << endl;
                } else {
                    cout << "El libro con ISBN " << id << " ya esta prestado" << endl;
                }
                return;
            }
        }
    }
    cout << "No se encontro ningun libro con el ISBN " << id << endl;
}

void MostrarHistorial(Prestamo* historial) {
    if (historial == nullptr) {
        cout << "No hay prestamos registrados " << endl;
        return;
    }
    cout << "Historial de prestamos" << endl;
    for (Prestamo* p = historial; p != nullptr; p = p->sig) {
        cout << p->titulo << " autor " << p->autor << " ISBN " << p->ISBN << " genero " << p->genero << endl;
    }
}

int main() {
    NodoISBN* raizABB = nullptr;
    Prestamo* historial = nullptr;
    Genero* cabGenero = nullptr;

    bool continuar = true;
    int opcion;
    while (continuar) {
        cout << "MENU" << endl;
        cout << "1. insertar genero" << endl;
        cout << "2. insertar libro en genero" << endl;
        cout << "3. mostrar biblioteca" << endl;
        cout << "4. buscar libro por ISBN" << endl;
        cout << "5. prestar libro" << endl;
        cout << "6. devolver libro" << endl;
        cout << "7. eliminar libro por ISBN" << endl;
        cout << "8. mostrar libros por autor" << endl;
        cout << "9. historial" << endl;
        cout << "10. Buscar libro por ISBN (ABB)" << endl;
        cout << "11. Recorrido Inorden del ABB" << endl;
        cout << "0. salir" << endl;
        cout << "seleccione una opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpiar buffer

        switch (opcion) {
            case 1: {
                string nombre;
                cout << "ingrese el nombre del genero: ";
                getline(cin, nombre);
                Insertar_Genero(nombre, cabGenero);
                break;
            }
            case 2: {
                string genero, titulo, autor, isbn;
                cout << "ingrese el genero donde se agregara el libro: ";
                getline(cin, genero);
                cout << "titulo: ";
                getline(cin, titulo);
                cout << "autor: ";
                getline(cin, autor);
                cout << "ISBN: ";
                getline(cin, isbn);
                Insertar_LibroEnGenero(genero, titulo, isbn, autor, true, cabGenero, raizABB);
                break;
            }
            case 3:
                MostrarBiblioteca(cabGenero);
                break;
            case 4: {
                string id;
                cout << "ingrese el ISBN a buscar: ";
                getline(cin, id);
                BuscarLibroISBN(id, cabGenero);
                break;
            }
            case 5: {
                string id;
                cout << "ingrese el ISBN del libro a prestar: ";
                getline(cin, id);
                PrestarLibro(id, cabGenero, historial);
                break;
            }
            case 6: {
                string id;
                cout << "ingrese el ISBN del libro a devolver: ";
                getline(cin, id);
                DevolverLibro(id, cabGenero);
                break;
            }
            case 7: {
                string id;
                cout << "ingrese el ISBN del libro a eliminar: ";
                getline(cin, id);
                EliminarLibroID(id, cabGenero);
                break;
            }
            case 8: {
                string autor;
                cout << "ingrese el nombre del autor: ";
                getline(cin, autor);
                MostrarLibrosAutor(autor, cabGenero);
                break;
            }
            case 9: {
                MostrarHistorial(historial);
                break;
            }
            case 10: {
                string isbn;
                int saltos = 0;
                cout << "Ingrese ISBN: ";
                getline(cin, isbn);
                if (!BuscarABB(raizABB, isbn, saltos))
                    cout << "Libro no encontrado\n";
                cout << "Saltos en ABB: " << saltos << endl;
                break;
            }
            case 11: {
                InordenABB(raizABB);
                break;
            }
            case 0:
                cout << "Saliendo del programa" << endl;
                continuar = false;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    }
    return 0;
}

