all:
	mkdir -p bin
	mkdir -p logs
	/usr/bin/g++ source/Main.cpp source/RedisHandler.cpp source/ExceptionsHandler.cpp source/Settings.cpp source/StartUp.cpp  -o bin/RX -lslog -pthread -lhiredis

clean:
	$(RM) -r bin/RX
	$(RM) -r logs/*.log