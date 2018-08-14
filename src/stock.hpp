#ifndef STOCK_H
#define STOCH_H

#ifndef MONEY_DECIMALS
#define MONEY_DECIMALS 5
#endif

class Stock{
  string tick;
  string name;
  long price;//Can be 32 bits, 5 decimals included
  long q_div;
  long a_div;
public:
  Stock(string tick){
    this.tick = tick;
  }

  void setName(string name){
    this.name = nake;
  }

  void setPrice(long price){
    this.price = price;
  }

  void setQDiv(long div){
    this.q_div = div;
  }

  void setADiv(long div){
    this.a_div = div;
  }

  string getTick(){ return tick; }
  string getName(){ return name; }
  long getPrice(){ return price; }
  long getQDiv(){ return q_div; }
  long getADiv(){ return a_div; }

  static long stringToPrice(string price_str){
    long price=0;
    double d=atof(price_str.c_str());
    price = d * 10 ^ MONEY_DECIMALS;
    return price;
  }
};
#endif
