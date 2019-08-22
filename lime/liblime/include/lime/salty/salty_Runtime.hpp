
#include <libsalt/salt_Types.hpp>
#include <saltysd/saltysd_core.h>
#include <saltysd/saltysd_dynamic.h>
#include <saltysd/saltysd_ipc.h>

namespace lime
{
    namespace salty
    {
        const auto &LogFmt = SaltySD_printf;
        const auto &ReplaceSymbol = SaltySDCore_ReplaceImport;
        const auto &FindSymbol = SaltySDCore_FindSymbol;
    }
}