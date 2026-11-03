#include <iostream>
#include <string>
using namespace std;
struct Nodo {
    string nombre;
    Nodo* siguiente;
    Nodo* anterior;
};
void insertar(Nodo* &cab,string nombre) {
    Nodo* nuevo = new Nodo{nombre,NULL,NULL};
    if (cab==NULL) {
        cab=nuevo;
        cab->siguiente=cab;
        cab->anterior=cab;
    } else {
        Nodo* ultimo=cab->anterior;
        nuevo->siguiente=cab;
        nuevo->anterior=ultimo;
        ultimo->siguiente=nuevo;
        cab->anterior=nuevo;
    }
}
void mostrarLista(Nodo* cab) {
    if (cab==NULL){
        cout<<"Lista vacia"<<endl;
        return;
    }
    Nodo* temp=cab;
    do {
        cout<<temp->nombre<<" ";
        temp=temp->siguiente;
    } while (temp!=cab);
    cout<<endl;
}
Nodo* eliminar(Nodo* &cab,Nodo* jugador) {
    if (cab==NULL or jugador==NULL) return NULL;
    if (jugador->siguiente==jugador) { 
        cab=NULL;
    } else {
        jugador->anterior->siguiente=jugador->siguiente;
        jugador->siguiente->anterior=jugador->anterior;
        if (jugador==cab) cab=jugador->siguiente;
    }
    Nodo* siguiente=jugador->siguiente;
    delete jugador;
    return siguiente;
}
int main() {
    Nodo* lista=NULL;
    int n;
    cout<<"ingrese cantidad de jugadores"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        string nombre;
        cout<<"Jugador "<<i+1<<": ";
        cin>>nombre;
        insertar(lista,nombre);
    }
    cout<<"lista inicial"<<endl;
    mostrarLista(lista);
    string elegido;
    cout << "ingrese el jugador inicial"<<endl;
    cin>>elegido;
    Nodo* actual=lista;
    while(actual->nombre!=elegido and actual->siguiente!=lista){
        actual = actual->siguiente;
    }
    string equipo1[100], equipo2[100];
    int e1 = 0, e2 = 0;
    bool turnoEquipo1 = true;
    while (lista!=NULL and lista->siguiente!=lista){
        int dado;
        cout<<"ingrese valor del dado (1-6)"<<endl;
        cin>>dado;
        if(turnoEquipo1) {
            cout <<" turno equipo 1 (sentido horario)"<<endl;
            for(int i=0;i<dado;i++) actual=actual->siguiente;
            cout<<" seleccionado "<<actual->nombre<<endl;
            equipo1[e1++]=actual->nombre;
            actual=eliminar(lista,actual);
        } else {
            cout<<" turno equipo 2 (sentido antihorario)"<<endl;
            for(int i=0;i<dado;i++) actual=actual->anterior;
            cout<<" seleccionado "<<actual->nombre<<endl;
            equipo2[e2++]=actual->nombre;
            actual=eliminar(lista, actual);
        }
        cout<<"Lista actual"<<endl;
        mostrarLista(lista);
        turnoEquipo1=!turnoEquipo1;
    }
    if (lista!=NULL) {
        if (turnoEquipo1) {
            equipo1[e1++]=lista->nombre;
        } else {
            equipo2[e2++]=lista->nombre;
        }
        delete lista;
        lista=NULL;
    }
    cout<<"equipo 1"<<endl;
    for (int i=0; i<e1;i++) cout<<equipo1[i]<<" ";
    cout<<"equipo 2";
    for(int i=0;i<e2;i++) cout<<equipo2[i]<< " ";
    cout<<endl;
    return 0;
}











