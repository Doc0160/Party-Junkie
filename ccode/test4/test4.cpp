#include <windows.h>
#include <stdint.h>

#define local_persist static
#define global_variable static
#define internal static

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t bool8;
typedef uint16_t bool16;
typedef uint32_t bool32;
typedef uint64_t bool64;

typedef float real32;
typedef double real64;

global_variable bool Running;
global_variable BITMAPINFO BitmapInfo;
global_variable HBITMAP BitmapHandle;
global_variable HDC BitmapDeviceContext;
global_variable void * BitmapMemory;
global_variable int BitmapWidth;
global_variable int BitmapHeight;
global_variable int BytesPerPixel = 4;

internal void
RenderWeirdGradient(int BlueOffset, int GreenOffset)
{
  int Width = BitmapWidth;
  int Height = BitmapHeight;

  int Pitch = Width * BytesPerPixel;
  uint8 *Row = (uint8 *)BitmapMemory;

  for(int Y = 0;Y < BitmapHeight; Y++)
  {
    uint32 *Pixel = (uint32 *)Row;
    for(int X = 0; X < BitmapWidth; X++)
    {
      // Memory Order: BB GG RR XX
      // 0xXXBBGGRR
      uint8 Blue = X + BlueOffset;
      uint8 Green = Y + GreenOffset;

      *Pixel++ = ((Green << 8) | Blue );

    }
    Row += Pitch;
  }
}

internal void
Win32ResizeDIBSection(int Width, int Height)
{
  if(BitmapMemory){
    VirtualFree(BitmapMemory, 0, MEM_RELEASE);
  }
  BitmapWidth = Width;
  BitmapHeight = Height;

  BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
  BitmapInfo.bmiHeader.biWidth = Width;
  BitmapInfo.bmiHeader.biHeight = Height;
  BitmapInfo.bmiHeader.biPlanes = 1;
  BitmapInfo.bmiHeader.biBitCount = 32;
  BitmapInfo.bmiHeader.biCompression = BI_RGB;

  int BitmapMemorysize = Width * Height * BytesPerPixel;
  BitmapMemory = VirtualAlloc(0, BitmapMemorysize, MEM_COMMIT, PAGE_READWRITE);
}

internal void 
Win32UpdateWindow(HDC DeviceContext,int WindowWidth, int WindowHeight)
{
  StretchDIBits(DeviceContext,
    0,0,BitmapWidth,BitmapHeight,
    0,0,WindowWidth,WindowHeight,
    BitmapMemory,
    &BitmapInfo,
    DIB_RGB_COLORS,SRCCOPY);
}

LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
    UINT   Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;
    switch(Message){
		case WM_SIZE:{
			RECT ClientRect;
			GetClientRect(Window, &ClientRect);
			int Height = ClientRect.bottom - ClientRect.top;
			int Width = ClientRect.right - ClientRect.left;
			Win32ResizeDIBSection(Width, Height);
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
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			Win32UpdateWindow(DeviceContext, Width, Height);
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
	WindowClass.lpfnWndProc = Win32MainWindowCallback;
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
			
			int XOffset = 0;
			int YOffset = 0;
			while(Running)
			{
				while(PeekMessage(&Message,WindowHandle,0,0, PM_REMOVE))
				{
					if(Message.message == WM_QUIT){
						Running = false;
					}
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}

				HDC DeviceContext = GetDC(WindowHandle);

				RenderWeirdGradient(XOffset, YOffset);
				RECT ClientRect;
				GetClientRect(WindowHandle, &ClientRect);
			
				int WindowWidth = ClientRect.right - ClientRect.left;
				int WindowHeight = ClientRect.bottom - ClientRect.top;
			
				Win32UpdateWindow(DeviceContext, WindowWidth, WindowHeight);
				ReleaseDC(WindowHandle, DeviceContext);

				XOffset++;
				YOffset += 2;
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