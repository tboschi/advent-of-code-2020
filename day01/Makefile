TOPTARGETS := cpp go py clean

cpp:
	@echo "Compiling C++"
	$(MAKE) -C cpp

py:
	@echo "Don't need to compile python scripts :)"

go:
	@echo "Compiling go"
	$(MAKE) -C go

clean:
	$(MAKE) -C cpp clean
	$(MAKE) -C go  clean

.PHONY: $(TOPTARGETS)
