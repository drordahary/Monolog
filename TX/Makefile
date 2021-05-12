all:
	mkdir -p bin
	mkdir -p logs
	mkdir -p staging
	mkdir -p archive
	/usr/bin/g++ source/Main.cpp source/RedisHandler.cpp source/ExceptionsHandler.cpp source/Group.cpp source/DataWorker.cpp source/MetadataWorker.cpp source/DataWorkerPool.cpp source/GroupFactory.cpp source/Settings.cpp source/StartUp.cpp source/DirectoryReader.cpp source/DirectoryOrganizer.cpp -o bin/TX -lslog -pthread -lhiredis -lboost_system -lboost_filesystem -lboost_thread

clean:
	$(RM) -r bin/TX
	$(RM) -r logs/*.log
	$(RM) -r staging/*
	$(RM) -r archive/*