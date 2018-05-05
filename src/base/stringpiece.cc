#include "base/stringpiece.h"
#include <iostream>

std::ostream& operator<<(std::ostream& o, const muduonet::StringPiece& sp) {
    o << sp.data();
    return o;
}


