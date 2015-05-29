#include "utils.h"

utils::utils()
{

}

utils::~utils()
{

}

int utils::gcd(int a,int b){
    if(0==a%b)
        return b;
    else
        gcd(b,a%b);
}
