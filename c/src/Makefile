
CORE_DIRS = common soap wsdd server xml engine

DIRS = $(CORE_DIRS)

ALL_DIRS = $(DIRS)

all:
	@for dir in $(DIRS) ; do \
	( cd $$dir ; \
	$(MAKE) -q && { echo "$$dir up to date" ; } || \
	{ echo "Making $$dir" ; $(MAKE) -$(MAKEFLAGS) ; } ) ; done

clean:
	@ for dir in $(DIRS) ; do ( \
	cd $$dir ; echo "Cleaning `basename \`pwd\``" ; \
	$(MAKE) -$(MAKEFLAGS) clean ; ) ; done

