#ifndef Field_h
#define Field_h

#include <stdint.h>


struct Field {
	/// Variables:
	uint8_t x, y;
	
	/// Operator overloading:
    bool operator==(const Field& field) const {
        return x == field.x && y == field.y;
    }
    bool operator!=(const Field& field) const {
        return x != field.x || y != field.y;
    }
};


#endif
