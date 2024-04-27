####### MCU #######

## STC8H1K08 STC8H8K64U
MCU                 ?= STC8H1K08
MCU_IRAM            ?= 256
# 1024, 2048, 3072, 4096, 8192
MCU_XRAM            ?= 1024
# 8192, 16384, 32768, 65536
MCU_CODE_SIZE       ?= 8192

# ## STC8H1K08
# MCU                 ?= STC8H1K08
# MCU_IRAM            ?= 256
# MCU_XRAM            ?= 1024
# MCU_CODE_SIZE       ?= 8192

# ## STC8H8K64U
# MCU                 ?= STC8H8K64U
# MCU_IRAM            ?= 256
# MCU_XRAM            ?= 8192
# MCU_CODE_SIZE       ?= 65536

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


## STC8H1K08 36.864MHz
LIB_FLAGS           := __CONF_FOSC=36864000UL \
					__CONF_MCU_MODEL=MCU_MODEL_STC8H1K08 \
					__CONF_CLKDIV=0x00 \
					__CONF_IRCBAND=0x01 \
					__CONF_VRTRIM=0x1F \
					__CONF_IRTRIM=0xB5 \
					__CONF_LIRTRIM=0x00 

# ## STC8H8K64U 44.2368MHz
# LIB_FLAGS           := __CONF_FOSC=44236800UL \
#           __CONF_MCU_MODEL=MCU_MODEL_STC8H8K64U \
#           __CONF_CLKDIV=0x00 \
#           __CONF_IRCBAND=0x03 \
#           __CONF_VRTRIM=0x1B \
#           __CONF_IRTRIM=0xAC \
#           __CONF_LIRTRIM=0x01

# ## STC8H8K64U 36.864MHz  IRCBAND:83, VRTRIM:1B, IRTRIM:5E, LIRTRIM:A8
# LIB_FLAGS           := __CONF_FOSC=36864000UL \
#           __CONF_MCU_MODEL=MCU_MODEL_STC8H8K64U \
#           __CONF_CLKDIV=0x00 \
#           __CONF_IRCBAND=0x83 \
#           __CONF_VRTRIM=0x1B \
#           __CONF_IRTRIM=0x5E \
#           __CONF_LIRTRIM=0xA8

include ./rules.mk