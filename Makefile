# Executable names:
EXE = main
TEST = test

EXE_OBJ = main.o
OBJS = streamer.o CSVParser.o graph.o graph_visual.o main.o

include cs225/make/cs225.mk

TMP_OBJ := $(OBJS)
OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
OBJS += shortest_path.o

shortest_path: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@