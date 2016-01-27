dirs := $(shell echo */)

.PHONY: all clean

all:
	$(foreach dir,$(dirs), ( cd $(dir); [ -f Makefile ] && make || cd ..;) )

clean:
	$(foreach dir,$(dirs), ( cd $(dir); [ -f Makefile ] && make clean || cd ..;) )

echo:
	echo $(Makefile)

