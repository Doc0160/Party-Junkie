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
      WindowClass.lpfnWndProc = MainWindowCallback;
      WindowClass.hInstance = Instance;
      WindowClass.lpszClassName = "RainbowCreatorWindowClass";

      if(RegisterClass(&WindowClass))
      {

      HWND WindowHandle = CreateWindowEx(0, //NOTE(doc): we don't need any of this
          WindowClass.lpszClassName, //NOTE(doc): the window class name
          "Taste the Rainbow", //NOTE(doc): The actual window title
          WS_VISIBLE|WS_OVERLAPPEDWINDOW, //NOTE(doc): WS_OVERLAPPEDWINDOW
          CW_USEDEFAULT, //NOTE(doc): default x position
          CW_USEDEFAULT, //NOTE(doc): default y position
          CW_USEDEFAULT, //NOTE(doc): default width
          CW_USEDEFAULT, //NOTE(doc): default height
          0, //NOTE(doc): if you want windows inside windows
          0, //NOTE(doc): we don't use menus
          Instance, //NOTE(doc): our program instance
          0); //NOTE(doc): don't need to pass a thing to our window
		MSG Message;
		
		if(WindowHandle)
          {
                    for(;;){
          BOOL MessageResult =
              GetMessage(&Message,
                  0, // NOTE(doc): do not filter witch window of our program
                  0,0); // NOTE(doc): do not filter witch messages

          //NOTE(doc): if MessageResult = 0; you have to stop your application
          if(MessageResult > 0)
          {
              TranslateMessage(&Message);
              DispatchMessage(&Message);
          }
          else
          {
             //NOTE(doc): break the for loop
             break;
          }

      }
          }
          else
          {
              MessageBox(0, "CreateWindowEx FAIL",
                  "Rainbow", MB_OK|MB_ICONERROR);
          }

      }
      else
      {
          MessageBox(0, "RegisterClass FAIL",
              "Party Junkie Rules", MB_OK|MB_ICONERROR);
      }
    return(0);
}
