CXX=clang++
CXXFLAGS  =-Weverything -Werror -Wno-padded -Wno-c++98-compat -Wno-reorder-ctor
CXXFLAGS += -Wno-c++20-designator -Wno-error=weak-vtables #-Wno-error=unused-parameter -Wno-error=unused-private-field -Wno-error=switch #-Wno-error=unused-command-line-argument

CXXOPTFLAG=-O2
DEFINE=-DNDEBUG

BUILDDIR=./Build

OFILES  = $(BUILDDIR)/WindowHandler.o
OFILES += $(BUILDDIR)/SnakeEngine.o 
OFILES += $(BUILDDIR)/Snake.o 
OFILES += $(BUILDDIR)/Tile.o 
OFILES += $(BUILDDIR)/SnakeEngineInterfaceController.o 
OFILES += $(BUILDDIR)/snakegonom.o

HFILES  = WindowHandler.hpp
HFILES += SnakeEngine.hpp
HFILES += Snake.hpp
HFILES += Tile.hpp
HFILES += SnakeEngineInterfaceController.hpp

SNEKENGDEP = $(BUILDDIR)/Snake.o $(BUILDDIR)/Tile.o
WINHANDDEP = $(BUILDDIR)/SnakeEngine.o $(BUILDDIR)/Snake.o $(BUILDDIR)/Tile.o
MAINDEP = $(filter-out $(BUILDDIR)/snakegonom.o, $(OFILES))

INTCONTDEP  = $(BUILDDIR)/WindowHandler.o
INTCONTDEP += $(BUILDDIR)/SnakeEngine.o $(BUILDDIR)/Snake.o $(BUILDDIR)/Tile.o


EXE=$(BUILDDIR)/snakegonom

$(EXE): $(OFILES) 
	$(CXX) $(CXXOPTFLAG) $(DEFINE) $^ -o $@ -lncurses -ltinfo -lboost_system

$(BUILDDIR)/snakegonom.o: snakegonom.cpp $(MAINDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $(DEFINE) -c $< -o $@

$(BUILDDIR)/SnakeEngineInterfaceController.o: SnakeEngineInterfaceController.cpp $(INTCONTDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $(DEFINE) -c $< -o $@

$(BUILDDIR)/WindowHandler.o: WindowHandler.cpp $(WINDHANDDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $(DEFINE) -c $< -o $@

$(BUILDDIR)/SnakeEngine.o: SnakeEngine.cpp $(SNEKENGDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $(DEFINE) -c $< -o $@

$(BUILDDIR)/Tile.o: Tile.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $(DEFINE) -c $< -o $@

$(BUILDDIR)/Snake.o: Snake.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $(DEFINE) -c $< -o $@

test: CXXFLAGS += -g -pg
test: CXXOPTFLAG=-O0
test: DEFINE= #on a normal build we build with NDEBUG
test: $(EXE)

run: $(BUILDDIR)/snakegonom
	$?

clean:
	rm -f $(OFILES) $(EXE) compile_commands.json

