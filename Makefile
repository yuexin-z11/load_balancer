CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
TARGET  := $(BINDIR)/loadbalancer

all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean out build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
