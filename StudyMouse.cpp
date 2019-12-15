#include <windows.h>    // Windows API
#include <windowsx.h>   // Windows macro API
#include <string>       // for std::wstring
#include <strsafe.h>    // for StringC*

static std::wstring s_str;
static BOOL s_bWM_MOUSEMOVE = FALSE;

void DoPrint(HWND hwnd, const WCHAR *fmt, ...)
{
    va_list va;
    WCHAR szText[256];
    va_start(va, fmt);
    StringCbVPrintfW(szText, sizeof(szText), fmt, va);
    s_str += szText;
    SetDlgItemTextW(hwnd, edt1, s_str.c_str());
    SendDlgItemMessageW(hwnd, edt1, EM_SETSEL, -1, -1);
    SendDlgItemMessageW(hwnd, edt1, EM_SCROLLCARET, 0, 0);
    va_end(va);
}

LPCWSTR TextFromCodeNotify(UINT codeNotify)
{
    static WCHAR s_sz[32];
    switch (codeNotify)
    {
    case BN_CLICKED: return L"BN_CLICKED";
    case BN_PAINT: return L"BN_PAINT";
    case BN_DISABLE: return L"BN_DISABLE";
    case BN_DOUBLECLICKED: return L"BN_DOUBLECLICKED";
    case BN_PUSHED: return L"BN_PUSHED";
    case BN_UNPUSHED: return L"BN_UNPUSHED";
    case BN_DBLCLK: return L"BN_DBLCLK";
    case BN_SETFOCUS: return L"BN_SETFOCUS";
    case BN_KILLFOCUS: return L"BN_KILLFOCUS";
    default:
        StringCbPrintfW(s_sz, sizeof(s_sz), L"%u", codeNotify);
        return s_sz;
    }
}

std::wstring TextFromKeyFlags(UINT keyFlags)
{
    std::wstring ret;
    if (keyFlags & MK_CONTROL)
    {
        if (ret.size())
            ret += L" | ";
        ret += L"MK_CONTROL";
    }
    if (keyFlags & MK_LBUTTON)
    {
        if (ret.size())
            ret += L" | ";
        ret += L"MK_LBUTTON";
    }
    if (keyFlags & MK_MBUTTON)
    {
        if (ret.size())
            ret += L" | ";
        ret += L"MK_MBUTTON";
    }
    if (keyFlags & MK_RBUTTON)
    {
        if (ret.size())
            ret += L" | ";
        ret += L"MK_RBUTTON";
    }
    if (keyFlags & MK_SHIFT)
    {
        if (ret.size())
            ret += L" | ";
        ret += L"MK_SHIFT";
    }
    return ret;
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
        DoPrint(hwnd, L"OnCommand(IDOK, %s)\r\n", TextFromCodeNotify(codeNotify));
        break;
    case IDCANCEL:
        DoPrint(hwnd, L"OnCommand(IDCANCEL, %s)\r\n", TextFromCodeNotify(codeNotify));
        EndDialog(hwnd, id);
        break;
    case psh1:
        DoPrint(hwnd, L"OnCommand(psh1, %s)\r\n", TextFromCodeNotify(codeNotify));
        break;
    case psh2:
        DoPrint(hwnd, L"OnCommand(psh2, %s)\r\n", TextFromCodeNotify(codeNotify));
        break;
    case chx1:
        DoPrint(hwnd, L"OnCommand(chx1, %s)\r\n", TextFromCodeNotify(codeNotify));
        s_bWM_MOUSEMOVE = (IsDlgButtonChecked(hwnd, chx1) == BST_CHECKED);
        break;
    }
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    if (fDoubleClick)
    {
        DoPrint(hwnd, L"WM_LBUTTONDBLCLK(%d, %d, %s)\r\n",
                x, y, TextFromKeyFlags(keyFlags).c_str());
    }
    else
    {
        DoPrint(hwnd, L"WM_LBUTTONDOWN(%d, %d, %s)\r\n",
                x, y, TextFromKeyFlags(keyFlags).c_str());
    }
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    DoPrint(hwnd, L"WM_LBUTTONUP(%d, %d, %s)\r\n",
            x, y, TextFromKeyFlags(keyFlags).c_str());
}

void OnMButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    if (fDoubleClick)
    {
        DoPrint(hwnd, L"WM_MBUTTONDBLCLK(%d, %d, %s)\r\n",
                x, y, TextFromKeyFlags(keyFlags).c_str());
    }
    else
    {
        DoPrint(hwnd, L"WM_MBUTTONDOWN(%d, %d, %s)\r\n",
                x, y, TextFromKeyFlags(keyFlags).c_str());
    }
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    DoPrint(hwnd, L"WM_LBUTTONUP(%d, %d, %s)\r\n",
            x, y, TextFromKeyFlags(keyFlags).c_str());
}

void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    if (fDoubleClick)
    {
        DoPrint(hwnd, L"WM_RBUTTONDBLCLK(%d, %d, %s)\r\n",
                x, y, TextFromKeyFlags(keyFlags).c_str());
    }
    else
    {
        DoPrint(hwnd, L"WM_RBUTTONDOWN(%d, %d, %s)\r\n",
                x, y, TextFromKeyFlags(keyFlags).c_str());
    }
}

void OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    DoPrint(hwnd, L"WM_RBUTTONUP(%d, %d, %s)\r\n",
            x, y, TextFromKeyFlags(keyFlags).c_str());
}

void OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos)
{
    DoPrint(hwnd, L"WM_CONTEXTMENU(%d, %d)\r\n", x, y);
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (s_bWM_MOUSEMOVE)
        DoPrint(hwnd, L"WM_MOUSEMOVE(%d, %d, %s)\r\n", x, y, TextFromKeyFlags(keyFlags).c_str());
}

void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys)
{
    DoPrint(hwnd, L"WM_MOUSEWHEEL(%d, %d, %d, %s)\r\n",
            xPos, yPos, zDelta, TextFromKeyFlags(fwKeys).c_str());
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, OnLButtonDown);
        HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLButtonUp);
        HANDLE_MSG(hwnd, WM_MBUTTONDOWN, OnMButtonDown);
        HANDLE_MSG(hwnd, WM_MBUTTONDBLCLK, OnMButtonDown);
        HANDLE_MSG(hwnd, WM_MBUTTONUP, OnMButtonUp);
        HANDLE_MSG(hwnd, WM_RBUTTONDOWN, OnRButtonDown);
        HANDLE_MSG(hwnd, WM_RBUTTONDBLCLK, OnRButtonDown);
        HANDLE_MSG(hwnd, WM_RBUTTONUP, OnRButtonUp);
        HANDLE_MSG(hwnd, WM_CONTEXTMENU, OnContextMenu);
        HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMouseMove);
        HANDLE_MSG(hwnd, WM_MOUSEWHEEL, OnMouseWheel);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
