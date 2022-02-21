#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=sr9700-jl
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/sr9700-jl
  SUBMENU:=Other modules
  DEPENDS:= +kmod-usb-net
  TITLE:=Driver for KY-RD9700 USB ethernet devices
  AUTOLOAD:=$(call AutoLoad,70,sr9700_ml)
  FILES:=$(PKG_BUILD_DIR)/sr9700_ml.ko \
		$(PKG_BUILD_DIR)/sr9700.ko
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(BUILDFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,sr9700-jl))
