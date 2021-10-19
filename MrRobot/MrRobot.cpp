
#include "Engine.h"
#include "MrRobot.h"
#include "Home.h"
#include "GameOver.h"

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game* MrRobot::level = nullptr;
Player* MrRobot::player = nullptr;
Audio* MrRobot::audio = nullptr;
bool    MrRobot::viewBBox = false;

// ------------------------------------------------------------------------------

void MrRobot::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC1, "Resources/Nivel1.wav");
    audio->Add(MUSIC2, "Resources/Nivel2.wav");
    audio->Add(TRANSITION, "Resources/Enter.wav");
    audio->Add(GAMEOVER, "Resources/GameOver.wav");
    audio->Add(JUMP, "Resources/Jump.wav");
    // bounding box não visível
    viewBBox = false;

    // cria jogador
    player = new Player();

    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void MrRobot::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // atualiza nível
    level->Update();
}

// ------------------------------------------------------------------------------

void MrRobot::Draw()
{
    // desenha nível
    level->Draw();
}

// ------------------------------------------------------------------------------

void MrRobot::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Gravity Guy");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new MrRobot());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

