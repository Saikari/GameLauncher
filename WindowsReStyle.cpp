#include <Windows.h>

void WindowsReStyle(HWND hwnd)
{
    // Get menu
    HMENU hMenu = GetMenu(hwnd);
    // Get item count
    int count = GetMenuItemCount(hMenu);
    // Loop & remove
    for (int i = 0; i < count; i++)
        RemoveMenu(hMenu, 0, (MF_BYPOSITION | MF_REMOVE));
    // Force a redraw
    DrawMenuBar(hwnd);
}
