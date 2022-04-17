DRVVERSION=-DLEVEL=4 -DREVI=1 -DBUILD=1
ESD_CPPFLAGS += -DESDCAN_SPLIT_BUILD -DBOARD_pcie402
ESD_CPPFLAGS += -DOSIF_OS_LINUX $(DRVVERSION)
ESD_CPPFLAGS += -I$(src)
ESD_CPPFLAGS +=  -DMAJOR_LINUX=52  -DHOST_DRIVER=1 
ESD_CPPFLAGS += -DESDCAN_USES_STACKPROTECTOR
ESD_CPPFLAGS += $(shell if ( cat /proc/version | grep -i suse 2>&1 > /dev/null ); then echo -DDISTR_SUSE; fi;)
ifdef KBUILD_CPPFLAGS
  KBUILD_CPPFLAGS += $(ESD_CPPFLAGS)
  ifneq (,$(findstring -fstack-protector,$(KBUILD_CFLAGS)))
    KBUILD_CPPFLAGS += -DESDCAN_KERNEL_HAS_STACKPROTECTOR
  endif
# This is for debugging of possible build problems at the user site
  $(info "KBUILD_CPPFLAGS=$(KBUILD_CPPFLAGS)")
  $(info "KBUILD_CFLAGS=$(KBUILD_CFLAGS)")
else
  ifdef ccflags-y
    ccflags-y += $(ESD_CPPFLAGS)
  else
    CPPFLAGS += $(ESD_CPPFLAGS)
  endif
endif
obj-m += esdcan-pcie402.o
esdcan-pcie402-objs := esdcan.o osif.o nucleus.o baud.o esdacc.o esdlin.o board.o boardrc.o crc32.o irigb.o
