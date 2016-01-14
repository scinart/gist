dirs = $(shell echo */)

.PHONY: all clean

all:
	$(foreach dir,$(dirs),cd $(dir); make;)

clean:
	$(foreach dir,$(dirs),cd $(dir); make clean;)