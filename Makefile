TARGET ?= Pac-Man
SRC_DIRS ?= ./Sources

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP `pkg-config --cflags gtk+-3.0` -lm -g 
LDLIBS= `pkg-config --libs gtk+-3.0` -MMD -g -lm 

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

help:
	@echo "Usage: {Action}[_{Target}]"
	@echo ""
	@echo "if no {Target} is specify apply {Action} to all {Target}"
	@echo ""
	@echo "Action: "
	@echo "- help: show this help"
	@echo "- clean: remove all the bin and object files"
	@echo "- : build the project"

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) $(shell find $(SRC_DIRS) -name *.gch)

-include $(DEPS)
