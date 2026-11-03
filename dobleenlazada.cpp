#include <iostream>
using namespace std;
struct Atleta {
    int id;
    int tiempo;
    Atleta* sig;
    Atleta* ant;
};
Atleta* crearAtleta(int i, int t) {
    Atleta* nuevoA = new Atleta{i, t, NULL, NULL};
    return nuevoA;
}
void insertarInicio(Atleta*& cab, Atleta* nuevo) {
    if (cab == NULL) {
        cab = nuevo;
    } else {
        nuevo->sig = cab;
        cab->ant = nuevo;
        cab = nuevo;
    }
}
void mostrarAtletas(Atleta* cab) {
    Atleta* aux = cab;
    cout << "\nLista de Atletas:\n";
    while (aux != NULL) {
        cout << "ID: " << aux->id << " Tiempo: " << aux->tiempo << endl;
        aux = aux->sig;
    }
}
double promedioTiempos(Atleta* cab) {
    if (cab == NULL) return 0.0;
    int suma = 0, contador = 0;
    Atleta* aux = cab;
    while (aux != NULL) {
        suma += aux->tiempo;
        contador++;
        aux = aux->sig;
    }
    return (double)suma / contador;
}
void modificarTiempo(Atleta* cab) {
    if (cab == NULL) {
        cout << "No hay atletas registrados.\n";
        return;
    }
    int idBuscar, nuevoTiempo;
    cout << "Ingrese el ID del atleta para modificar su tiempo: ";
    cin >> idBuscar;
    Atleta* aux = cab;
    while (aux != NULL && aux->id != idBuscar) {
        aux = aux->sig;
    }
    if (aux == NULL) {
        cout << "Atleta no encontrado.\n";
    } else {
        cout << "Ingrese el nuevo tiempo para el atleta ID " << idBuscar << ": ";
        cin >> nuevoTiempo;
        aux->tiempo = nuevoTiempo;
        cout << "Tiempo actualizado.\n";
    }
}
void compararTiempos(Atleta* cab) {
    if (cab == NULL) {
        cout << "No hay atletas registrados.\n";
        return;
    }
    int id1, id2;
    cout << "Ingrese el ID del primer atleta: ";
    cin >> id1;
    cout << "Ingrese el ID del segundo atleta: ";
    cin >> id2;
    Atleta* a1 = NULL;
    Atleta* a2 = NULL;
    Atleta* aux = cab;
    while (aux != NULL) {
        if (aux->id == id1) a1 = aux;
        if (aux->id == id2) a2 = aux;
        aux = aux->sig;
    }
    if (a1 == NULL || a2 == NULL) {
        cout << "Alguno de los atletas no fue encontrado.\n";
        return;
    }
    if (a1->tiempo < a2->tiempo) {
        cout << "El atleta con ID " << a1->id << " tiene mejor tiempo: " << a1->tiempo << endl;
    } else if (a2->tiempo < a1->tiempo) {
        cout << "El atleta con ID " << a2->id << " tiene mejor tiempo: " << a2->tiempo << endl;
    } else {
        cout << "Ambos atletas tienen el mismo tiempo: " << a1->tiempo << endl;
    }
}
void compararConAnterior(Atleta* cab) {
    if (cab == NULL) {
        cout << "No hay atletas registrados.\n";
        return;
    }
    int idBuscar;
    cout << "Ingrese el ID del atleta para comparar con su anterior: ";
    cin >> idBuscar;
    Atleta* aux = cab;
    while (aux != NULL && aux->id != idBuscar) {
        aux = aux->sig;
    }
    if (aux == NULL) {
        cout << "Atleta no encontrado.\n";
        return;
    }
    if (aux->ant == NULL) {
        cout << "El atleta con ID " << idBuscar << " no tiene atleta anterior.\n";
        return;
    }
    cout << "Atleta actual (ID " << aux->id << ") tiempo: " << aux->tiempo << endl;
    cout << "Atleta anterior (ID " << aux->ant->id << ") tiempo: " << aux->ant->tiempo << endl;

    if (aux->tiempo < aux->ant->tiempo) {
        cout << "El atleta actual tiene mejor tiempo.\n";
    } else if (aux->tiempo > aux->ant->tiempo) {
        cout << "El atleta anterior tiene mejor tiempo.\n";
    } else {
        cout << "Ambos tienen el mismo tiempo.\n";
    }
}
double promedioUltimosN(Atleta* cab, int N) {
    if (cab == NULL || N <= 0) return 0.0;
    Atleta* aux = cab;
    int total = 0;
    while (aux->sig != NULL) {
        aux = aux->sig;
        total++;
    }
    total++; 
    if (N > total) N = total;
    int suma = 0, contador = 0;
    while (aux != NULL && contador < N) {
        suma += aux->tiempo;
        contador++;
        aux = aux->ant;
    }
    return (double)suma / contador;
}
void eliminarPeorTiempo(Atleta*& cab) {
    if (cab == NULL) {
        cout << "No hay atletas para eliminar.\n";
        return;
    }
    Atleta* aux = cab;
    Atleta* peor = cab;
    while (aux != NULL) {
        if (aux->tiempo > peor->tiempo) {
            peor = aux;
        }
        aux = aux->sig;
    }
    if (peor->ant != NULL) {
        peor->ant->sig = peor->sig;
    } else {
        cab = peor->sig;
    }
    if (peor->sig != NULL) {
        peor->sig->ant = peor->ant;
    }
    delete peor;
    cout << "Atleta con peor tiempo eliminado.\n";
}
void atletasConTiempoMayorA(Atleta* cab) {
    if (cab == NULL) {
        cout << "No hay atletas registrados.\n";
        return;
    }
    int tiempoRef;
    cout << "Ingrese el tiempo de referencia: ";
    cin >> tiempoRef;
    Atleta* aux = cab;
    bool encontrado = false;
    cout << "Atletas con tiempo mayor a " << tiempoRef << ":\n";
    while (aux != NULL) {
        if (aux->tiempo > tiempoRef) {
            cout << "ID: " << aux->id << " Tiempo: " << aux->tiempo << endl;
            encontrado = true;
        }
        aux = aux->sig;
    }
    if (!encontrado) {
        cout << "No hay atletas con tiempo mayor a " << tiempoRef << endl;
    }
}
int main() {
    Atleta* cab = NULL;
    Atleta* aux;
    int tiempo, id = 100, N;
    cout << "Cuantos atletas quiere registrar? ";
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cout << "Ingrese el tiempo del atleta " << i << ": ";
        cin >> tiempo;
        aux = crearAtleta(id, tiempo);
        insertarInicio(cab, aux);
        id++;
    }
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Mostrar atletas\n";
        cout << "2. Promedio de tiempos de todos los atletas\n";
        cout << "3. Modificar tiempo de un atleta\n";
        cout << "4. Comparar tiempos de dos atletas\n";
        cout << "5. Comparar tiempo de un atleta con el anterior\n";
        cout << "6. Promedio de tiempos de los N últimos atletas\n";
        cout << "7. Eliminar atleta con peor tiempo\n";
        cout << "8. Mostrar atletas con tiempo mayor a un valor\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                mostrarAtletas(cab);
                break;
            case 2:
                cout << "Promedio de tiempos: " << promedioTiempos(cab) << endl;
                break;
            case 3:
                modificarTiempo(cab);
                break;
            case 4:
                compararTiempos(cab);
                break;
            case 5:
                compararConAnterior(cab);
                break;
            case 6:
                cout << "Ingrese N para promedio de los N ultimos atletas: ";
                int n;
                cin >> n;
                cout << "Promedio de los ultimos " << n << " atletas: " << promedioUltimosN(cab, n) << endl;
                break;
            case 7:
                eliminarPeorTiempo(cab);
                break;
            case 8:
                atletasConTiempoMayorA(cab);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);
    Atleta* temp;
    while (cab != NULL) {
        temp = cab;
        cab = cab->sig;
        delete temp;
    }
    return 0;
}
