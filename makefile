chess: clean
	cd clcp && $(MAKE)
	cd clcp && mv game ../.

#! Only works if GTest is set up
all: clean
	cd clcp && $(MAKE) all
	cd clcp && mv game ../.

clean:
	rm -f game
	cd clcp && $(MAKE) clean