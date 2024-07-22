#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
using namespace std;

// Acá van los prototipos de las funciones

void mostrarMenu(); // Dibuja el menú

void mostrarEstadisticas(string jugadorMayorPuntaje, int mayorPuntaje); // Muestra las estadisticas de la mejor partida

void mostrarCreditos(); // Muestra los créditos de los desarrolladores.

bool confirmarNombres();

bool modificarEmbaucadora(string nombre, int puntosJugador[], int numeroRonda, int jugador); // Modifica la carta embaucadora (el palo) pregunta a los jugadores si quiere cambiarla

string obtenerEmbaucadora(); // nos genera un palo que será la embaucadora

void imprimirCalcularPuntaje(int mano[], string embaucadora); // Realiza calculos sobre los puntos que tiene en su mano, y muestra las cartas que van a ser sumadas antes de que finalice la ronda, y sume los puntos.

int calcularPuntaje(int mano[], string embaucadora); // calcula el puntaje que tiene en su mano y los suma al vector de puntos

void registrarNombres(string& nombre1, string& nombre2);

void startGame(string &jugadorMayorPuntaje, int &mayorPuntaje); // Inicia el juego

void jugarRonda(int numeroRonda, string nombre1, string nombre2, int puntosJugador1[], int puntosJugador2[]); // Ejecutar ronda

int definirGanador(int puntosJugador1[], int puntosJugador2[]); // define el ganador, entre los 2 vectores de puntos, arroja 1 si gana el jugador 1, 2 si gana el jugador 2, y 0 si hay empate entre los 2

int sumarValoresVector(int vec[], int tam); // suma todos los valores del vector que le pasemos.

int buscarMaximoValor(int vec[], int tam); // Busca cual es el numero más alto del vector que le pasemos.

int numeroRandom(int inicial, int maximo); // Nos retorna un número random, entre inicial y máximo (Inclusive)

int generarCartaRandom(int barajaJugador[], int barajaOtroJugador[]); // Genera una carta random (nos retorna el ID de la carta)

void darCartas(int barajaJugador[], int barajaOtroJugador[]); // asigna valores (id de carta) al vector que le pasamos. (Vector hace referencia a la mano de jugador 1 o jugador 2)

void mostrarCartas(int vec[]); // Muestra el contenido del vector que le pasemos (Vector hace referencia a mano de jugador 1 o jugador 2) el mismo hace la conversión de ID de carta a Formato Humano de cartas.

string obtenerNumeroCarta(int idCarta); // Le pasamos un ID de carta (número de 1 a 20) y nos devuelve el número de carta que hace referencia: (10, J, Q, K, A)

string obtenerPaloCarta(int idPalo); // Le pasamos un ID de palo (número de 1 a 20) y nos devuelve el palo de carta que hace referencia: (Picas, Corazones, etc)

int obtenerValorCarta(int idCarta); // Le pasamos un ID de carta (número de 1 a 20) Devuelve el valor numérico que representa la carta en el juego.

bool esRepetida(int idCarta, int barajaJugador[], int barajaOtroJugador[]); // Para saber si la carta a dar, ya está en juego en alguna de las manos de los jugadores.

bool buscarEnVector(int vec[], int size, int value); // Busca si un valor está dentro de un vector.

void coutInfoCarta(int idCarta); // Useful para imprimir en consola info del idCarta

#endif // FUNCIONES_H_INCLUDED
