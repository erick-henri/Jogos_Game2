
#include "MrRobot.h"
#include "Home.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"
#include "FireBall.h"
#include "Nivel11.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene* Nivel1::scene = nullptr;

// ------------------------------------------------------------------------------

void Nivel1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(0);
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
    fin.open("Nivel1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

   

    // ----------------------

    // inicia com música
    MrRobot::audio->Frequency(MUSIC1, 1.0f);
    MrRobot::audio->Play(MUSIC1);
}

// ------------------------------------------------------------------------------

void Nivel1::Update()
{
    if (window->KeyPress(VK_ESCAPE))
    {
        //Retorna ao menu caso esc seja pressionado
        MrRobot::audio->Stop(MUSIC1);
        MrRobot::NextLevel<Home>();
        MrRobot::player->Reset();
    }
    else if (MrRobot::player->Bottom() > (window->Height() - 32) || Player::coli == true)
    {
        //Caso o personagem caia na tela ou colida com alguma armadilha, perderá uma vida
        Player::life -= 1;


        // Caso ele identifique que as vidas acabaram, ira cessar o jogo e ir para a tela de game over
        if (Player::life == 0) 
        {
            MrRobot::audio->Stop(MUSIC1);
            MrRobot::NextLevel<GameOver>();
            Player::life = 9;
            MrRobot::player->Reset();
            
        }
        else {
            MrRobot::NextLevel<Nivel1>();
            MrRobot::player->Reset();
        }
    }
    else if (MrRobot::player->Level() == 1 || window->KeyPress('N'))
    {
        // Caso o player tenha chegado na plataforma de passar o level ou pressione enter, irá para o próximo nivel
        MrRobot::NextLevel<Nivel11>();
        MrRobot::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Nivel1::Draw()
{
    backg->Draw();
    scene->Draw();

    if (MrRobot::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Nivel1::Finalize()
{
    scene->Remove(MrRobot::player, MOVING);
    delete scene;

}

// ------------------------------------------------------------------------------
