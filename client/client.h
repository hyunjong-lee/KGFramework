#pragma once

class ClientCore;

void write_position(const boost::system::error_code& e, boost::asio::deadline_timer* t, ClientCore* client);
