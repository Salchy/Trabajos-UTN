#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
extern int puntajes[2];
extern int lanzamientosTotales[2];
extern string jugadores[2];
extern int ronda;
extern int turno;
extern int puntosRondaActual;
extern bool state;
extern int lanzamientos;
extern int puntajeGuardadoNum[3];
extern string puntajeGuardadoString;

int puntosTiradaActual = 0;

// Prototipos de funciones:

void drawTitle(); // Dibujar el titulo y los autores

void freeze(int secounds); // Congelar el programa por 'secounds' segundos.

void tirarDados(int dados[6]); // Tirar dados.

void mostrarDados(int dados[6]); // Recibe un vector, que serían los dados.

void gotoxy(int x, int y); // Poner el puntero en las coordenadas X e Y de la consola.

void start(bool type); // Registro de nombres de jugadores.

void drawStats(); // Dibujar las estadisticas de ambos jugadores

string ingresarNombre(); // Permite el ingreso del nombre de los jugadores.

int sumarDados(int vec); // Sumar los valores del vector 'vec'.

bool jugada(); // Conjunto de funciones que hace tirar dados, mostrarlos, y analizar los posibles combos con esos dados.

void restart(); // Reinicia variables para un nuevo juego.

void drawProxRonda(); // Dibuja el inicio de una ronda.

void drawGanador(int index); // Dibuja el cartel de ganador.

void guardarPuntos(int index); // Guardar estadísticas de las partidas.

bool printPuntesAltos(); // Imprime las estadisticas de la mejor partida.

int analizarTurno(); // Analiza los puntos obtenidos por el jugador al finalizar el turno, pregunta por si llegó al puntaje requerido, o si lo sobrepasó, para establecer el ganador. (Retorna -1 si no hay ganador, o el índice del vector de jugadores que ganó)

void iniciar(); // Inicia el juego

string analizarJugada(int dados[]); // Recibe los dados, y empieza a llamar a las funciones que analizan las posibles combinaciones. devuelve un string del nombre del combo que realizó.

void sumarPuntos(int puntos); // Recibe los puntos para sumar a un jugador, depende el turno (variable global)

int buscador(int dados[], int buscar); // Busca el valor 'buscar' en el vector 'dados' y devuelve cuantas veces se repite (0 si 'buscar' no está en el vector)

bool juegoDe1(int dados[]); // Analiza si en los numeros que dieron los dados, tiene el juego de 1.

bool juegoDe5(int dados[]); // Analiza si en los numeros que dieron los dados, tiene el juego de 5.

bool trio1(int dados[]); // Analiza si en los numeros que dieron los dados, tiene el juego de trio 1.

string trioNum(int dados[]); // Analiza si en los numeros que dieron los dados, tiene 3 numeros repetidos, para sacar el juego de trio de ese número.

string trioNumPlus(int dados[]); // Analiza si en los numeros que dieron los dados, tiene 4 o más números repetidos para sacar el juego de trio de ese número++.

bool trio1Ampliado(int dados[]); // Analiza si en los numeros que dieron los dados, tiene el juego de trio 1 amplio.

bool tresPares(int dados[]); // Analiza si en los números que dieron los dados, tiene el juego de tres pares.

bool escalera(int dados[]); // Analiza si en los números que dieron los dados, tiene el juego de escalera larga.

bool seisUnos(int dados[]); // Analiza si en los números que dieron los dados, tiene el juego Sexteto.

// Funciones:

void drawTitle() {
    gotoxy(37, 8);
    cout << "DIEZ MIL" << endl;
    gotoxy(32, 12);
    cout << "Leandro Correa Gimenez" << endl;
    gotoxy(32, 13);
    cout << "Chiara Sandoval" << endl;
    gotoxy(32, 14);
    cout << "Nicolas Nuñez" << endl;
    freeze(4);
}

void freeze(int secounds) {
    Sleep(secounds * 1000);
}

void mostrarDados(int dados[6]) {
    cout << "Jugada:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Dado " << (i + 1) << ": " << dados[i] << endl;
    }
}

void tirarDados(int dados[6]) {
    for (int i = 0; i < 6; i++) {
        dados[i] = 1 + rand() % (7 - 1);
    }

    /*
    dados[0] = 1;
    dados[1] = 1;
    dados[2] = 5;
    dados[3] = 5;
    dados[4] = 3;
    dados[5] = 3;
    */
}

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

string ingresarNombre(int index) {
    string nombre;
    system("cls");
    cout << "Ingrese un nombre del jugador " << index << ": ";
    cin >> nombre;
    return nombre;
}

void start(bool dos) {
    restart();
    jugadores[0] = ingresarNombre(1);
    if (dos == true) {
        jugadores[1] = ingresarNombre(2);
    }
    iniciar();
}

