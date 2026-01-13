all:
	g++ -std=c++17 main.cpp -o log_server

clean:
	rm -f log_server
