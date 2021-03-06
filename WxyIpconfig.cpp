#include <winsock2.h>
#include <iphlpapi.h>
#include <stdlib.h>
#pragma comment(lib, "IPHLPAPI.lib")
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

IP_ADAPTER_INFO  *pAdapterInfo;
ULONG            ulOutBufLen;
DWORD            dwRetVal;

void call_ip_config_all() {
	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS) {
		printf("GetAdaptersInfo call failed with %d\n", dwRetVal);
	}
	else {
		PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
		printf("Windows IP Configuration\n\n\n");
		while (pAdapter) {
			printf("%s\n\n", pAdapter->Description);
			printf("\tConnection-specific DNS Suffix  .: %s\n", pAdapter->DhcpServer.IpAddress.String);
			printf("\tDescription . . . . . . . . . . . : %s\n", pAdapter->Description);
			printf("\tPhysical Address. . . . . . . . . : ");
			for (UINT i = 0; i < pAdapter->AddressLength; i++) {
				if (i == (pAdapter->AddressLength - 1))
					printf("%.2X\n", (int)pAdapter->Address[i]);
				else
					printf("%.2X-", (int)pAdapter->Address[i]);
			}
			printf("\tDHCP Enabled. . . . . . . . . . . : %s\n", pAdapter->DhcpEnabled ? "YES" : "NO");
			printf("\tAutoconfiguration Enabled . . . . : \n");
			printf("\tLink-local IPv6 Address . . . . . : \n");
			printf("\tIPv4 Address. . . . . . . . . . . : %s\n", pAdapter->IpAddressList.IpAddress.String);
			printf("\tSubnet Mask . . . . . . . . . . . : %s\n", pAdapter->IpAddressList.IpMask.String);
			printf("\tDefault Gateway . . . . . . . . . : %s\n", pAdapter->GatewayList.IpAddress.String);
			printf("\tDHCP Server . . . . . . . . . . . : %s\n\n", pAdapter->DhcpServer.IpAddress.String);
			pAdapter = pAdapter->Next;
		}
	}
}

int main()
{
	pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS) {
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
	}
	call_ip_config_all();
	free(pAdapterInfo);
	system("pause");
}