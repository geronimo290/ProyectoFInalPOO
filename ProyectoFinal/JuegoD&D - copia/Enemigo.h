#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Objeto.h"


#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Personaje.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Enemigo.h"
#include "Disparo.h"

using namespace std;
using namespace sf;

class Enemigo : public Objeto {
private:
	//la velocidad se la pido segun el tipo de personaje
	Vector2f velocidad = {2.5,2};
	float vida, escudo, danio;
	//vector2f pos;
	string tipo_ataque;
	//sonido - tiene que ir en el objeto?
	// Establecer ancho y alto del collider
	float nuevoAncho = 60.f, nuevoAlto = 60.f;
	
	/// Añadir un temporizador y una bandera para controlar el estado de espera
	Clock relojEspera;
	bool enEspera;
	float tiempoEspera; // Tiempo en segundos que el enemigo permanece quieto
	
	bool enMovimiento; // Para controlar si el enemigo está en movimiento
	float velocidadMovimiento; // Velocidad de movimiento del enemigo

public:
	//Enemigo(tipo_ataque, pos, vida, escudo, danio, velocidad){}
	Enemigo();
	//moviemnto
	void actualizar(Personaje& personaje);
	//colider
	FloatRect rectColision;
	//limite de mapa
	void Bounce(); 
	//detectar personaje para moverse 
	//ataque
	
	void dibujar(RenderWindow &window);
	
	/// Método para establecer el tiempo de espera
	void establecerTiempoEspera(float tiempo); 
	
	bool colisionConDisparo(const Disparo& disparo);
};

#endif

