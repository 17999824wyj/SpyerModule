#include "TurnToDesktopStrategy.h"
#include <windows.h>
#include <winUser.h>

void TurnToDesktopStrategy::execute()
{
    // ͨ��ģ�⡰win + D����������ʵ��
    keybd_event(VK_LWIN, 0, 0, 0); // ģ�ⰴ��Win��
    keybd_event('D', 0, 0, 0);     // ģ�ⰴ��D��

    keybd_event('D', 0, KEYEVENTF_KEYUP, 0); // �ͷ�D��
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0); // �ͷ�Win��
}
