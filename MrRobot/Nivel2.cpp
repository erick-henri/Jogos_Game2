
#include "MrRobot.h"
#include "Home.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel22.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Nivel2::scene = nullptr;
// ------------------------------------------------------------------------------

void Nivel2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(2);
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(MrRobot::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    float posX, posY;
    uint  platType;

    ifstream fin;
    fin.open("Nivel2.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // l� linha com informa��es da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora coment�rios
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    // ----------------------

    // inicia com m�sica
    MrRobot::audio->Frequency(MUSIC2, 1.0f);
   MrRobot::audio->Play(MUSIC2);
}

// ------------------------------------------------------------------------------

void Nivel2::Update()
{
    if (window->KeyPress(VK_ESCAPE))
    {
        MrRobot::audio->Stop(MUSIC2);
        MrRobot::NextLevel<Home>();
        MrRobot::player->Reset();
    }
    else if (MrRobot::player->Bottom() < 0 || MrRobot::player->Top() > window->Height() || Player::coli == true)
    {
        //Caso o personagem caia na tela ou colida com alguma armadilha, perder� uma vida
        Player::life -= 1;


        // Caso ele identifique que as vidas acabaram, ira cessar o jogo e ir para a tela de game over
        if (Player::life == 0)
        {
            MrRobot::audio->Stop(MUSIC2);
            MrRobot::NextLevel<GameOver>();
            MrRobot::player->Reset();
            Player::life = 9;
        }
        else {
            MrRobot::NextLevel<Nivel2>();
            MrRobot::player->Reset();
        }
    }
    else if (MrRobot::player->Level() == 3 || window->KeyPress('N'))
    {
        // Caso o player tenha chegado na plataforma de passar o level ou pressione enter, ir� para o pr�ximo nivel
        MrRobot::NextLevel<Nivel22>();
        MrRobot::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Nivel2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (MrRobot::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Nivel2::Finalize()
{
    
    scene->Remove(MrRobot::player, MOVING);
    delete scene;

}

// ------------------------------------------------------------------------------
