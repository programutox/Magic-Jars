EXECUTABLE = MagicJars
CHECKS = -Wall -pedantic-errors
LIBS = -lraylib -lgdi32 -lwinmm
NO_CONSOLE = -Wl,-subsystem,windows
RAYLIB_INCLUDE_PATH = C:/raylib/include
RAYLIB_LIB_PATH = C:/raylib/lib

default:
	windres resources.rc resources.o
	g++ -std=c++2a -O3 -c ../src/*.cpp -I$(RAYLIB_INCLUDE_PATH) $(CHECKS)
	g++ -static ./*.o -o $(EXECUTABLE) -L$(RAYLIB_LIB_PATH) $(LIBS) $(NO_CONSOLE)
	del *.o