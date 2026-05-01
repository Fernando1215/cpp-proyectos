#include <iostream>
using namespace std;
struct Jugador {
	string nom;
	int bo;
	Jugador* sig;
};
struct Pais {
	string nom;
	Pais* sig;
	Jugador* sub;
};
Pais* crearPais(string nom) {
	Pais* nuevo = new Pais{nom};
	return nuevo;
}
void insertarPais(Pais*& cab, Pais* nuevo) {
	nuevo->sig = cab;
	cab = nuevo;
}
Jugador* crearJugador(string nom, int bo) {
	Jugador* nuevo = new Jugador{nom, bo};
	return nuevo;
}
void insertarJugador(Jugador*& cab, Jugador* nuevo) {
	nuevo->sig = cab;
	cab = nuevo;
}
void imprimirTodo(Pais* cab) {
	Pais* actualPais = cab;
	Jugador* actualJugador;
	while (actualPais != NULL) { 
		cout << "\nPais: " << actualPais->nom << endl;
		actualJugador = actualPais->sub;
		while (actualJugador != NULL) {
			cout << "  Jugador: " << actualJugador->nom
			     << " | Balones: " << actualJugador->bo << endl;
			actualJugador = actualJugador->sig;
		}
		actualPais = actualPais->sig;
	}
}
Pais* buscarPais(Pais* cab, string nomPais) {
    Pais* aux = cab;
    while (aux != NULL && aux->nom != nomPais) {
        aux = aux->sig;
    }
    return aux;
} 
Jugador* buscarJugador(Jugador* cab, string nomJugador) {
    Jugador* aux = cab;
    while (aux != NULL && aux->nom != nomJugador) {
        aux = aux->sig;
    }
    return aux;
}
void totalBalones(Pais* cab) {
    string nomPais;
    cout << "\nIngrese el nombre del país: ";
    cin >> nomPais;
    Pais* p = buscarPais(cab, nomPais);
    if (p == NULL) {
        cout << "El país no existe.\n";
        return;
    }
    int total = 0;
    Jugador* j = p->sub;
    while (j != NULL) {
        total += j->bo;
        j = j->sig;
    }
    cout << "Total de balones de oro en " << nomPais << ": " << total << endl;
}
void cambiarJugadorDePais(Pais* cab) {
    string jugadorNom, paisOrigen, paisDestino;
    cout << "\nIngrese el nombre del jugador a mover: ";
    cin >> jugadorNom;
    cout << "Ingrese el país actual del jugador: ";
    cin >> paisOrigen;
    cout << "Ingrese el nuevo país: ";
    cin >> paisDestino;
    Pais* origen = buscarPais(cab, paisOrigen);
    Pais* destino = buscarPais(cab, paisDestino);
    if (origen == NULL || destino == NULL) {
        cout << "Alguno de los países no existe.\n";
        return;
    }
    Jugador* actual = origen->sub;
    Jugador* anterior = NULL;
    while (actual != NULL && actual->nom != jugadorNom) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual == NULL) {
        cout << "Jugador no encontrado en " << paisOrigen << endl;
        return;
    }
    if (anterior == NULL){
        origen->sub = actual->sig;}
    else{
        anterior->sig = actual->sig;
    actual->sig = destino->sub;
    destino->sub = actual;
    cout << "Jugador movido correctamente a " << paisDestino << endl;
}
}
void actualizarBalones(Pais* cab) {
    string nomPais, nomJugador;
    int nuevosBalones;
    cout << "\nIngrese el país del jugador: ";
    cin >> nomPais;
    Pais* p = buscarPais(cab, nomPais);
    if (p == NULL) {
        cout << "El país no existe.\n";
        return;
    }
    cout << "Ingrese el nombre del jugador: ";
    cin >> nomJugador;
    Jugador* j = buscarJugador(p->sub, nomJugador);
    if (j == NULL) {
        cout << "El jugador no existe en " << nomPais << endl;
        return;
    }
    cout << "Ingrese la nueva cantidad de balones: ";
    cin >> nuevosBalones;
    j->bo = nuevosBalones;
    cout << "Cantidad actualizada correctamente.\n";
}
int main() {
    Pais* cab = NULL;
    string nom;
    int balones;
    for (int i = 1; i <= 3; i++) {
        cout << "Ingrese el país: ";
        cin >> nom;
        insertarPais(cab, crearPais(nom));
    }
    Pais* aux = cab;
    while (aux != NULL) {
        cout << "\n=== " << aux->nom << " ===" << endl;
        for (int i = 1; i <= 3; i++) {
            cout << "Ingrese el jugador: ";
            cin >> nom;
            cout << "Ingrese la cantidad de balones: ";
            cin >> balones;
            insertarJugador(aux->sub, crearJugador(nom, balones));
        }
        aux = aux->sig;
    }
    int opc;
    do {
        cout << "MENÚ"<<endl;
        cout << "1. Mostrar todos los países y jugadores"<<endl;
        cout << "2. Calcular total de balones de un país"<<endl;
        cout << "3. Cambiar un jugador de país"<<endl;
        cout << "4. Actualizar balones de un jugador"<<endl;
        cout << "5. Salir"<<endl;
        cout << "Opción"<<endl;
        cin >> opc;
        switch (opc) {
            case 1:
			 imprimirTodo(cab); 
			 break;
            case 2:
			 totalBalones(cab); 
			 break;
            case 3:
			 cambiarJugadorDePais(cab);
			  break;
            case 4:
			 actualizarBalones(cab); 
			 break;
            case 5:
			 cout<<"Saliendo"<<endl; 
			 break;
            default:
			 cout<<"opcion invalida"<<endl;
			  break;
        }

    } while (opc != 5);
    return 0;
}








