# Detect the operating system
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # Call the Linux Makefile
    include Makefile.linux
else ifeq ($(UNAME_S),Windows_NT)
    # Call the Windows Makefile
    include Makefile.windows
else
    # Unsupported operating system
    $(error Unsupported operating system: $(UNAME_S))
endif

