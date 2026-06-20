#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif

// Representa um atalho completo 
struct Atalho {
    const int* teclas;
    int tamanho;
};

namespace AtalhoMap {

    // =========================
    // ATALHOS MAIS USADOS
    // =========================

    static constexpr int ALT_TAB_KEYS[] = { VK_MENU, VK_TAB };
    static constexpr Atalho ALT_TAB = { ALT_TAB_KEYS, 2 };

    static constexpr int ALT_F4_KEYS[] = { VK_MENU, VK_F4 };
    static constexpr Atalho ALT_F4 = { ALT_F4_KEYS, 2 };

    static constexpr int CTRL_C_KEYS[] = { VK_CONTROL, 'C' };
    static constexpr Atalho CTRL_C = { CTRL_C_KEYS, 2 };

    static constexpr int CTRL_V_KEYS[] = { VK_CONTROL, 'V' };
    static constexpr Atalho CTRL_V = { CTRL_V_KEYS, 2 };

    static constexpr int CTRL_X_KEYS[] = { VK_CONTROL, 'X' };
    static constexpr Atalho CTRL_X = { CTRL_X_KEYS, 2 };

    static constexpr int CTRL_Z_KEYS[] = { VK_CONTROL, 'Z' };
    static constexpr Atalho CTRL_Z = { CTRL_Z_KEYS, 2 };

    static constexpr int CTRL_A_KEYS[] = { VK_CONTROL, 'A' };
    static constexpr Atalho CTRL_A = { CTRL_A_KEYS, 2 };

    static constexpr int CTRL_S_KEYS[] = { VK_CONTROL, 'S' };
    static constexpr Atalho CTRL_S = { CTRL_S_KEYS, 2 };

    static constexpr int CTRL_SHIFT_ESC_KEYS[] = {
        VK_CONTROL, VK_SHIFT, VK_ESCAPE
    };
    static constexpr Atalho CTRL_SHIFT_ESC = { CTRL_SHIFT_ESC_KEYS, 3 };

    static constexpr int WIN_D_KEYS[] = { VK_LWIN, 'D' };
    static constexpr Atalho WIN_D = { WIN_D_KEYS, 2 };

    static constexpr int WIN_E_KEYS[] = { VK_LWIN, 'E' };
    static constexpr Atalho WIN_E = { WIN_E_KEYS, 2 };

    static constexpr int WIN_L_KEYS[] = { VK_LWIN, 'L' };
    static constexpr Atalho WIN_L = { WIN_L_KEYS, 2 };
}