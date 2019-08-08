#ifndef _MONO_MARSHAL_HOOKS_H_
#define _MONO_MARSHAL_HOOKS_H_

G_BEGIN_DECLS

typedef gpointer (*MonoStringToBstrFunc)(MonoString *string_obj);
typedef MonoString * (*MonoStringFromBstrFunc)(gpointer bstr);
typedef void (*MonoFreeBstrFunc)(gpointer str);

void 
mono_install_bstr_funcs (MonoStringToBstrFunc new_mono_string_to_bstr_pfunc,
			 MonoStringFromBstrFunc new_mono_string_from_bstr_pfunc,
			 MonoFreeBstrFunc new_mono_free_bstr_pfunc);

typedef void* (*MonoMarshalAllocHGlobalFunc)(int size, MonoError *error);
typedef gpointer (*MonoMarshalReAllocHGlobalFunc)(gpointer ptr, int size, MonoError *error);
typedef void (*MonoMarshalFreeHGlobalFunc)(void *ptr, MonoError *error);

void 
mono_install_alloc_hglobal_funcs (MonoMarshalAllocHGlobalFunc alloc_fprt,
				  MonoMarshalReAllocHGlobalFunc realloc_fptr,
				  MonoMarshalFreeHGlobalFunc free_fptr);

typedef void* (*MonoMarshalAllocCoTaskMemFunc)(int size, MonoError *error);
typedef gpointer (*MonoMarshalReAllocCoTaskMemFunc)(gpointer ptr, int size, MonoError *error);
typedef void (*MonoMarshalFreeCoTaskMemFunc)(void *ptr, MonoError *error);

void 
mono_install_alloc_cotaskmem_funcs (MonoMarshalAllocCoTaskMemFunc alloc_fprt,
				    MonoMarshalReAllocCoTaskMemFunc realloc_fptr,
				    MonoMarshalFreeCoTaskMemFunc free_fptr);

typedef mono_bstr (*MonoPtrToBstrFunc)(const gunichar2* ptr, int slen);

void
mono_install_ptr_to_bstr_funcs(MonoPtrToBstrFunc ptr_to_bstr_fptr);

G_END_DECLS

#endif

#ifndef _MONO_MARSHAL_HOOKS_H_
#define _MONO_MARSHAL_HOOKS_H_

G_BEGIN_DECLS

typedef gpointer (*MonoStringToBstrFunc)(MonoString *string_obj);
typedef MonoString * (*MonoStringFromBstrFunc)(gpointer bstr);
typedef void (*MonoFreeBstrFunc)(gpointer str);

void 
mono_install_bstr_funcs (MonoStringToBstrFunc new_mono_string_to_bstr_pfunc,
			 MonoStringFromBstrFunc new_mono_string_from_bstr_pfunc,
			 MonoFreeBstrFunc new_mono_free_bstr_pfunc);

typedef void* (*MonoMarshalAllocHGlobalFunc)(int size, MonoError *error);
typedef gpointer (*MonoMarshalReAllocHGlobalFunc)(gpointer ptr, int size, MonoError *error);
typedef void (*MonoMarshalFreeHGlobalFunc)(void *ptr, MonoError *error);

void 
mono_install_alloc_hglobal_funcs (MonoMarshalAllocHGlobalFunc alloc_fprt,
				  MonoMarshalReAllocHGlobalFunc realloc_fptr,
				  MonoMarshalFreeHGlobalFunc free_fptr);

typedef void* (*MonoMarshalAllocCoTaskMemFunc)(int size, MonoError *error);
typedef gpointer (*MonoMarshalReAllocCoTaskMemFunc)(gpointer ptr, int size, MonoError *error);
typedef void (*MonoMarshalFreeCoTaskMemFunc)(void *ptr, MonoError *error);

void 
mono_install_alloc_cotaskmem_funcs (MonoMarshalAllocCoTaskMemFunc alloc_fprt,
				    MonoMarshalReAllocCoTaskMemFunc realloc_fptr,
				    MonoMarshalFreeCoTaskMemFunc free_fptr);

G_END_DECLS

#endif

