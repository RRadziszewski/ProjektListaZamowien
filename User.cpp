/*
 * User.cpp
 *
 *  Created on: 19 lis 2017
 *      Author: robert
 */

#include "User.h"
#include "general.h"

number counter = 0;

User::User()
{}

User::User(std::string login) {
	this->name = "guest";
	this->surname = "guest";
	this->access = 0;
	this->login = login;
	this->classId = counter;
	counter++;
}

User::~User() {
	// TODO Auto-generated destructor stub
}

void User::setLogin(std::string login){
	this->login = login;
}

void User::setAccess(int access){
	this->access = access;
}

void User::setName(std::string name){
	this->name = name;
}

void User::setSurname(std::string surname){
	this->surname = surname;
}

void User::removeClassId(){
	this->classId = 0;
}

void User::showInfo(){
	std::cout << "Name: " << this->name << "Surname: " << this->surname << "Login: " << this->login << std::endl;
}

void login(User &person, MYSQL *base){
	MYSQL_RES *res,*res1;
	MYSQL_ROW row,row1;
	std::string login;
	std::string password;
	std::cout << "Login: ";
	std::getline(std::cin, login);
	std::cout << std::endl << "Password: ";
	std::getline(std::cin, password);
	std::cout << std::endl;
	std::ostringstream query;
	query << "SELECT `Name` FROM `Account` WHERE `Login` = '" << login << "' AND `Password` = '" << password << "';";
	mysql_query(base, query.str().c_str());
	res = mysql_store_result(base);
	if(row = mysql_fetch_row(res)){
		std::ostringstream query1;
		query1 << "SELECT Name,Surname,Access FROM `Account` WHERE `Login` = '" << login << "';";
		mysql_query(base, query1.str().c_str());
		res1 = mysql_store_result(base);
		row1 = mysql_fetch_row(res1);
		person.name = row1[0];
		person.surname = row1[1];
		person.access = atoi(row1[2]);
		person.login = login;
		mysql_free_result(res1);
	}else{
		std::cout << "Wrong login or password!" << std::endl;
	}
	if(res != NULL)
	mysql_free_result(res);
	std::cout << "OK!" << std::endl;
}

void logout(User &person){
	person.name = "guest";
	person.surname = "guest";
	person.access = 0;
	person.removeClassId();
	person.login = "guest";
}

void create(std::vector<std::string> tmp, MYSQL *base){
	User *person = new User(tmp[1]);
	person->setName(tmp[2]);
	person->setSurname(tmp[3]);
	std::string password = tmp[4];
	person->setAccess(std::stoi(tmp[5]));
	std::cout << "insert into Account values ('','"<< tmp[2] <<"','" << tmp[3] << "','"<< tmp[1] <<"','" << tmp[4] << "'," << tmp[5] << ");"<<std::endl;
	std::ostringstream query;
	query << "insert into Account values ('','"<< tmp[2] <<"','" << tmp[3] << "','"<< tmp[1] <<"','" << tmp[4] << "'," << tmp[5] << ");";
	if(mysql_query(base, query.str().c_str())) std::cout << "OK!" << std::endl;
	free(person);
}

void delUser(std::string login,MYSQL *base){
	std::ostringstream query;
	query << "DELETE FROM Account WHERE Login = '" << login << "';";
	std::cout << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
}

void set(std::vector<std::string>tmp, MYSQL*base){
	std::ostringstream query2;
	User *person = new User(tmp[1]);
	if(tmp[2] == "-n"){
		person->setName(tmp[3]);
		query2 << "UPDATE Account SET Name = '" << tmp[3] << "' where Login = '" << tmp[1] <<"';";
	}else if(tmp[2] == "-s"){
		person->setSurname(tmp[3]);
		query2 << "UPDATE Account SET Surname = '" << tmp[3] << "' where Login = '" << tmp[1] <<"';";
	}else if(tmp[2] == "-a"){
		person->setAccess(std::stoi(tmp[3]));
		query2 << "UPDATE Account SET Access = " << tmp[3] << " where Login = '" << tmp[1] <<"';";
	}

	std::cout << query2.str().c_str() << std::endl;

	if(mysql_query(base, query2.str().c_str())) std::cout << std::endl;
	free(person);
}
