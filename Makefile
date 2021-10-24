all : main

main :
	@$(MAKE) -C src
	$(mkdir -p bin)
	$(shell cp src/cconv bin)
clean :
	@$(MAKE) clean -C src
