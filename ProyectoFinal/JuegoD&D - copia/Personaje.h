#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Disparo.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/CircleShape.hpp>


using namespace std;
using namespace sf;

class Personaje {
private:
	//texturas
	Texture tex;
	Sprite spr;
	//asignacion de teclas
	Keyboard::Key disp;
	//contar frames para calcular disparos por seg
	Clock disp_clock, temporizador;
	//tiempo que esta desactivado las teclas ante una rectColision
	Time tiempoDesactivado;
	bool teclaDesactivada;
	//velocidad de movimiento
	Vector2f velo;
	// Establecer ancho y alto del collider
	float nuevoAncho = 60.f, nuevoAlto = 60.f;
	
	// Velocidad adicional cuando se presiona Shift
	float velocidadAdicionalShift = 2.0f; // Ejemplo: aumenta la velocidad en 2 unidades
	
	// Distancia de sprint cuando se presiona Shift
	float distanciaSprint = 100.0f; // Ejemplo: el personaje se desplazará 100 unidades al hacer sprint
	Clock sprintClock; 
	bool sprintActivo = false; 
	Time duracionSprint = seconds(0.5f);
	
	
public:
	Personaje(); //va a recibir el tipo de personaje 
	
	void actualizar();//aca van los movimientos de teclado
	void dibujar(RenderWindow &win); //dibuja y muestra en pantalla
	
	//metodos para cambiar y ver velocidad de movimiento
	Vector2f verVelo(Vector2f v);
	void cambiarVelo(Vector2f nuevaVelo);
	float verVelo_x(Vector2f v);
	float verVelo_y(Vector2f v);
	
	//Disparo
	bool debeDisparar();
	Disparo GenerarDisparo(Texture & flecha_tex);
	
	//rectangulo de colision 
	FloatRect rectColision;//hacer funcion de mostrar la colision 
	
	//posicion spr
	Sprite& getSprite();
	
	//posicion
	Vector2f getPosition();
	
	void cambiar_tiempoDesactivado(int ms);
	void cambiar_teclaDesactivada(bool b);
	
	// Función para obtener la velocidad actual del personaje
	Vector2f obtenerVelocidadActual() const;
	
	// Función para ajustar la velocidad adicional cuando se presiona Shift
	void ajustarVelocidadShift();
	
	// Función para realizar el sprint cuando se presiona Shift
	void sprint(Vector2f direccion);
	
};

#endif

