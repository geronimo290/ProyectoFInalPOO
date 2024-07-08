#include "Personaje.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include "Disparo.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace std;
using namespace sf;

//el personaje deberia recibir la clase del hereo
Personaje::Personaje() {
	// Cargamos las texturas
	if (!tex.loadFromFile("aqueroconflow.png")) {
		cerr << "Error al cargar la imagen" << endl;
	}
	
	// Establecemos la textura en el sprite
	spr.setTexture(tex);
	spr.setScale(.30,.30);
	spr.setPosition(1920 / 2, 1080 / 2);
	spr.setOrigin(spr.getLocalBounds().width / 2, spr.getLocalBounds().height / 2);
	
	distanciaSprint = 100.0f; // Añadido
	
}

Vector2f Personaje::verVelo(Vector2f v){
	return velo;
}

float Personaje::verVelo_x(Vector2f v){
	float velx = v.x;
	return velx;
}

float Personaje::verVelo_y(Vector2f v){
	float vely = v.y;
	return vely;
}

void Personaje::cambiarVelo(Vector2f nuevaVelo){
	velo = nuevaVelo;
}


void Personaje::actualizar() {
	// Actualizar el rectángulo de colisión según la posición del personaje
	rectColision = spr.getGlobalBounds();
	rectColision.width = nuevoAncho;
	rectColision.height = nuevoAlto;

	
	// Velocidad de movimiento
	velo = { 4.f, 4.f };
	float vely = verVelo_y(velo);
	float velx = verVelo_x(velo);
	
	//Direccion
	Vector2f direccion(0.f, 0.f); 
	
	// Límites de mapa
	auto p = spr.getPosition();  // Posición del sprite
	
	// Cambios en los límites para evitar la duplicación de código
	if (p.x < 310 || p.x + 420 > 1920) velx = -velx;
	if (p.y < 260 || p.y + 260 > 1080) vely = -vely;
	
	// Verificar si la tecla está desactivada
	if (teclaDesactivada && temporizador.getElapsedTime() >= tiempoDesactivado) {
		teclaDesactivada = false; // Volver a activar la tecla
	}
	

	
	// Movimiento
	if (!teclaDesactivada) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p.y > 260 ) {
			spr.move(0, -verVelo_y(obtenerVelocidadActual()));
			spr.setRotation(180);
			direccion = Vector2f(0.f, -1.f);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && p.y + 260 < 1080 ){
		spr.move(0, verVelo_y(obtenerVelocidadActual()));
		spr.setRotation(0);
		direccion = Vector2f(0.f, 1.f);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && p.x > 310) {
		spr.move(-verVelo_x(obtenerVelocidadActual()), 0);
		spr.setRotation(90);
		direccion = Vector2f(-1.f, 0.f);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && p.x + 420 < 1920) {
		spr.move(verVelo_y(obtenerVelocidadActual()), 0);
		spr.setRotation(270);
		direccion = Vector2f(1.f, 0.f);
	}
	
	// Movimientos diagonales
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and sf::Keyboard::isKeyPressed(sf::Keyboard::Left)and p.y > 260 and p.x > 310) {
		spr.move(0, -verVelo_y(obtenerVelocidadActual())/-2); 
		spr.setRotation(135); 
		direccion = Vector2f(-1.f, -1.f); 
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and sf::Keyboard::isKeyPressed(sf::Keyboard::Right)and p.y > 260 and p.x + 420 < 1920) {
		spr.move(0, -verVelo_y(obtenerVelocidadActual())/-2);
		spr.setRotation(225);
		direccion = Vector2f(1.f, -1.f);
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and sf::Keyboard::isKeyPressed(sf::Keyboard::Left)and p.y + 260 < 1080 and p.x > 310) {
		spr.move(0, verVelo_x(obtenerVelocidadActual())/-2); 
		spr.setRotation(45); 
		direccion = Vector2f(-1.f, 1.f);
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and sf::Keyboard::isKeyPressed(sf::Keyboard::Right)and p.y + 260 < 1080 and p.x + 420 < 1920) {
		spr.move(0, verVelo_x(obtenerVelocidadActual())/-2);
		spr.setRotation(315); 
		direccion = Vector2f(1.f, 1.f);
	}
	
	if (sprintActivo && sprintClock.getElapsedTime() >= duracionSprint) {
		sprintActivo = false;
	}
	
	if (!sprintActivo && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {
		sprintActivo = true;
		sprintClock.restart();
		Vector2f posicionActual = spr.getPosition();
		Vector2f nuevaPosicion = posicionActual + direccion * distanciaSprint;
		spr.setPosition(nuevaPosicion);
	}
	
	
	// condiciones para evitar salir en los vértices
	if ((p.x < 310 && p.y < 260) || (p.x + 420 > 1920 && p.y > 260)) {
		spr.move(velx / 2, vely / 2);
	}
	
	if ((p.x < 310 && p.y + 260 > 1080) || (p.x + 420 > 1920 && p.y + 260 > 1080)) {
		spr.move(-velx / 2, -vely / 2);
	}
	
	if (p.x < 310) {
		spr.setPosition(310, p.y);  // Ajuste a la posición izquierda
	}
	
	if (p.x + 420 > 1920) {
		spr.setPosition(1920 - 420, p.y);  // Ajuste a la posición derecha
	}
	
	if (p.y < 260) {
		spr.setPosition(p.x, 260);  // Ajuste a la posición arriba
	}
	
	if (p.y + 260 > 1080) {
		spr.setPosition(p.x, 1080 - 260);  // Ajuste a la posición abajo
	}
	
	//asignacion de tecla de disparo
	disp = Keyboard::A;
	
	
}

