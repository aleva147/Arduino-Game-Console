#ifndef SnakeBody_h
#define SnakeBody_h

#include <Constants.h>
#include <Field.h>

/// Constants:
const uint8_t MAX_LENGTH = ROWS_CNT * COLS_CNT;


class SnakeBody {
public:
	/// Constructors:
	SnakeBody();
	SnakeBody(Field start);
	
	/// Typical operations for a queue:
	Field removeTail();
	void appendHead(const Field& newHead);
	
	/// Operations for in-game logic:
	Field getNewHead(int8_t direction) const;
	bool collisionWithBody(const Field& newHead) const;
	uint8_t getLength() const;
	
private:
	/// Circular FIFO Queue implementation:
	Field body[MAX_LENGTH];		// Fields currently occupied by the snake's body.
	uint8_t length;				// Current length of the snake (number of relevant fields in the "body" array).
	uint8_t idBeg, idEnd;		// Snake's tail = idBeg, snake's head = idEnd.
};


#endif