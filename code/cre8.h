/* 
 ==============================================================================
 Cre8 C++ Win32 Game Development Header Lib
  
 creation date = June 27th 2020 11:03 pm 
 last revision = July 6th - GameCre8ion
 ==============================================================================
*/
// TODO(GameCre8ion): document how to use

#ifndef CRE8_H
#define CRE8_H


// ============================================================================
// Win32 API
// ============================================================================
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>


// ========================================================================
// Cre8 C MACRO 
// ========================================================================
// NOTE(GameCre8ion): For searching source code purposes!
#define INTERNAL      static
#define LOCAL_PERSIST static
#define GLOBAL        static


namespace cre8 {
    // ========================================================================
    // Cre8 types 
    // ========================================================================
    typedef signed char        i8;
    typedef short              i16;
    typedef int                i32;
    typedef long long          i64;
    typedef unsigned char      u8;
    typedef unsigned short     u16;
    typedef unsigned int       u32;
    typedef unsigned long long u64;
    
    typedef float              r32;
    typedef double             r64;
    
    // Change to set other default values
    GLOBAL const i32 DEFAULT_WIN_WIDTH  = 640;
    GLOBAL const i32 DEFAULT_WIN_HEIGHT = 480;
    // Constants
    GLOBAL const i32 NR_KEYBOARD_KEYS   = 256;
    GLOBAL const i32 NR_MOUSE_BUTTONS   = 5;
        
    // RGBA color constants
    GLOBAL const i32 WHITE       = 0xFFFFFFFF;
    GLOBAL const i32 SILVER      = 0xC0C0C0FF;
    GLOBAL const i32 GRAY        = 0x808080FF;
    GLOBAL const i32 BLACK       = 0x000000FF;
    GLOBAL const i32 RED         = 0xFF0000FF;
    GLOBAL const i32 MAROON      = 0x800000FF;
    GLOBAL const i32 YELLOW      = 0xFFFF00FF;
    GLOBAL const i32 OLIVE       = 0x808000FF;
    GLOBAL const i32 LIME        = 0x00FF00FF;
    GLOBAL const i32 GREEN       = 0x008000FF;
    GLOBAL const i32 BRIGHTGREEN = 0x00FF00FF;
    GLOBAL const i32 AQUA        = 0x00FFFFFF;
    GLOBAL const i32 TEAL        = 0x008080FF;
    GLOBAL const i32 BLUE        = 0x0000FFFF;
    GLOBAL const i32 NAVY        = 0x000080FF;
    GLOBAL const i32 FUCHSIA     = 0xFF00FFFF;
    GLOBAL const i32 PURPLE      = 0x800080FF;
    
    // TODO(GameCre8ion): Solve FullScreenScaling without enum; dont like current solution
    enum FullScreenScaling {
        NO,
        STRETCH,
        SCALE
    };   
    
