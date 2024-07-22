Proyecto Final Integrador de la materia Programacion I año 2024.
El desarollo fue realizado por:
- Carrillo, Francisco Luis
- Mariucci, Agustina
- Stucchi, Joel
- Correa Gimenez, Leandro

Extra: Librería gráfica para mostrar las cartas en consola:
- Correa Gimenez, Leandro
Utilizando la librería rlutil:

![image](https://github.com/user-attachments/assets/9fafea30-9f8f-42a4-86c1-08a3104c0fdf)



Durante la defensa, nos remarcaron que podemos solucionar el tema de la utilización de variables globales.
- Encontraron algunos bugs a la hora de ingresar letras en el ingreso del menú.
- Cambiamos una mecánica del juego que ya estaba definida dentro del problema (no mostrar las cartas al momento de preguntar por cambiar embaucadora), por lo que afectó a la nota final.
- No mostramos los puntos obtenidos en cada ronda al finalizar la partida, por lo que no cumple con la consigna final. afectando a la nota final.
- EXTRA: Por la librería gráfica y la animación del muestreo de cartas en consola, nos sumó los puntos antes descontados por los 2 puntos anteriores.

Nota calificada final: 10

----------------------------------------------------

Reglas del juego

Embaucado es un juego de naipes para dos jugadores que puede jugarse con algunas cartas de la baraja francesa y con un mazo de cartas especiales llamado figuras.
Las cartas de la baraja francesa a utilizar son los 10, J, Q, K y A de las cuatro figuras Corazón, Diamantes, Picas y Tréboles. En total son 20 cartas.
Del mazo de figuras solamente se cuenta con 4 cartas: Corazón, Diamante, Pica y Trébol. Estas cartas, como se puede observar, no disponen de valor sino de una figura.

Una partida de Embaucado la gana quien haya obtenido más puntos a lo largo de tres rondas. En cada ronda los jugadores reciben cinco cartas al azar que se denominan mano. Además, se da vuelta sobre la mesa una carta de las figuras. Esta carta se denomina embaucadora y es la que da nombre al juego.

El puntaje de cada jugador se determina a partir de los naipes de su mano y la carta embaucadora es la que impide que el jugador pueda sumar puntaje.

- Desarollo de la partida
Supongamos que la carta embaucadora es Corazones.

Para la ronda n° 1, los puntajes se calculan en base a los valores de las cartas obtenidas a excepción de aquellas cuyos palos coincidan con los de la carta embaucadora.
En el caso del Jugador 1, los naipes de su mano que no fueron embaucados son: J de Diamante y K de Pica.
En el caso del Jugador 2, los naipes de su mano que no fueron embaucados son: 10 de Diamante, Q de Pica, Q de Trébol y Q de Diamante.

Una vez determinados los naipes es necesario calcular los puntajes de la ronda. Los mismos se calculan a partir de la siguiente tabla:

![image](https://github.com/user-attachments/assets/1ee1bce3-7dee-411d-93da-c729d4250aa8)

El puntaje de la ronda 1 para el jugador 1 es:
J de Diamante (11) + K de Pica (15) → 26 puntos

El puntaje de la ronda 1 para el jugador 2 es:
10 de Diamante (10), Q de Pica (12), Q de Trébol (12) y Q de Diamante (12) → 46 puntos

Como se puede observar, las cartas embaucadas de cada jugador no son utilizadas para el cálculo de sus respectivos puntajes.

Esta mecánica de juego se repite tres veces y quien logre la mayor cantidad de puntos en total entre todas las rondas es la persona ganadora del juego.

Por último, existe otra mecánica a partir de la ronda 2 que permite a los jugadores sacrificar 20 puntos de los acumulados para poder cambiar la carta embaucadora. Luego de haber recibido las cartas y que se haya revelado cuál es la carta embaucadora de la ronda, cada jugador puede decidir sacrificar 20 puntos para que la carta embaucadora se vuelva a obtener. Si un jugador en una ronda utiliza este sacrificio de puntos entonces el otro jugador no puede utilizarlo. Sólo pueden hacerlo si disponen de al menos 20 puntos para restar.
En la ronda 2, es el jugador 1 quien puede acceder a sacrificar puntos primero y si no lo hace, puede hacerlo el jugador 2.
En la ronda 3, es el jugador 2 quien puede acceder a sacrificar puntos primero y si no lo hace, puede hacerlo el jugador 1.

- Fin de la partida
Luego de haber transcurrido las tres rondas, quien haya obtenido más puntos en total es quien gana la partida. En el caso de que ambos jugadores se encuentren empatados al finalizar, ganará aquel jugador que haya obtenido más puntos en una ronda.

![image](https://github.com/user-attachments/assets/90f8b958-2a4d-413c-a987-0fe2d112f213)

Dado el caso como el que se visualiza en la tabla que figura arriba, ambos jugadores llegaron al final de la partida con 30 puntos. Sin embargo, el ganador de la partida es el jugador 1 por haber tenido una ronda en la que registró el puntaje más alto.

Si ocurre el caso en que ambos jugadores también empaten con este criterio secundario de desempate entonces no habrá ganador y el juego terminará en empate.
