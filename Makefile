dirs := $(shell echo */)

.PHONY: all clean

all:
	$(foreach dir,$(dirs), ( cd $(dir); [ -f Makefile ] && make); )

clean:
	$(foreach dir,$(dirs), ( cd $(dir); [ -f Makefile ] && make clean); )

echo:
	echo $(Makefile)

