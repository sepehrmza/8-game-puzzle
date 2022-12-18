CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -O3 -c
LXXFLAGS = -std=c++2a -Ih -pthread -ltbb
OBJECTS =  ./obj/menu.o ./obj/matrix.o ./obj/dfs.o ./obj/BFS.o ./obj/Bidirectional.o ./obj/main.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS)
./obj/matrix.o: ./cpp/matrix.cpp
	$(CXX) $(CXXFLAGS) ./cpp/matrix.cpp -o ./obj/matrix.o
./obj/menu.o: ./cpp/menu.cpp
	$(CXX) $(CXXFLAGS) ./cpp/menu.cpp -o ./obj/menu.o
./obj/dfs.o: ./cpp/dfs.cpp
	$(CXX) $(CXXFLAGS) ./cpp/dfs.cpp -o ./obj/dfs.o
./obj/BFS.o: ./cpp/BFS.cpp
	$(CXX) $(CXXFLAGS) ./cpp/BFS.cpp -o ./obj/BFS.o
./obj/Bidirectional.o: ./cpp/Bidirectional.cpp
	$(CXX) $(CXXFLAGS) ./cpp/Bidirectional.cpp -o ./obj/Bidirectional.o
./obj/menu.o: ./cpp/menu.cpp 
	$(CXX) $(CXXFLAGS) ./cpp/menu.cpp -o ./obj/menu.o
./obj/main.o: ./cpp/main.cpp ./h/menu.h ./h/matrix.h ./h/dfs.h ./h/BFS.h ./h/Bidirectional.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)