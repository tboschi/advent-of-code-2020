GO := go build

SRCDIR := src
TARGET := part1 part2

all: $(TARGET)

$(TARGET): % : $(SRCDIR)/%
	@cp $^ .

$(SRCDIR)/%: $(SRCDIR)/%.go
	$(GO) -o $@ $^

clean:
	$(RM) $(TARGET) $(addprefix $(SRCDIR)/,$(TARGET))

.PHONY: all clean
