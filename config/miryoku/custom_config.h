#pragma once

#define MIRYOKU_ALPHAS_QWERTY
#define MIRYOKU_KLUDGE_DOUBLETAPBOOT

#include <behaviors.dtsi>

// up/down for roller encoder
/ {
    keymap {
        BASE {
            sensor-bindings = <&inc_dec_kp C_VOL_DN C_VOL_UP>;
        };
    };
};

// optional file "my_macros.h" defines macros that can be assigned to RGB control keys
#if __has_include ("my_macros.h")
#include "my_macros.h"
#endif
#ifndef MY_MACRO_1
#define MY_MACRO_1 &none
#endif
#ifndef MY_MACRO_2
#define MY_MACRO_2 &none
#endif
#ifndef MY_MACRO_3
#define MY_MACRO_3 &none
#endif
#ifndef MY_MACRO_4
#define MY_MACRO_4 &none
#endif
#ifndef MY_MACRO_5
#define MY_MACRO_5 &none
#endif

#define MY_MACRO(NAME, BINDINGS)            \
    NAME: NAME {                            \
        compatible = "zmk,behavior-macro";  \
        #binding-cells = <0>;               \
        wait-ms = <10>;                     \
        tap-ms = <5>;                       \
        bindings = <BINDINGS>;              \
    };

/ {
    macros {
        MY_MACRO(my_macro_1, MY_MACRO_1)
        MY_MACRO(my_macro_2, MY_MACRO_2)
        MY_MACRO(my_macro_3, MY_MACRO_3)
        MY_MACRO(my_macro_4, MY_MACRO_4)
        MY_MACRO(my_macro_5, MY_MACRO_5)
    };
};

// MIRYOKU_ALTERNATIVES_MEDIA from miryoku_layer_alternatives.h, with macros on RGB control keys
#define MIRYOKU_LAYER_MEDIA \
U_BOOT,            &u_to_U_TAP,       &u_to_U_EXTRA,     &u_to_U_BASE,      U_NA,              &my_macro_1,       &my_macro_2,       &my_macro_3,       &my_macro_4,       &my_macro_5,       \
&kp LGUI,          &kp LALT,          &kp LCTRL,         &kp LSHFT,         U_NA,              U_EP_TOG,          &kp C_PREV,        &kp C_VOL_DN,      &kp C_VOL_UP,      &kp C_NEXT,        \
U_NA,              &kp RALT,          &u_to_U_FUN,       &u_to_U_MEDIA,     U_NA,              &u_out_tog,        &u_bt_sel_0,       &u_bt_sel_1,       &u_bt_sel_2,       &u_bt_sel_3,       \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              &kp C_STOP,        &kp C_PP,          &kp C_MUTE,        U_NP,              U_NP
