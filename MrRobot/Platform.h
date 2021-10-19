#ifndef _MRROBOT_PLATFORM_H_
#define _MRROBOT_PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

// ---------------------------------------------------------------------------------

enum PLATTYPES { INICIAL,PLAT1,PLAT2,PLAT3, PLAT4,FINISH1,INICIAL2,PLAT21,PLAT22,PLAT23,FINISH2 };

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite* platform = nullptr;            // sprite da plataforma

    float velx;
public:
    Platform(float posX, float posY,
        uint platType);                   // construtor    
    ~Platform();                            // destrutor
    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto

    Rect* bbox = nullptr;               //Bbox das plataformas
    Rect* last = nullptr;               //Rect para pegar as ultimas cordenadas da plataforma 
    static bool colileft;               // Variavel estatica para identificar que a plataforma colidiu com o personagem              
    float lastleft;                     // Registrar a ultima cordenada do ponto left da plataforma
    float lasttop;                      // Registrar a ultima cordenada do ponto top da plataforma
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Platform::Draw()
{
    platform->Draw(x, y, z, 1.0f);
}

// ---------------------------------------------------------------------------------

#endif