#ifndef _MRROBOT_FIREBALL_H_
#define _MRROBOT_FIREBALL_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Scene.h"
#include "Types.h"                                      // tipos espec�ficos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
#include "Animation.h"
// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------

class FireBall : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                    

public:
    FireBall(float posX, float posY);   //Construtor
    ~FireBall();                        //Destrutor

    void Update();                          // atualiza��o do objeto
    void Draw();                            // desenho do objeto
    void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void FireBall::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif