/*
 * Auction.cpp
 *
 *  Created on: 20 lis 2017
 *      Author: robert
 */

#include "Auction.h"
#include "User.h"
#include "general.h"

std::string cut( const std::string & str, const char ch, const unsigned int v )
{
    std::string ret = "";
    for( size_t i = 0, tmp = 0; i < str.size(); ++i ) {
        if( str[ i ] == ch ) {
            if( tmp > v ) break;
            else ++tmp;

        }
        else if( tmp == v ) ret += str[ i ];

    }
    return ret;
}

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

Auction::Auction()
{}

Auction::Auction(std::string x, std::string y) {
	this->title = x;
	this->synopsis = y;
	this->aid = counter;
	counter++;
}

std::string Auction::showTitle(){
	return this->title;
}
std::string Auction::showSyn(){
	return this->synopsis;
}
std::string Auction::showStartDate(){
	return this->startDate;
}
std::string Auction::showEndDate(){
	return this->endDate;
}
std::string Auction::showOwner(User &usr){
	return usr.login;
}

void Auction::relate(User &usr){
	this->uid = usr.classId;
}

void Auction::setTitle(std::string x){
	this->title = x;
}
void Auction::setSyn(std::string x){
	this->synopsis = x;
}
void Auction::setStart(std::string x){
	this->startDate = x;
}
void Auction::setEnd(std::string x){
	this->endDate = x;
}
void Auction::setUID(int x){
	this->uid = x;
}
void Auction::setUIDA(int x){
	this->uida = x;
}

int Auction::showUID(){
	return this->uid;
}
int Auction::showUIDA(){
	return this->uida;
}

Auction::~Auction() {
	// TODO Auto-generated destructor stub
}

void newAuction(User *own,MYSQL *base){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::vector<std::string> tmp;
	std::string input;
	std::ostringstream query;
	query << "SELECT UID FROM Account WHERE login = '" << own->login << "';";
	mysql_query(base,query.str().c_str());
	res=mysql_store_result(base);
	row=mysql_fetch_row(res);
	std::cout << "Title: ";
	std::getline(std::cin, input);
	tmp.push_back(input);
	std::cout << "Description: ";
	std::getline(std::cin, input);
	tmp.push_back(input);

	[](std::ostringstream *query)->void{
		query->clear();
		query->str("");
	}(&query);

	Auction *at = new Auction(tmp[0],tmp[1]);
	std::cout << "Working mr. " << at->showOwner(*own) << std::endl;

	query << "INSERT INTO Auction VALUES(''," << row[0] << ",'" << tmp[0] << "','" << tmp[1] << "',DATE_FORMAT(NOW(), '%d.%m.%Y'),NULL,NULL);";
	std::cout << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
	mysql_free_result(res);
	free(at);
}

void setAuction(std::string title, MYSQL *base, User *s){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;

	query << "SELECT UID FROM Account WHERE login = '" << s->login << "';";
	std::cout << "Query: " << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
	res=mysql_store_result(base);
	row=mysql_fetch_row(res);
	query.clear();
	query.str("");

	query << "UPDATE Auction SET EndDate = DATE_FORMAT(NOW(), '%d.%m.%Y'), UIDA = "<< row[0] <<"  WHERE Title = '" << title << "';";
	std::cout << "Query: " << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
	query.clear();
	query.str("");
	query << "SELECT Auction.Title,Auction.Synopsis,Auction.StartDate,IFNULL(Auction.EndDate,'Brak'),Account.Name,Account.Surname FROM Auction JOIN Account ON Auction.UID = Account.UID WHERE Title = '" << title << "' LIMIT 1;";
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	row = mysql_fetch_row(res);
	std::cout << "Query: " << query.str().c_str() << std::endl;
	std::cout << "Report: " << std::endl << "*******" << std::endl;
	std::cout << "Title: " << row[0] << std::endl;
	std::cout << "Description: " << row[1] << std::endl;
	std::cout << "Date of order: " << row[2] << " " << std::endl;
	std::cout << "Date of execute: " << row[3] << std::endl;
	std::cout << "Surname: " << row[5] << " " << row[4] << std::endl;
	mysql_free_result(res);
};

void setAuction(MYSQL *base, User *s){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;

	query << "SELECT UID FROM Account WHERE login = '" << s->login << "';";
	std::cout << "Query: " << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
	res=mysql_store_result(base);
	row=mysql_fetch_row(res);
	query.clear();
	query.str("");

	query << "UPDATE Auction SET EndDate = DATE_FORMAT(NOW(), '%d.%m.%Y'), UIDA = "<< row[0] <<"  WHERE EndDate IS NULL;";
	std::cout << "Query: " << query.str().c_str() << std::endl;
	mysql_query(base,query.str().c_str());
	mysql_free_result(res);
};

