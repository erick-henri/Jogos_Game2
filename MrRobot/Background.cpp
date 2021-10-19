#include "Background.h"
#include "Platform.h"
// ---------------------------------------------------------------------------------


Background::Background(uint type)
{
    velx = 200; // Velocidade das telas de fundo se movendo
    xF = x;  
    Xn = x;

    // Vai verificar qual o nivel da fase para colocar o sprite correspondente
    switch (type)
    {
    case NIVEL1:  level = new Sprite("Resources/Nivel1.png"); type = NIVEL1; break;
    case NIVEL11:  level = new Sprite("Resources/Nivel11.png"); type = NIVEL11; break;
    case NIVEL2:  level = new Sprite("Resources/Nivel2.png"); type = NIVEL2; break;
    case NIVEL22:  level = new Sprite("Resources/Nivel22.png"); type = NIVEL22; break;
    }

    // carrega imagens

    img = new Image("Resources/Vida.png");
    life = new Sprite(img);
   
    img = new Image("Resources/Background.png");
    back1 = new Sprite(img);
    back2 = new Sprite(img);
    
    // Carrega animações
    tileset = new TileSet("Resources/lava.png", 800, 64, 1, 5);
    anim = new Animation(tileset, 0.120f, true);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete img;
    delete back1;
    delete back2;
    delete tileset;
    delete anim;
    delete life;
    delete level;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
    // Se houver colisão a velocidade do background vai paralisar
    if (Platform::colileft == true)
    {
        velx = 0;
    }

    // move sprites com velocidades diferentes
    xF -= velx * gameTime;
    Xn -= velx * gameTime;
    anim->NextFrame();
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // Carrega as posições dos sprites de background
    level->Draw(Xn+600, 400,Layer::FRONT);


    life->Draw(64, 64, Layer::UPPER);
    anim->Draw(window->CenterX(), window->CenterY() + 280, Layer::FRONT);

    back1->Draw(xF, window->Height() / 2.0f, Layer::MIDDLE, 1.0f, 0.0f);
    back2->Draw(xF + img->Width(), window->Height() / 2.0f, Layer::MIDDLE, 1.0f, 0.0f);

    // traz pano de fundo de volta para dentro da tela
    if (xF + img->Width() / 2.0f < 0)
        xF += img->Width();
}

// -------------------------------------------------------------------------------
