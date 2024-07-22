#include <iostream>
#include <ctime>
#include <windows.h>
#include "funciones.h";
#include "draw.h";
#include "rlutil.h";
using namespace std;

void mostrarMenu() {
    system("cls");
    cout << "---------------------------------------------------------" << endl;
    cout << " ##### #   #  ####     #   #  # #####    #   ####   ### \n";
    cout << " #     ## ##  #   #   # #  #  # #       # #  #   # #   # \n";
    cout << " ####  # # #  ####   ##### #  # #      ##### #   # #   # \n";
    cout << " #     #   #  #   #  #   # #  # #      #   # #   # #   # \n";
    cout << " ##### #   #  ####   #   # #### #####  #   # ####   ### \n";
    cout << "----------------------------------------------------------" << endl;
    cout << "1 - JUGAR" << endl;
    cout << "2 - ESTADISTICAS" << endl;
    cout << "3 - CREDITOS" << endl;
    cout << "---------------------" << endl;
    cout << "0 - SALIR" << endl;
    cout << "Ingrese una opcion: ";
}

void mostrarEstadisticas(string jugadorMayorPuntaje, int mayorPuntaje) {
    system("cls");
    cout << "ESTADISTICAS" << endl;
    if (jugadorMayorPuntaje == "") {
        cout << "No hay estadisticas disponibles." << endl;
    } else {
        cout << "Jugador con mas puntos: " << jugadorMayorPuntaje << " (" << mayorPuntaje << " puntos)" << endl;
    }

    system("pause");
}

void mostrarCreditos() {
    system("cls");
    cout << "CREDITOS" << endl;
    cout << "Integrantes del equipo:" << endl;
    cout << "-----------------------" << endl << endl;
    cout << "- Carrillo, Francisco Luis - 30278" << endl;
    cout << "- Mariucci, Agustina       - 28012" << endl;
    cout << "- Stucchi, Joel            - 30618" << endl;
    cout << "- Correa Gimenez, Leandro  - 23908" << endl;
    cout << endl << "- Numero de grupo: 6" << endl << endl;

    system("pause");
}

void startGame(string &jugadorMayorPuntaje, int &mayorPuntaje) {
    string nombre1, nombre2;
    do {
        registrarNombres(nombre1, nombre2);
    } while (!confirmarNombres());

    int puntosJugador1[3] = {0};
    int puntosJugador2[3] = {0};

    for (int i = 0; i < 3; i++) {
        jugarRonda(i + 1, nombre1, nombre2, puntosJugador1, puntosJugador2);
        rlutil::anykey();
    }

    int puntosTotalesJugador1 = sumarValoresVector(puntosJugador1, 3);
    int puntosTotalesJugador2 = sumarValoresVector(puntosJugador2, 3);

    system("cls");

    int ganador = definirGanador(puntosJugador1, puntosJugador2);
    switch (ganador) {
        case 0:
            cout << "Hay empate, no hubo ganadores." << endl << endl;
            break;
        case 1:
            cout << "El ganador es " << nombre1 << "! Puntos: " << puntosTotalesJugador1 << endl << endl;
            break;
        case 2:
            cout << "El ganador es " << nombre2 << "! Puntos: " << puntosTotalesJugador2 << endl << endl;
            break;
    }

    // Guardar si es puntaje mayor al actual guardado
    if (puntosTotalesJugador1 > puntosTotalesJugador2) {
        if (puntosTotalesJugador1 > mayorPuntaje) {
            jugadorMayorPuntaje = nombre1;
            mayorPuntaje = puntosTotalesJugador1;
            cout << "Felicidades, registraste un nuevo puntaje historico." << endl << endl;
        }
    } else if (puntosTotalesJugador2 > puntosTotalesJugador1) {
        if (puntosTotalesJugador2 > mayorPuntaje) {
            jugadorMayorPuntaje = nombre2;
            mayorPuntaje = puntosTotalesJugador2;
            cout << "Felicidades, registraste un nuevo puntaje historico." << endl << endl;
        }
    }

    system("pause");

}

int definirGanador(int puntosJugador1[], int puntosJugador2[]) {
    int puntajeTotalJugador1 = sumarValoresVector(puntosJugador1, 3);
    int puntajeTotalJugador2 = sumarValoresVector(puntosJugador2, 3);

    if (puntajeTotalJugador1 == puntajeTotalJugador2) { // En caso de empate
        int maximoJugador1 = buscarMaximoValor(puntosJugador1, 3);
        int maximoJugador2 = buscarMaximoValor(puntosJugador2, 3);
        if (maximoJugador1 == maximoJugador2) { // Empate doble
            return 0;
        } else if (maximoJugador1 > maximoJugador2) {
            return 1;
        } else {
            return 2;
        }
    } else if (puntajeTotalJugador1 > puntajeTotalJugador2) {
        return 1;
    }
    return 2;
}

