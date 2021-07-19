all:
	mkdir -p bin
	mkdir -p logs
	mkdir -p staging
	mkdir -p archive
	/usr/bin/g++ source/*.cpp ntp/*.cpp -o bin/TX -lslog -pthread -lhiredis -lboost_system -lboost_filesystem -lboost_thread

clean:
	$(RM) -r bin/TX
	$(RM) -r logs/*.log
	$(RM) -r staging/*
	$(RM) -r archive/*