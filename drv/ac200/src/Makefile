# $Id$
#
# Makefile 
#
# Copyright (C) 2007 Andreas Engel
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version
# 2 of the License, or (at your option) any later version.
#

obj-m		+= clk-pwm.o

#CONFIG_MFD_AC200
obj-m		+= ac200-mfd.o
#CONFIG_AC200_PHY
obj-m		+= ac200-phy.o


ifeq ($(MAKING_MODULES),1)

-include $(TOPDIR)/Rules.make
endif
