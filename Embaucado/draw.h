#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

using namespace std;

void drawMainBoard(int numeroRonda, string nombre1, string nombre2, string cartaEmbaucadora, int puntosJugador1[], int puntosJugador2[]); // Dibuja la interfaz principal de partida

void mostrarEmbaucadora(string embaucadora); // Muestra la carta embaucadora

void dibujarCartasJugador(int vec[], int jugador, bool visible, bool animation); // dibuja todas las cartas que le pasemos como vector (indicar el arg 'visible' a false si dibujarlas dada vuelta, o true para darlas vuelta. Indicar al arg 'animation' true si queremos mostrarla una a una, o false si solamente dibujar todas las cartas de una)

void dibujarCarta(int idCarta, int x, int y, bool visible); // dibuja la carta id que le pasemos, estableciendo el x e y de inicio del dibujo, indicarle al argumento 'visible' si quereoms que

void dibujarRectangulo(int posX, int posY, int sizeX, int sizeY, int caracter, int color); // dibuja el rectangulo de la carta

void escribirCarta(int x, int y, string numeroCarta, string palo); // escribe los valores de la carta (10, J, Trebol, etc)

int obtenerPaloChar(string palo); // Useful para obtener el char del icono del palo

void fixDraw(int x, int y); // Para arreglar un bug visual, a la hora de cambiar de tamaño la consola

#endif // DRAW_H_INCLUDED
