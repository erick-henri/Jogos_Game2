#include "Platform.h"
#include "Player.h"
// ---------------------------------------------------------------------------------


bool  Platform::colileft = false;

Platform::Platform(float posX, float posY, uint platType)
{
    velx = -200.0f;
    switch (platType)
    {
    case PLAT1:  platform = new Sprite("Resources/Nivel1/Plat1.png"); type = PLAT1; break;
    case INICIAL:  platform = new Sprite("Resources/Nivel1/PlatInicial.png"); type = INICIAL; break;
    case PLAT2:  platform = new Sprite("Resources/Nivel1/Plat2.png"); type = PLAT2; break;
    case PLAT3:  platform = new Sprite("Resources/Nivel1/Plat3.png"); type = PLAT3; break;
    case PLAT4:  platform = new Sprite("Resources/Nivel1/Plat4.png"); type = PLAT4; break;
    case FINISH1: platform = new Sprite("Resources/Nivel1/PlatFinal.png"); type = FINISH1; break;
    case PLAT21:  platform = new Sprite("Resources/Nivel2/Plat1.png"); type = PLAT1; break;
    case INICIAL2:  platform = new Sprite("Resources/Nivel2/PlatInicial.png"); type = INICIAL2; break;
    case PLAT22:  platform = new Sprite("Resources/Nivel2/Plat2.png"); type = PLAT22; break;
    case PLAT23:  platform = new Sprite("Resources/Nivel2/Plat3.png"); type = PLAT23; break;
    case FINISH2: platform = new Sprite("Resources/Nivel2/PlatFinal.png"); type = FINISH2; break;
    }

    //Caso seja as plataformas iniciais irá fazeruma bbox diferente das demais
    if (platType == INICIAL || platType == INICIAL2)
    {
        BBox(new Rect(-platform->Width() / 2.0f,
            5,
            platform->Width() / 2.0f,
            platform->Height() / 2.0f));
    }
    else
    {
        BBox(new Rect(-platform->Width() / 2.0f,
            -platform->Height() / 2.0f,
            platform->Width() / 2.0f,
            platform->Height() / 2.0f));
    }
   

    MoveTo(posX, posY, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
    colileft = false;
}

void Platform::OnCollision(Object* obj)
{
    Rect* objec = (Rect*)obj->BBox();
    Rect* platform = (Rect*)BBox();

    bool bot = (lasttop >= objec->Bottom() && platform->Top() <= objec->Bottom());
    bool left = (lastleft >= objec->Right() && platform->Left() <= objec->Right());
    if (left&& bot == false) {
        colileft = true;
       
    }
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    //Pega as informações das ultimas coordenadas percorridas
    last = (Rect*)BBox();
    lastleft = last->Left();
    lasttop = last->Top();
    if (colileft)
    {
        velx = 0;
    }
    else {
        velx = -200.0f;
    }
    // move plataforma apenas no eixo x
    Translate(velx * gameTime, 0);
}

// -------------------------------------------------------------------------------
