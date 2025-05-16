#include "raylib.h"
#include <iostream>
#include<vector>

class Player {
public: 
	float x, y;
	int breite, hoehe;

	Player(float startX, float startY) {
		x = startX;
		y = startY;
		
		breite = 20;
		hoehe = 20;

	}
	void Move(float deltaX) {
		x += deltaX;
	}


};

class Bullet {
public:
	float x, y;
	int durchmesser;
	
	Color color;
		Bullet(float startX, float startY) {
			x = startX;
			y = startY;
			durchmesser = 2;
			color = RED;

	}
		void Move(float deltaY) {
			y += deltaY;
		}
};



int main() {
	const int screenWidth = 800;   // Variable für Fensterbreite
	const int screenHeight = 600;  // Variable für Fensterhöhe
	std::vector<Bullet> bullets;
	static int lastDirection = 0;

	InitWindow(screenWidth, screenHeight, "Raylib: Spieler Bewegung"); //RayLib Befehl
	SetTargetFPS(65); // Setzen der Bildwiederholrate
	HideCursor();
	SetWindowOpacity(0.9f);

	
	

	Player meinPlayer(screenWidth / 2, screenHeight - 50);
	float x = screenWidth / 2.0f;  // Setzen der Spieler-X-Position (halbe Fensterbreite) //screenwidth geteilt durch 2 -> Mitte des Fensters //"f" steht für float Wert (fkt. auch ohne f!)
	float y = screenHeight - 50; // Setzen der Spieler-Y-Position (Fensterhöhe – 50px)

	while (!WindowShouldClose()) {   // Hauptschleife //Solange das Fenster nicht geschlossen wird, wird die Schleife ausgeführt

		// Steuerung mit der Tastatur 
	
		if (IsKeyDown(KEY_LEFT)) lastDirection = -1;
		if (IsKeyDown(KEY_RIGHT)) lastDirection = 1;

		if (lastDirection == -1 && !IsKeyDown(KEY_LEFT)) {
			if (IsKeyDown(KEY_RIGHT)) lastDirection = 1;
			else lastDirection = 0;
		}
		else if (lastDirection == 1 && !IsKeyDown(KEY_RIGHT)) {
			if (IsKeyDown(KEY_LEFT)) lastDirection = -1;
			else lastDirection = 0;
		}

		if (lastDirection == -1 && meinPlayer.x > 0) meinPlayer.x -= 5;
		if (lastDirection == 1 && meinPlayer.x < screenWidth - meinPlayer.breite) meinPlayer.x += 5;

		if (IsKeyDown(KEY_UP) && meinPlayer.y > 0) meinPlayer.y -= 5;
		if (IsKeyDown(KEY_DOWN) && meinPlayer.y < screenHeight - meinPlayer.hoehe) meinPlayer.y += 5;
		if (IsKeyDown(KEY_SPACE)) bullets.push_back(Bullet(meinPlayer.x + meinPlayer.breite / 2, meinPlayer.y));
		

		//Steuerung mit der Maus
		/*
		Vector2 mousePos = GetMousePosition();
		meinPlayer.x = mousePos.x - meinPlayer.breite / 2;
		if (meinPlayer.x < 0) meinPlayer.x = 0;
		if (meinPlayer.x + meinPlayer.breite > screenWidth) meinPlayer.x = screenWidth - meinPlayer.breite;
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) bullets.push_back(Bullet(meinPlayer.x + meinPlayer.breite / 2, meinPlayer.y));*/

		//Bullets bewegen
		for (Bullet &b : bullets) { //wichtig Referenz!!!
			DrawCircle(b.x, b.y, b.durchmesser, b.color);
			b.Move(-5); //Geschoss bewegen
			if (b.y < 0) {
				bullets.erase(bullets.begin());
				break;
			}
			//std::cout << "Bullet position: " << b.x << ", " << b.y << std::endl; //Debug Ausgabe
		}
		
		
		

		// Zeichnen beginnen
		BeginDrawing();
		ClearBackground(RAYWHITE);  // Hintergrund löschen mit weiser Farbe
		DrawRectangle(meinPlayer.x, meinPlayer.y, meinPlayer.breite, meinPlayer.hoehe, BLUE); // Rechteck zeichnen
		for (Bullet b : bullets) {
			DrawCircle(b.x, b.y, b.durchmesser, b.color);
			if (b.y < 0) {
				bullets.erase(bullets.begin());
				break;
			}
		}
		EndDrawing();

		// Zeichnen beenden
	}
	CloseWindow();
	return 0;
	// Fenster schließen
	
}


