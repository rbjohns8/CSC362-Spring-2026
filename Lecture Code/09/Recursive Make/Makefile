# Root Makefile (project/Makefile)

.PHONY: all clean

all:
	$(MAKE) -C lib        # Build library files
	$(MAKE) -C src        # Build source files and link with library

clean:
	$(MAKE) -C lib clean  # Clean lib directory
	$(MAKE) -C src clean  # Clean src directory
