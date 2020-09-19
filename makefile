
CC           = g++
LIBS         = -lraylib 
CFLAGS       = -g -rdynamic
PROGRAM_NAME = automata
CCFILES       = $(shell find src/ -type f -name '*.cc')
OFILES       = $(patsubst src/%.cc,bin/src/%.o,$(CCFILES))

vpath %.cc src
.PHONY: $(PROGRAM_NAME)

compileAndRun:
		@make -s clean
		@make -s $(PROGRAM_NAME)
		# @catchsegv ./bin/$(PROGRAM_NAME)
		@./bin/$(PROGRAM_NAME)

$(PROGRAM_NAME): $(OFILES)
		mkdir -p ./bin/
		$(CC) -g -rdynamic -o ./bin/$(PROGRAM_NAME) $(OFILES) -lraylib

bin/src/%.o: %.cc
		mkdir -p $(dir $@)
		$(CC) -g -rdynamic -c -o $@ $<

clean:
		rm -rf ./bin/