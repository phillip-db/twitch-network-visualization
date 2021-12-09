# Executable names:
EXE = visualize
TEST = test

EXE_OBJ = main.o
OBJS = streamer.o CSVParser.o graph.o graph_visual.o utils.o main.o

include cs225/make/cs225.mk

CLEAN_RM += shortest_path test visualize bfs graph_vis.png graph_vis2.png

EXE2_OBJ = shortest_path.o

TMP_OBJ := $(OBJS)
OBJS = $(filter-out $(EXE_OBJ), $(TMP_OBJ))
OBJS += shortest_path.o

shortest_path: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

TMP_OBJ := $(OBJS)
OBJS = $(filter-out $(EXE2_OBJ), $(TMP_OBJ))
OBJS += bfs.o

bfs: $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@