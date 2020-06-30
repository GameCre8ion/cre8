#include "cre8.h"


class Game : public cre8::App {
    public:
    Game() { }
    ~Game() { }
    
    virtual void OnUserRender(cre8::r32 dt) override {
        ClearScreen(cre8::BLUE);
        PutPixel(100, 100, cre8::RED);
        DrawLine(50, 200, 450, 180, cre8::LIME);
        return;
    }
    
    virtual void OnUserUpdate(cre8::r32 dt) override {
        return;
    }
};


int main(int argc, char* argv[]) {
    
    Game game;
    
    if (game.Init(640, 480, false, 30.0f)) {
        game.Run();
    }
    game.ShutDown();
    
    return 0;    
}


