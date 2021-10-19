#ifndef _MRROBOT_NIVEL11_H_
#define _MRROBOT_NIVEL11_H_

// ------------------------------------------------------------------------------
// Inclusões

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


    static Scene* scene;           // cena do nível

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

#endif