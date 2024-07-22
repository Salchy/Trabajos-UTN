#include "rlutil.h";
#include <iostream>
#include <ctime>
#include "draw.h";
#include "funciones.h";
using namespace std;

int getInitX(int jugador) {
    if (jugador == 1) {
        return 2;
    } else if (jugador == 2) {
        return 2;
    }
}

int getInitY(int jugador) {
    if (jugador == 1) {
        return 10;
    } else if (jugador == 2) {
        return 20;
    }
}

int getSizeCartaX() {
    return 7;
}

int getSizeCartaY() {
    return 5;
}

int obtenerPaloChar(string palo) {
    if (palo == "Picas") {
        return 6;
    } else if (palo == "Corazones") {
        return 3;
    } else if (palo == "Trebol") {
        return 5;
    } else if (palo == "Diamante") {
        return 4;
    }
}

void dibujarCartasJugador(int vec[], int jugador, bool visible, bool animation) {
    const int separacionX = 1;
    for (int i = 0; i < 5; i++) {
        //dibujarCarta(vec[i], getInitX(jugador), getInitY(jugador) + ((sizeCartaY + separacionY) * i), visible);
        dibujarCarta(vec[i], getInitX(jugador) + ((getSizeCartaX() + separacionX) * i), getInitY(jugador), visible);
        if (animation) {
            Sleep(300);
        }
    }
}

void dibujarCarta(int idCarta, int x, int y, bool visible) {
    int caracter = 178;
    int color = rlutil::RED;
    if (visible) {
        color = rlutil::WHITE;
        caracter = 219;
    }
    dibujarRectangulo(x, y, getSizeCartaX(), getSizeCartaY(), caracter, color);
    if (!visible) {
        return;
    }
    escribirCarta(x, y, obtenerNumeroCarta(idCarta), obtenerPaloCarta(idCarta));
}

void escribirCarta(int x, int y, string numeroCarta, string palo) {
    // Colores
    rlutil::saveDefaultColor(); // Guardo los color actuales
    rlutil::setBackgroundColor(rlutil::WHITE);
    if (palo == "Picas" || palo == "Trebol") {
        rlutil::setColor(rlutil::BLACK);
    } else {
        rlutil::setColor(rlutil::RED);
    }

    // Dibujo palo
    rlutil::locate(x + 3, y + 2);
    cout << char(obtenerPaloChar(palo));

    // Numeros
    rlutil::locate(x, y);
    cout << numeroCarta;
    if (numeroCarta == "10") {
        rlutil::locate(x + getSizeCartaX() - 2, y + getSizeCartaY() - 1);
    } else {
        rlutil::locate(x + getSizeCartaX() - 1, y + getSizeCartaY() - 1);
    }
    cout << numeroCarta;

    rlutil::resetColor();
}

void dibujarRectangulo(int posX, int posY, int sizeX, int sizeY, int caracter, int color) {
    rlutil::saveDefaultColor(); // Guardo el color actual
    rlutil::locate(posX, posY);
    rlutil::setColor(color);
    for (int i = 0; i < sizeY; i++) {
        rlutil::locate(posX, posY + i);
        for (int j = 0; j < sizeX; j++) {
            cout << char(caracter);
        }
        fixDraw(posX + sizeX, posY + i);
        rlutil::setColor(color);
    }
    rlutil::resetColor();
}

void fixDraw(int x, int y) { // Un hotfix para arreglar un problema a la hora de agrandar la consola, porque se desfiguraban las cartas
    rlutil::saveDefaultColor(); // Guardo los color actuales
    rlutil::setColor(rlutil::BLACK);
    rlutil::locate(x, y);
    cout << char(219);
    rlutil::resetColor();
}

void drawMainBoard(int numeroRonda, string nombre1, string nombre2, string cartaEmbaucadora, int puntosJugador1[], int puntosJugador2[]) {
    system("cls");
    rlutil::locate(1, 1);
    cout << "-----------------------" << endl;
    cout << "Ronda: " << numeroRonda << endl;
    cout << "-----------------------" << endl;

    cout << nombre1 << ": " << sumarValoresVector(puntosJugador1, 3) << " puntos" << endl;
    cout << nombre2 << ": " << sumarValoresVector(puntosJugador2, 3) << " puntos" << endl;

    cout << "-----------------------" << endl;
    cout << "Cartas " << nombre1 << ": " << endl;
    cout << "-----------------------" << endl;

    rlutil::locate(1, 16);

    cout << "-----------------------" << endl;
    cout << "Cartas " << nombre2 << ": " << endl;
    cout << "-----------------------" << endl;

    rlutil::locate(1, 26);

    cout << "-----------------------" << endl;
}

void mostrarEmbaucadora(string embaucadora) {
    rlutil::locate(1, 28);
    cout << "Carta embaucadora: ";
    rlutil::saveDefaultColor(); // Guardo el color actual
    rlutil::setBackgroundColor(rlutil::WHITE);
    if (embaucadora == "Picas" || embaucadora == "Trebol") {
        rlutil::setColor(rlutil::BLACK);
    } else {
        rlutil::setColor(rlutil::RED);
    }

    cout << char(obtenerPaloChar(embaucadora)) << " " << embaucadora << " " << char(obtenerPaloChar(embaucadora));
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << endl;
    rlutil::resetColor();
}
