/*
 * Auction.h
 *
 *  Created on: 20 lis 2017
 *      Author: robert
 */

#ifndef AUCTION_H_
#define AUCTION_H_

#include "general.h"
#include "User.h"

class Auction {
public:
	Auction();
	Auction(std::string x, std::string y);
	virtual ~Auction();
	void relate(User &usr);
	std::string showTitle();
	std::string showSyn();
	int showMP();
	std::string showStat();
	std::string showOwner(User &usr);
	std::string showStartDate();
	std::string showEndDate();
	void setTitle(std::string x);
	void setSyn(std::string x);
	void setStart(std::string x);
	void setEnd(std::string x);
	void setUID(int x);
	void setUIDA(int x);

	int showUID();
	int showUIDA();
protected:
	std::string title;
	std::string synopsis;
	std::string startDate;
	std::string endDate;
private:
	int aid;
	int uid;
	int uida;
};

std::string cut( const std::string & str, const char ch, const unsigned int v );

std::vector<std::string> explode(std::string const & s, char delim);

void newAuction(User *own,MYSQL *base);

void setAuction(std::string title, MYSQL *base, User *s);

void setAuction(MYSQL *base, User *s);

void showAuctions(MYSQL *base);

void showAuctions(MYSQL *base, User *session);

void findAuctions(MYSQL *base, std::vector<std::string>tmp);

void loadAuctions(MYSQL *base, std::string tmp);

void statOne(MYSQL *base);

void statTwo(MYSQL *base);

#endif /* AUCTION_H_ */
