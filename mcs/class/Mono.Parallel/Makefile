thisdir = class/Mono.Parallel
SUBDIRS = 
include ../../build/rules.make

LIBRARY = Mono.Parallel.dll

include ../../build/library.make

LIB_MCS_FLAGS += -d:INSIDE_MONO_PARALLEL -r:$(corlib) -r:System.Core.dll -r:System.dll
