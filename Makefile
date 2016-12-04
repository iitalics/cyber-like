target=./cyb

bin: $(target)
all: makefiles $(target)

# linker
LD=clang++
LDFLAGS=-O2

# makefiles
PYTHON=python2
.PHONY: makefiles
makefiles:
	$(PYTHON) gen-makefiles.py

# global compiler flags
SRC_DIR=$(shell pwd)/src
export SRC_DIR

# libraries
-include libs.make

# target
$(target): $(libs)
	$(LD) $(LDFLAGS) -o $(target) $(libs)
	@echo -e "Linked \x1b[37;1m$@\x1b[0m"

# clean
.PHONY: clean
clean: clean-libs
	rm -f $(target)

