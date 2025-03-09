all:
	g++ -std=c++20 -O3 src/attacks.cpp src/position.cpp src/magics.cpp src/movegen.cpp src/perft.cpp src/uci.cpp src/main.cpp -o volta
