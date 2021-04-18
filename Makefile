CXX= clang++
CXXFLAGS= -Weverything -Werror -Wno-error=padded -Wno-error=c++98-compat #-Wno-error=unused-parameter -Wno-error=unused-private-field

#You should make a test build system and have it set to zero there (set this as 2)
CXXOPTFLAG= -O0

BUILDDIR= ./Build
OFILES= $(BUILDDIR)/WindowHandler.o $(BUILDDIR)/SnakeEngine.o $(BUILDDIR)/Snake.o
HFILES= WindowHandler.hpp SnakeEngine.hpp Snake.hpp
EXE= $(BUILDDIR)/snakegonom

$(EXE): $(OFILES) snakegonom.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $? -o $@ -lncurses -ltinfo

$(BUILDDIR)/WindowHandler.o: WindowHandler.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/SnakeEngine.o: SnakeEngine.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

$(BUILDDIR)/Snake.o: Snake.cpp 
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

run: $(BUILDDIR)/snakegonom
	$?

clean:
	rm -f $(OFILES) $(EXE)