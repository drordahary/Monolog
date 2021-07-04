#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
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
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <slog.h>
#include <hiredis/hiredis.h>
#include "ExceptionsHandler.h"

#define REDIS_RX_DB 1

#define FILES_DIR "../files/"
#define UNTRACKED_DIR "../untracked"

extern bool exiting;