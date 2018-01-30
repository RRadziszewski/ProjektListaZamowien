/*
 * User.h
 *
 *  Created on: 19 lis 2017
 *      Author: robert
 */

#ifndef USER_H_
#define USER_H_

#include "general.h"

extern number counter;
class User {
public:
	User();
	User(std::string login);
	virtual ~User();
	friend void login(User & ,MYSQL *base);
	friend void logout(User &);
	friend class Auction;
	void setLogin(std::string login);
	void setAccess(int access);
	void setName(std::string name);
	void setSurname(std::string surname);
	void setPassword(std::string password);
	void removeClassId();
	void showInfo();
	std::string login;
	int access;
protected:
	std::string name;
	std::string surname;
private:
	int classId;
};

void delUser(std::string login,MYSQL *base);
void create(std::vector<std::string> tmp,MYSQL *base);
void set(std::vector<std::string>tmp, MYSQL*base);

#endif /* USER_H_ */
