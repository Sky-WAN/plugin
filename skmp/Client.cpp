#include "Client.h"
#include "easywsclient/easywsclient.cpp"

Client::Client(const std::string & url) {
	Client::ws = easywsclient::WebSocket::from_url(url);
	Client::ws->send("test");
}