void drawStats() {
    system("cls");
    string turnoActual;
    cout << "Jugadores:";
    gotoxy(0, 1);
    cout << jugadores[0] << ": " << puntajes[0] << endl;
    gotoxy(0, 2);
    cout << jugadores[1] << ": " << puntajes[1] << endl;
    gotoxy(18, 0);
    cout << "|";
    gotoxy(18, 1);
    cout << "|";
    gotoxy(18, 2);
    cout << "|";
    if (turno == 1) {
        turnoActual = jugadores[0];
    } else {
        turnoActual = jugadores[1];
    }
    gotoxy(20, 1);
    cout << "Es el turno de: " << turnoActual;
    gotoxy(48, 0);
    cout << "|";
    gotoxy(48, 1);
    cout << "|";
    gotoxy(48, 2);
    cout << "|";
    gotoxy(50, 0);
    cout << "Ronda N°: " << ronda;
    gotoxy(50, 1);
    cout << "Puntos en esta ronda: " << (puntosRondaActual + puntosTiradaActual) << endl;
    gotoxy(50, 2);
    cout << "Lanzamientos: " << lanzamientos << endl;
    cout << "--------------------------------------------------------------------------------" << endl << endl;
}

void drawProxRonda() {
    system("cls");
    gotoxy(20, 5);
    cout << "*---------------------------------------*";
    for (int i = 1; i <= 7; i++) {
        gotoxy(20, 5 + i);
        cout << "|";
    }
    gotoxy(35, 7);
    cout << "Ronda N° " << ronda;
    gotoxy(30, 8);
    cout << "Próximo turno: " << jugadores[turno - 1];
    gotoxy(30, 10);
    cout << "Puntos: " << jugadores[0] << ": " << puntajes[0];
    gotoxy(30, 11);
    cout << "Puntos: " << jugadores[1] << ": " << puntajes[1];
    for (int i = 1; i <= 7; i++) {
        gotoxy(60, 5 + i);
        cout << "|";
    }
    gotoxy(20, 13);
    cout << "*---------------------------------------*" << endl << endl << endl << endl;
    freeze(3);
}

void drawGanador(int index) {
    system("cls");
    gotoxy(20, 5);
    cout << "*---------------------------------------*";
    for (int i = 1; i <= 7; i++) {
        gotoxy(20, 5 + i);
        cout << "|";
    }
    gotoxy(25, 7);
    cout << "El jugador " << jugadores[index] << " ganó la partida";
    gotoxy(25, 9);
    cout << "Número de rondas jugadas: " << ronda;
    gotoxy(25, 10);
    cout << "Número de lanzamientos: " << lanzamientosTotales[index];
    gotoxy(35, 11);
    cout << "Puntaje: " << puntajes[index];
    for (int i = 1; i <= 7; i++) {
        gotoxy(60, 5 + i);
        cout << "|";
    }
    gotoxy(20, 13);
    cout << "*---------------------------------------*" << endl << endl << endl << endl;
    system("pause");
}

int analizarTurno() {
    if (puntajes[turno - 1] < 10000) {
        return -1;
    } else if (puntajes[turno - 1] == 10000) {
        return (turno - 1);
    } else if (puntajes[turno - 1] > 10000) {
        if (turno == 2) {
            return 0;
        }
        return 1;
    }
    return -1;
}

void guardarPuntos(int index) {
    if (puntajeGuardadoNum[0] == 0 || ronda < puntajeGuardadoNum[0]) {
        puntajeGuardadoNum[0] = ronda;
        puntajeGuardadoNum[1] = lanzamientosTotales[index];
        puntajeGuardadoNum[2] = puntajes[index];
        puntajeGuardadoString = jugadores[index];
    }
}

bool printPuntesAltos() {
    system("cls");
    gotoxy(20, 5);
    cout << "*---------------------------------------*";
    for (int i = 1; i <= 7; i++) {
        gotoxy(20, 5 + i);
        cout << "|";
    }
    for (int i = 1; i <= 7; i++) {
        gotoxy(60, 5 + i);
        cout << "|";
    }
    if (puntajeGuardadoNum[0] == 0) {
        gotoxy(28, 9);
        cout << "No hay partida registrada." << endl;
        gotoxy(20, 13);
        cout << "*---------------------------------------*" << endl << endl << endl << endl;
        system("pause");
        return false;
    }
    gotoxy(28, 7);
    cout << "Nombre: " << puntajeGuardadoString;
    gotoxy(28, 9);
    cout << "Rondas jugadas: " << puntajeGuardadoNum[0];
    gotoxy(28, 10);
    cout << "Lanzamientos realizados: " << puntajeGuardadoNum[1];
    gotoxy(28, 11);
    cout << "Puntaje: " << puntajeGuardadoNum[2];

    gotoxy(20, 13);
    cout << "*---------------------------------------*" << endl << endl << endl << endl;
    system("pause");
}

int buscador(int dados[], int buscar) {
    int repeticiones = 0;
    for (int i = 0; i < 6; i++) {
        if (dados[i] == buscar) {
            repeticiones = repeticiones + 1;
        }
    }
    return repeticiones;
}