void jugarRonda(int numeroRonda, string nombre1, string nombre2, int puntosJugador1[], int puntosJugador2[]) {
    // Iniciar los vectores de mano del jugador en 0 (0 no es un id de carta, quiere decir que no tiene carta en esa posicion.
    int cartasJugador1[5] = {0};
    int cartasJugador2[5] = {0};

    darCartas(cartasJugador1, cartasJugador2);
    darCartas(cartasJugador2, cartasJugador1);

    string cartaEmbaucadora = obtenerEmbaucadora();

    drawMainBoard(numeroRonda, nombre1, nombre2, cartaEmbaucadora, puntosJugador1, puntosJugador2);

    //mostrarCartas(cartasJugador1);
    dibujarCartasJugador(cartasJugador1, 1, false, true);

    //mostrarCartas(cartasJugador2);
    dibujarCartasJugador(cartasJugador2, 2, false, true);

    mostrarEmbaucadora(cartaEmbaucadora);

    if (numeroRonda == 2) { // Caso ronda numero 2
        if (modificarEmbaucadora(nombre1, puntosJugador1, numeroRonda, 1)) {
            cartaEmbaucadora = obtenerEmbaucadora();
            mostrarEmbaucadora(cartaEmbaucadora);
        } else if (modificarEmbaucadora(nombre2, puntosJugador2, numeroRonda, 2)) {
            cartaEmbaucadora = obtenerEmbaucadora();
            mostrarEmbaucadora(cartaEmbaucadora);
        }
    } else if (numeroRonda == 3) { // Caso ronda 3
        if (modificarEmbaucadora(nombre2, puntosJugador2, numeroRonda, 2)) {
            cartaEmbaucadora = obtenerEmbaucadora();
            mostrarEmbaucadora(cartaEmbaucadora);
        } else if (modificarEmbaucadora(nombre1, puntosJugador1, numeroRonda, 1)) {
            cartaEmbaucadora = obtenerEmbaucadora();
            mostrarEmbaucadora(cartaEmbaucadora);
        }
    }

    rlutil::locate(1, 30);
    cout << "Presione una tecla para relevar las cartas...";
    rlutil::anykey();

    drawMainBoard(numeroRonda, nombre1, nombre2, cartaEmbaucadora, puntosJugador1, puntosJugador2);
    mostrarEmbaucadora(cartaEmbaucadora);

    dibujarCartasJugador(cartasJugador1, 1, false, false);
    dibujarCartasJugador(cartasJugador2, 2, false, false);

    dibujarCartasJugador(cartasJugador1, 1, true, true);
    dibujarCartasJugador(cartasJugador2, 2, true, true);

    int puntos1 = calcularPuntaje(cartasJugador1, cartaEmbaucadora);
    int puntos2 = calcularPuntaje(cartasJugador2, cartaEmbaucadora);

    puntosJugador1[numeroRonda - 1] = puntos1;
    puntosJugador2[numeroRonda - 1] = puntos2;

    rlutil::locate(50, 6);
    cout << "-----------------------" << endl;
    rlutil::locate(50, 7);
    cout << "Puntos obtenidos:" << endl;
    rlutil::locate(50, 8);
    cout << "-----------------------" << endl;

    rlutil::locate(50, 12);
    imprimirCalcularPuntaje(cartasJugador1, cartaEmbaucadora);
    rlutil::locate(50, 22);
    imprimirCalcularPuntaje(cartasJugador2, cartaEmbaucadora);
}

string obtenerEmbaucadora() {
    const string figuras[4] = {"Picas", "Corazones", "Trebol", "Diamante"};
    string embaucadora = figuras[rand() % 4];
    return embaucadora;
}

int calcularPuntaje(int jugador[], string embaucadora) {
    int puntaje = 0;
    for (int i = 0; i < 5; i++) {
        if (obtenerPaloCarta(jugador[i]) != embaucadora) {
            puntaje += obtenerValorCarta(jugador[i]);
        }
    }
    return puntaje;
}

void imprimirCalcularPuntaje(int jugador[], string embaucadora) {
    int puntaje = 0;
    int cartasParaSumar = 0;
    int cartasSumadas = 0;
    for (int i = 0; i < 5; i++) {
        if (obtenerPaloCarta(jugador[i]) != embaucadora) {
            cartasParaSumar++;
        }
    }
    if (cartasParaSumar == 0) {
        cout << "Mala suerte. Todas tus cartas fueron embaucadas :(";
        return;
    }
    for (int i = 0; i < 5; i++) {
        if (obtenerPaloCarta(jugador[i]) != embaucadora) {
            cartasSumadas++;
            if (cartasSumadas == cartasParaSumar) {
                cout << obtenerNumeroCarta(jugador[i]) << " de " << obtenerPaloCarta(jugador[i]) << " (" << obtenerValorCarta(jugador[i]) << ")";
            } else {
                cout << obtenerNumeroCarta(jugador[i]) << " de " << obtenerPaloCarta(jugador[i]) << " (" << obtenerValorCarta(jugador[i]) << ") + ";
            }
            puntaje += obtenerValorCarta(jugador[i]);
        }
    }
    cout << " = " << puntaje;
}

