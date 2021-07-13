all:
	mkdir -p bin
	mkdir -p logs
	mkdir -p files
	mkdir -p untracked
	/usr/bin/g++ source/*.cpp -o bin/RX -lslog -pthread -lhiredis -levent -lboost_system -lboost_thread

clean:
	$(RM) -r bin/RX
	$(RM) -r logs/*.log
	$(RM) -r files/*
	$(RM) -r untracked/*