#include <iostream>
using namespace std;
struct Equipo {
    string nom;
    int numIntegrantes;
    Equipo* sig;
};
struct Concurso {
    string nom;
    Equipo* sub;
    Concurso* sig;
};
Concurso* crearConcurso(string nom) {
    Concurso* nuevoConcurso = new Concurso{nom};
    return nuevoConcurso;
}
Equipo* crearEquipo(string nom, int numIntegrantes) {
    Equipo* nuevoEquipo = new Equipo{nom, numIntegrantes};
    return nuevoEquipo;
}
void insertarEquipo(Equipo*& cab, Equipo* nuevoEquipo) {
    if (cab == NULL) {
        cab = nuevoEquipo;
    } else {
        Equipo* aux = cab;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevoEquipo;
    }
}
void insertarConcurso(Concurso*& cab, Concurso* nuevoConcurso) {
    if (cab == NULL) {
        cab = nuevoConcurso;
    } else {
        Concurso* aux = cab;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevoConcurso;
    }
}
Concurso* buscarConcurso(Concurso* cab, string nom) {
    Concurso* aux = cab;
    while (aux != NULL && aux->nom != nom) {
        aux = aux->sig;
    }
    return aux;
}
void imprimirTodo(Concurso* cab) {
    Concurso* aux1 = cab;
    Equipo* aux2;
    while (aux1 != NULL) {
        cout << "\nConcurso: " << aux1->nom << endl;
        aux2 = aux1->sub;
        while (aux2 != NULL) {
            cout << "  Equipo: " << aux2->nom << " | Integrantes: " << aux2->numIntegrantes << endl;
            aux2 = aux2->sig;
        }
        aux1 = aux1->sig;
    }
}
int main() {
    Concurso* cab = NULL, *temp;
    string nom;
    int nIntegrantes;
    for (int i = 0; i < 3; i++) {
        cout << "Ingrese el nombre del concurso [" << i << "]"<<endl;
        cin >> nom;
        insertarConcurso(cab, crearConcurso(nom));
    }
    imprimirTodo(cab);
    cout << "Nombre del concurso a buscar"<<endl;
    cin >> nom;
    temp = buscarConcurso(cab, nom);
    if (temp != NULL) {
        for (int i = 0; i < 3; i++) {
            cout << "Digite el nombre del equipo: ";
            cin >> nom;
            cout << "Ingrese la cantidad de participantes: ";
            cin >> nIntegrantes;
            insertarEquipo(temp->sub, crearEquipo(nom, nIntegrantes));
        }
        imprimirTodo(cab);
    } else {
        cout << "Concurso no encontrado" << endl;
    }
    return 0;
}












