#include "Edge.h"


Edge::Edge (int idverticeone, int idverticetwo) {
    this->idVerticeOne = idverticeone;
    this->idVerticeTwo = idverticetwo;
}

int Edge::gimmeIdverticeOne() {
    return this->idVerticeOne;
};
int Edge::gimmeIdverticeTwo() {
    return this->idVerticeTwo;
};