string analizarJugada(int dados[]) {
    int cachePuntos = 0;
    puntosTiradaActual = 0;
    string combo = "";
    int puntos = 0;
    bool check;
    string check2;
    check = juegoDe1(dados);
    if (check) {
        combo = "Juego de 1";
        cachePuntos = puntosTiradaActual;
    }
    check = juegoDe5(dados);
    if (check) {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = "Juego de 5";
        }
    }
    check = trio1(dados);
    if (check) {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = "Trio 1";
        }
    }
    check2 = trioNum(dados);
    if (check2 != "sin combo") {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = check2;
        }
    }
    check2 = trioNumPlus(dados);
    if (check2 != "sin combo") {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = check2;
        }
    }
    check = trio1Ampliado(dados);
    if (check) {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = "Trio 1 ampliado";
        }
    }
    check = escalera(dados);
    if (check) {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = "Escalera larga";
        }
    }
    check = tresPares(dados);
    if (check) {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = "Tres Pares";
        }
    }
    check = seisUnos(dados);
    if (check) {
        if (puntosTiradaActual >= cachePuntos) {
            cachePuntos = puntosTiradaActual;
            combo = "Sexteto";
        }
    }
    puntosTiradaActual = cachePuntos;
    return combo;
}

void sumarPuntos(int puntos) {
    puntajes[turno - 1] = puntajes[turno - 1] + puntos;
}

// Funciones que buscan las combinaciones.

bool juegoDe1(int dados[]) {
    int repeticiones = buscador(dados, 1);
    if (repeticiones > 0) {
        puntosTiradaActual = repeticiones * 100;
        return true;
    }
    return false;
}

bool juegoDe5(int dados[]) {
    int repeticiones = buscador(dados, 5);
    if (repeticiones > 0) {
        puntosTiradaActual = repeticiones * 50;
        return true;
    }
    return false;
}

bool trio1(int dados[]) {
    int repeticiones = buscador(dados, 1);
    if (repeticiones == 3) {
        puntosTiradaActual = 1000;
        return true;
    }
    return false;
}

string trioNum(int dados[]) {
    int cache = 0;
    string combo = "sin combo";
    for (int i = 0; i < 6; i++) {
        int repeticiones = buscador(dados, dados[i]);
        if (repeticiones == 3 && dados[i] * 100 >= cache) {
            cache = dados[i] * 100;
            puntosTiradaActual = cache;
        }
    }
    switch (cache / 100) { // no me dejaba concatenar un int con el string: "Trio de " << (cache / 100) y por eso tuve que rebuscarmela con esto.
        case 1:
            combo = "Trio de 1";
            break;
        case 2:
            combo = "Trio de 2";
            break;
        case 3:
            combo = "Trio de 3";
            break;
        case 4:
            combo = "Trio de 4";
            break;
        case 5:
            combo = "Trio de 5";
            break;
        case 6:
            combo = "Trio de 6";
            break;
    }
    return combo;
}

string trioNumPlus(int dados[]) {
    int cache = 0;
    string combo = "sin combo";
    for (int i = 0; i < 6; i++) {
        if (dados[i] > 1) {
            int repeticiones = buscador(dados, dados[i]);
            if (repeticiones >= 4 && dados[i] * 200 >= cache) {
                cache = dados[i] * 200;
                puntosTiradaActual = cache;
            }
        }
    }
    switch (cache / 200) { // no me dejaba concatenar un int con el string: "Trio de " << (cache / 200) << "++" y por eso tuve que rebuscarmela con esto.
        case 2:
            combo = "Trio de 2++";
            break;
        case 3:
            combo = "Trio de 3++";
            break;
        case 4:
            combo = "Trio de 4++";
            break;
        case 5:
            combo = "Trio de 5++";
            break;
        case 6:
            combo = "Trio de 6++";
            break;
    }
    return combo;
}

bool trio1Ampliado(int dados[]) {
    for (int i = 0; i < 6; i++) {
        int repeticiones = buscador(dados, 1);
        if (repeticiones >= 4) {
            puntosTiradaActual = 2000;
            return true;
        }
    }
    return false;
}

bool tresPares(int dados[]) {
    int pares = 0;
    for (int i = 0; i < 6; i++) {
        if (buscador(dados, dados[i]) == 2) {
            pares = pares + 1;
        }
    }
    if ((pares / 2) == 3) {
        puntosTiradaActual = 1000;
        return true;
    }
    return false;
}

bool escalera(int dados[]) {
    int ordenado[6] = {0};
    int i, j, posmin, aux;
    bool result = false;
	for (i = 0; i < 5; i++) {
		posmin = i;
		for (j = i + 1; j < 6; j++) {
			if (ordenado[j] < ordenado[posmin]) {
				posmin = j;
			}
		}
		aux = ordenado[i];
		ordenado[i] = ordenado[posmin];
		ordenado[posmin] = aux;
	}
	for (i = 0; i < 6; i++) {
        if (i != 6 && ordenado[i] < ordenado[i + 1]) {
            puntosTiradaActual = 1500;
            result = true;
        } else {
            result = false;
            break;
        }
	}
	return result;
}

bool seisUnos(int dados[]) {
    int repeticiones = buscador(dados, 1);
    if (repeticiones == 6) {
        puntosTiradaActual = 10000;
        return true;
    }
    return false;
}
