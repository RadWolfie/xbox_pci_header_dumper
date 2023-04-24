XBE_TITLE=PCI\ Header\ Dumper
SRCS = $(CURDIR)/src/main.c $(CURDIR)/src/output.c $(CURDIR)/src/lib/pci.c $(CURDIR)/src/lib/pci_database.c
include $(NXDK_DIR)/Makefile
