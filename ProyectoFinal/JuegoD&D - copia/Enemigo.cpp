#include "Enemigo.h"
#include <iostream>
#include "Objeto.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Personaje.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib> // Para std::rand() y std::srand()
#include <ctime>   // Para std::time()
#include "Disparo.h"

using namespace std;

//la carga de textura se hace desde el Objeto
Enemigo::Enemigo() : Objeto("esqueletobasico.png"), enEspera(true), tiempoEspera(3.0f) {
	// Establecer una semilla para la generación de números aleatorios
	std::srand(static_cast<unsigned>(std::time(0)));
	
	// Generar posición aleatoria dentro del mapa
	float posX = static_cast<float>(std::rand() % 1920); // Asumiendo que el ancho del mapa es 1920
	float posY = static_cast<float>(std::rand() % 1080); // Asumiendo que la altura del mapa es 1080
	
	// Establecer la posición inicial del enemigo
	sprite.setPosition(posX, posY);
	
	// Restablecer el origen del sprite al centro
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	
	// Escalar el sprite
	sprite.setScale(.35, .35);
}

void Enemigo::actualizar(Personaje& personaje) {
	// Obtener la posición actual del enemigo
	Vector2f posicionActual = sprite.getPosition();
	
	// Obtener la posición del personaje
	Vector2f personajePos = personaje.getSprite().getPosition();
	
	// Calcular la dirección hacia el personaje
	Vector2f direccion = personajePos - posicionActual;
	
	// Normalizar la dirección (convertir a un vector unitario)
	float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
	if (magnitud != 0) {
		direccion /= magnitud;
	}
	
	// Establecer la rotación del sprite del enemigo
	float angulo = std::atan2(direccion.y, direccion.x) * (180.f / static_cast<float>(M_PI));
	sprite.setRotation(angulo - 90.f); // Rotar el sprite hacia el jugador
	
	/// Si el enemigo está en espera y no ha transcurrido el tiempo de espera, no hacer nada
	if (enEspera) {
		if (relojEspera.getElapsedTime().asSeconds() >= tiempoEspera) {
			enEspera = false;
			relojEspera.restart();
		}
		return;
	}
	
	// Multiplicar la dirección normalizada por la velocidad deseada
	Vector2f movimiento = direccion * velocidad.x; // Usa solo velocidad.x como velocidad escalar
	
	sprite.move(movimiento);
	
	// rectángulo de colisión
	rectColision = sprite.getGlobalBounds();
	rectColision.width = nuevoAncho;
	rectColision.height = nuevoAlto;
	
	// Verificar colisión con el personaje
	if (rectColision.intersects(personaje.rectColision)) {
		cout << "colision con personaje" << endl;
		
		// Desactivar la tecla
		personaje.cambiar_teclaDesactivada(true);
		
		// Configurar el temporizador (por ejemplo, 1000 ms)
		personaje.cambiar_tiempoDesactivado(1000);
		
		// Retroceder al enemigo para evitar colisiones constantes
		sprite.move(-movimiento.x, -movimiento.y);
		
		// Volver a poner en espera al enemigo después de la colisión
		enEspera = true;
		relojEspera.restart();
	}

}

void Enemigo::dibujar(RenderWindow &window) {
	// Modificar el tamaño del rectángulo de colisión
	rectColision.width = nuevoAncho;
	rectColision.height = nuevoAlto;
	
	// Obtener la posición del sprite
	Vector2f spritePosition = sprite.getPosition();
	
	// Calcular la posición del cuadrado para que esté centrado en el sprite
	float posX = spritePosition.x - nuevoAncho / 2;
	float posY = spritePosition.y - nuevoAlto / 2;
	
	// Dibujar el rectángulo de colisión (para visualización)
	RectangleShape rectColisionShape(Vector2f(rectColision.width, rectColision.height));
	rectColisionShape.setPosition(posX, posY);
	rectColisionShape.setFillColor(Color::Transparent);
	rectColisionShape.setOutlineColor(Color::Red);   // Color del contorno (puedes cambiarlo)
	rectColisionShape.setOutlineThickness(1.f);      // Grosor del contorno (puedes cambiarlo)
	window.draw(rectColisionShape);
	
	// Dibujar Sprite
	window.draw(sprite);
}

void Enemigo::establecerTiempoEspera(float tiempo) { /// Implementación del método para establecer el tiempo de espera
	tiempoEspera = tiempo;
}
