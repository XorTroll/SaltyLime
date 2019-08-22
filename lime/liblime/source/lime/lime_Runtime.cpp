#include <switch_min.h>

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <cstdlib>
#include <dirent.h>
#include <sys/iosupport.h>
#include <sys/reent.h>
#include <switch_min/kernel/ipc.h>
#include <cstdarg>

#include "saltysd/saltysd_core.h"
#include "saltysd/saltysd_ipc.h"
#include "saltysd/saltysd_dynamic.h"

#ifndef LIME_RUNTIME_HEAP
#define LIME_RUNTIME_HEAP 0x20000
#endif

extern "C"
{
	extern u32 __start__;

	static char g_heap[LIME_RUNTIME_HEAP];

	void __libnx_init(void* ctx, Handle main_thread, void* lr);
	void __attribute__((weak)) NORETURN __libnx_exit(int rc);
	void __nx_exit(int, void*);
	void __libc_fini_array(void);
	void __libc_init_array(void);
}

u32 __nx_applet_type = AppletType_Application;

void* __lime_runtime_lr;

void __libnx_init(void* ctx, Handle main_thread, void* lr)
{
	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = g_heap;
	fake_heap_end   = &g_heap[LIME_RUNTIME_HEAP];
	
	__lime_runtime_lr = lr;
	
	__libc_init_array();
}

void __attribute__((weak)) NORETURN __libnx_exit(int rc)
{
	__libc_fini_array();
	__nx_exit(0, __lime_runtime_lr);
    __builtin_unreachable();
}

void __attribute__((weak)) limeSaltyRuntime()
{
	// This should be overrided if the user wants to replace custom imports
}

// SaltyLime's entrypoint
void limeMain();

int main(int argc, char *argv[])
{
    u64 appid = 0;
    svcGetInfo(&appid, InfoType_TitleId, CUR_PROCESS_HANDLE, 0);

	char nn_main_symbol[] = "nnMain";
	void *nn_main = (void*)SaltySDCore_FindSymbol(nn_main_symbol);
	void *new_main = (void*)&limeMain;

	if(nn_main == NULL) // No nnMain found (could be a non official title...)
	{
		SaltySD_printf("[SaltyLime - 0x%016lX] nnMain wasn't found - skipping injection...\n", appid);
	}
	else
	{
		SaltySDCore_ReplaceImport(nn_main_symbol, new_main);
		SaltySD_printf("[SaltyLime - 0x%016lX] Redirected nnMain from %p to %p!\n", appid, nn_main, new_main);
	}

	__libnx_exit(0);
}