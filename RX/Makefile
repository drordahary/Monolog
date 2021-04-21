all:
	mkdir -p bin
	mkdir -p logs
	/usr/bin/g++ source/Main.cpp -o bin/RX -lslog -pthread

clean:
	$(RM) -r bin/RX
	$(RM) -r logs/*.log