// server.cpp : Defines the entry point for the console application.
//

#include "serverpch.h"
#include "serverprocess.h"


int main(int argc, char* argv[])
{
	ServerProcess *serverProcess = new ServerProcess();
    serverProcess->run(argc, argv);
	return 0;
}
