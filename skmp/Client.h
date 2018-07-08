#pragma once

#include "easywsclient/easywsclient.hpp"

class Client
{
	easywsclient::WebSocket::pointer ws;
public:
	Client::Client(const std::string & url);
};

