CXX= clang++
CXXFLAGS= -Weverything -Werror

#You should make a test build system and have it set to zero there (set this as 2)
CXXOPTFLAG= -O0

BUILDDIR= ./Build
OFILES= $(BUILDDIR)/WindowHandler.o $(BUILDDIR)/SnakeEngine.o
HFILES= WindowHandler.hpp SnakeEngine.hpp
EXE= $(BUILDDIR)/snakegonom

$(EXE): $(OFILES) $(HFILES) snakegonom.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $? -o $@ -lncurses -ltinfo

$(BUILDDIR)/WindowHandler.o: WindowHandler.cpp WindowHandler.hpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/SnakeEngine.o: SnakeEngine.cpp SnakeEngine.hpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

run: $(BUILDDIR)/snakegonom
	$?

clean:
	rm -f $(OFILES) $(EXE)