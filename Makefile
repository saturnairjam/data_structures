# compiler & linker
CC = g++
LD = $(CC)

# paths
PATH_SRC = src
PATH_OUT = out

# compiler & linker flags
CFLAGS  = -Wall -Wextra -Werror -g
LDFLAGS =

# source files
SOURCES = $(shell find $(PATH_SRC)/ -name '*.cpp')

# object files
OBJECTS = $(SOURCES:$(PATH_SRC)/%.cpp=$(PATH_OUT)/%.o)

# dependency files
DEPENDENCIES = $(OBJECTS:.o=.d)

# test binary
BIN_TEST = test.exe

# main rule
all: create_out_dir $(BIN_TEST)

$(BIN_TEST): $(OBJECTS)
	@echo "[LD]" $(notdir $(BIN_TEST)) "<=" $(notdir $(OBJECTS))
	@$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

# create out directory
.PHONY: create_out_dir
create_out_dir:
	@mkdir -p $(PATH_OUT)/

# clean
.PHONY: clean
clean:
	@rm -rfv $(PATH_OUT)
	@rm -rfv $(BIN_TEST)

# pattern rule: .cpp -> .o
$(PATH_OUT)/%.o: $(PATH_SRC)/%.cpp
	@echo "[CC]" $(notdir $<)
	@$(CC) -MP -MMD -c $(CFLAGS) $< -o $@

# include dependency files
-include $(DEPENDENCIES)