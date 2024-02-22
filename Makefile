SOURCE_FILES = Vector3D.cc main.cc

### CONFIG ###
EXE_NAME = Simulation

DEBUG_DIR =debug
RELEASE_DIR =release
TEST_DIR =tests

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -pedantic
DEBUG_CXXFLAGS = -g -O0 -DDEBUG
RELEASE_CXXFLAGS = -O3 -DNDEBUG

################
CXX=g++
OBJS=$(SOURCE_FILES:.cc=.o)

# Debug
DEBUG_OBJS = $(addprefix $(DEBUG_DIR)/, $(OBJS))
DEBUG_EXE = $(DEBUG_DIR)/$(EXE_NAME)


# Release
RELEASE_OBJS = $(addprefix $(RELEASE_DIR)/, $(OBJS))
RELEASE_EXE = $(RELEASE_DIR)/$(EXE_NAME)

# Testing
TEST_SRCS = $(SOURCE_FILES:.cc=.test.cc)
_TEST_OBJS = $(TEST_SRCS:.cc=.o)
TEST_OBJS = $(addprefix $(TEST_DIR)/, $(_TEST_OBJS)) $(addprefix $(TEST_DIR)/, $(OBJS))
TEST_EXE = $(TEST_DIR)/$(EXE_NAME)

.PHONY: debug test release
.PHONY: all clean prep remake

all: prep debug

## Debug
debug: $(DEBUG_EXE)
$(DEBUG_EXE): $(DEBUG_OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUG_CXXFLAGS) -o $(DEBUG_EXE) $^

$(DEBUG_DIR)/%.o: %.cc 
	$(CXX) $(CXXFLAGS) $(DEBUG_CXXFLAGS) -c $< -o $@

## Release
release: $(RELEASE_EXE)
$(RELEASE_EXE): $(RELEASE_OBJS)
	$(CXX) $(CXXFLAGS) $(RELEASE_CXXFLAGS) -o $(RELEASE_EXE) $^

$(RELEASE_DIR)/%.o: %.cc 
	$(CXX) $(CXXFLAGS) $(RELEASE_CXXFLAGS) -c $< -o $@

rep: 
	@mkdir -p $(DEBUG_DIR) $(TEST_DIR) $(RELEASE_DIR)

remake: clean all

clean:
	rm -f $(RELEASE_EXE) $(TEST_EXE) $(DEBUG_EXE) \
	$(RELEASE_OBJS) $(TEST_OBJS) $(DEBUG_OBJS)


