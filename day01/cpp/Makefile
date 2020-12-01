SRCDIR := src
TARGET := part1 part2

BUILD  := $(patsubst %, $(SRCDIR)/%, $(TARGET))

all: $(TARGET)

$(TARGET): $(BUILD)
	@cp $^ .

$(SRCDIR)/%: $(SRCDIR)/%.cpp

clean:
	$(RM) $(TARGET) $(BUILD)

.PHONY: all clean
