DAYS := $(shell find * -type d -name day*)
DAYSCPP := $(patsubst %, %/cpp, $(DAYS))
DAYSGO := $(patsubst %, %/go, $(DAYS))

cpp: $(DAYSCPP)

py: $(DAYSPY)
	@echo "Don't need to compile python scripts :)"

go: #$(DAYSGO)
	@echo "Soon to be implemented..."


$(DAYSCPP):
	@echo "Compiling $@"
	$(MAKE) -C $@

clean: $(DAYS)

$(DAYS):
	$(MAKE) -C $@ clean


.PHONY: cpp py go $(DAYSCPP) $(DAYSGO) clean $(DAYS) 
