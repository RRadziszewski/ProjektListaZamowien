/*
 * Offer.h
 *
 *  Created on: 21 lis 2017
 *      Author: robert
 */

#ifndef OFFER_H_
#define OFFER_H_

#include "Auction.h"
#include "User.h"
#include "general.h"

class Offer {
public:
	Offer(int p);
	virtual ~Offer();
	int showPrice();
protected:
	int price;
private:
	int ofid;
};

void newOffer(User *own,MYSQL *base);

#endif /* OFFER_H_ */
