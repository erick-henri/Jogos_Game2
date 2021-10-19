#include "Player.h"
#include "MrRobot.h"
#include "Platform.h"
#include "GameOver.h"
#include "Font.h"
// ---------------------------------------------------------------------------------

bool  Player::coli = false;
uint Player::life = 9;
Player::Player()
{

    //Carrega sprites
    tileset = new TileSet("Resources/Playerset34.png", 64, 64, 8, 16);
    anim = new Animation(tileset, 0.120f, true);

    uint normal[8] = { 8,9,10,11,12,13,14,15 };
    uint pulando[8] = { 0,1,2,3,4,5,6,7 };

    anim->Add(NORMAL, pulando, 8);
    anim->Add(PULANDO, normal, 8);


    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 4.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 4.0f,
        tileset->TileHeight() / 2.0f));
    
   
    // inicializa estado do player
    level = 0;
    pulo = NORMAL;
    // posição inicial
    MoveTo(window->CenterX() + 10.0f , 10.0f, Layer::FRONT);

    // cria fontes
    gameFont = new Font("Resources/Font.png");
    gameFont->Spacing(9);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete gameFont;
    delete last;
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    coli = false;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    
        Rect* objec = (Rect*)obj->BBox();
        Rect* player = (Rect*)BBox();

        bool top = (lastbot <= objec->Top() && player->Bottom() >= objec->Top());
        if (top)
        {
            if (obj->Type() == FINISH1 || obj->Type() == FINISH2)
            {
                // chegou ao final do nível
                level++;

            }

            //Colisão com armadilhas
            if ((obj->Type() == PLAT3 || obj->Type() == PLAT4) || (obj->Type() == PLAT22 || obj->Type() == PLAT23))
            {
                coli = true;
            }

            //Colisão com platafomra simples
            if ((obj->Type() == PLAT1) || (obj->Type() == PLAT21))
            {
                MoveTo(window->CenterX(), obj->Y() - 46);
            }

            //Colisão com plataforma inicial
            if ((obj->Type() == INICIAL) || (obj->Type() == INICIAL2))
            {

                MoveTo(window->CenterX(), obj->Y() - 27);
            }
            // se personagem está na plataforma
            if (window->KeyPress(VK_SPACE))
            {
                pressSpace = true;
               
                //Irá reproduzir audio indicando pulo
                MrRobot::audio->Frequency(JUMP, 1.0f);
                MrRobot::audio->Play(JUMP,false);
            }
            
        }
        if (Platform::colileft == true)
        {
            if ((obj->Type() == PLAT3 || obj->Type() == PLAT4) || (obj->Type() == PLAT22 || obj->Type() == PLAT23))
            {
                coli = true;
                
            }
        }
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    last = (Rect*)BBox();
    
    lastbot = last->Bottom();
    if (jump)
    {

        //Caso já tenha passado 1 segundo irá dar como finalizado o pulo
        if (jumpTimer.Elapsed(1.0f))
        {
            pulo = NORMAL;
            jump = false;
            pressSpace = false;
        }

        else
        {
            anim->NextFrame();

            if (jumpTimer.Elapsed(1.5f))
            {
                // descida

                vely += 150.0f * gameTime;
                Translate(0, vely * gameTime);


            }
            else
            {
                // subida
                vely += 150.0f * gameTime;
                Translate(0, vely * gameTime);

            }
        }
    }
    else
    {
        if (pressSpace)
        {
            // inicia pulo
            vely = -120;


            pulo = PULANDO;
            // inicia temporizadores
            jumpTimer.Start();
            jump = true;
        }
    }

    if (pulo == NORMAL)
    {
        Translate(0, 120 * gameTime);
    }
    if (Bottom() > 300) {
        Translate(0, 200 * gameTime);
    }


    // atualiza animação
    anim->Select(pulo);
    anim->NextFrame();
   
    //Exibe a qunatidade de vidas
    text.str("");
    text << life;
    int length = int(text.tellp());
    gameFont->Draw(64, 64, text.str());
}

void Player::Draw()
{

    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------