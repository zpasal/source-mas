#################################################################
## This Makefile Exported by MinGW Developer Studio
## Copyright (c) 2002-2004 by Parinya Thipchart
#################################################################

ifneq (,$(findstring Release, $(CFG)))
override CFG = Release
else
override CFG = Debug
endif

PROJECT = mas
CC = g++

ifeq ($(CFG),Debug)
	OBJ_DIR = 
	OUTPUT_DIR = 
	TARGET = mas
	C_INCLUDE_DIRS = 
	C_PREPROC = 
	CFLAGS = -pipe  -Wall -ggdb3 -O0 -frtti -fexceptions 
	RC_INCLUDE_DIRS = 
	RC_PREPROC =
	RCFLAGS = 
	LIB_DIRS = 
	LIBS = 
	LDFLAGS = -pipe 
endif

ifeq ($(CFG),Release)
	OBJ_DIR =  
	OUTPUT_DIR =  
	TARGET = mas
	C_INCLUDE_DIRS = 
	C_PREPROC = 
	CFLAGS = -pipe  -Wall -g0 -O2 -frtti -fexceptions
	RC_INCLUDE_DIRS = 
	RC_PREPROC = 
	RCFLAGS = 
	LIB_DIRS = 
	LIBS = 
	LDFLAGS = -pipe -s 
endif

ifeq ($(OS),Windows_NT)
	NULL =
else
	NULL = nul
endif

SRC_OBJS = \
	$(OBJ_DIR)/labels.o	\
	$(OBJ_DIR)/mas.o	\
	$(OBJ_DIR)/parser.o	\
	$(OBJ_DIR)/pass1.o	\
	$(OBJ_DIR)/config.o	\
	$(OBJ_DIR)/pass2.o	\
	$(OBJ_DIR)/objects.o

define build_target
	@echo Linking...
	@$(CC) -o "$(TARGET)" $(SRC_OBJS) $(LIB_DIRS) $(LIBS) $(LDFLAGS)
endef

define compile_source
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(C_PREPROC) $(C_INCLUDE_DIRS) -c "$<" -o "$@"
endef

.PHONY: print_header 

$(TARGET): print_header $(SRC_OBJS)
	$(build_target)

.PHONY: clean cleanall

cleanall:
	@echo Deleting intermediate files for 'mas - $(CFG)'
	-@rm *.o
	-@rm "$(TARGET)"
	-@rmdir "$(OUTPUT_DIR)"

clean:
	@echo Deleting intermediate files for 'mas - $(CFG)'
	-@rm *.o

print_header:
	@echo ----------Configuration: mas - $(CFG)----------


$(OBJ_DIR)/labels.o: labels.cpp	\
labels.h	\
tools/Lista.hpp
	$(compile_source)

$(OBJ_DIR)/mas.o: mas.cpp	\
tools/Lista.hpp	\
config.h	\
parser.h	\
mas.h	\
pass1.h	\
pass2.h	\
labels.h	\
objects.h
	$(compile_source)

$(OBJ_DIR)/parser.o: parser.cpp	\
mas.h	\
labels.h	\
tools/Lista.hpp	\
parser.h	\
config.h
	$(compile_source)

$(OBJ_DIR)/pass1.o: pass1.cpp	\
tools/Alati.hpp	\
labels.h	\
tools/Lista.hpp	\
parser.h	\
config.h	\
mas.h
	$(compile_source)

$(OBJ_DIR)/config.o: config.cpp	\
labels.h	\
tools/Lista.hpp	\
parser.h	\
mas.h	\
config.h
	$(compile_source)

$(OBJ_DIR)/pass2.o: pass2.cpp	\
tools/Alati.hpp	\
labels.h	\
tools/Lista.hpp	\
parser.h	\
pass1.h	\
mas.h	\
config.h	\
pass2.h
	$(compile_source)

$(OBJ_DIR)/objects.o: objects.cpp	\
config.h	\
parser.h	\
mas.h	\
pass1.h	\
pass2.h	\
labels.h	\
tools/Lista.hpp	\
objects.h
	$(compile_source)

