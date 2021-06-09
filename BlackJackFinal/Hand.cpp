
#include "Hand.h"

void Hand::setHandSize(int hs) {
    HSize = hs;
}
int Hand::getHandSize() {
    return HSize;
}
void PHand::setMoney(int m) {
    money = m;
}
void PHand::setBet(int b) {
    bet = b;
} 
int PHand::getMoney() {
    return money;
}
int PHand::getBet() {
    return bet;
}
void DHand::Display() {
    cout<<"The Dealer's Hand Size is "<<HSize<<endl;
}