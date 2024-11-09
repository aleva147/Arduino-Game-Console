#include "SnakeBody.h"


/// Constructors:
SnakeBody::SnakeBody() {}
SnakeBody::SnakeBody(Field start) {
	idBeg = 0;
	idEnd = 0;
	body[idEnd] = start;
	length = 1;
}


/// Typical operations for a queue:
Field SnakeBody::removeTail() {
	// Will never happen unless there is an error in the source code.
	if (length < 0) { return {-1,-1}; }

	Field tail = body[idBeg];
	idBeg = (idBeg + 1) % MAX_LENGTH;
	length--;
	
	return tail;
}

void SnakeBody::appendHead(const Field& newHead) {
	// Will never happen unless there is an error in the source code.
	if (length >= MAX_LENGTH) { return; }
	
	idEnd = (idEnd + 1) % MAX_LENGTH;
	body[idEnd] = newHead;
	length++;
	
	return;
}


/// Operations for in-game logic:
Field SnakeBody::getNewHead(int8_t direction) const {
	Field head = body[idEnd];
	
	if (direction == LEFT) head.x -= 1;
	else if (direction == RIGHT) head.x += 1;
	else if (direction == DOWN) head.y -= 1;
	else if (direction == UP) head.y += 1;
	
	return head;
}

//  * Should be called after tail removal, so that the old tail position (in case the snake didn't grow) wouldn't be considered.
bool SnakeBody::collisionWithBody(const Field& newHead) const {
	uint8_t i = idBeg;	
	for (uint8_t cnt = 0; cnt < length; cnt++) {
		if (body[i] == newHead) return true;
		i = (i + 1) % MAX_LENGTH;
	}
	return false;
}

uint8_t SnakeBody::getLength() const {
	return length;
}