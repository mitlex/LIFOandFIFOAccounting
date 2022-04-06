#include "Purchase.h"
#include <iostream>

Purchase::Purchase()
{
	Stock_name = "";
	Num_shares = 0;
	Share_price = 0.00;
}

Purchase::Purchase(string stock_name, int num_shares, double share_price)
{
	Stock_name = stock_name;
	Num_shares = num_shares;
	Share_price = share_price;
}

// Overloaded << to allow for terminal output of Purchase objects
ostream& operator<<(ostream& outs, const Purchase& p)
{
	cout << p.Num_shares << " shares " << p.Stock_name << " at " << p.Share_price << " per share";
	return outs;
}


