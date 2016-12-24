#include <windows.h>

#define local_persist static
#define global_variable static
#define internal static

global_variable bool Running;

LRESULT CALLBACK
MainWindowCallback(HWND Window,
    UINT   Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;
    switch(Message){
		case WM_SIZE:{
			OutputDebugString("WM_SIZE\n");
		}break;
		case WM_DESTROY:{
			Running = false;
		}break;
		case WM_CLOSE:{
			Running = false;
		}break;
		case WM_ACTIVATEAPP:{
			OutputDebugString("WM_ACTIVATEAPP\n");
		}break;
		case WM_PAINT:{
			local_persist DWORD Color = WHITENESS;
			if(Color == WHITENESS)
			{
				Color = BLACKNESS;
			}
			else
			{
				Color = WHITENESS;
			}
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			PatBlt(DeviceContext, X, Y, Width, Height, Color);
			EndPaint(Window, &Paint);
		}break;
		default:{
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
		HWND WindowHandle = CreateWindowEx(0,
			WindowClass.lpszClassName, "Taste the Rainbow",
			WS_VISIBLE|WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
			0, 0, Instance, 0);
		if(WindowHandle)
		{
			Running = true;
			MSG Message;
			while(Running)
			{
				BOOL MessageResult = GetMessage(&Message,0,0,0);
				if(MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
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
