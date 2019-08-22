# SaltyLime

> Execute your own code under an official game, with full SDK symbol access!

SaltyLime (temporary name) is a SaltyNX plugin replacing every official application's entrypoint function, **`nnMain`**.

This way, the actual code the application would normally run is replaced by your own code, and since the SDK libraries' initialization happens before calling `nnMain`, there is nothing to worry about initialization.

## Structure

SaltyLime "libraries" are headers/sources inside `/lime/liblime` directory, which are automatically compiled along with the injection project's sources.

SaltyLime also uses custom libnx (used by other SaltyNX plugins as well) named `libnx_min` and custom linker scripts.

## Libraries

SaltyLime's libraries (`lime::` namespace) consist on aliases for official SDK code. See more [here](SYMBOLS.md)

The libraries are a WIP (need to add every symbol like this), so don't expect it to be fully featured.

### Custom heap

You can always define `LIME_RUNTIME_HEAP` macro, which will indicate runtime code how much heap to use.

### Custom replacements

You can always override `void limeSaltyRuntime()` and use `lime::salty::*` functions to replace custom functions

## Credits

First of all, [SaltyNX and ShinyQuagsire](https://github.com/shinyquagsire23/SaltyNX) for all his amazing work on the aforementioned project, and the same for the original 3DS one.

This project's base is ReverseNX (Makefile, linker scripts, libnx_min...), another SaltyNX plugin made by [masagrator](https://github.com/masagrator/ReverseNX).
