# Salt

> Execute your own code under an official game, with full SDK symbols' access!

Salt (temporary name) is a SaltyNX plugin replacing every official application's entrypoint function, **`nnMain`**.

This way, the actual code the application would normally run is replaced by your own code, and since the SDK libraries' initialization happens before calling `nnMain`, there is nothing to worry about initialization.

## Structure

Salt "libraries" are headers/sources inside `/salt/libsalt` directory, which are automatically compiled along with the injection project's sources.

Salt also uses custom libnx (used by other SaltyNX plugins as well) named `libnx_min` and custom linker scripts.

## Custom heap

You can always define `SALT_RUNTIME_HEAP` macro, which will indicate runtime code how much heap to use.

## Libraries

Salt's libraries (`salt::` namespace) consist on aliases for official SDK code. Example of how the code sets them internally (using macros to simplify the process)

```cpp
extern "C" // We use C-linkage of the functions to be precise with their symbols
{
    // (nn::Result struct's size is u64)
    // Original function would be: nn::Result nn::err::ShowError(nn::Result error)
    extern u64 _ZN2nn3err9ShowErrorENS_6ResultE(u64 error) __attribute__((weak));
}

// Then later, using C++'s aliasing create a more good-looking alias for the function

namespace salt
{
    namespace err
    {
        const auto &ShowError = _ZN2nn3err9ShowErrorENS_6ResultE;
    }
}

void saltMain() // Later, in main code
{
    salt::err::ShowError(0xDEAD); // Will prompt error window with result 0xDEAD -> 2173-0111
}
```

The libraries are a WIP (need to add every symbol like this), so don't expect it to be fully featured.

## Credits

First of all, [SaltyNX and ShinyQuagsire](https://github.com/shinyquagsire23/SaltyNX) for all his amazing work on the aforementioned project, and the same for the original 3DS one.

This project's base is ReverseNX (Makefile, linker scripts, libnx_min...), another SaltyNX plugin made by [masagrator](https://github.com/masagrator/ReverseNX).