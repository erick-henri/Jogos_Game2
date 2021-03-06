#ifndef _MRROBOT_NIVEL11_H_
#define _MRROBOT_NIVEL11_H_

// ------------------------------------------------------------------------------
// Inclus?es

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

// ------------------------------------------------------------------------------

class Nivel11 : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo animado

public:


    static Scene* scene;           // cena do n?vel

    void Init();                    // inicializa??o do n?vel
    void Update();                  // atualiza l?gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza??o do n?vel
};

// -----------------------------------------------------------------------------

#endif