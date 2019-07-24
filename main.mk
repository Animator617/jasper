## this is the makefile for the main.cpp
#
#    @File:      main.mk
#    @Author:    Animator617 (c)

# define module name for compile use
MODULE = main

# define expected lib
MOD_LIB = $(LIB_PREFIX)$(MODULE).$(LIB_POSTFIX)


CC_DEFS :=
# modify sys-make/config/build.config to control 
ifeq '$(filter FEATURE_1, $(FEATURE))' 'FEATURE_1'
	CC_DEFS += dir1_DEF_1
	CC_DEFS += dir1_DEF_2
	CC_DEFS += dir1_DEF_3
endif

# add srouce files, which would like to compile
SRC_FILES =
SRC_FILES += main.cpp
#SRC_FILES += b1.c

# modify sys-make/config/build.config to control 
ifeq '$(filter FEATURE_1, $(FEATURE))' 'FEATURE_1'
	SRC_FILES += c1.c
endif

# add include search path
INC_PATH =
INC_PATH += $(TOP_DIR)/common

# add source file search path together with vpath
SRC_PATH =
SRC_PATH += $(TOP_DIR)/$(MODULE)
SRC_PATH += $(TOP_DIR)/$(MODULE)/sub_dir1

vpath %.c $(SRC_PATH)

# use general compiler and compile rules
include $(MKFILE_DIR)/gcc.mk
include $(MKFILE_DIR)/rules.mk
