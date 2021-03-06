#ifndef __MONO_MINI_ARM_H__
#define __MONO_MINI_ARM_H__

#include <mono/arch/arm/arm-codegen.h>
#include <mono/utils/mono-context.h>
#include <glib.h>

#if defined(ARM_FPU_NONE) || (defined(__ARM_EABI__) && !defined(ARM_FPU_VFP))
#define MONO_ARCH_SOFT_FLOAT 1
#endif

#if defined(__ARM_EABI__)
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
#define ARM_ARCHITECTURE "armel"
#else
#define ARM_ARCHITECTURE "armeb"
#endif
#else
#define ARM_ARCHITECTURE "arm"
#endif

#if defined(ARM_FPU_FPA)
#define ARM_FP_MODEL "fpa"
#elif defined(ARM_FPU_VFP)
#define ARM_FP_MODEL "vfp"
#elif defined(ARM_FPU_NONE)
#define ARM_FP_MODEL "soft-float"
#else
#error "At least one of ARM_FPU_NONE or ARM_FPU_FPA or ARM_FPU_VFP must be defined."
#endif

#define MONO_ARCH_ARCHITECTURE ARM_ARCHITECTURE "," ARM_FP_MODEL

#define MONO_ARCH_CPU_SPEC arm_cpu_desc

#if G_BYTE_ORDER == G_LITTLE_ENDIAN
#define ARM_LSW_REG ARMREG_R0
#define ARM_MSW_REG ARMREG_R1
#else
#define ARM_LSW_REG ARMREG_R1
#define ARM_MSW_REG ARMREG_R0
#endif

#define MONO_MAX_IREGS 16
#define MONO_MAX_FREGS 16

#define MONO_SAVED_GREGS 10 /* r4-r11, ip, lr */
#define MONO_SAVED_FREGS 8

/* r4-r11, ip, lr: registers saved in the LMF  */
#define MONO_ARM_REGSAVE_MASK 0x5ff0
#define MONO_ARM_FIRST_SAVED_REG ARMREG_R4
#define MONO_ARM_NUM_SAVED_REGS 10

/* Parameters used by the register allocator */

#define MONO_ARCH_CALLEE_REGS ((1<<ARMREG_R0) | (1<<ARMREG_R1) | (1<<ARMREG_R2) | (1<<ARMREG_R3) | (1<<ARMREG_IP))
#define MONO_ARCH_CALLEE_SAVED_REGS ((1<<ARMREG_V1) | (1<<ARMREG_V2) | (1<<ARMREG_V3) | (1<<ARMREG_V4) | (1<<ARMREG_V5) | (1<<ARMREG_V6) | (1<<ARMREG_V7))

#ifdef ARM_FPU_VFP
/* Every double precision vfp register, d0/d1 is reserved for a scratch reg */
#define MONO_ARCH_CALLEE_FREGS 0x55555550
#else
#define MONO_ARCH_CALLEE_FREGS 0xf
#endif
#define MONO_ARCH_CALLEE_SAVED_FREGS 0

#define MONO_ARCH_USE_FPSTACK FALSE
#define MONO_ARCH_FPSTACK_SIZE 0

#define MONO_ARCH_INST_SREG2_MASK(ins) (0)

#ifdef MONO_ARCH_SOFT_FLOAT
#define MONO_ARCH_INST_FIXED_REG(desc) (((desc) == 'l' || (desc == 'f') || (desc == 'g')) ? ARM_LSW_REG: (((desc) == 'a') ? ARMREG_R0 : -1))
#define MONO_ARCH_INST_IS_REGPAIR(desc) ((desc) == 'l' || (desc) == 'L' || (desc) == 'f' || (desc) == 'g')
#define MONO_ARCH_INST_IS_FLOAT(desc) (FALSE)
#else
#define MONO_ARCH_INST_FIXED_REG(desc) (((desc) == 'l')? ARM_LSW_REG: (((desc) == 'a') ? ARMREG_R0 : -1))
#define MONO_ARCH_INST_IS_REGPAIR(desc) (desc == 'l' || desc == 'L')
#define MONO_ARCH_INST_IS_FLOAT(desc) ((desc == 'f') || (desc == 'g'))
#endif
#define MONO_ARCH_INST_REGPAIR_REG2(desc,hreg1) (desc == 'l'  || (desc == 'f') || (desc == 'g')? ARM_MSW_REG : -1)

#define MONO_ARCH_FRAME_ALIGNMENT 8

/* fixme: align to 16byte instead of 32byte (we align to 32byte to get 
 * reproduceable results for benchmarks */
#define MONO_ARCH_CODE_ALIGNMENT 32

void arm_patch (guchar *code, const guchar *target);
guint8* mono_arm_emit_load_imm (guint8 *code, int dreg, guint32 val);
int mono_arm_is_rotated_imm8 (guint32 val, gint *rot_amount);

void
mono_arm_throw_exception_by_token (guint32 type_token, unsigned long eip, unsigned long esp, gulong *int_regs, gdouble *fp_regs);

