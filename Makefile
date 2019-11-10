BUILD_DIR := "./build"
# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
CPP_SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(CPP_SRCS))

HPP_SRCS := $(wildcard *.hpp)

CC := g++

# Linux (default)
EXE = $(BUILD)/contour
LDFLAGS = -lGL -lGLU -lglut

# Windows (cygwin)
ifeq ($(OS), "Windows_NT")
	EXE = $(BUILD)/$(EXE).exe
	LDFLAGS = -lopengl32 -lglu32 -lglut32
endif

# OS X
ifeq "$(shell uname)" "Darwin"
	LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
endif

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(HPP_SRCS)

clean:
	rm -rf $(TARGET) $(OBJS)

.PHONY: all clean