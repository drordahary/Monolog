#pragma once

#include <iostream>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <boost/algorithm/string/find.hpp>
#include <thread>
#include <signal.h>
#include <slog.h>
#include <hiredis/hiredis.h>
#include "ExceptionsHandler.h"
#include "DirectoryOrganizer.h"
#include "FileHandler.h"

#define STAGING_DIR "../staging/"
#define ARCHIVE_DIR "../archive/"

extern bool exiting;