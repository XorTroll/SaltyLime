
#pragma once
#include <lime/lime_Types.hpp>

namespace lime
{
	namespace err
	{
        typedef u64 ErrorCode;
    }
}

LIME_LINKNN(void _ZN2nn3err14SystemErrorArgC2Ev(LIME_THIS))
LIME_LINKNN(lime::Result _ZN2nn3err14SystemErrorArg16SetDialogMessageEPKc(LIME_THIS, const char *msg))
LIME_LINKNN(lime::Result _ZN2nn3err14SystemErrorArg20SetFullScreenMessageEPKc(LIME_THIS, const char *msg))

LIME_LINKNN(lime::Result _ZN2nn3err9ShowErrorENS_6ResultE(lime::Result res))
LIME_LINKNN(lime::Result _ZN2nn3err9ShowErrorENS0_9ErrorCodeE(lime::err::ErrorCode code))
LIME_LINKNN(lime::err::ErrorCode _ZN2nn3err13MakeErrorCodeEjj(u32 module, u32 description))
LIME_LINKNN(lime::Result _ZN2nn3err15ShowSystemErrorERKNS0_14SystemErrorArgE(void *arg))

namespace lime
{
	namespace err
	{
		LIME_MAKE_CLASS(SystemErrorArg, 0x1000, _ZN2nn3err14SystemErrorArgC2Ev, (void),
		
			public:
				Result SetDialogMessage(const char *msg)
				{
					LIME_RETURN_MEMBER(_ZN2nn3err14SystemErrorArg16SetDialogMessageEPKc, msg)
				}

				Result SetFullScreenMessage(const char *msg)
				{
					LIME_RETURN_MEMBER(_ZN2nn3err14SystemErrorArg20SetFullScreenMessageEPKc, msg)
				}
		)

		LIME_DEFINE(ShowError, _ZN2nn3err9ShowErrorENS_6ResultE)
        LIME_DEFINE(ShowErrorCode, _ZN2nn3err9ShowErrorENS0_9ErrorCodeE)
        LIME_DEFINE(MakeErrorCode, _ZN2nn3err13MakeErrorCodeEjj)
		LIME_DEFINE(ShowSystemError, _ZN2nn3err15ShowSystemErrorERKNS0_14SystemErrorArgE)
	}
}

#define LIME_LOG(fmt, ...) \
{ \
	lime::err::SystemErrorArg arg; \
	char shortmsg[0x800] = {0}; \
	sprintf(shortmsg, "SaltyLime runtime --- log message\n\n%s (line %d)", __PRETTY_FUNCTION__, __LINE__); \
	arg.SetDialogMessage(shortmsg); \
	char longmsg[0x800] = {0}; \
	sprintf(longmsg, fmt, ##__VA_ARGS__); \
	arg.SetFullScreenMessage(longmsg); \
	lime::err::ShowSystemError(arg); \
}
