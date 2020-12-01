TOPTARGETS := cpp go py clean
DAYS := $(shell find * -type d -name day*)

$(TOPTARGETS): $(DAYS)

$(DAYS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


.PHONY: $(TOPTRAGETS) $(DAYS) 
