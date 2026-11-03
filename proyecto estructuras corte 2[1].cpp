#include <iostream>
#include <string>
using namespace std;
struct Libro{
    string titulo;
    string autor;
    string ISBN;
    bool estado; 
    Libro* siguiente;
};
struct Genero{
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
Prestamo* historial = NULL;

void Insertar_Genero(string nombre, Genero*& cab) {
    for (Genero* temporal = cab; temporal != NULL; temporal = temporal->sig) {
        if (temporal->nombre==nombre) {
            cout<<"El genero "<<nombre<<" ya existe"<<endl;
            return;
        }
    }
    Genero* nuevo=new Genero{nombre, NULL, NULL};
    if (cab==NULL)
        cab=nuevo;
    else {
        Genero* temporal = cab;
        while (temporal->sig != NULL)
            temporal = temporal->sig;
        temporal->sig = nuevo;
    }
    cout << "Genero '" << nombre << "' agregado correctamente.\n";
}

Genero* BuscarGenero(string nombre,Genero* cab) {
    Genero* temporal=cab;
    while (temporal != NULL) {
        if (temporal->nombre==nombre)
            return temporal;
        temporal = temporal->sig;
    }
    return NULL ;
}
void Insertar_Libro(string titulo, string id, string autor, bool estado, Libro*& cab) {
    Libro* temporal=cab;
    while (temporal!=NULL) {
        if (temporal->ISBN==id) {
            cout<<"El ISBN ingresado ya existe"<<endl;
            return;
        }
        if (temporal->titulo==titulo and temporal->autor==autor) {
            cout<<"El titulo y el autor ya existen"<<endl;
            return;
        }
        temporal=temporal->siguiente;
    }
    Libro* nuevo=new Libro{titulo, autor, id, estado, NULL};
    if (cab == NULL)
        cab=nuevo;
    else {
        temporal=cab;
        while(temporal->siguiente!=NULL)
            temporal=temporal->siguiente;
        temporal->siguiente=nuevo;
    }
    cout<<"Libro "<<titulo <<" agregado correctamente"<<endl;
}
void Insertar_LibroEnGenero(string generoBuscado, string titulo, string id, string autor, bool estado, Genero*& cabGenero) {
    Genero* gen=BuscarGenero(generoBuscado, cabGenero);
    if(gen==NULL) {
        cout<<"El genero no existe, no se puede insertar el libro"<<endl;
        return;
    }
    Insertar_Libro(titulo, id, autor, estado, gen->listaLibros);
}
void MostrarBiblioteca(Genero* cab) {
    Genero* auxGenero=cab;
    if(auxGenero == NULL) {
	    cout<<"No hay generos registrados"<<endl;
        return;
    }
    while (auxGenero!=NULL) {
        cout<<"Genero:"<<auxGenero->nombre<<endl;
        Libro* auxLibro=auxGenero->listaLibros;
        if (auxLibro==NULL)
            cout<<"No hay libros registrados en este genero"<<endl;
        else {
            while (auxLibro!=NULL){
                cout<<"titulo: "<<auxLibro->titulo<<endl;
                cout<<"autor: "<<auxLibro->autor<<endl;
                cout<<"ISBN: "<<auxLibro->ISBN<<endl;
                cout<<"estado: "<<(auxLibro->estado ? "Disponible" : "Prestado")<<endl;
                auxLibro = auxLibro->siguiente;
            }
        }
        auxGenero=auxGenero->sig;
    }
}
void BuscarLibroISBN(string id, Genero* cabGenero) {
    Genero* g=cabGenero;
    while (g!=NULL) {
        Libro* l=g->listaLibros;
        while (l!= NULL) {
            if (l->ISBN==id) {
                cout<<"libro encontrado en el genero "<< g->nombre<<endl;
                cout<<"titulo "<<l->titulo << endl;
                cout<<"autor "<<l->autor<<endl;
                cout<<"ISBN " << l->ISBN << endl;
                cout<<"estado " << (l->estado ? "Disponible" : "Prestado") << endl;
                return;
            }
            l = l->siguiente;
        }
        g = g->sig;
    }
    cout<<"no se encontro ningun libro con el ISBN"<<id<<endl;
}
void DevolverLibro(string id, Genero* cabGenero) {
    Genero* g=cabGenero;
    while (g!=NULL) {
        Libro* l=g->listaLibros;
        while (l!=NULL) {
            if (l->ISBN==id) {
                if (!l->estado) {
                    l->estado=true;
                    cout<<"el libro con ISBN "<<id<<" ha sido devuelto"<<endl;
                } else {
                    cout<<"el libro con ISBN"<<id<<"ya estaba disponible";
                }
                return;
            }
            l = l->siguiente;
        }
        g = g->sig;
    }
    cout<<"no se encontro ningún libro con el ISBN"<<id<<endl;
}
void EliminarLibroID(string id, Genero* cabGenero) {
    Genero* g = cabGenero;
    while (g != NULL) {
        Libro* actual = g->listaLibros;
        Libro* anterior = NULL;
        while (actual != NULL && actual->ISBN != id) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (actual != NULL) {
            if (anterior == NULL)
                g->listaLibros = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;
            delete actual;
            cout << "libro con ISBN "<<id<<" eliminado correctamente del genero "<< g->nombre<<endl;
            return;
        }
        g=g->sig;
    }
    cout<<"no se encontro ningun libro con ese ISBN.\n";
}
void MostrarLibrosAutor(string autorBuscado, Genero* cabGenero) {
    bool encontrado=false;
    for (Genero* g=cabGenero;g!=NULL;g=g->sig) {
        for (Libro* l=g->listaLibros;l!= NULL;l=l->siguiente) {
            if (l->autor==autorBuscado){
                if (!encontrado) {
                    cout<<"libros del autor "<<autorBuscado<<endl;
                    encontrado=true;
                }
                cout<<"Titulo "<<l->titulo<<" genero "<< g->nombre<<endl;
            }
        }
    }
    if (!encontrado)
        cout << "no se encontraron libros del autor "<<autorBuscado<<endl;
}
void RegistrarPrestamo(Libro* libro, string genero, Prestamo*& historial) {
    Prestamo* nuevo = new Prestamo{libro->titulo, libro->autor, libro->ISBN, genero, historial};
    historial = nuevo;
}
void PrestarLibro(string id, Genero* cabGenero, Prestamo*& historial) {
    for (Genero* g = cabGenero; g != NULL; g = g->sig) {
        for (Libro* l = g->listaLibros; l != NULL; l = l->siguiente) {
            if (l->ISBN == id) {
                if (l->estado) {
                    l->estado=false;
                    RegistrarPrestamo(l,g->nombre,historial);
                    cout << "el libro con ISBN "<<id<<" ha sido prestado"<<endl;
                } else {
                    cout << "el libro con ISBN "<<id<<" ya esta prestado"<<endl;
                }
                return;
            }
        }
    }
    cout<<"no se encontro ningun libro con el ISBN "<<id<<endl;
}
void MostrarHistorial(Prestamo* historial) {
    if (historial==NULL) {
        cout << "no hay prestamos registrados "<<endl;
        return;
    }
    cout << "historial de prestamos"<<endl;
    for (Prestamo* p=historial;p!=NULL;p=p->sig) {
        cout<< p->titulo<<" autor "<<p->autor<<" ISBN "<<p->ISBN<<" genero "<<p->genero<<endl;
    }
}
int main() {
    Genero* cabGenero = NULL;
    bool continuar=true;
    int opcion;
    while (continuar) {
        cout<<"MENU"<<endl;
        cout<<"1. insertar genero"<<endl;
        cout<<"2.insertar libro en genero"<<endl;
        cout<<"3.mostrar biblioteca"<<endl;
        cout<<"4.buscar libro por ISBN"<<endl;
        cout<<"5.prestar libro"<<endl;
        cout<<"6.devolver libro"<<endl;
        cout<<"7.eliminar libro por ISBN"<<endl;
        cout<<"8.mostrar libros por autor"<<endl;
        cout<<"9. historial"<<endl;
        cout<<"0. salir"<<endl;
        cout<<"seleccione una opcion"<<endl;
        cin>>opcion;
        cin.ignore();
        switch (opcion) {
            case 1: {
                string nombre;
                cout<<"ingrese el nombre del genero"<<endl;
                getline(cin, nombre);
                Insertar_Genero(nombre, cabGenero);
                break;
            }
            case 2: {
                string genero, titulo, autor, isbn;
                cout<<"ingrese el genero donde se agregara el libro: ";
                getline(cin, genero);
                cout<<"titulo: ";
                getline(cin, titulo);
                cout<<"autor: ";
                getline(cin, autor);
                cout<<"ISBN: ";
                getline(cin, isbn);
                Insertar_LibroEnGenero(genero, titulo, isbn, autor, true, cabGenero);
                break;
            }
            case 3:
                MostrarBiblioteca(cabGenero);
                break;
            case 4: {
			string id;
			cout<<"ingrese el ISBN a buscar: ";
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
		    cout<<"ingrese el ISBN del libro a devolver ";
			getline(cin, id);
			DevolverLibro(id, cabGenero);
			break;
		}
        case 7: {
            string id;
            cout<<"ingrese el ISBN del libro a eliminar ";
            getline(cin, id);
            EliminarLibroID(id, cabGenero);
            break;
        }
        case 8: {
		string autor;
		cout<<"ingrese el nombre del autor ";
		getline(cin, autor);
		 MostrarLibrosAutor(autor, cabGenero);
		 break;
		}
		case 9:
		MostrarHistorial(historial);
		break;
        case 0:
            cout<<"Saliendo del programa"<<endl;
            continuar = false;
            break;
            default:
            cout<<"Opcion invalida"<<endl;
        }
    }
    return 0;
}
