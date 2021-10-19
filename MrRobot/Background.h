#ifndef _MRROBOT_BACKGROUND_H_
#define _MRROBOT_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites
#include "animation.h"

// ---------------------------------------------------------------------------------
enum LEVEL { NIVEL1,NIVEL11,NIVEL2,NIVEL22 };

class Background : public Object
{
private:
    float xF;                       // posi��o horizontal dos sprites
    Image* img;                     // imagem de fundo frontal
    Sprite* back1;                  // Primeira imagem de fundo
    Sprite* back2;                  // Segunda imagem de fundo
    Sprite* life;                   // Sprite para exibir a quantidade de vidas
    Sprite* level;                  // Sprite para mostrar o nivel atual
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // anima��o do personagem
    int velx;
    float Xn;

public:
    Background(uint type);             // construtor
    ~Background();                      // destrutor

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif