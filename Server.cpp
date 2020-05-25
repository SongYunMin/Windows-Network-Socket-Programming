//#pragma comment(lib, "ws2_32")
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//#define SERVERPORT 9000
//#define BUFSIZE 512
//
//// 소켓 함수 오류 출력 후 종료
//void err_quit(char* msg)
//{
//	LPVOID IpMsgBuf;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&IpMsgBuf, 0, NULL);
//	MessageBox(NULL, (LPCTSTR)IpMsgBuf, msg, MB_ICONERROR);
//	LocalFree(IpMsgBuf);
//	exit(1);
//}
//
//// 소켓 함수 오류 출력
//void err_display(char* msg)
//{
//	LPVOID IpMsgBuf;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&IpMsgBuf, 0, NULL);
//	printf("[%s] %s", msg, (char*)IpMsgBuf);
//	LocalFree(IpMsgBuf);
//}
//
//// TCP 서버(IPv4)
//DWORD WINAPI TCPServer4(LPVOID arg)
//{
//	int retval;
//	char msg_1[] = { "socket()" };
//	char msg_2[] = { "bind()" };
//	char msg_3[] = { "listen()" };
//	char msg_accept[] = { "accept()" };
//	// socket()
//	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
//	if (listen_sock == INVALID_SOCKET) err_quit(msg_1);
//	SOCKADDR_IN serveraddr;
//	ZeroMemory(&serveraddr, sizeof(serveraddr));
//	serveraddr.sin_family = AF_INET;
//	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	serveraddr.sin_port = htons(SERVERPORT);
//	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
//	if (retval == SOCKET_ERROR) err_quit(msg_2);
//
//	//listen()
//	retval = listen(listen_sock, SOMAXCONN);
//	if (retval == SOCKET_ERROR) err_quit(msg_3);
//
//	// 데이터 통신에 사용할 변수
//	SOCKET client_sock;
//	SOCKADDR_IN clientaddr;
//	int addrlen;
//	char buf[BUFSIZE + 1];
//	char msg_recv[] = { "recv()" };
//
//	while (1) {
//		// accept()
//		addrlen = sizeof(clientaddr);
//		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
//		if (client_sock == INVALID_SOCKET) {
//			err_display(msg_accept);
//			break;
//		}
//		// 접속한 클라이언트 정보 출력
//		printf("[TCP 서버] 클라이언트 시작 : IP주소= %s, 포트 번호= %d\n",
//			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
//
//		// 클라이언트와 데이터 통신
//		while (1) {
//			// 데이터 받기
//			retval = recv(client_sock, buf, BUFSIZE, 0);
//			if(retval == SOCKET_ERROR){
//				err_display(msg_recv);
//				break;
//		}
//		else if (retval == 0){
//			break;
//		}
//
//		// 받은 데이터 출력
//		buf[retval] = '\0';
//		printf("%s", buf);
//	}
//	// closesocket()
//	closesocket(client_sock);
//	printf("[TCP 서버] 클라이언트 종료 : IP주소= %s, 포트 번호= %d\n",
//		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
//	}
//	closesocket(listen_sock);
//
//	return 0;
//}
//
//// TCP 서버(IPv6)
//
//DWORD WINAPI TCPServer6(LPVOID arg)
//{
//	int retval;
//	char msg_socket[] = { "socket()" };
//	char msg_bind[] = { "bind()" };
//	char msg_listen[] = { "listen()" };
//	char msg_accept[] = { "accept()" };
//	char msg_recv[] = { "recv()" };
//	// socket()
//	SOCKET listen_sock = socket(AF_INET6, SOCK_STREAM, 0);
//	if (listen_sock == INVALID_SOCKET) err_quit(msg_socket);
//
//	// bind()
//	SOCKADDR_IN6 serveraddr;
//	ZeroMemory(&serveraddr, sizeof(serveraddr));
//	serveraddr.sin6_family = AF_INET6;
//	serveraddr.sin6_addr = in6addr_any;
//	serveraddr.sin6_port = htons(SERVERPORT);
//	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
//	if (retval == SOCKET_ERROR) err_quit(msg_bind);
//
//	// listen()
//	retval = listen(listen_sock, SOMAXCONN);
//	if (retval == SOCKET_ERROR) err_quit(msg_listen);
//
//	// 데이터 통신에 사용할 변수
//	SOCKET client_sock;
//	SOCKADDR_IN6 clientaddr;
//	int addrlen;
//	char buf[BUFSIZE + 1];
//
//	while (1) {
//		// accept
//		addrlen = sizeof(clientaddr);
//		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
//		if (client_sock == INVALID_SOCKET) {
//			err_display(msg_accept);
//			break;
//		}
//
//		// 접속한 클라이언트 정보 출력
//		char ipaddr[50];
//		DWORD ipaddrlen = sizeof(ipaddr);
//		WSAAddressToString((SOCKADDR*)&clientaddr, sizeof(clientaddr),
//			NULL, ipaddr, &ipaddrlen);
//		printf("\n[TCP 서버] 클라이언트 접속 : %s\n", ipaddr);
//
//		// 클라이언트와 데이터 통신
//		while (1) {
//			// 데이터 받기
//			retval = recv(client_sock, buf, BUFSIZE, 0);
//			if (retval == SOCKET_ERROR) {
//				err_display(msg_recv);
//				break;
//			}
//			else if (retval == 0)
//				break;
//
//			// 받은 데이터 출력
//			buf[retval] = '\0';
//			printf("%s", buf);
//		}
//
//		// closesocket()
//		closesocket(client_sock);
//		printf("[TCP 서버] 클라이언트 종료 : %s\n", ipaddr);
//	}
//
//	// closesocket()
//	closesocket(listen_sock);
//
//	return 0;
//}
//
//int main(int argc, char* argv[])
//{
//	// 원속 초기화
//	WSADATA wsa;
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//	HANDLE hThread[2];
//	hThread[0] = CreateThread(NULL, 0, TCPServer4, NULL, 0, NULL);
//	hThread[1] = CreateThread(NULL, 0, TCPServer6, NULL, 0, NULL);
//
//	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
//
//	// 원속 종료
//	WSACleanup();
//
//	return 0;
//}