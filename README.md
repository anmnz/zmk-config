<h1>zmk-config</h1>

This is my [ZMK](https://github.com/zmkfirmware/zmk/) configuration,
which I am currently using on a [Chocofi](https://shop.beekeeb.com/products/presoldered-chocofi-split-keyboard)
and a [Sofle variant](https://ergomech.store/shop/sofle-hybrid-sandwich-style-423).

It uses the [Miryoku](https://github.com/manna-harbour/miryoku_zmk) layout,
but with the standard ZMK build workflow instead of Miryoku's own.

<h2>Contents</h2>
<!-- TOC -->
  * [Using Miryoku in a standard ZMK build](#using-miryoku-in-a-standard-zmk-build)
  * [Macros on RGB keys](#macros-on-rgb-keys)
  * [How to add a new keyboard](#how-to-add-a-new-keyboard)
<!-- TOC -->

## Using Miryoku in a standard ZMK build

I wanted to use Miryoku ZMK keymaps, but with the standard ZMK build workflow
instead of Miryoku's own, and without forking Miryoku ZMK itself.
This repository achieves that as follows:

1. Miryoku ZMK is declared as a Git submodule, in `modules/miryoku_zmk`.
   (I have also tried pulling it in as West project instead of as a Git submodule;
   this is entirely possible but more complicated.)

2. Miryoku customizations (e.g. [`custom_config.h`](config/miryoku/custom_config.h),
   and mappings for additional keyboards)
   are done by creating new files under [`config/miryoku`](config/miryoku), which _override_ files
   with the same relative path under [`modules/miryoku_zmk/miryoku`](modules/miryoku_zmk/miryoku).

3. ZMK `.keymap` and `.conf` files are placed in the `config` directory as normal;
   they can be copied there _unchanged_ from [`modules/miryoku_zmk/config`](modules/miryoku_zmk/config).

4. Miryoku `.keymap` files refer to other Miryoku files with `#include` directives like this:
    ```c++
    #include "../miryoku/custom_config.h"
    #include "../miryoku/mapping/42/corne.h"
    #include "../miryoku/miryoku.dtsi"
    ```
   I wanted these directives to refer to the customized files under `config/miryoku` if present,
   otherwise to the original Miryoku files under
   `modules/miryoku_zmk/miryoku`.
   A ZMK "snippet", named `miryoku`, updates the paths used by the C preprocessor
   so that they can resolve to files in either location.

5. The snippet needs to be used in builds that use Miryoku.
   For workflow builds, that is done by adding `snippet: miryoku` to each entry in `build.yaml`.
   For local builds, add `-S miryoku` to the `west build` command.

## Macros on RGB keys

None of my keyboards have LEDs, and I wanted to use Miryoku's RGB control keys for macros.

To achieve this, `custom_config.h` looks for an adjacent file named `my_macros.h`.
If present, this file can define C preprocessor macros named `MY_MACRO_1` through `MY_MACRO_5`,
which are used as the `bindings` for ZMK macros named `&my_macro_1` through `&my_macro_5`.

For example:
```
#define MY_MACRO_1 \
&macro_press &kp LSHFT &macro_tap &kp H &macro_release &kp LSHFT  \
&macro_tap &kp E &kp L &kp L &kp O &kp COMMA &kp SPACE &kp W &kp O &kp R &kp L &kp D &kp EXCL
```

These ZMK macros are then bound to the keys that Miryoku uses for RGB controls,
by redefining `MIRYOKU_LAYER_MEDIA` in `custom_config.h`, as described in
[the Miryoku ZMK customization documentation](https://github.com/manna-harbour/miryoku_zmk#customisation).

`my_macros.h` is excluded from source control, and treated as optional, because sometimes
I wanted to put things in macros without pushing them to the source repository.

## How to add a new keyboard

* For a keyboard that Miryoku already supports, copy the `.keymap` file and any `.conf` files
  from `modules/miryoku_zmk/config` to the `config` directory.
* For a keyboard that Miryoku does not support, write a new `.keymap` file, just like you
  would for plain Miryoku, and put it in the `config` directory.
* Add a new entry or entries to `build.yaml` for the new keyboard. Be sure to add `snippet: miryoku`
  to the entry as described below.
