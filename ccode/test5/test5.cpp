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

struct win32_offscreen_buffer
{
  BITMAPINFO Info;
  void *Memory;
  int Width;
  int Height;
  int Pitch;
};

struct win32_window_dimension
{
  int Width;
  int Height;
};

global_variable bool GlobalRunning;
global_variable win32_offscreen_buffer GlobalBackbuffer;

win32_window_dimension
Win32GetWindowDimension(HWND Window)
{
  win32_window_dimension Result;

  RECT ClientRect;
  GetClientRect(Window, &ClientRect);
  Result.Width = ClientRect.right - ClientRect.left;
  Result.Height = ClientRect.bottom - ClientRect.top;
  return Result;
}

internal void
RenderWeirdGradient(win32_offscreen_buffer Buffer, 
	int BlueOffset, 
	int GreenOffset)
{
  uint8_t *Row = (uint8_t *)Buffer.Memory;

  for(int Y = 0;Y < Buffer.Height; Y++)
  {
    uint32_t *Pixel = (uint32_t *)Row;
    for(int X = 0; X < Buffer.Width; X++)
    {
      // Memory Order: BB GG RR XX
      // 0xXXRRGGBB
      uint8_t Blue = X + BlueOffset;
      uint8_t Green = Y + GreenOffset;

      *Pixel++ = ((Green << 8) | Blue );

    }
    Row += Buffer.Pitch;
  }
}

internal void 
Win32DisplayBufferInWindow(HDC DeviceContext,
	int WindowWidth, 
	int WindowHeight,
	win32_offscreen_buffer Buffer)
{
  StretchDIBits(DeviceContext,
    0,0,WindowWidth,WindowHeight,
    0,0,Buffer.Width,Buffer.Height,
    Buffer.Memory,
    &Buffer.Info,
    DIB_RGB_COLORS,SRCCOPY);
}

internal void 
Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
  if(Buffer->Memory){
    VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
  }
  Buffer->Width = Width;
  Buffer->Height = Height;

  Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
  Buffer->Info.bmiHeader.biWidth = Width;
  Buffer->Info.bmiHeader.biHeight = Height;
  Buffer->Info.bmiHeader.biPlanes = 1;
  Buffer->Info.bmiHeader.biBitCount = 32;
  Buffer->Info.bmiHeader.biCompression = BI_RGB;

  int BytesPerPixel = 4;
  int BitmapMemorysize = Width * Height * BytesPerPixel;
  Buffer->Memory = VirtualAlloc(0, BitmapMemorysize, MEM_COMMIT, PAGE_READWRITE);
  Buffer->Pitch = BytesPerPixel * Width;
}


LRESULT CALLBACK
Win32MainWindowCallback(HWND WindowHandle,
    UINT   Message,
    WPARAM WParam,
    LPARAM LParam)
{
    LRESULT Result = 0;
    switch(Message){
		case WM_SIZE:{
			RECT ClientRect;
			GetClientRect(WindowHandle, &ClientRect);
			int Height = ClientRect.bottom - ClientRect.top;
			int Width = ClientRect.right - ClientRect.left;
			Win32ResizeDIBSection(&GlobalBackbuffer, Width, Height);
		}break;
		case WM_DESTROY:{
			GlobalRunning = false;
		}break;
		case WM_CLOSE:{
			GlobalRunning = false;
		}break;
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("ACTIVATEAPP\n");
		} break;
	
		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(WindowHandle,&Paint);
			win32_window_dimension Dimension = Win32GetWindowDimension(WindowHandle);
			Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height, GlobalBackbuffer);
			EndPaint(WindowHandle,&Paint);
		} break;
		default:{
			Result = DefWindowProc(WindowHandle, Message, WParam, LParam);
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
			GlobalRunning = true;
			MSG Message;
			
			HDC DeviceContext = GetDC(WindowHandle);
			win32_window_dimension Dimension = Win32GetWindowDimension(WindowHandle);
			Win32ResizeDIBSection(&GlobalBackbuffer, Dimension.Width, Dimension.Height);
			
			int XOffset = 0;
			int YOffset = 0;
			while(GlobalRunning)
			{
				while(PeekMessage(&Message,WindowHandle,0,0, PM_REMOVE))
				{
					if(Message.message == WM_QUIT){
						GlobalRunning = false;
					}
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}

				
				RenderWeirdGradient(GlobalBackbuffer, XOffset, YOffset);
				win32_window_dimension Dimension = Win32GetWindowDimension(WindowHandle);
				Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height, GlobalBackbuffer);
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
