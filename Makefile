CXX= clang++
CXXFLAGS= -Wall -Wextra -Wpedantic -Wdeprecated -Wcomment -Wdiv-by-zero -Wshadow -Wunused -Wcomma -Werror

#You should make a test build system and have it set to zero there (set this as 2)
CXXOPTFLAG= -O0

BUILDDIR= ./Build
OFILES= $(BUILDDIR)/WindowHandler.o
HFILES= WindowHandler.hpp
EXE= $(BUILDDIR)/snakegonom

$(EXE): $(OFILES) snakegonom.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) $? -o $@ -lncurses -ltinfo

$(BUILDDIR)/WindowHandler.o: WindowHandler.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAG) -c $? -o $@

run: $(BUILDDIR)/snakegonom
	$?

clean:
	rm -f $(OFILES) $(EXE)