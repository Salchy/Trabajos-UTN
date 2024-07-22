#include <iostream>
#include <ctime>
#include "funciones.h";
#include "draw.h";
#include "sounds.h";
using namespace std;

int main(){
    srand(time(0)); // Seteo la semilla
    reproducirMusica();

    string jugadorMayorPuntaje = "";
    int mayorPuntaje = 0;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                startGame(jugadorMayorPuntaje, mayorPuntaje);
                break;
            case 2:
                mostrarEstadisticas(jugadorMayorPuntaje, mayorPuntaje);
                break;
            case 3:
                mostrarCreditos();
                break;
            case 0:
                cout << "¿Seguro que desea salir? (S/N): ";
                char salir;
                cin >> salir;
                if (salir == 'S' || salir == 's') {
                    opcion = 0;
                } else {
                    opcion = -1;
                }
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 0);
      return 0;
}
