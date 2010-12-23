#pragma once

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <list>
#include <set>
#include <vector>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/unordered_map.hpp>

class ServerInterface
{
public:
    virtual void update_data_from_client(const std::vector<double>& pos, const int id) = 0;
    virtual void leave_client(unsigned int playerId) = 0;
};

typedef boost::shared_ptr<ServerInterface> server_interface_ptr;
