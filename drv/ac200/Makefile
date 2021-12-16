#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ac200
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/ac200
  SUBMENU:=Other modules
  DEPENDS:=
  TITLE:=Driver for AC200
  AUTOLOAD:=$(call AutoLoad,70,ac200-mfd)
  FILES:=$(PKG_BUILD_DIR)/ac200-mfd.ko \
		$(PKG_BUILD_DIR)/clk-pwm.ko \
		$(PKG_BUILD_DIR)/ac200-phy.ko
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(BUILDFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,ac200))
