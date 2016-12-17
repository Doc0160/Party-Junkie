#include <windows.h>
int CALLBACK
WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR     CmdLine,
    int       CmdShow)
{
    MessageBox(0,
        "Mandrew was a superdog. It's true.\nYou can tell from its bright green glowing poo.",
        "Party Junkie Rules",
        MB_OK | MB_ICONINFORMATION);
    return(0);
}