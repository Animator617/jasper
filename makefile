
# main makefile
#
#    @File:      makefile
#    @Author:    Animator617 (c)

# define useful directory path
TOP_DIR = $(PWD)
MKFILE_DIR = $(TOP_DIR)/sys-make
CFG_DIR = $(MKFILE_DIR)/config
OUTPUT_DIR = $(TOP_DIR)/output

# define useful prefix/postfix
LIB_PREFIX = lib
LIB_POSTFIX = a

# include build configuration
# FEATURE define in it
include $(CFG_DIR)/build.config

# export var, which need be known by sub-makefile
export TOP_DIR MKFILE_DIR OUTPUT_DIR
export LIB_PREFIX LIB_POSTFIX

all: obj link

obj:
	@$(MAKE) -f $(TOP_DIR)/brain/brain.mk
	@$(MAKE) -f $(TOP_DIR)/bot/bot.mk
	@$(MAKE) -f $(TOP_DIR)/python/python.mk
	@$(MAKE) -f $(TOP_DIR)/python_scripts/python_scripts.mk
	@$(MAKE) -f $(TOP_DIR)/protocol/protocol.mk
	@$(MAKE) -f $(TOP_DIR)/main/main.mk
	@$(MAKE) -f $(TOP_DIR)/src/src.mk
	@$(MAKE) -f $(TOP_DIR)/main.mk
	

# link workaround
# pass link to rules.mk to trigger link
link:
	@$(MAKE) -f $(MKFILE_DIR)/rules.mk link

# check
# to display each module build info
check:
	@$(MAKE) -f $(TOP_DIR)/brain/brain.mk check
	@$(MAKE) -f $(TOP_DIR)/bot/bot.mk check
	@$(MAKE) -f $(TOP_DIR)/python/python.mk check
	@$(MAKE) -f $(TOP_DIR)/python_scripts/python_scripts.mk check
	@$(MAKE) -f $(TOP_DIR)/protocol/protocol.mk check
	@$(MAKE) -f $(TOP_DIR)/main/main.mk check
	@$(MAKE) -f $(TOP_DIR)/src/src.mk check
	@$(MAKE) -f $(TOP_DIR)/main.mk check
	
# remove ouyput
clean:
	@$(MAKE) -f $(TOP_DIR)/brain/brain.mk clean
	@$(MAKE) -f $(TOP_DIR)/bot/bot.mk clean
	@$(MAKE) -f $(TOP_DIR)/python/python.mk clean
	@$(MAKE) -f $(TOP_DIR)/python_scripts/python_scripts.mk clean
	@$(MAKE) -f $(TOP_DIR)/protocol/protocol.mk clean
	@$(MAKE) -f $(TOP_DIR)/main/main.mk clean
	@$(MAKE) -f $(TOP_DIR)/src/src.mk clean
	@$(MAKE) -f $(TOP_DIR)/main.mk clean
	-rm -rf $(OUTPUT_DIR)