/* keep the size of the structure a multiple of 8 */
struct MonoLMF {
	/* 
	 * If the second lowest bit is set to 1, then this is a MonoLMFExt structure, and
	 * the other fields are not valid.
	 */
	gpointer    previous_lmf;
	gpointer    lmf_addr;
	/* This is only set in trampoline LMF frames */
	MonoMethod *method;
	gulong     esp;
	gulong     eip;
	/* all but sp and pc: matches the PUSH instruction layout in the trampolines
	 * 0-4 should be considered undefined (execpt in the magic tramp)
	 * sp is saved at IP.
	 */
	gulong     iregs [14];
};

typedef struct MonoCompileArch {
	gpointer seq_point_info_var, ss_trigger_page_var;
	gboolean omit_fp, omit_fp_computed;
	gpointer cinfo;
} MonoCompileArch;

#define MONO_ARCH_EMULATE_FCONV_TO_I8 1
#define MONO_ARCH_EMULATE_LCONV_TO_R8 1
#define MONO_ARCH_EMULATE_LCONV_TO_R4 1
#define MONO_ARCH_EMULATE_LCONV_TO_R8_UN 1
#define MONO_ARCH_EMULATE_FREM 1
#define MONO_ARCH_EMULATE_DIV 1
#define MONO_ARCH_EMULATE_CONV_R8_UN 1
#define MONO_ARCH_EMULATE_MUL_OVF 1
//#define MONO_ARCH_BIGMUL_INTRINS 1

#define ARM_FIRST_ARG_REG 0
#define ARM_LAST_ARG_REG 3

#define MONO_ARCH_USE_SIGACTION 1
#define MONO_ARCH_NEED_DIV_CHECK 1

#define MONO_ARCH_HAVE_CREATE_DELEGATE_TRAMPOLINE
#define MONO_ARCH_HAVE_XP_UNWIND 1
#define MONO_ARCH_HAVE_GENERALIZED_IMT_THUNK 1

#define ARM_NUM_REG_ARGS (ARM_LAST_ARG_REG-ARM_FIRST_ARG_REG+1)
#define ARM_NUM_REG_FPARGS 0

#define MONO_ARCH_HAVE_FULL_AOT_TRAMPOLINES 1
#define MONO_ARCH_HAVE_IMT 1
#define MONO_ARCH_HAVE_STATIC_RGCTX_TRAMPOLINE 1
#define MONO_ARCH_HAVE_DECOMPOSE_LONG_OPTS 1

#define MONO_ARCH_AOT_SUPPORTED 1
#define MONO_ARCH_LLVM_SUPPORTED 1
#define MONO_ARCH_THIS_AS_FIRST_ARG 1

#define MONO_ARCH_GSHARED_SUPPORTED 1
#define MONO_ARCH_DYN_CALL_SUPPORTED 1
#define MONO_ARCH_DYN_CALL_PARAM_AREA 24

#define MONO_ARCH_SOFT_DEBUG_SUPPORTED 1
#define MONO_ARCH_HAVE_EXCEPTIONS_INIT 1
#define MONO_ARCH_HAVE_GET_TRAMPOLINES 1

/* Matches the HAVE_AEABI_READ_TP define in mini-arm.c */
#if defined(__ARM_EABI__) && defined(__linux__) && !defined(PLATFORM_ANDROID)
#define MONO_ARCH_HAVE_TLS_GET 1
#endif

/* ARM doesn't have too many registers, so we have to use a callee saved one */
#define MONO_ARCH_RGCTX_REG ARMREG_V5
/* First argument reg */
#define MONO_ARCH_VTABLE_REG ARMREG_R0

#define MONO_CONTEXT_SET_LLVM_EXC_REG(ctx, exc) do { (ctx)->regs [0] = (gsize)exc; } while (0)

#define MONO_INIT_CONTEXT_FROM_FUNC(ctx,func) do {	\
		MONO_CONTEXT_SET_BP ((ctx), __builtin_frame_address (0));	\
		MONO_CONTEXT_SET_SP ((ctx), __builtin_frame_address (0));	\
		MONO_CONTEXT_SET_IP ((ctx), (func));	\
	} while (0)

#define MONO_ARCH_INIT_TOP_LMF_ENTRY(lmf)

void
mono_arm_throw_exception (MonoObject *exc, unsigned long eip, unsigned long esp, gulong *int_regs, gdouble *fp_regs);

void
mono_arm_throw_exception_by_token (guint32 type_token, unsigned long eip, unsigned long esp, gulong *int_regs, gdouble *fp_regs);

void
mono_arm_resume_unwind (guint32 dummy1, unsigned long eip, unsigned long esp, gulong *int_regs, gdouble *fp_regs);

gboolean
mono_arm_thumb_supported (void);

GSList*
mono_arm_get_exception_trampolines (gboolean aot) MONO_INTERNAL;

guint8*
mono_arm_get_thumb_plt_entry (guint8 *code) MONO_INTERNAL;

#endif /* __MONO_MINI_ARM_H__ */

