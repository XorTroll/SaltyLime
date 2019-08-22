
#pragma once

#define LIME_LINKNN(...) \
extern "C" \
{ \
    extern __VA_ARGS__ __attribute__((weak)); \
}

#define LIME_DEFINE(name, externc) const auto &name = externc;

#define LIME_CALL_MEMBER(externc, ...) externc(__inner_ptr, __VA_ARGS__);
#define LIME_RETURN_MEMBER(externc, ...) return LIME_CALL_MEMBER(externc, __VA_ARGS__)

#define LIME_THIS void *self

#define LIME_MAKE_CLASS(name, size, externc_ctor, externc_dtor, ...) \
class name \
{ \
	static constexpr size_t Size = size; \
	public: \
		name() \
		{ \
			__inner_ptr = operator new(Size); \
			externc_ctor(__inner_ptr); \
		} \
		~name() \
		{ \
			externc_dtor(__inner_ptr); \
			operator delete(__inner_ptr); \
		} \
        operator void*() \
        { \
            return __inner_ptr; \
        } \
	private: \
		void *__inner_ptr; \
	__VA_ARGS__ \
};
