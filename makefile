# Compiler and flags
CC = gcc
CCFLAGS = -O2 -Wall -Wextra
LDFLAGS = -lraylib -lm

# Directories
SRCDIR = .
OBJDIR = obj
DATADIR = data

# Target executable
TARGET = game

# Source files
SOURCES = main.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Create the executable
$(TARGET): $(OBJECTS) | $(DATADIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DATADIR):
	mkdir -p $(DATADIR)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Clean everything including data directory
cleanall: clean
	rm -rf $(DATADIR)

# Rebuild everything
rebuild: clean all

# Install raylib (Ubuntu/Debian)
install-deps:
	sudo apt update
	sudo apt install libraylib-dev

# Run the game
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CCFLAGS += -g -DDEBUG -O0
debug: clean $(TARGET)

# Release build with maximum optimization
release: CCFLAGS = -O3 -Wall -Wextra -DNDEBUG
release: clean $(TARGET)

# Clean WebAssembly build files
clean-wasm:
	rm -f index.html index.js index.wasm index.data

# Initialize Raylib for WebAssembly (only if not already built)
init_wasm:
	@if [ ! -d "raylib_wasm/raylib/build/raylib" ]; then \
		echo "Building Raylib for WebAssembly..."; \
		rm -rf raylib_wasm; \
		mkdir -p raylib_wasm; \
		cd raylib_wasm && git clone https://github.com/raysan5/raylib.git; \
		cd raylib_wasm/raylib && mkdir -p build; \
		cd raylib_wasm/raylib/build && emcmake cmake ..; \
		cd raylib_wasm/raylib/build && emmake make -j$$(nproc); \
	else \
		echo "Raylib WASM already built, skipping..."; \
	fi

# WebAssembly build target
wasm: init_wasm clean-wasm
	emcc $(SOURCES) \
		-Iraylib_wasm/raylib/src \
		-Lraylib_wasm/raylib/build/raylib \
		-lraylib \
		-s USE_GLFW=3 -s USE_WEBGL2=1 \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s ASYNCIFY=1 \
		-s TOTAL_MEMORY=67108864 \
		--shell-file index_template.html \
		-o index.html

# Serve the WebAssembly build locally
serve-wasm: wasm
	@echo "Starting web server on http://localhost:8000"
	@which python3 >/dev/null 2>&1 && python3 -m http.server 8000 || python -m SimpleHTTPServer 8000

# Help
help:
	@echo "Available targets:"
	@echo "  all          - Build the game (default)"
	@echo "  clean        - Remove build files"
	@echo "  cleanall     - Remove build files and data directory"
	@echo "  rebuild      - Clean and build"
	@echo "  run          - Build and run the game"
	@echo "  debug        - Build with debug symbols"
	@echo "  release      - Build optimized release version"
	@echo "  init_wasm    - Initialize Raylib for WebAssembly"
	@echo "  wasm         - Build WebAssembly version"
	@echo "  clean-wasm   - Remove WebAssembly build files"
	@echo "  serve-wasm   - Build and serve WebAssembly version locally"
	@echo "  install-deps - Install raylib dependencies (Ubuntu/Debian)"
	@echo "  help         - Show this help message"

# Phony targets
.PHONY: all clean cleanall rebuild install-deps run debug release help wasm clean-wasm serve-wasm init_wasm
