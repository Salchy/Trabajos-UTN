#include <iostream>
#include <locale.h>
#include <time.h>
#include <Windows.h>
#include "funciones.h"
using namespace std;

int puntajes[2] = {0, 0}; // puntaje
int lanzamientosTotales[2] = {0, 0}; // total de lanzamientos en la partida
int puntosRondaActual = 0;
string jugadores[2] = {"", "IA"};
int turno = 2; // Turno 1 = Jugador 1, turno 2 = jugador 2.
int ronda = 0;
int dados[6] = {0}; // dados
bool state = true; // bandera para comprobar si debería seguir el juego.
int lanzamientos = 0;
int ganador;
bool sumarRonda = true; // Bandera que sirve para comprobar si debe sumar ronda.
bool continuar = true; // bandera que va a servir para ver si el jugador puede seguir tirando
int puntajeGuardadoNum[3] = {0}; // [0] = Rondas, [1] = Lanzamientos, [2] = Puntos.
string puntajeGuardadoString; // Jugador con mejor estadistica.

extern int puntosTiradaActual;

int main() {
    setlocale(LC_ALL, "spanish");
    drawTitle(); // activar luego, este muestra el menú del juego y los devs.
    int opcion, puntos;
    do {
        system("cls");
        gotoxy(33, 0);
        cout << "Menú principal" << endl;
        cout << "1) Modo 1 jugador." << endl;
        cout << "2) Modo 2 jugadores." << endl;
        cout << "3) Mostrar puntuación más alta." << endl;
        cout << "4) Cerrar." << endl << endl;
        cout << "Ingrese opción: ";

        cin >> opcion;
        switch (opcion) {
            case 1:
                start(false); // Inicia el juego como 1 jugador.
                break;
            case 2:
                start(true); // Inicia el juego como 2 jugadores.
                break;
            case 3:
                printPuntesAltos(); // Imprime la mejor partida.
                break;
            case 4:
                cout << endl << "Hasta luego." << endl << endl;
                state = false;
                break;
            default:
                cout << "Opcion incorrecta.";
                freeze(1);
                break; // ¿?
        }
	} while (opcion != 4);
    return 0;
}

void iniciar() {
    while (state) {
        if (sumarRonda) {
            ronda = ronda + 1;
            sumarRonda = false;
        } else {
            sumarRonda = true;
        }
        continuar = true;
        puntosRondaActual = 0;
        lanzamientos = 0;
        if (turno == 1) {
            turno = 2;
        } else {
            turno = 1;
        }
        drawProxRonda();
        do {
            char value;
            lanzamientos = lanzamientos + 1;
            continuar = jugada();
            if (continuar) {
                cout << "¿Volver a tirar? (S/N): ";
                cin >> value;
                if (value == 's' || value == 'S') {
                    puntosRondaActual = puntosRondaActual + puntosTiradaActual;
                } else if (value == 'n' || value == 'N') {
                    puntosRondaActual = puntosRondaActual + puntosTiradaActual;
                    sumarPuntos(puntosRondaActual);
                    lanzamientosTotales[turno - 1] = lanzamientosTotales[turno - 1] + lanzamientos;
                    continuar = false;
                    ganador = analizarTurno();
                    if (ganador > -1) {
                        state = false;
                    }
                }
            } else {
                lanzamientosTotales[turno - 1] = lanzamientosTotales[turno - 1] + lanzamientos;
                continuar = false;
                ganador = analizarTurno();
                if (ganador > -1) {
                    state = false;
                }
            }
        } while (continuar);
    }
    if (!state) {
        drawGanador(ganador);
        guardarPuntos(ganador);
    }
}

void restart() {
    state = true;
    puntajes[0] = 0;
    puntajes[1] = 0;
    lanzamientosTotales[0] = 0;
    lanzamientosTotales[1] = 0;
    puntosRondaActual = 0;
    puntosTiradaActual = 0;
    jugadores[0] = "";
    jugadores[1] = "IA";
    turno = 2;
    ronda = 0;
    state = true;
    lanzamientos = 0;
    ganador = -1;
    sumarRonda = true;
    continuar = true;
}

bool jugada() {
    string combo = "";
    tirarDados(dados);
    combo = analizarJugada(dados);
    drawStats();
    mostrarDados(dados);
    if (combo != "") {
        if (combo == "Sexteto") {
            cout << endl << "Combo en este tiro: " << combo << " | ¡Ganaste la partida!" << endl << endl;
            puntajes[turno - 1] = 10000;
            system("pause");
            return false;
        } else {
            cout << endl << "Combo en este tiro: " << combo << " | Puntos a sumar: " << puntosTiradaActual << endl;
            return true;
        }
    } else {
        cout << endl << "No sumaste puntos en este tiro." << endl << endl;
        return false;
    }
}
