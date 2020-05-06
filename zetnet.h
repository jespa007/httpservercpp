#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <memory.h>
#include <pthread.h>

#ifdef __GNUC__
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#endif

// include socket platform
#ifdef _WIN32

		#include <winsock2.h>
		#include <ws2tcpip.h>
		#include <windows.h>


		#define ioctl ioctlsocket
		#define bzero ZeroMemory
#else

	typedef  int SOCKET;
	#define INVALID_SOCKET -1

	#define addrinfo sockaddr_in



	#ifdef __GNUC__
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <sys/ioctl.h>
	#endif
#endif



#ifdef __MEMMANAGER__
#include "memmgr.h"
#endif

//----------------------------
// START ZETNET PROTOTYPES

#define ZETNET_MAJOR_VERSION 1
#define ZETNET_MINOR_VERSION 0
#define ZETNET_PATCH_VERSION 0


#ifdef  __cplusplus
extern "C" {
#endif

#include "util/ZNMem.h"
#include "util/ZNList.h"
#include "util/ZNString.h"
#include "util/ZNIO.h"
#include "util/ZNPath.h"
#include "util/ZNUrl.h"


#include "TcpUtils.h"
#include "TcpServer.h"
#include "HttpParamValue.h"
#include "HttpServerMPS.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpHandleClient.h"
#include "HttpServer.h"


bool ZetNet_Init(void);
void ZetNet_DeInit(void);


#ifdef  __cplusplus
}
#endif


