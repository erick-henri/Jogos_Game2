

#include "Engine.h"
#include "MrRobot.h"
#include "Home.h"
#include "Nivel1.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
	backg = new Sprite("Resources/TitleScreen.png");
	tileset = new TileSet("Resources/Transicao.png", 800, 600, 5, 10);

}

// ------------------------------------------------------------------------------

void Home::Update()
{

	// sai com o pressionar do ESC
	if (window->KeyPress(VK_ESCAPE))
		window->Close();

	// se a tecla ENTER for pressionada
	if (window->KeyPress(VK_RETURN))
	{
		// Vai tocar um som de transição
		MrRobot::audio->Play(TRANSITION, false);

		// Vai levar o periodo de 2 segundos enquanto toca o som de transição
		time.Start();
		MrRobot::audio->Stop(MENU);
		while (!time.Elapsed(2.0f))
		{
			
		}
		MrRobot::NextLevel<Nivel1>();
	}

	

}

// ------------------------------------------------------------------------------

void Home::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{

	delete tileset;
	delete backg;
}

// ------------------------------------------------------------------------------