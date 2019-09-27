PROJECT_NAME := example-lua-vfs

EXTRA_COMPONENT_DIRS := $(CURDIR)/../..

include $(IDF_PATH)/make/project.mk

SPIFFS_IMAGE_FLASH_IN_PROJECT := 1
$(eval $(call spiffs_create_partition_image,storage,spiffs_image))
