#include "networking/base.h"

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

void MultiplyByThree(){
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each( in(std::cin), in(), std::cout << (_1 * 3) << " \n");
}