#include "pch.h"
#include "CppUnitTest.h"
//#include "..\StaticLibmDNS\mDNSlib.h"
#include "..\mdns.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#pragma comment(lib, "Ws2_32.lib")  // important winsocket dependencies

// Link with Iphlpapi.lib
//#pragma comment(lib, "IPHLPAPI.lib")


namespace UnitTestmDNS
{
	TEST_CLASS(UnitTestmDNS)
	{
	public:
		
		TEST_METHOD(Initialize_mDNS_library)
		{

			mdns_socket_open_ipv4(0);

			mdns_discovery_send(0);

			//int sockets[32];
			//int num_sockets = open_client_sockets(sockets, sizeof(sockets) / sizeof(sockets[0]), 0);
			//if (num_sockets <= 0) {
			//	printf("Failed to open any client sockets\n");
			//	//return -1;
			//}
			//printf("Opened %d socket%s for DNS-SD\n", num_sockets, num_sockets > 1 ? "s" : "");

			//printf("Sending DNS-SD discovery\n");
			//for (int isock = 0; isock < num_sockets; ++isock) {
			//	if (mdns_discovery_send(sockets[isock]))
			//		printf("Failed to send DNS-DS discovery: %s\n", strerror(errno));
			//}

			//size_t capacity = 2048;
			//void* buffer = malloc(capacity);
			//void* user_data = 0;
			//size_t records;

			//// This is a simple implementation that loops for 5 seconds or as long as we get replies
			//int res;
			//printf("Reading DNS-SD replies\n");
			//do {
			//	struct timeval timeout;
			//	timeout.tv_sec = 5;
			//	timeout.tv_usec = 0;

			//	int nfds = 0;
			//	fd_set readfs;
			//	FD_ZERO(&readfs);
			//	for (int isock = 0; isock < num_sockets; ++isock) {
			//		if (sockets[isock] >= nfds)
			//			nfds = sockets[isock] + 1;
			//		FD_SET(sockets[isock], &readfs);
			//	}

			//	records = 0;
			//	res = select(nfds, &readfs, 0, 0, &timeout);
			//	if (res > 0) {
			//		for (int isock = 0; isock < num_sockets; ++isock) {
			//			if (FD_ISSET(sockets[isock], &readfs)) {
			//				records += mdns_discovery_recv(sockets[isock], buffer, capacity, query_callback,
			//											   user_data);
			//			}
			//		}
			//	}
			//} while (res > 0);

			//free(buffer);

			//for (int isock = 0; isock < num_sockets; ++isock)
			//	mdns_socket_close(sockets[isock]);
			//printf("Closed socket%s\n", num_sockets ? "s" : "");


		}
	
		TEST_METHOD(Test_open_service_sockets) 
		{
	        int* sockets = nullptr;
	        int max_sockets = 0;
	        int result = open_service_sockets(sockets, max_sockets);
			Assert::IsTrue(result == 0, L"FAILED: open_service_sockets was called with invalid parameters, it should return 0 indicating zero sockets, it did NOT");

			max_sockets = 10;
	        result = open_service_sockets(sockets, max_sockets);
	        Assert::IsTrue(result == 0, L"FAILED: open_service_sockets was called with nullptr as sockets parameters, it should return zero, it did NOT ");

			int _sockets[32];
	        int _num_sockets = open_service_sockets(_sockets, sizeof(_sockets) / sizeof(_sockets[0]));
	        Assert::IsTrue(_num_sockets > 0, L"Failed to open any client sockets");

			// cleanup
			for (int isock = 0; isock < _num_sockets; ++isock)
		        mdns_socket_close(_sockets[isock]);

		}
		TEST_METHOD(Test_mdns_resp_add_service) 
		{
	        const char *hostname = nullptr;
	        const char* service_name = nullptr;
	        int service_port = 0;
	        int result = mdns_resp_add_service(hostname, service_name, service_port);
	        Assert::IsTrue(result == -1, L"FAILED: mdns_resp_add_service call with invalid parameters should return -1, it did NOT ");

			std::string strHostname = "localhost";
	        std::string strService_name = ""; // invalid service name
	        result = mdns_resp_add_service(strHostname.c_str(), strService_name.c_str(), service_port);
	        Assert::IsTrue(result == -1, L"FAILED: mdns_resp_add_service call with invalid parameters should return -1, it did NOT ");
		
		}
	};
}
