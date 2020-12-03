TOPTARGETS := cpp go py clean
DAYS := $(wildcard day*)

$(TOPTARGETS): $(DAYS)

$(DAYS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


.PHONY: $(TOPTRAGETS) $(DAYS) 
