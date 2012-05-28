#include <iostream>

#include <ROTMG/Encryption/Encryption.hpp>
#include <ROTMG/Proxy/Proxy2.hpp>

int main(int _argc, char** _argv) {
	
	// Start the proxy
	rotmg::Proxy proxy;
	proxy.SetServerIp("176.34.240.11");
	proxy.Start();
	proxy.Wait();
}