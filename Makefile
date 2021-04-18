CXX= clang++
CXXFLAGS= -Weverything -Werror -Wno-error=padded -Wno-c++98-compat -Wno-error=reorder-ctor #-Wno-error=unused-parameter -Wno-error=unused-private-field

#You should make a test build system and have it set to zero there (set this as 2)
CXXOPTFLAG= -O0

BUILDDIR= ./Build
OFILES= $(BUILDDIR)/WindowHandler.o $(BUILDDIR)/SnakeEngine.o $(BUILDDIR)/Snake.o $(BUILDDIR)/Tile.o $(BUILDDIR)/SnakeEngineInterfaceController.o
HFILES= WindowHandler.hpp SnakeEngine.hpp Snake.hpp Tile.hpp SnakeEngineInterfaceController.hpp
EXE= $(BUILDDIR)/snakegonom

$(EXE): $(OFILES) snakegonom.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $? -o $@ -lncurses -ltinfo -lboost_system

$(BUILDDIR)/SnakeEngineInterfaceController.o: SnakeEngineInterfaceController.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/WindowHandler.o: WindowHandler.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/SnakeEngine.o: SnakeEngine.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/Tile.o: Tile.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/Snake.o: Snake.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

run: $(BUILDDIR)/snakegonom
	$?

clean:
	rm -f $(OFILES) $(EXE)