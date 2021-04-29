all:
	mkdir -p bin
	mkdir -p logs
	/usr/bin/g++ source/Main.cpp source/RedisHandler.cpp source/ExceptionsHandler.cpp source/Settings.cpp source/StartUp.cpp source/Group.cpp source/GroupFactory.cpp source/Ports.cpp source/Receivers.cpp  -o bin/RX -lslog -pthread -lhiredis

clean:
	$(RM) -r bin/RX
	$(RM) -r logs/*.log