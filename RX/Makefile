all:
	mkdir -p bin
	mkdir -p logs
	/usr/bin/g++ source/*.cpp -o bin/RX -lslog -pthread -lhiredis -lboost_system -lboost_thread

clean:
	$(RM) -r bin/RX
	$(RM) -r logs/*.log