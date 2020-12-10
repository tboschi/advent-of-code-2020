SRCDIR := src
TARGET := part1 part2

all: $(TARGET)

$(TARGET): % : $(SRCDIR)/%
	@cp $^ .

clean:
	$(RM) $(TARGET) $(addprefix $(SRCDIR)/,$(TARGET))

.PHONY: all clean
