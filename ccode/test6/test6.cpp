#include <windows.h>
#include <stdint.h>
#include <xinput.h>

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

#define X_INPUT_GET_STATE(name) DWORD name(DWORD dwUserIndex,XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(f_x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
  return 0;
}
global_variable f_x_input_get_state *XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_

#define X_INPUT_SET_STATE(name) DWORD name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(f_x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
  return 0;
}
global_variable f_x_input_set_state *XInputSetState_ = XInputSetStateStub;
#define XInputSetState XInputSetState_

internal void
Win32LoadXInput(void){
  HMODULE XInputLibrary = LoadLibraryA("xinput1_3.dll");
  if(XInputLibrary){
    XInputGetState = (f_x_input_get_state *) GetProcAddress(XInputLibrary,"XInputGetState");
    XInputSetState = (f_x_input_set_state *) GetProcAddress(XInputLibrary,"XInputSetState");
  }
}

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
  uint8 *Row = (uint8 *)Buffer.Memory;

  for(int Y = 0;Y < Buffer.Height; Y++)
  {
    uint32 *Pixel = (uint32 *)Row;
    for(int X = 0; X < Buffer.Width; X++)
    {
      // Memory Order: BB GG RR XX
      // 0xXXRRGGBB
      uint8 Blue = X + BlueOffset;
      uint8 Green = Y + GreenOffset;

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
	
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			uint32 VKCode = WParam;
			bool WasDown = ((LParam & (1 << 30)) != 0);
			bool IsDown = ((LParam & (1<< 31)) == 0 );
			switch(VKCode){
				case VK_TAB:
				{
					OutputDebugStringA("TAB");
				} break;
				case 'W':
				{
					OutputDebugStringA("W");
				} break;
				case 'D':
				{
					OutputDebugStringA("D");
				} break;
			}
		}
	
		case WM_PAINT:
		{
			OutputDebugStringA("WM Paint");
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(WindowHandle,&Paint);
			win32_window_dimension Dimension = Win32GetWindowDimension(WindowHandle);
			Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height, 
				GlobalBackbuffer);
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
				
				// Poll message from controller
				for(DWORD ControllerIndex = 0; ControllerIndex < XUSER_MAX_COUNT; ControllerIndex++)
				{
					XINPUT_STATE ControllerState;
					if(XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS)
					{
						XINPUT_GAMEPAD *Pad = &ControllerState.Gamepad;
						bool Up = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
						bool Down = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
						bool Left = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
						bool Right = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
						bool Start = (Pad->wButtons & XINPUT_GAMEPAD_START);
						bool Back = (Pad->wButtons & XINPUT_GAMEPAD_BACK);
						bool LeftShoulder = (Pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
						bool RightShoulder = (Pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
						bool AButton = (Pad->wButtons & XINPUT_GAMEPAD_A);
						bool BButton = (Pad->wButtons & XINPUT_GAMEPAD_B);
						bool XButton = (Pad->wButtons & XINPUT_GAMEPAD_X);
						bool YButton = (Pad->wButtons & XINPUT_GAMEPAD_Y);
						int16 StickX = Pad->sThumbLX;
						int16 StickY = Pad->sThumbLY;
					}
					else
					{
			
					}
				}
				
				RenderWeirdGradient(GlobalBackbuffer, XOffset, YOffset);
				win32_window_dimension Dimension = Win32GetWindowDimension(WindowHandle);
				Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height, 
					GlobalBackbuffer);

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
