/*
 * main.cpp
 *
 *  Created on: 19 lis 2017
 *      Author: robert
 */

#include "general.h"
#include "User.h"
#include "Auction.h"

void help(){
	std::cout << "help - list of commands" << std::endl << "quit" << std::endl << "login - you must enter the login and password" << std::endl;
	std::cout << "create - create new account: create login name surname password access" << std::endl;
};

void help(std::string x){
	if( strcmp( x.c_str(), "help")){
		std::cout << "help - list of commands" << std::endl;
	}else if( strcmp( x.c_str(), "quit")){
		std::cout << "quit - Zamyka sesje" <<std::endl;
	}
}

int main(int argc, char *argv[]){
	MYSQL db0;
	mysql_init(&db0);
	if(mysql_real_connect(&db0, "127.0.0.1", "root", "", "listorder", 0, NULL, 0)){

		std::string command = "TEST";

		User *session = new User("guest");

		std::cout << "@" << session->login << "> " ;
		std::getline(std::cin, command);
		std::cout << std::endl;
		while( command != "quit" ){
			auto comV = explode(command, ' ');
			if(session->access == 1){
				if( strcmp( command.c_str(), "logout" ) == 0 ){
									logout(*session);
				}else if(strcmp( command.c_str(), "help" ) == 0){
					help();
				}else if(strcmp( command.c_str(), "who" ) == 0){
					session->showInfo();
				}else if(strcmp( command.c_str(), "showall" ) == 0 ){
					showAuctions(&db0,session);
				}else if(strstr( command.c_str(), "set" ) != NULL ){
					set(comV,&db0);
				}else if(strstr( command.c_str(), "neword" ) != NULL ){
					newAuction(session, &db0);
				}else{
					std::cout << "Wrong command! " << std::endl;
				}
			}else if(session->access == 2){
				if( strcmp( command.c_str(), "logout" ) == 0 ){
					logout(*session);
				}else if(strcmp( command.c_str(), "help" ) == 0){
					help();
				}else if(strcmp( command.c_str(), "who" ) == 0){
					session->showInfo();
				}else if(strcmp( command.c_str(), "showall" ) == 0 ){
					showAuctions(&db0);
				}else if(strstr( command.c_str(), "create" ) != NULL ){
					create(comV,&db0);
				}else if(strstr( command.c_str(), "set" ) != NULL ){
					set(comV,&db0);
				}else if(strstr( command.c_str(), "endord" ) != NULL ){
					setAuction(comV[1], &db0, session);
				}else if(strcmp( command.c_str(), "fordend" ) == 0 ){
					setAuction(&db0, session);
				}else if(strstr( command.c_str(), "deluser" ) != NULL ){
					delUser(comV[1],&db0);
				}else if(strstr( command.c_str(), "find" ) != NULL ){
					findAuctions(&db0, comV);
				}else if(strstr( command.c_str(), "loadord" ) != NULL ){
					loadAuctions(&db0, comV[1]);
				}else if(strstr( command.c_str(), "stats" ) != NULL ){
					statOne(&db0);
					statTwo(&db0);
				}else{
					std::cout << "Wrong command! " << std::endl;
				}
			}
			else if(session->access == 0){
				if( strcmp( command.c_str(), "login" ) == 0 ){
					login(*session,&db0);
					command = "test";
				}else if(strcmp( command.c_str(), "help" ) == 0){
					help();
				}else{
					std::cout << "Wrong command! " << std::endl;
				}
			}

			std::cout << "@" << session->login << "> " ;
			std::getline(std::cin, command);
			std::cout << std::endl;
		}
		mysql_close(&db0);
	}else{
		std::cout << "Database error!";
	}
	return 0;
}
