#ifndef _MRROBOT_FIREBALL_H_
#define _MRROBOT_FIREBALL_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Scene.h"
#include "Types.h"                                      // tipos específicos da engine
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

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
    void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void FireBall::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif