#include "Socket.h"

#define SERVER_IP "192.168.108.128"
#define BUFFER_LENGHT 4048
#define PORT 51051

Socket::Socket() = default;
Socket::~Socket() = default;

int Socket::connectClientOpen()
{
	struct sockaddr_in serveraddress;
	struct sockaddr_in client;

	int socket_discriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_discriptor == -1)
	{
		std::cout << "Ошибка созадния сокета!" << std::endl;
		return -1;
	}

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr(SERVER_IP);

	int connection = connect(socket_discriptor, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
	if (connection == -1)
	{
		std::cout << "Не удалось установить соединение с сервером!" << std::endl;
		return -1;
	}
	
	return socket_discriptor;	
}

// отправить
void Socket::sendMessage(int connection, std::string &str)
{	
	char buffer[str.size()+1]{};
	for(int i=0; i<=(str.size()); i++)
	{
		buffer[i] = str[i];
	}
	size_t bytes = write(connection, buffer, (str.size()+1));
	
	if (bytes == -1)
	{
		std::cout << "Ошибка отправки сообщения!" << std::endl;
	}
}

// получить
std::string Socket::reseiveMessage(int connection)
{	
	char buffer [BUFFER_LENGHT]{};   
    read(connection, buffer, sizeof(buffer));
	std::string str = buffer;	
    return str;
}

void Socket::connectClose(int socket_discriptor)
{
	close(socket_discriptor);
}
