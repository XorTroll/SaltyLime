# Symbols and lime libraries

## Simple functions

Example of how the code sets them internally (lime uses macros to simplify the process)

```cpp
extern "C" // We use C-linkage of the functions to be precise with their symbols
{
    // (nn::Result struct's size is u64)
    // Original function would be: nn::Result nn::err::ShowError(nn::Result error)

    extern u64 _ZN2nn3err9ShowErrorENS_6ResultE(u64 error) __attribute__((weak));
}

// Then later, using C++'s aliasing create a more good-looking alias for the function

namespace lime
{
    namespace err
    {
        const auto &ShowError = _ZN2nn3err9ShowErrorENS_6ResultE;
    }
}

void limeMain() // Later, in main code
{
    lime::err::ShowError(0xDEAD); // Will prompt error window with result 0xDEAD -> 2173-0111
}
```

## Member functions, structs, classes

Basically explained, member functions are normla functions which internally take a pointer to the actual instance as an extra parameter (the classic `this`)

```cpp
extern "C" // We use C-linkage of the functions to be precise with their symbols
{
    // Original function: nn::err::SystemErrorArg::SystemErrorArg([SystemErrorArg *this])
    extern void _ZN2nn3err14SystemErrorArgC2Ev(void *this_ptr) __attribute__((weak));

    // Original function: nn::Result nn::err::SystemErrorArg::SetDialogMessage([SystemErrorArg *this], const char *msg)
    extern u64 _ZN2nn3err14SystemErrorArg16SetDialogMessageEPKc(LIME_THIS, const char *msg) __attribute__((weak));

    // Original function: nn::Result nn::err::ShowSystemError(nn::err::SystemErrorArg&)

    extern u64 _ZN2nn3err15ShowSystemErrorERKNS0_14SystemErrorArgE(void *arg) __attribute__((weak));

    /* How would this be in official code:

    nn::err::SystemErrorArg arg;
    arg.SetDialogMessage("Demo");
    nn::err::ShowSystemError(arg);

    */

    /* How it could be later "translated":

    nn::err::SystemErrorArg *arg = (...); // Allocate pointer with nn::err::SystemErrorArg's full size
    nn::err::SystemErrorArg::SystemErrorArg(arg); // Call constructor

    nn::err::SystemErrorArg::SetDialogMessage(arg, "Demo");
    nn::err::ShowSystemError(arg); // This one is the same

    // After use, dispose it, what the destructor actually does (in this case, just free the pointer)

    */
}

void limeMain() // Thus, we do the same with our symbols
{
    void *arg = operator new(0x1000) // We don't know the size, using a big one to ensure we have enough (better to have more than less)

    _ZN2nn3err14SystemErrorArgC2Ev(arg); //Despite being a raw pointer, this will fill the pointer as if it was an actual instance
    _ZN2nn3err14SystemErrorArg16SetDialogMessageEPKc(arg, "Demo");

    // Now we can use it easily
    _ZN2nn3err15ShowSystemErrorERKNS0_14SystemErrorArgE(arg);

    operator delete(arg);
}
```