all:
	mkdir -p bin
	mkdir -p logs
	/usr/bin/g++ source/Main.cpp -o bin/TX -lslog -pthread

clean:
	$(RM) -r bin/TX
	$(RM) -r logs/*.log