#ifndef PURCHASE_H
#define PURCHASE_H
#include <string>
using namespace std;

struct Purchase
{
	string Stock_name;
	int Num_shares;
	double Share_price;

	//default constructor
	Purchase();

	//constructor
	Purchase(string stock_name, int num_shares, double share_price);

	//overload << to allow Purchase objects to be output with cout
	friend ostream& operator<<(ostream& outs, const Purchase& p);
};

#endif
