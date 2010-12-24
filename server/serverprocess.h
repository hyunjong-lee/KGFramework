#pragma once

#include "serverpch.h"
#pragma once

#include "servercore.hpp"


class ServerProcess : KGFProcess
{
public:
	ServerProcess();
	~ServerProcess(void);

    int run(int argc, char *argv[]);

private:
    void write_position(const boost::system::error_code& e, boost::asio::deadline_timer* t);

    server_ptr  server_ptr_;
};
