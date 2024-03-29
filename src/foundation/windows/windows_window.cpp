/*
** EPITECH PROJECT, 2022
** hoppy
** File description:
** window_windows.cpp
*/

#include "foundation/window.h"
#include "foundation/log.h"
#include "foundation/event.h"

#include <Windows.h>

namespace hoppy {
    LRESULT CALLBACK event_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
        case WM_CREATE:
        {
            LPCREATESTRUCT create_struct = (LPCREATESTRUCT)lparam;
            window *w = (window*)create_struct->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(w));
            
            w->is_open = true;
        } break;
        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        {
            window *w = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            w->is_open = false;
        } break;
        case WM_SIZE:
        {
            RECT r;
            GetClientRect(hwnd, &r);
            AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
            uint32_t width = r.right - r.left;
            uint32_t height = r.bottom - r.top;
			
            event data;
            data.payload.u32[0] = width;
            data.payload.u32[1] = height;
            event_system_fire(event_type::resize, nullptr, data);
        } break;
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    void window_init(window *w, uint32_t width, uint32_t height, const char *title)
    {
        w->width = width;
        w->height = height;
        w->title = title;
        w->is_open = true;

        WNDCLASSA window_class = {};
        window_class.hInstance = GetModuleHandle(nullptr);
        window_class.lpszClassName = "hoppy_window_class";
        window_class.lpfnWndProc = event_callback;
        window_class.hbrBackground  = (HBRUSH)GRAY_BRUSH;
        RegisterClassA(&window_class);

        w->platform_handle = (void*)CreateWindowA(window_class.lpszClassName,
                                                  title,
                                                  WS_OVERLAPPEDWINDOW,
                                                  CW_USEDEFAULT,
                                                  CW_USEDEFAULT,
                                                  width,
                                                  height,
                                                  nullptr,
                                                  nullptr,
                                                  window_class.hInstance,
                                                  w);
        if (!reinterpret_cast<HWND>(w->platform_handle)) {
            log_crit("Failed to create window!");
        }
        ShowWindow((HWND)w->platform_handle, SW_SHOW);
    }

    void window_free(window *w)
    {
        HWND hwnd = reinterpret_cast<HWND>(w->platform_handle);
        DestroyWindow(hwnd);
    }

    void window_poll_events(window *w)
    {
        HWND hwnd = reinterpret_cast<HWND>(w->platform_handle);
        MSG message;

        while (PeekMessageA(&message, hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    bool window_is_open(window *w)
    {
        return w->is_open;
    }
}