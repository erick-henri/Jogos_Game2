/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     20 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Scene.h"
#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Font.h" 
#include <sstream>
using std::stringstream;
// ------------------------------------------------------------------------------

enum Pulo { NORMAL, PULANDO };         // tipo da gravidade

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // animação do personagem
    int         level;                  // nível finalizado
    Timer jumpTimer;                    // controla tempo do pulo
    bool jump = false;                          // Verifica se o personagem está pulando
    float vely = 0;
    float pressSpace = false;
    uint pulo;
    Font* gameFont = nullptr;              // fonte do jogo
    stringstream text;                      // texto para exibição
public:
    Player();                           // construtor
    ~Player();                          // destrutor

    
    static uint life;
    static bool coli;
    void Reset();                       // volta ao estado inicial
    int Level();                        // último nível finalizado
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo

    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto

    Rect* bbox = nullptr;               // BBoxdo player
    Rect* last =  nullptr;              //Para pegar as ultimas cordenadas do player
    float lastbot;                      // Pegar a ultima cordenada do ponto bot do personagem
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline int Player::Level()
{
    return level;
}

inline float Player::Bottom()
{
    return y + tileset->Height() / 2;
}

inline float Player::Top()
{
    return y - tileset->Height() / 2;
}
// ---------------------------------------------------------------------------------

#endif