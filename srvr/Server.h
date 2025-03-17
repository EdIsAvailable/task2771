/*#include "UserRepository.h"
#include"Chat.h"

#pragma once
class Server
{
	//UserRepository* _userRepo;
	//Chat* _msgRepo;

	UserRepository _userRepo;
	Chat _msgRepo;

public: Server();
		void MainProcess();
		~Server();

private: Acc* ProcessAuthorization();
		 void ProcessChat(Acc* user);
};
*/

#include "UserRepository.h"
#include "Chat.h"

#pragma once
class Server
{
    UserRepository _userRepo;
    Chat _msgRepo;

public: 
    Server();
    void MainProcess();
    ~Server();

private: 
    Acc* ProcessAuthorization();
    void ProcessChat(Acc* user);
};