void showAuctions(MYSQL *base){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;
	query << "SELECT Auction.Title,Auction.Synopsis,Auction.StartDate,IFNULL(Auction.EndDate,'Brak'),Account.Name,Account.Surname FROM Auction JOIN Account ON Auction.UID = Account.UID ORDER BY StartDate;";
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	while(row = mysql_fetch_row(res)) std::cout << row[0] << " " << row[1] << " Start from: " << row[2] << ", Realised: " << row[3] << " " << row[4] << " " << row[5] << std::endl;
	mysql_free_result(res);
}

void showAuctions(MYSQL *base, User *session){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;
	query << "SELECT Auction.Title,Auction.Synopsis,Auction.StartDate,IFNULL(Auction.EndDate,'Brak') FROM Auction JOIN Account ON Auction.UID = Account.UID WHERE Account.Login = '"<< session->login <<"' ORDER BY StartDate;";
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	while(row = mysql_fetch_row(res)) std::cout << row[0] << " " << row[1] << " Start from: " << row[2] << ", Realised: " << row[3] << std::endl;
	mysql_free_result(res);
}

void findAuctions(MYSQL *base, std::vector<std::string>tmp){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;
	query << "SELECT Auction.Title,Auction.Synopsis,Auction.StartDate,IFNULL(Auction.EndDate,'Brak') ,Account.Name,Account.Surname FROM Auction JOIN Account ON Auction.UID = Account.UID WHERE Auction.EndDate IS NOT NULL AND Auction.Title LIKE '%" << tmp[1] << "%';";
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	while(row = mysql_fetch_row(res)) std::cout << row[0] << " " << row[1] << " Start from: " << row[2] << ", Realised: " << row[3] << " " << row[4] << " " << row[5] << std::endl;
	mysql_free_result(res);
}

void loadAuctions(MYSQL *base, std::string tmp){
	std::list<Auction> L;
	std::ifstream file(tmp);
	std::vector<std::string>fields;
	if(file.is_open()){
		std::string line;
		std::ostringstream query;
		while(strstr(line.c_str(),"/END") == NULL){
				std::getline(file, line);
				if(strstr( line.c_str(), "/#" ) == NULL){
					Auction at;
					at.setUID(std::atoi(cut(line,':',0).c_str()));
					at.setTitle(cut(line,':',1));
					at.setSyn(cut(line,':',2));
					at.setStart(cut(line,':',3));
					at.setEnd(cut(line,':',4));
					at.setUIDA(std::atoi(cut(line,':',5).c_str()));
					if(strstr( line.c_str(), "/END" ) == NULL) L.push_back(at);
					delete &at;
				}else{
					std::cout << "Comment line: " << line << std::endl;
				}
		}
		file.close();
		std::cout << "Cur" <<std::endl;
		for(std::list<Auction>::iterator iter=L.begin(); iter != L.end(); ++iter){
			std::cout << "Import line: "<< iter->showUID() <<" '" << iter->showTitle() << "' '" << iter->showSyn() << "' '" << iter->showStartDate() << "' '" << iter->showEndDate() << "' " << iter->showUIDA() << std::endl;
			query << "INSERT INTO Auction VALUES(''," << iter->showUID() <<", '" << iter->showTitle() << "', '" << iter->showSyn() << "', '" << iter->showStartDate() << "', '" << iter->showEndDate() << "', " << iter->showUIDA() << ");";
			std::cout << "Query: " << query.str().c_str() << std::endl;
			mysql_query(base,query.str().c_str());
			query.clear();
			query.str("");
		}
	}else{
		std::cout << "Error: Wrong file path!" << std::endl;
	}
}

void statOne(MYSQL *base){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;
	query << "SELECT COUNT(*) FROM Auction;";
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	row = mysql_fetch_row(res);
	std::cout << "Number of orders: " << row[0] << std::endl;
	query.clear();
	query.str("");
	mysql_free_result(res);
}

void statTwo(MYSQL *base){
	MYSQL_RES *res;
	MYSQL_ROW row;
	std::ostringstream query;
	query << "SELECT StartDate, COUNT(*) AS 'Number' FROM Auction GROUP BY StartDate ORDER BY Number DESC LIMIT 1;";
	mysql_query(base,query.str().c_str());
	res = mysql_store_result(base);
	row = mysql_fetch_row(res);
	std::cout << "Max number of orders are submiting " << row[0] << ": " << row[1] << std::endl;
	query.clear();
	query.str("");
	mysql_free_result(res);
}
