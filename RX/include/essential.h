#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <thread>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <slog.h>
#include <hiredis/hiredis.h>
#include "ExceptionsHandler.h"

extern bool exiting;