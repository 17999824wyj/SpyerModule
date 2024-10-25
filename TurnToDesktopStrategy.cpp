#include "TurnToDesktopStrategy.h"
#include <windows.h>
#include <winUser.h>

void TurnToDesktopStrategy::execute()
{
    // 通过模拟“win + D”键，进行实现
    keybd_event(VK_LWIN, 0, 0, 0); // 模拟按下Win键
    keybd_event('D', 0, 0, 0);     // 模拟按下D键

    keybd_event('D', 0, KEYEVENTF_KEYUP, 0); // 释放D键
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0); // 释放Win键
}
