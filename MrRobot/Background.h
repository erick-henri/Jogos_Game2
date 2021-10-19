#ifndef _MRROBOT_BACKGROUND_H_
#define _MRROBOT_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites
#include "animation.h"

// ---------------------------------------------------------------------------------
enum LEVEL { NIVEL1,NIVEL11,NIVEL2,NIVEL22 };

class Background : public Object
{
private:
    float xF;                       // posição horizontal dos sprites
    Image* img;                     // imagem de fundo frontal
    Sprite* back1;                  // Primeira imagem de fundo
    Sprite* back2;                  // Segunda imagem de fundo
    Sprite* life;                   // Sprite para exibir a quantidade de vidas
    Sprite* level;                  // Sprite para mostrar o nivel atual
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // animação do personagem
    int velx;
    float Xn;

public:
    Background(uint type);             // construtor
    ~Background();                      // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif