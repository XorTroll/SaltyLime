
#pragma once
#include <libsalt/salt_Types.hpp>

namespace salt
{
	namespace err
	{
        typedef u64 ErrorCode;
    }
}

SALT_LINKNN(salt::Result _ZN2nn3err9ShowErrorENS_6ResultE(salt::Result res))
SALT_LINKNN(salt::Result _ZN2nn3err9ShowErrorENS0_9ErrorCodeE(salt::err::ErrorCode code))
SALT_LINKNN(salt::err::ErrorCode _ZN2nn3err13MakeErrorCodeEjj(u32 module, u32 description))

namespace salt
{
	namespace err
	{
		SALT_DEFINE(ShowError, _ZN2nn3err9ShowErrorENS_6ResultE)
        SALT_DEFINE(ShowErrorCode, _ZN2nn3err9ShowErrorENS0_9ErrorCodeE)
        SALT_DEFINE(MakeErrorCode, _ZN2nn3err13MakeErrorCodeEjj)
	}
}