    // NOTE(GameCre8ion): https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    typedef enum {
        NONE = 0x00,
        BACKSPACE = 0x08, TAB = 0x09, RETURN = 0x0D, SHIFT = 0x10, CTRL = 0x11,
        ALT = 0x12, PAUSE = 0x13, CAPSLOCK = 0x14, ESCAPE = 0x1B, SPACE = 0x20,
        PAGEUP = 0x21, PAGEDOWN = 0x22, END = 0x23, HOME = 0x24,
        LEFT = 0x25, UP = 0x26, RIGHT = 0x27, DOWN = 0x28,
        PRINTSCREEN = 0x2C, INSERT = 0x2D, DEL = 0x2E,
        K0 = 0x30, K1 = 0x31, K2 = 0x32, K3 = 0x33, K4 = 0x34, K5 = 0x35,
        K6 = 0x36, K7 = 0x37, K8 = 0x38, K9 = 0x39,
        A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47,
        H = 0x48, I = 0x49, J = 0x4A, K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E,
        O = 0x4F, P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54, U = 0x55,
        V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A,
        NUMPAD_0 = 0x60, NUMPAD_1 = 0x61, NUMPAD_2 = 0x62, NUMPAD_3 = 0x63,
        NUMPAD_4 = 0x64, NUMPAD_5 = 0x65, NUMPAD_6 = 0x66, NUMPAD_7 = 0x67,
        NUMPAD_8 = 0x68, NUMPAD_9 = 0x69,
        NUMPAD_MUL = 0x6A, NUMPAD_ADD = 0x6B, NUMPAD_SEPERATOR = 0x6C,
        NUMPAD_SUB = 0x6D, NUMPAD_DEC = 0x6E, NUMPAD_DIV = 0x6F,
        F1 = 0x70, F2 = 0x71, F3 = 0x72, F4 = 0x73, F5 = 0x74, F6 = 0x75,
        F7 = 0x76, F8 = 0x77, F9 = 0x78, F10 = 0x79, F11 = 0x7A, F12 = 0x7B,
        LSHIFT = 0xA0, RSHIFT = 0xA1, LCTRL = 0xA2, RCTRL = 0xA3, TILDE = 0xC0
    } Key;
    
    typedef enum {
        LBUTTON = 0x01, RBUTTON = 0x02, MBUTTON = 0x04
    } MouseButton;
        
    struct Window {
        i32               width;
        i32               height;
        i32               renderWidth;
        i32               renderHeight;
        i32               renderTopLeftX;
        i32               renderTopLeftY;
        i32               initWidth;
        i32               initHeight;
        r32               aspectRatio;
        bool              fullScreen;
        FullScreenScaling scaling;
        HWND              handle;
        HDC               deviceContext;            
    };
    
    struct RenderBuffer {
        BITMAPINFO bitmapinfo;
        i32        width;
        i32        height;
        i32        size;
        i32*       data;        
    };
    
    struct ButtonState {
        bool pressed = false;
        bool released = false;
        bool held= false;
    };
    
    
    // ========================================================================
    // Cre8 Core API 
    // ========================================================================
    class Core {
        
        public:
        Core() { }
        ~Core() { }
        
        public:
        bool Init(i32 width, i32 height, bool fullScreen, r32 fps = 60.0f);
        void Run();
        void Stop();
        bool ShutDown();
        
        
        // user function hooks
        virtual bool OnUserInit() { return true; }
        virtual void OnUserRender(r32 dt) = 0;
        virtual void OnUserUpdate(r32 dt) = 0;
        virtual bool OnUserShutDown() { return true; } 
        
        // Helper functions
        bool IsFullScreen();
        void SetFullScreenScaling(FullScreenScaling scaling);       
        void ToggleFullScreen();
                
        // user input functions
        ButtonState GetKey(Key key);
        ButtonState GetMouse(MouseButton button);
        i32         GetMouseWheel();
            
        
        //
        // Drawing Functions
        //
        void ClearScreen(i32 color);
        void PutPixel(u32 x, u32 y, i32 color);
        void PutPixelAlpha(u32 x, u32 y, i32 color);
        i32  GetPixel(u32 x, u32 y); // returns in ARGB format!!!
        void DrawRect(u32 x, u32 y, u32 width, u32 height, i32 color);
        void FillRect(u32 x, u32 y, u32 width, u32 height, i32 color);
        void DrawRectAlpha(u32 x, u32 y, u32 width, u32 height, i32 color);
        void FillRectAlpha(u32 x, u32 y, u32 width, u32 height, i32 color);
        void DrawLine(u32 x1, u32 y1, u32 x2, u32 y2, i32 color);
        void DrawCircle(u32 xCenter, u32 yCenter, u32 radius, i32 color);
        void DrawCircleAlpha(u32 xCenter, u32 yCenter, u32 radius, i32 color);
        void FillCircle(u32 xCenter, u32 yCenter, u32 radius, i32 color);
        void FillCircleAlpha(u32 xCenter, u32 yCenter, u32 radius, i32 color);
        
        
        private:
        Window       window;
        RenderBuffer renderBuffer;
        u64          perfCountFrequency;
        r32          targetMS;
        
        bool         oldKeyState[NR_KEYBOARD_KEYS];
        bool         newKeyState[NR_KEYBOARD_KEYS];
        ButtonState  KeyboardState[NR_KEYBOARD_KEYS];
        bool         hasKeyFocus;
        
        bool         oldMouseState[NR_MOUSE_BUTTONS];
        bool         newMouseState[NR_MOUSE_BUTTONS];
        ButtonState  MouseState[NR_MOUSE_BUTTONS];
        i32          mouseX;
        i32          mouseY;
        i32          mouseWheelDelta;
        bool         hasMouseFocus;
        
        // platform independent functions
        void ScanInputDevices();
        void HandleKeyInput(i32 key, bool state);
        void HandleMousePosition(i32 x, i32 y);
        void HandleMouseWheel(i32 delta);
        void HandleMouseButtonInput(i32 button, bool state);
        void SetKeyFocus(bool hasFocus);
        void SetMouseFocus(bool hasFocus);        
        
        // win32 platform layer
        bool                    win32_CreateWindow(i32 width, i32 height, bool fullScreen);
        void                    win32_RunMessageLoop();
        GLOBAL LRESULT CALLBACK win32_Callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        void                    win32_SetWindowedMode(i32 width, i32 height);
        void                    win32_SetFullScreen();
        void                    win32_EnableDPIAwareness();
        
        void                    win32_SetupRenderBuffer();
        void                    win32_DestroyRenderBuffer();
        void                    win32_SetupClock();
        void                    win32_HandleResize();        
        
    };
}


// ========================================================================
// CRE8 CORE IMPLEMENTATION
// ========================================================================
namespace cre8 {
        
