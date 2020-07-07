#include <stdio.h>
#include "cre8.h"


class Game : public cre8::Core {
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
                
        if(GetKey(cre8::ESCAPE).pressed) {
            Stop();
        }
        
        if(GetKey(cre8::SPACE).pressed) {
            ToggleFullScreen();
        }
        
        if(GetMouse(cre8::LBUTTON).pressed) {
            printf("Left Mouse Button pressed\n");
        }
        
        if(GetMouse(cre8::RBUTTON).pressed) {
            printf("Right Mouse Button pressed\n");    
        }
        
        if(GetMouse(cre8::MBUTTON).pressed) {
            printf("Middle Mouse Button pressed\n");    
        }
        
        if(GetMouseWheel() != 0) {
            printf("Mouse wheel delta : %d\n", GetMouseWheel());    
        }
        
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


