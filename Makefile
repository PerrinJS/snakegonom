CXX=clang++
CXXFLAGS  =-Weverything -Werror -Wno-padded -Wno-c++98-compat -Wno-reorder-ctor
CXXFLAGS += -Wno-c++20-designator -Wno-error=weak-vtables #-Wno-error=unused-parameter -Wno-error=unused-private-field -Wno-error=switch #-Wno-error=unused-command-line-argument

#You should make a test build system and have it set to zero there (set this as 2)
CXXOPTFLAG=-O2

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
	$(CXX) $(CXXOPTFLAG) $^ -o $@ -lncurses -ltinfo -lboost_system

$(BUILDDIR)/snakegonom.o: snakegonom.cpp $(MAINDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $< -o $@

$(BUILDDIR)/SnakeEngineInterfaceController.o: SnakeEngineInterfaceController.cpp $(INTCONTDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $< -o $@

$(BUILDDIR)/WindowHandler.o: WindowHandler.cpp $(WINDHANDDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $< -o $@

$(BUILDDIR)/SnakeEngine.o: SnakeEngine.cpp $(SNEKENGDEP)
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $< -o $@

$(BUILDDIR)/Tile.o: Tile.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $< -o $@

$(BUILDDIR)/Snake.o: Snake.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $< -o $@

test: CXXFLAGS += -g -pg
test: CXXOPTFLAG=-O0
test: $(EXE)

run: $(BUILDDIR)/snakegonom
	$?

clean:
	rm -f $(OFILES) $(EXE)