bool modificarEmbaucadora(string nombre, int puntos[], int ronda, int jugador) {
    if (jugador == 1) {
        rlutil::locate(50, 12);
    } else {
        rlutil::locate(50, 22);
    }

    if (sumarValoresVector(puntos, 3) < 20) {
        cout << "ERROR: " << nombre << " no tiene suficientes puntos para cambiar la carta Embaucadora." << endl;
        return false;
    }

    char decision;
    cout << nombre << ", ¿Deseas modificar la carta embaucadora actual? (S/N) (Cuesta 20 puntos): ";
    cin >> decision;

    if (decision == 'S' || decision == 's') {
        if (jugador == 1) {
            rlutil::locate(50, 12);
        } else {
            rlutil::locate(50, 22);
        }
        cout << nombre << " modifico la carta embaucadora, y fueron descontados 20 puntos de su total de puntos." << endl;
        puntos[ronda - 1] -= 20;
        return true;
    }
    return false;
}

void registrarNombres(string& nombre1, string& nombre2) {
    system("cls");
    cout << "¿Nombre del Jugador 1? ";
    cin >> nombre1;
    cout << "¿Nombre del Jugador 2? ";
    cin >> nombre2;
}

bool confirmarNombres() {
    system("cls");
    char confirmacion;
    cout << "¿Confirmar nombres? (S/N): ";
    cin >> confirmacion;
    return confirmacion == 'S' || confirmacion == 's';
}

int sumarValoresVector(int vec[], int tam) {
    int sumaTotal = 0;
    for (int i = 0; i < tam; i++) {
        sumaTotal += vec[i];
    }
    return sumaTotal;
}

int buscarMaximoValor(int vec[], int tam) {
    int valorMaximo = 0;
    for (int i = 0; i < tam; i++) {
        if (vec[i] > valorMaximo) {
            valorMaximo = vec[i];
        }
    }
    return valorMaximo;
}

int numeroRandom(int minimo, int maximo) { // Obtener numero random entre rangos (Incluye los extremos)
    return (rand() % (maximo - minimo + 1)) + minimo;
}

void darCartas(int barajaJugador[], int barajaOtroJugador[]) {
    int idCarta;
    for (int i = 0; i < 5; i++) {
        idCarta = generarCartaRandom(barajaJugador, barajaOtroJugador);
        barajaJugador[i] = idCarta;
    }
}

int generarCartaRandom(int barajaJugador[], int barajaOtroJugador[]) {
    int idCarta;
    do {
        idCarta = numeroRandom(1, 20);
    } while(esRepetida(idCarta, barajaJugador, barajaOtroJugador));
    return idCarta;
}

bool esRepetida(int idCarta, int barajaJugador[], int barajaOtroJugador[]) {
    if (buscarEnVector(barajaJugador, 5, idCarta)) {
        return true;
    }
    if (buscarEnVector(barajaOtroJugador, 5, idCarta)) {
        return true;
    }
    return false;
}

bool buscarEnVector(int vec[], int tam, int value) {
    for (int i = 0; i < tam; i++) {
        if (vec[i] == value) {
            return true;
        }
    }
    return false;
}

void mostrarCartas(int barajaJugador[]) {
    for (int i = 0; i < 5; i++) {
        coutInfoCarta(barajaJugador[i]); // luego quitar
    }
}

void coutInfoCarta(int idCarta) {
    cout << "- " << obtenerNumeroCarta(idCarta) << " de " << obtenerPaloCarta(idCarta) << endl; //<< " (Valor de carta: " << obtenerValorCarta(idCarta) << ")" << endl;
    //cout << idCarta << " - " << obtenerNumeroCarta(idCarta) << " de " << obtenerPaloCarta(idCarta) << " (Valor de carta: " << obtenerValorCarta(idCarta) << ")" << endl;
}

string obtenerPaloCarta(int idCarta) {
    string palo;
    if (idCarta > 0 && idCarta <= 5) {
        palo = "Picas";
    } else if (idCarta > 5 && idCarta <= 10) {
        palo = "Corazones";
    } else if (idCarta > 10 && idCarta <= 15) {
        palo = "Trebol";
    } else if (idCarta > 15 && idCarta <= 20) {
        palo = "Diamante";
    }
    return palo;
}

string obtenerNumeroCarta(int idCarta) {
    const string ID_CARTAS[5] = {"A", "10", "J", "Q", "K"};
    return ID_CARTAS[idCarta % 5];
}

int obtenerValorCarta(int idCarta) {
    const int VALORES_CARTAS[5] = {20, 10, 11, 12, 15};
    return VALORES_CARTAS[idCarta % 5];
}
