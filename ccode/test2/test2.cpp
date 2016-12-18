#include <windows.h>

LRESULT CALLBACK
MainWindowCallback(HWND Window,
    UINT   Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;
    switch(Message){

    //NOTE(doc): when our windows is resized
    case WM_SIZE:{
        OutputDebugString("WM_SIZE\n");
    }break;
        
    //NOTE(doc): when windows "destroy" our window
    case WM_DESTROY:{
        OutputDebugString("WM_DESTROY\n");
    }break;
        
     //NOTE(doc): when the user click on the little red "X"
    case WM_CLOSE:{
        OutputDebugString("WM_CLOSE\n");
    }break;
        
    //NOTE(doc): when our windows gain or loses focus
    case WM_ACTIVATEAPP:{
        OutputDebugString("WM_ACTIVATEAPP\n");
    }break;
        
    //NOTE(doc): for every thing else
    default:{
        //NOTE(doc): call the default behaviour
        Result = DefWindowProc(Window, Message, WParam, LParam);
    }break;
        
    }
    return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR     CmdLine,
    int       CmdShow)
{
	 WNDCLASS WindowClass = {0};
      WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
      WindowClass.lpfnWndProc = ; //TODO(doc): explain what to add here
      WindowClass.hInstance = Instance;
      //NOTE(doc): not PJ's window class name
      WindowClass.lpszClassName = "RainbowCreatorWindowClass";
    return(0);
}
