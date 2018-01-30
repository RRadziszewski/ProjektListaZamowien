/*
 * Offer.cpp
 *
 *  Created on: 21 lis 2017
 *      Author: robert
 */

#include "Offer.h"
#include "Auction.h"
#include "User.h"
#include "general.h"

Offer::Offer(int p) {
	this->price = p;
	this->ofid = counter;
	counter++;
}

int Offer::showPrice(){
	return this->price;
}

void newOffer(User *own,MYSQL *base){
	MYSQL_RES *res,*res1;
	MYSQL_ROW row,row1;
	std::ostringstream query,query1,query2,query3,query4;
	query << "SELECT UID FROM Account WHERE Login = '" << own->login << "';";
	std::cout << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	row = mysql_fetch_row(res);
	int uid = std::stoi(row[0]), tmp = -1;
	std::string tmp1;
	while(uid == tmp || tmp == -1){
		std::cout << "Please, enter title of auction: ";
		std::getline(std::cin, tmp1);
		query1 << "SELECT UID FROM Auction WHERE Title = '" << tmp1 << "';";
		std::cout << query1.str().c_str() << std::endl;
		mysql_query(base,query1.str().c_str());
		res = mysql_store_result(base);
		row = mysql_fetch_row(res);
		tmp = std::stoi(row[0]);
		if(tmp==uid){
			std::cout << "You are author! ";
		}
		query1.clear();
		query1.str("");
	}
	query2 << "SELECT Offer.Amount FROM Auction JOIN Offer ON Auction.AID =  Offer.AID JOIN Account ON Auction.UID = Account.UID WHERE Title = '" << tmp1 << "' ORDER BY Offer.Amount DESC LIMIT 1;";
	std::cout << query2.str().c_str() << std::endl;
	mysql_query(base,query2.str().c_str());
	res = mysql_store_result(base);
	row = mysql_fetch_row(res);
	query3 << "SELECT Auction.MinPrice,Auction.AID FROM Auction WHERE Title = '" << tmp1 << "';";
	std::cout << query3.str().c_str() << std::endl;
	mysql_query(base,query3.str().c_str());
	res1 = mysql_store_result(base);
	row1 = mysql_fetch_row(res1);
	int tmp2 = -1;
	int aid = std::stoi(row1[1]);
	int prc;
	if(row!=NULL){ prc = std::stoi(row[0]); }
	else { prc  = std::stoi(row1[0]);}
	while(tmp2 < prc){
		std::cout << "Please, your price (Actual:  " << prc << " zł: ";
		std::getline(std::cin, tmp1);
		tmp2 = std::stoi(tmp1);
		if(tmp2 <= prc){
			std::cout << "Amount to small!" <<std::endl;
		}
	}
	Offer *of = new Offer(tmp2);

	query.clear();
	query.str("");
	query << "INSERT INTO Offer VALUES('',"<< uid <<","<< aid <<"," << of->showPrice() << ");";
	std::cout << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());

	mysql_free_result(res);
	mysql_free_result(res1);
	free(of);
}

Offer::~Offer() {
	// TODO Auto-generated destructor stub
}

