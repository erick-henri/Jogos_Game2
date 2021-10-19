
#include "MrRobot.h"
#include "Home.h"
#include "Nivel22.h"
#include "Nivel2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"
#include "FireBall.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros estáticos da classe

Scene* Nivel22::scene = nullptr;

// ------------------------------------------------------------------------------

void Nivel22::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(3);
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(MrRobot::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    FireBall* ball;
    float posX, posY;
    uint  platType;


    ifstream fin;
    fin.open("Nivel22.txt");

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


    fin;
    fin.open("Fireball.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY;
            ball = new FireBall(posX, posY);
            scene->Add(ball, MOVING);
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

}

// ------------------------------------------------------------------------------

void Nivel22::Update()
{
    if (window->KeyPress(VK_ESCAPE))
    {
        MrRobot::audio->Stop(MUSIC2);
        MrRobot::NextLevel<Home>();
        MrRobot::player->Reset();
    }
    else if (MrRobot::player->Bottom() > (window->Height() - 64) || Player::coli == true)
    {
        //Caso o personagem caia na tela ou colida com alguma armadilha, perderá uma vida
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
            MrRobot::NextLevel<Nivel22>();
            MrRobot::player->Reset();
        }

    }
    else if (MrRobot::player->Level() == 4 || window->KeyPress('N'))
    {
        // Caso o player tenha chegado na plataforma de passar o level ou pressione enter, irá para o próximo nivel
        MrRobot::audio->Stop(MUSIC2);
        MrRobot::NextLevel<GameOver>();
        MrRobot::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Nivel22::Draw()
{
    backg->Draw();
    scene->Draw();

    if (MrRobot::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Nivel22::Finalize()
{
    scene->Remove(MrRobot::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
