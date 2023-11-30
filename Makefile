.PHONY: src

all: src

debug:
	$(MAKE) debug -C src


src:
	$(MAKE) -C src

install:
	$(MAKE) -C src install

clean:
	$(MAKE) -C src clean

sst:
	$(MAKE) -C src
	$(MAKE) -C src install
	sst pizzaProj.py