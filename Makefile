####### MCU #######

MCU                 ?= STC8H1K08
MCU_IRAM            ?= 256
MCU_XRAM            ?= 1024
MCU_CODE_SIZE       ?= 8192

##### Project #####

PROJECT             ?= app
# The path for generated files
BUILD_DIR           = build

TOOCHAIN_PREFIX     ?= /opt/sdcc/sdcc-4.3.0/bin/

# C source folders
USER_CDIRS          := user
# C source single files
USER_CFILES         := 
USER_INCLUDES       := user

LIB_FLAGS           := __CONF_FOSC=36864000UL \
					__CONF_MCU_MODEL=MCU_MODEL_STC8H1K08 \
					__CONF_CLKDIV=0x00 \
					__CONF_IRCBAND=0x01 \
					__CONF_VRTRIM=0x1F \
					__CONF_IRTRIM=0xB5 \
					__CONF_LIRTRIM=0x00 

include ./rules.mk