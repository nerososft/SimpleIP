//
// Created by neroyang on 2017/10/20.
//

#include "TerminalState.h"

TerminalState::TerminalState(int x, int y, int terminalValue, bool absorbing) : x(x), y(y), terminalValue(terminalValue), absorbing(absorbing) {}

int TerminalState::getX() const {
    return x;
}

void TerminalState::setX(int x) {
    TerminalState::x = x;
}

int TerminalState::getY() const {
    return y;
}

void TerminalState::setY(int y) {
    TerminalState::y = y;
}

int TerminalState::getTerminalValue() const {
    return terminalValue;
}

void TerminalState::setTerminalValue(int terminalValue) {
    TerminalState::terminalValue = terminalValue;
}

bool TerminalState::isAbsorbing() const {
    return absorbing;
}

void TerminalState::setAbsorbing(bool absorbing) {
    TerminalState::absorbing = absorbing;
}
