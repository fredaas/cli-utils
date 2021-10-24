all : main

main :
	$(mkdir -p bin)
	$(MAKE) -C src
	$(shell cp src/cconv bin)
clean :
	$(MAKE) clean -C src