void Personaje::dibujar(RenderWindow &win){
	// Establecer ancho y alto del collider
	//float nuevoAncho = 80.f, nuevoAlto = 90.f;
	
	// Modificar el tamaño del rectángulo de colisión
	rectColision.width = nuevoAncho;
	rectColision.height = nuevoAlto;
	
	// Obtener la posición del sprite
	Vector2f spritePosition = spr.getPosition();
	
	// Calcular la posición del cuadrado para que esté centrado en el sprite
	float posX = spritePosition.x - nuevoAncho / 2;
	float posY = spritePosition.y - nuevoAlto / 2;
	
	// Dibujar el rectángulo de colisión (para visualización)
	RectangleShape rectColisionShape(Vector2f(rectColision.width, rectColision.height));
	rectColisionShape.setPosition(posX, posY);
	rectColisionShape.setFillColor(Color::Transparent);
	rectColisionShape.setOutlineColor(Color::Red);   // Color del contorno (puedes cambiarlo)
	rectColisionShape.setOutlineThickness(1.f);      // Grosor del contorno (puedes cambiarlo)
	win.draw(rectColisionShape);

	// Dibujar Sprite
	win.draw(spr);
}

bool Personaje::debeDisparar(){
	//tiempo entre disparos, el personaje dispara reinicio el reloj
	//pregunto si el tiempo que paso en milisegundos si es menos a X milisegundos, no disparo
	if (disp_clock.getElapsedTime().asMilliseconds()<500) return false;
	//           tiempo que paso  en miliseg
	
	//si la tecla de disparo no esta apretada no Disparo
	if (not Keyboard::isKeyPressed(disp))return false;
	
 	disp_clock.restart();
	// si no paso nada de lo anterior si disparo
	return true;
}
Disparo Personaje::GenerarDisparo(Texture &flecha_tex){
	
	float velo = 4;
	//cout<< spr.getPosition().x <<endl;
	Vector2f pos = spr.getPosition();
	float ang = spr.getRotation()*M_PI/180.0f;
	Vector2f direc(velo * -sin(ang),velo * cos(ang));
	return Disparo(flecha_tex,pos+20.f*direc, direc);
}


//posicion spr
Sprite& Personaje::getSprite(){
	return spr;
}

//posicion
Vector2f Personaje::getPosition(){
	return spr.getPosition();
}

void Personaje::cambiar_tiempoDesactivado(int ms){ 
	tiempoDesactivado = sf::milliseconds(ms);
}

void Personaje::cambiar_teclaDesactivada(bool b){teclaDesactivada = b;}


void Personaje::ajustarVelocidadShift() {
	// Si se presiona la tecla Shift, ajustar la velocidad
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		velo *= velocidadAdicionalShift;
	}
}

Vector2f Personaje::obtenerVelocidadActual() const {
	return velo;
}


void Personaje::sprint(Vector2f direccion) { // Añadido
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		Vector2f posicionActual = spr.getPosition();
		Vector2f nuevaPosicion = posicionActual + direccion * distanciaSprint;
		spr.setPosition(nuevaPosicion);
	}
	
}