    GLOBAL Core* corePtr   = nullptr;
    GLOBAL bool bIsRunning = true;
    
    
    // ----------------------------------------------------------------------------
    // Controlled initialization; use hook function OnUserInit 
    // ----------------------------------------------------------------------------
    bool Core::Init(i32 width, i32 height, bool fullScreen, r32 fps) {
        corePtr = this;
        targetMS = (1.0f / fps) * 1000.0f;
        // NOTE(GameCre8ion): Need to call DPI awareness mode before any win32 code
        win32_EnableDPIAwareness();
        // NOTE(GameCre8ion): Set scheduler granularity to 1 ms
        timeBeginPeriod(1);  
        win32_SetupClock();
        if (win32_CreateWindow(width, height, fullScreen)) {            
            win32_SetupRenderBuffer();
            return OnUserInit();
        } else {
            return false;
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Actual game loop
    // ----------------------------------------------------------------------------
    void Core::Run() {
        bIsRunning = true;
        r32 dt = 0.0f;
        
        LARGE_INTEGER counter;
        LARGE_INTEGER lastCounter; 
        QueryPerformanceCounter(&lastCounter);
                
        while (bIsRunning) {
            // NOTE(GameCre8ion): need to reset the mouse wheel delta every frame
            mouseWheelDelta = 0;
            
            win32_RunMessageLoop();    
            
            ScanInputDevices();
            
            // NOTE(GameCre8ion): clamp dt when in debugging mode or something happens
            // keeps the simulation controlled
            // TODO(GameCre8ion): improve clamping and timing mechanism. Handle missed frame rate
            if (dt > 0.05f) {
                dt = 0.05f;
            }
            
            // Run simulation for 1 time step
            OnUserUpdate(dt);
            OnUserRender(dt);                                
                        
            // clock current frame
            QueryPerformanceCounter(&counter);
            i64 ticksElapsed = counter.QuadPart - lastCounter.QuadPart;
            lastCounter = counter;
            dt = ticksElapsed / perfCountFrequency;
            
            // TODO(GameCre8ion): improve sleeping algorithm;
            // base timing on multiple previous frames
            i32 remainingMS = targetMS - (1000 * dt);
            if (remainingMS > 0) {
                Sleep(remainingMS);    
            }            
            
            // Software blit and stretch
            StretchDIBits(window.deviceContext, window.renderTopLeftX, window.renderTopLeftY, 
                          window.renderWidth, window.renderHeight,
                          0, 0, renderBuffer.width, renderBuffer.height, renderBuffer.data, 
                          &renderBuffer.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);    
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Code run on exit process, use hook function OnUserShutdown 
    // ----------------------------------------------------------------------------
    bool Core::ShutDown() {
        if(OnUserShutDown()) {
            // NOTE(GameCre8ion): Resets scheduler clock granularity
            timeEndPeriod(1);
            win32_DestroyRenderBuffer();
            PostQuitMessage(0); 
            return true;
        } else {
            // keep running on user request
            // TODO(GameCre8ion): implement return state
            return false;
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Getter for static win32 callback to give full screen status
    // ----------------------------------------------------------------------------
    bool Core::IsFullScreen() {
        return window.fullScreen;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Setter for scaling mode to full screen
    // ----------------------------------------------------------------------------
    void Core::SetFullScreenScaling(FullScreenScaling scaling) {
        // TODO(GameCre8ion): solve with a different solution?
        window.scaling = scaling;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Toggle full screen to windows mode or visa versa
    // ----------------------------------------------------------------------------
    void Core::ToggleFullScreen() {
        if (window.fullScreen) {
            win32_SetWindowedMode(window.initWidth, window.initHeight);
        } else {
            win32_SetFullScreen();    
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Helper function to enable user to quit the game loop
    // ----------------------------------------------------------------------------
    void Core::Stop(){
        bIsRunning = false;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Scans all hardware user input devices
    // ----------------------------------------------------------------------------
    void Core::ScanInputDevices() {
        // keyboard scan
        for(i32 i = 0; i < NR_KEYBOARD_KEYS; i++) {
            // reset current state
            KeyboardState[i].pressed = false;
            KeyboardState[i].released = false;
            // check if something has changed since last frame
            if (newKeyState[i] != oldKeyState[i]) {
                if (newKeyState[i]) {
                    // if key was already held previous frame, it is not considered pressed
                    // but held
                    KeyboardState[i].pressed = !KeyboardState[i].held;
                    KeyboardState[i].held = true;
                }
                else {
                    KeyboardState[i].released = true;
                    KeyboardState[i].held = false;
                }
            }
            // store state for next frame
            oldKeyState[i] = newKeyState[i];    
        }
        // mouse scan
        for(i32 i = 0; i < NR_MOUSE_BUTTONS; i++) {
            MouseState[i].pressed = false;
            MouseState[i].released = false;
            if (newMouseState[i] != oldMouseState[i]) {
                if (newMouseState[i]) {
                    // if button was already held previous frame, it is not considered pressed
                    // but held
                    MouseState[i].pressed = !MouseState[i].held;
                    MouseState[i].held = true;
                }
                else {
                    MouseState[i].released = true;
                    MouseState[i].held = false;
                }
            }
            // store state for next frame
            oldMouseState[i] = newMouseState[i];            
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Handle key press
    // ----------------------------------------------------------------------------
    void Core::HandleKeyInput(i32 key, bool state) {
        // TODO(GameCre8ion): static cast is ugly solution; come up with different idea? 
        Key k = static_cast<Key>(key); // map wparam integer into enum 
        newKeyState[k] = state;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Get the current key state
    // ----------------------------------------------------------------------------
    ButtonState Core::GetKey(Key key) {
        return KeyboardState[key];    
    }
    
    
    // ----------------------------------------------------------------------------
    // Handle mouse position change and convert to pixel coordinates
    // ----------------------------------------------------------------------------
    void Core::HandleMousePosition(i32 x, i32 y) {
        // NOTE(GameCre8ion): x and y are in screen coordinates
        float ratioX = (float)renderBuffer.width / (float)window.renderWidth;
        float ratioY = (float)renderBuffer.height / (float)window.renderHeight;
        // NOTE(GameCre8ion): corrects for scaling modes in full screen
        mouseX = (x - window.renderTopLeftX) * ratioX;
        mouseY = (y - window.renderTopLeftY) * ratioY;
        
        if (mouseX < 0) mouseX = 0;
        if (mouseX > renderBuffer.width) mouseX = renderBuffer.width;
        if (mouseY < 0) mouseY = 0;
        if (mouseY > renderBuffer.height) mouseY = renderBuffer.height;
    }
    
    
    // ----------------------------------------------------------------------------
    // Handle mouse wheel scroll
    // ----------------------------------------------------------------------------
    void Core::HandleMouseWheel(i32 delta) {
        // NOTE(GameCre8ion): add delta, there can be multiple scrolls per frame
        // TODO(GameCre8ion): where to reset to 0? ScanInput?
        mouseWheelDelta += delta;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Handle Mouse Button press
    // ----------------------------------------------------------------------------
    void Core::HandleMouseButtonInput(i32 button, bool state) {
        // TODO(GameCre8ion): static cast is ugly solution; come up with different idea? 
        MouseButton k = static_cast<MouseButton>(button); // map wparam integer into enum 
        newMouseState[k] = state;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Get the current Mouse state
    // ----------------------------------------------------------------------------
    ButtonState Core::GetMouse(MouseButton button) {
        return MouseState[button];    
    }
    
    
    // ----------------------------------------------------------------------------
    // Get Mouse wheel 
    // ----------------------------------------------------------------------------
    i32 Core::GetMouseWheel() {
        return mouseWheelDelta;
    }
    
    
    // ----------------------------------------------------------------------------
    // Helper to set key focus state
    // ----------------------------------------------------------------------------
    void Core::SetKeyFocus(bool hasFocus) {
        hasKeyFocus = hasFocus;
    }
    
    
    // ----------------------------------------------------------------------------
    // Helper to set key focus state
    // ----------------------------------------------------------------------------
    void Core::SetMouseFocus(bool hasFocus) {
        hasMouseFocus = hasFocus;
    }
    
}


// ========================================================================
// WIN32 PLATFORM IMPLEMENTATION
// ========================================================================
namespace cre8 { 
    // ----------------------------------------------------------------------------
    // Registers and creates application window.
    // ----------------------------------------------------------------------------
    bool Core::win32_CreateWindow(i32 width, i32 height, bool fullScreen) {        
        // Store initial window state
        window.width = width;
        window.height = height;
        window.renderWidth = width;
        window.renderHeight = height;
        window.renderTopLeftX = 0;
        window.renderTopLeftY = 0;
        window.initWidth = width;
        window.initHeight = height;
        window.fullScreen = fullScreen;
        window.aspectRatio = (r32)width / (r32)height;
        window.scaling = SCALE;
        
        // Register the class
        WNDCLASSEX wcex;
        // NOTE(GameCre8ion): Init to zero, otherwise garbage can create weird bugs
        ZeroMemory(&wcex, sizeof(wcex));
        wcex.cbSize = sizeof(wcex);
        // NOTE(GameCre8ion): DirectX / OpenGL requires own DC
        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
        wcex.lpfnWndProc = win32_Callback;
        wcex.hInstance = GetModuleHandle(nullptr);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.lpszMenuName = nullptr;
        wcex.hbrBackground = nullptr;
        wcex.lpszClassName = L"Cre8_Window_Class";
        
        if(RegisterClassEx(&wcex)) {
            DWORD exStyle = WS_EX_APPWINDOW;
            DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN;
                
            window.handle = CreateWindowEx(exStyle, wcex.lpszClassName, L"Game App", style,
                                           10, 10, window.width, window.height,
                                           NULL, NULL,
                                           GetModuleHandle(nullptr), this);
            if (window.fullScreen) {
                win32_SetFullScreen();    
            } else {
                win32_SetWindowedMode(window.width, window.height);                
            }
            // obtain device context;
            window.deviceContext = GetDC(window.handle);
            return true;
        } else {
            MessageBox(NULL, L"Could not register app window.", NULL, MB_OK | MB_ICONERROR);
            return false;    
        }        
    }
        
    
    // ----------------------------------------------------------------------------
    // Peeks at the message queue and dispatch any messages to the Handler.
    // Uses PeekMessage to prevent stall in case there is no messages in the 
    // queue. PeekMessage removes the handles message from the queue.
    // ----------------------------------------------------------------------------
    void Core::win32_RunMessageLoop() {
        MSG msg = { };
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }    
    }
    
    
    // ----------------------------------------------------------------------------
    // Handles the win32 system events
    // ----------------------------------------------------------------------------
    LRESULT CALLBACK Core::win32_Callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        // TODO(GameCre8ion): rewrite EventHandler --> implement keyboard state etc.
        // TODO(GameCre8ion): handle lost of focus / background gracefully
        switch (uMsg)
        {
            case WM_DESTROY:
            { PostQuitMessage(0); }
            return 0;
            
            case WM_CLOSE:
            { bIsRunning = false; }
            return 0;
            
            case WM_SIZE:
            { /* do nothing when this message is fired. resizing is fully controlled */ }
            return 0;
            
            case WM_DPICHANGED:
            { /*// TODO(GameCre8ion): handle switch to other screen with different dpi  */ }
            return 0;
            
            case WM_SETFOCUS:
            { corePtr->SetKeyFocus(true); }
            return 0;
            
            case WM_KILLFOCUS:
            { corePtr->SetKeyFocus(false); }
            return 0;
            
            case WM_KEYDOWN:
            { corePtr->HandleKeyInput(wParam, true); }
            return 0;
            
            case WM_KEYUP:
            { corePtr->HandleKeyInput(wParam, false); }
            return 0;
            
            case WM_MOUSELEAVE:
            { corePtr->SetMouseFocus(false); }
            return 0;
            
            case WM_MOUSEWHEEL:
            { corePtr->HandleMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam)); } 
            return 0;
            
            case WM_MOUSEMOVE:
            {
                // NOTE(GameCre8ion): Based on code in the OneLoneCoder Pixel Engine
                u16 x = lParam & 0xFFFF; 
                u16 y = (lParam >> 16) & 0xFFFF;
                i16 ix = *(i16*)&x;   
                i16 iy = *(i16*)&y;
                corePtr->SetMouseFocus(true);
                corePtr->HandleMousePosition(ix, iy);        
            } return 0;
            
            case WM_LBUTTONDOWN:
            { corePtr->HandleMouseButtonInput(LBUTTON, true); }
            return 0;
            
            case WM_LBUTTONUP:
            { corePtr->HandleMouseButtonInput(LBUTTON, false); }
            return 0;
            
            case WM_RBUTTONDOWN:
            { corePtr->HandleMouseButtonInput(RBUTTON, true); }
            return 0;
            
            case WM_RBUTTONUP:
            { corePtr->HandleMouseButtonInput(RBUTTON, false); }
            return 0;
            
            case WM_MBUTTONDOWN:
            { corePtr->HandleMouseButtonInput(MBUTTON, true); }
            return 0;
            
            case WM_MBUTTONUP:
            { corePtr->HandleMouseButtonInput(MBUTTON, false); }
            return 0;            
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    
    
    // ----------------------------------------------------------------------------
    // Sets full screen; uses HMONITOR for compatibility with multiple displays
    // ----------------------------------------------------------------------------
    void Core::win32_SetFullScreen() {
        DWORD style = (WS_VISIBLE | WS_POPUP) &~(WS_CAPTION | WS_THICKFRAME);
        HMONITOR monitor = MonitorFromWindow(nullptr, MONITOR_DEFAULTTONEAREST);
        MONITORINFO monitorinfo = { sizeof(monitorinfo) };
        if (GetMonitorInfo(monitor, &monitorinfo)) {
            SetWindowLongPtr(window.handle, GWL_STYLE, style);
            bool resize = SetWindowPos(window.handle, HWND_TOP, 
                                       monitorinfo.rcMonitor.left,
                                       monitorinfo.rcMonitor.top,
                                       monitorinfo.rcMonitor.right - monitorinfo.rcMonitor.left,
                                       monitorinfo.rcMonitor.bottom - monitorinfo.rcMonitor.top,
                                           SWP_FRAMECHANGED | SWP_SHOWWINDOW);
            if (resize) {
                window.width = monitorinfo.rcMonitor.right;
                window.height = monitorinfo.rcMonitor.bottom;
                window.fullScreen = true;
                
                win32_HandleResize();
            } else {
                // TODO(GameCre8ion): LOGGING
            }
        } else {
            // TODO(GameCre8ion): LOGGING
        }        
    }
    
    
    // ----------------------------------------------------------------------------
    // Sets windowed mode; uses HMONITOR for compatibility with multiple displays
    // ----------------------------------------------------------------------------
    void Core::win32_SetWindowedMode(i32 width, i32 height) {
        DWORD style = ((WS_OVERLAPPEDWINDOW  // use overlapped window
                        ^ WS_THICKFRAME      // no thick frame (no resizing)
                        ^ WS_MAXIMIZEBOX     // no maximizing button 
                        ^ WS_MINIMIZEBOX)    // no minimizing button
                       | WS_VISIBLE          // window is visible
                       | WS_CLIPCHILDREN);
        HMONITOR monitor = MonitorFromWindow(nullptr, MONITOR_DEFAULTTONEAREST);
        MONITORINFO monitorinfo = { sizeof(monitorinfo) };
        if (GetMonitorInfo(monitor, &monitorinfo)) {
            i32 desktopWidth = monitorinfo.rcMonitor.right - monitorinfo.rcMonitor.left;
            i32 desktopHeight = monitorinfo.rcMonitor.bottom - monitorinfo.rcMonitor.top;
            // NOTE(GameCre8ion): always center window
            i32 topLeftX = (desktopWidth - width) / 2;
            i32 topLeftY = (desktopHeight - height) / 2;
            SetWindowLongPtr(window.handle, GWL_STYLE, style);
            
            // NOTE(GameCre8ion): correct for window decorations
            RECT clientRect = { 0, 0, width, height };
            AdjustWindowRect(&clientRect, style, FALSE);
            int corrWidth = clientRect.right - clientRect.left;
            int corrHeight = clientRect.bottom - clientRect.top;
                        
            SetWindowPos(window.handle, HWND_TOP,
                         topLeftX, topLeftY , corrWidth, corrHeight,
                         SWP_FRAMECHANGED | SWP_SHOWWINDOW);
            window.width = width;
            window.height = height;
            window.fullScreen = false;
            win32_HandleResize();
        } else {
            // TODO(GameCre8ion): LOGGING
        }           
    }
    
    
    // ----------------------------------------------------------------------------
    // Enable DPI awareness mode 
    // ----------------------------------------------------------------------------
    // TODO(GameCre8ion): Leave out and do in manifest file?
    void Core::win32_EnableDPIAwareness() {
        bool dpiAware = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        // TODO(GameCre8ion): Handle failure more gracefully?
        if (!dpiAware) {
            MessageBox(0, L"Could not enable DPI scaling support", L"Error", MB_OK);
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Handle window resize (happens only to full screen and back to init size
    // ----------------------------------------------------------------------------
    void Core::win32_HandleResize() {
        switch(window.scaling) {
            case NO:
            {
                window.renderWidth = renderBuffer.width;
                window.renderHeight = renderBuffer.height;                
            }
            break;
            case SCALE:
            {
                window.renderWidth = window.aspectRatio * window.height;
                window.renderHeight = window.height;
            }
            break;
            case STRETCH:
            {
                window.renderWidth = window.width;
                window.renderHeight = window.height;
            }
            break;
            default:
            {
                // NOTE(GameCre8ion): stretch is default behaviour
                window.renderWidth = window.width;
                window.renderHeight = window.height;
            }
            break;
            
        }
        window.renderTopLeftX = (window.width - window.renderWidth) / 2;
        window.renderTopLeftY = (window.height - window.renderHeight) / 2;    
    }
    
    
    // ----------------------------------------------------------------------------
    // Allocates memory for the render buffer creates the bitmapinfo
    // ----------------------------------------------------------------------------
    void Core::win32_SetupRenderBuffer() {
        renderBuffer.width = window.width;
        renderBuffer.height = window.height;
        renderBuffer.size = sizeof(i32) * renderBuffer.width * renderBuffer.height;
        renderBuffer.data = (i32*) VirtualAlloc(0, renderBuffer.size, 
                                                MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        // Fill bitmap info
        renderBuffer.bitmapinfo = { };
        renderBuffer.bitmapinfo.bmiHeader.biSize = sizeof(renderBuffer.bitmapinfo.bmiHeader);
        renderBuffer.bitmapinfo.bmiHeader.biWidth = renderBuffer.width;
        // NOTE(GameCre8ion): biHeight negative for top left origin
        renderBuffer.bitmapinfo.bmiHeader.biHeight = -renderBuffer.height;
        renderBuffer.bitmapinfo.bmiHeader.biPlanes = 1;
        renderBuffer.bitmapinfo.bmiHeader.biBitCount = 32;
        renderBuffer.bitmapinfo.bmiHeader.biCompression = BI_RGB;
    }
    
    
    // ----------------------------------------------------------------------------
    // Cleans up render buffer memory
    // ----------------------------------------------------------------------------
    void Core::win32_DestroyRenderBuffer() {
        if (renderBuffer.data) {
            VirtualFree(renderBuffer.data, 0, MEM_RELEASE);
        }        
    }
    
    
    // ----------------------------------------------------------------------------
    // Setup high resolution clock
    // ----------------------------------------------------------------------------
    void Core::win32_SetupClock() {
        LARGE_INTEGER PerfCountFrequencyResult;
        QueryPerformanceFrequency(&PerfCountFrequencyResult);
        perfCountFrequency = PerfCountFrequencyResult.QuadPart;        
    }    
    
}


// ========================================================================
// SOFTWARE RENDERER IMPLEMENTATION
// ========================================================================
namespace cre8 {
    // ----------------------------------------------------------------------------
    // color in RGBA format
    // ----------------------------------------------------------------------------
    void Core::PutPixel(u32 x, u32 y, i32 color) {
        
        i32 red = 0xFF000000 & color; 
        i32 green = 0x00FF0000 & color;
        i32 blue = 0x0000FF00 & color;
        i32 alpha = GetPixel(x, y) & 0xFF000000;
        
        i32 output = (red >> 8) | (green >> 8 ) | (blue >> 8) | alpha;
        
        if ((x > 0) & (x < renderBuffer.width) & (y > 0) & (y < renderBuffer.height)) {
            *(renderBuffer.data + y * renderBuffer.width + x) = output;    
        }    
    }
    
    
    // ----------------------------------------------------------------------------
    // color in RGBA format
    // ----------------------------------------------------------------------------
    void Core::PutPixelAlpha(u32 x, u32 y, i32 color) {
        
        u8 inputR = (u8)((0xFF000000 & color) >> 24); 
        u8 inputG = (u8)((0x00FF0000 & color) >> 16);
        u8 inputB = (u8)((0x0000FF00 & color) >> 8);
        u8 inputA = (u8)(0x000000FF & color);
        
        // NOTE(GameCre8ion): target pixel in buffer will be of format ARGB
        u32 targetColor = GetPixel(x, y);
        u8 targetR = (u8)((0x00FF0000 & targetColor) >> 16); 
        u8 targetG = (u8)((0x0000FF00 & targetColor) >> 8);
        u8 targetB = (u8)(0x000000FF & targetColor);
        // NOTE(GameCre8ion): alpha not required but protect byte for other (future) purposes
        u8 targetA = (u8)((0xFF000000 & targetColor) >> 24);
        
        // Alpha blend
        r32 a = (r32)(inputA / 255.0f);
        r32 c = 1.0f - a;
        
        u8 outputR = a * (r32)inputR + c * (r32)targetR;
        u8 outputG = a * (r32)inputG + c * (r32)targetG;
        u8 outputB = a * (r32)inputB + c * (r32)targetB;
        u8 outputA = targetA; // no alpha in DIB buffer; do not overwrite, but keep value 
        
        i32 output =  ((u32)outputA << 24) | ((u32)outputR << 16) | ((u32)outputG << 8 ) | ((u32)outputB);
        
        if ((x > 0) & (x < renderBuffer.width) & (y > 0) & (y < renderBuffer.height)) {
            *(renderBuffer.data + y * renderBuffer.width + x) = output;    
        }   
    }
    
    
    // ----------------------------------------------------------------------------
    // returns color in ARGB format
    // ----------------------------------------------------------------------------
    i32 Core::GetPixel(u32 x, u32 y) {
        i32 color = 0;
        if ((x > 0) & (x < renderBuffer.width) & (y > 0) & (y < renderBuffer.height)) {
            color = *(renderBuffer.data + y * renderBuffer.width + x);
            return color;
        }
        return 0;
    }
    
    
    // ----------------------------------------------------------------------------
    // color in RGBA format
    // ----------------------------------------------------------------------------
    void Core::ClearScreen(i32 color) {
        
        for(int y = 0; y < renderBuffer.height; y++) {
            for(int x = 0; x < renderBuffer.width; x++) {
                PutPixel(x, y, color);    
            }
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Draws a rectangle in RGBA color format
    // ----------------------------------------------------------------------------
    void Core::DrawRect(u32 x, u32 y, u32 width, u32 height, i32 color) {
        // horizontal lines
        for(u32 i = x; i < (x + width + 1); i++) {
            PutPixel(i, y, color);
            PutPixel(i, y + height, color);
        }
        // vertical lines
        for(u32 j = y; j < (y + height + 1); j++) {
            PutPixel(x, j, color);
            PutPixel(x + width, j, color);
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Draws a rectangle in RGBA color format with alpha blending
    // ----------------------------------------------------------------------------
    void Core::DrawRectAlpha(u32 x, u32 y, u32 width, u32 height, i32 color) {
        // horizontal lines
        for(u32 i = x; i < (x + width + 1); i++) {
            PutPixelAlpha(i, y, color);
            PutPixelAlpha(i, y + height, color);
        }
        // vertical lines
        for(u32 j = y; j < (y + height + 1); j++) {
            PutPixelAlpha(x, j, color);
            PutPixelAlpha(x + width, j, color);
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Draws a filled retangle in color RGBA format
    // ----------------------------------------------------------------------------
    void Core::FillRect(u32 x, u32 y, u32 width, u32 height, i32 color) {
        for(u32 j = y; j < (y + height + 1); j++) {
            for(u32 i = x; i < (x + width + 1); i++) {
                PutPixel(i, j, color);
            }
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Draws a filled rectangle color RGBA format with alpha blending
    // ----------------------------------------------------------------------------
    void Core::FillRectAlpha(u32 x, u32 y, u32 width, u32 height, i32 color) {
        for(u32 j = y; j < (y + height + 1); j++) {
            for(u32 i = x; i < (x + width + 1); i++) {
                PutPixelAlpha(i, j, color);
            }
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Based on Run Length Slice algorithm as presented by Michael Abrash
    // http://www.phatcode.net/res/224/files/html/ch36/36-01.html#Heading1
    // ----------------------------------------------------------------------------
    void Core::DrawLine(u32 x1, u32 y1, u32 x2, u32 y2, i32 color) {
        
        // Always draw top to bottom to reduce number of cases
        // Lines between the same endpoints will draw same pixels
        if (y1 > y2) {
            i32 temp = y1;
            y1 = y2;
            y2 = temp;
            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        
        // original algorithm uses pointer to pointer in screen buffer
        i32 workX = x1;
        i32 workY = y1;
        
        i32 xDelta = x2 - x1;
        i32 xAdvance = 1;
        if (xDelta < 0) {
            xAdvance = -1;
            xDelta = -xDelta;
        }
        i32 yDelta = y2 - y1;
        
        // vertical line
        if (xDelta == 0) {
            for (i32 j = 0; j <= yDelta; j++) {
                PutPixel(workX, workY, color);
                workY++;    
            }
            return; // vertical line drawn
        }
        // horizontal line
        if (yDelta == 0) {        
            for (i32 i = 0; i <= xDelta; i++) {
                PutPixel(workX, workY, color);
                workX += xAdvance;
            }
            return; // horizontal line drawn
        }
        // diagonal line
        if (xDelta == yDelta) {
            for (i32 j = 0; j <= yDelta; j++) {
                PutPixel(workX, workY, color);
                workX += xAdvance;
                workY++;
            }
            return; // diagonal line drawn        
        }
        
        i32 wholeStep = 0;
        i32 adjUp = 0;
        i32 adjDown = 0;
        i32 errorTerm = 0;
        i32 initialPixelCount = 0;
        i32 finalPixelCount = 0;
        i32 runLength = 0;
        
        // X major line
        if (xDelta >= yDelta) {
            wholeStep = xDelta / yDelta; 
            adjUp = (xDelta % yDelta) * 2;
            adjDown = yDelta * 2;
            errorTerm = (xDelta % yDelta) - (yDelta * 2);
            initialPixelCount = (wholeStep / 2) + 1;
            finalPixelCount = initialPixelCount;
            // special case basic run length is even and no fractional advance
            if ((adjUp ==0) && ((wholeStep & 0x01) == 0)) {
                initialPixelCount--;
            }
            // if odd numer of pixels, one pixel left over
            if ((wholeStep & 0x01) != 0) {
                errorTerm += yDelta;            
            }
            
            // store where we are on the line
            workX = x1;
            workY = y1;
            runLength = initialPixelCount;
            
            // draw first partial run of pixels
            for (i32 i = 0; i < runLength; i++) {
                PutPixel(workX, workY, color);
                workX += xAdvance;
            }
            workY++; // next scan line
            
            // draw full runs
            for(i32 j = 0; j < (yDelta - 1); j++) {
                runLength = wholeStep;
                if ((errorTerm += adjUp) > 0) {
                    runLength++;
                    errorTerm -= adjDown; 
                }
                // draw
                for (i32 i = 0; i < runLength; i++) {
                    PutPixel(workX, workY, color);
                    workX += xAdvance;                
                }
                workY++; // next scan line
            }
            // draw final partial run of pixels
            runLength = finalPixelCount;
            for (i32 i = 0; i < runLength; i++) {
                PutPixel(workX, workY, color);
                workX += xAdvance;    
            }
            return; // end of x major
        } else {
            // y major
            wholeStep = yDelta / xDelta;
            adjUp = (yDelta % xDelta) * 2;
            adjDown = xDelta * 2;
            errorTerm = (yDelta % xDelta) - (xDelta * 2);
            initialPixelCount = (wholeStep / 2) + 1;
            finalPixelCount = initialPixelCount;
            // special cases
            if ((adjUp == 0) && ((wholeStep & 0x01) == 0)) {
                initialPixelCount--;
            }
            if ((wholeStep & 0x01) != 0) {
                errorTerm += xDelta;
            }
            // store where we are on the line
            workX = x1;
            workY = y1;
            runLength = initialPixelCount;
            
            // draw first partial run
            for (i32 i = 0; i < runLength; i++) {
                PutPixel(workX, workY, color);
                workY++;
            }
            workX += xAdvance; // next column
            
            // Draw all full runs
            for (i32 k = 0; k < (xDelta - 1); k++) {
                runLength = wholeStep;    
                if ((errorTerm += adjUp) > 0) {
                    runLength++;
                    errorTerm -= adjDown;
                }
                // draw run 
                for (i32 i = 0; i < runLength; i++) {
                    PutPixel(workX, workY, color);
                    workY++;
                }
                workX += xAdvance; // next column     
            }
            // draw final run
            runLength = finalPixelCount;
            for (i32 i = 0; i < runLength; i++) {
                PutPixel(workX, workY, color);
                workY++;
            }
            return; // end of y major        
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Midpoint circle algorithm 
    // ----------------------------------------------------------------------------
    void Core::DrawCircle(u32 xCenter, u32 yCenter, u32 radius, i32 color) {
        i32 x = radius;
        i32 y = 0;
        i32 decision = 1 - x;
        
        while (x >= y) {
            PutPixel(xCenter + x, yCenter + y, color); // oct 1
            PutPixel(xCenter - x, yCenter + y, color); // oct 4
            PutPixel(xCenter - x, yCenter - y, color); // oct 5
            PutPixel(xCenter + x, yCenter - y, color); // oct 8
            PutPixel(xCenter + y, yCenter + x, color); // oct 2
            PutPixel(xCenter - y, yCenter + x, color); // oct 3
            PutPixel(xCenter - y, yCenter - x, color); // oct 6
            PutPixel(xCenter + y, yCenter - x, color); // oct 7
            y++;
            if(decision <= 0) {
                decision += (y * 2 + 1);            
            } else {
                x--;
                decision += (y -x) * 2 + 1; 
            }
        }    
    }
    
    
    // ----------------------------------------------------------------------------
    // Midpoint circle algorithm - alpha
    // ----------------------------------------------------------------------------
    void Core::DrawCircleAlpha(u32 xCenter, u32 yCenter, u32 radius, i32 color) {
        i32 x = radius;
        i32 y = 0;
        i32 decision = 1 - x;
        
        while (x >= y) {
            PutPixelAlpha(xCenter + x, yCenter + y, color); // oct 1
            PutPixelAlpha(xCenter - x, yCenter + y, color); // oct 4
            PutPixelAlpha(xCenter - x, yCenter - y, color); // oct 5
            PutPixelAlpha(xCenter + x, yCenter - y, color); // oct 8
            PutPixelAlpha(xCenter + y, yCenter + x, color); // oct 2
            PutPixelAlpha(xCenter - y, yCenter + x, color); // oct 3
            PutPixelAlpha(xCenter - y, yCenter - x, color); // oct 6
            PutPixelAlpha(xCenter + y, yCenter - x, color); // oct 7
            y++;
            if(decision <= 0) {
                decision += (y * 2 + 1);            
            } else {
                x--;
                decision += (y -x) * 2 + 1; 
            }
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Midpoint circle algorithm - filled 
    // ----------------------------------------------------------------------------
    void Core::FillCircle(u32 xCenter, u32 yCenter, u32 radius, i32 color) {
        i32 errorTerm = -radius;
        i32 x = radius;
        i32 y = 0;
        i32 lastY = 0;
        i32 i;
        
        while(x >= y) {
            lastY = y;
            
            errorTerm += y;
            y++;
            errorTerm += y;
            
            for(i = -x; i <= x; i++) {
                PutPixel(xCenter + i, yCenter + lastY, color);
            }
            if (lastY != 0) {
                for(i = -x; i <= x; i++) {
                    PutPixel(xCenter + i, yCenter - lastY, color);
                }   
            }
            
            if (errorTerm >= 0) {
                
                if (x != lastY) {
                    for(i = -lastY; i <= lastY; i++) {
                        PutPixel(xCenter + i, yCenter + x, color);
                    }
                    if (y != 0) {
                        for(i = -lastY; i <= lastY; i++) {
                            PutPixel(xCenter + i, yCenter - x, color);
                        }   
                    }                
                }
                
                errorTerm -= x;
                --x;
                errorTerm -= x;
            }
        }
    }
    
    
    // ----------------------------------------------------------------------------
    // Midpoint circle algorithm - filled alpha
    // ----------------------------------------------------------------------------
    void Core::FillCircleAlpha(u32 xCenter, u32 yCenter, u32 radius, i32 color) {
        i32 errorTerm = -radius;
        i32 x = radius;
        i32 y = 0;
        i32 lastY = 0;
        i32 i;
        
        while(x >= y) {
            lastY = y;
            
            errorTerm += y;
            y++;
            errorTerm += y;
            
            for(i = -x; i <= x; i++) {
                PutPixelAlpha(xCenter + i, yCenter + lastY, color);
            }
            if (lastY != 0) {
                for(i = -x; i <= x; i++) {
                    PutPixelAlpha(xCenter + i, yCenter - lastY, color);
                }   
            }
            
            if (errorTerm >= 0) {
                
                if (x != lastY) {
                    for(i = -lastY; i <= lastY; i++) {
                        PutPixelAlpha(xCenter + i, yCenter + x, color);
                    }
                    if (y != 0) {
                        for(i = -lastY; i <= lastY; i++) {
                            PutPixelAlpha(xCenter + i, yCenter - x, color);
                        }   
                    }                
                }
                
                errorTerm -= x;
                --x;
                errorTerm -= x;
            }
        }
    }    
}


#endif //CRE8_H
