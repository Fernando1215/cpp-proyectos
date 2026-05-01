#include <iostream>
using namespace std;

struct Libro {
    string titulo;
    string autor;
    int ISBN;
    bool estado;
    Libro *siguiente;
};
void Insertar_Libro(string titulo,int id,string autor,bool estado, Libro *&cab ){
    Libro *temporal=cab;
    while(temporal!=NULL){
        if(temporal->ISBN==id){
            cout<<"El Id(ISBN) ingresado ya existe."<<endl;
            return;
        }
        if(autor==temporal->autor && titulo==temporal->titulo){
            cout<<"El titulo y el autor del libro no se pueden repetir."<<endl;
            return;
        }
        temporal=temporal->siguiente;
    }
    Libro *nuevo=new Libro{titulo, autor,id,estado,NULL};
    if(cab==NULL){
        cab=nuevo;
    }else{
        temporal=cab;
        while(temporal->siguiente!=NULL){
            temporal=temporal->siguiente;
        }
        temporal->siguiente=nuevo;
    }
    cout<<"Libro agregado correctamente."<<endl;
}

void MostrarLibros(Libro *cab){
    cout<<"--------- Libros ---------"<<endl;
    Libro *temporal=cab;
    while(temporal!=NULL){
        cout<<"----------------------------"<<endl;
        cout<<"Titulo: " <<temporal->titulo<<endl;
        cout<<"Autor: "<<temporal->autor<<endl;
        cout<<"Id: "<<temporal->ISBN<<endl;
        cout<<"Estado: "<<(temporal->estado ? "Disponible" : "Prestado")<<endl;
        temporal=temporal->siguiente;
    }
}
void BuscarLibroTitulo(string titulo, Libro *cab){
    Libro*temporal =cab;
    while(temporal!=NULL){
        if(temporal->titulo==titulo){
            cout<<"El libro '"<<titulo<<"' "<<(temporal->estado ? "esta disponible" : "esta prestado")<<endl;
            return;
        }
        temporal=temporal->siguiente;
    }
    cout<<"El libro "<<titulo<<" no existe."<<endl;
}
void PrestarLibro(Libro *cab,string titulo){
    Libro *temporal=cab;
    while(temporal!=NULL){
        if(temporal->estado==true && temporal->titulo==titulo){
            cout<<"El libro '"<<temporal->titulo<<"' ahora esta prestado."<<endl;
            temporal->estado=false;
            return;
        }
        temporal=temporal->siguiente;
    }
    cout<<"El libro "<<titulo<<" no estaba disponible o no existe."<<endl;
}
void DevolverLibro(Libro *cab,string titulo){
    Libro *temporal=cab;
    while(temporal!=NULL){
        if(temporal->estado==false && temporal->titulo==titulo){
            cout<<"Usted ha devuelto el libro '"<<temporal->titulo<<"'."<<endl;
            temporal->estado=true;
            return;
        }
        temporal=temporal->siguiente;
    }
    cout<<"El libro "<<titulo<<" no estaba prestado o no existe."<<endl;
}
void EliminarLibroID(Libro *&cab, int id_buscar){
    Libro *temporal=cab;
    Libro *temporal2=NULL;
    if(cab==NULL){
        cout<<"No existe una lista de libros."<<endl;
        return;
    }
    while(temporal!=NULL && temporal->ISBN!=id_buscar){
        temporal2=temporal;
        temporal=temporal->siguiente;
    }
    if(temporal==NULL){
        cout<<"El Id ingresado no existe."<<endl;
        return;
    }
    if(temporal2==NULL){
        cab=cab->siguiente;
    }else{
        temporal2->siguiente=temporal->siguiente;
    }
    delete temporal;
    cout<<"El libro con el ID "<<id_buscar<<" se ha eliminado exitosamente."<<endl;
}
int main(){
    Libro *cab=NULL;
    bool continuar=true;
    int opcion;
    while(continuar){
        cout<<"\n----- MENU -----"<<endl;
        cout<<"1. insertar libro"<<endl;
        cout<<"2. mostrar libros"<<endl;
        cout<<"3. buscar libro por titulo"<<endl;
        cout<<"4. prestar libro"<<endl;
        cout<<"5. devolver libro"<<endl;
        cout<<"6. eliminar libro por ID"<<endl;
        cout<<"7. salir"<<endl;
        cout<<"ingrese una opcion: ";
        cin>>opcion;
        switch(opcion){
            case 1:{
                string titulo, autor;
                int id;
                cout<<"Titulo: ";
                cin.ignore();
                getline(cin, titulo);
                cout<<"Autor: ";
                getline(cin, autor);
                cout<<"ISBN: ";
                cin>>id;
                Insertar_Libro(titulo,id,autor,true,cab);
                break;
            }
            case 2:
                MostrarLibros(cab);
                break;
            case 3:{
                string titulo;
                cout<<"Ingrese el titulo a buscar: ";
                cin.ignore();
                getline(cin, titulo);
                BuscarLibroTitulo(titulo,cab);
                break;
            }
            case 4:{
                string titulo;
                cout<<"Ingrese el titulo a prestar: ";
                cin.ignore();
                getline(cin, titulo);
                PrestarLibro(cab,titulo);
                break;
            }
            case 5:{
                string titulo;
                cout<<"Ingrese el titulo a devolver: ";
                cin.ignore();
                getline(cin, titulo);
                DevolverLibro(cab,titulo);
                break;
            }
            case 6:{
                int id;
                cout<<"Ingrese el ID del libro a eliminar: ";
                cin>>id;
                EliminarLibroID(cab,id);
                break;
            }
            case 7:
                cout<<"Saliendo del programa..."<<endl;
                continuar = false;  // aquí cambia a false y termina
                break;
            default:
                cout<<"Opcion invalida."<<endl;
        }
    }
    return 0;
}

