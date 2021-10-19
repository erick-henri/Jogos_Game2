#include "MrRobot.h"
#include "Fireball.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Player.h"
// ---------------------------------------------------------------------------------

FireBall::FireBall(float posX, float posY)
{
    //Carrega anima��es
    tileset = new TileSet("Resources/FireBall.png", 128, 32, 3, 6);
    anim = new Animation(tileset, 0.120f, true);

    // Cria��o da bbox
    BBox(new Rect(-1.0f * 128 / 2.0f, -1.0f * 32 / 2.0f,
        +1.0f * 100 / 2.0f, +1.0f * 32 / 2.0f));

    MoveTo(posX, posY, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

FireBall::~FireBall()
{
    delete anim;
    delete tileset;
}

// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------

void FireBall::OnCollision(Object* obj)
{
    //Envia a informa��o que houve colis�o
    Player::coli = true;
}

// ---------------------------------------------------------------------------------

void FireBall::Update()
{
    // Atualiza frames
    anim->NextFrame();
    Translate(-350.0f * gameTime, 0);
}

// ---------------------------------------------------------------------------------