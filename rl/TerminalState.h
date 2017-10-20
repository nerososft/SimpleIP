//
// Created by neroyang on 2017/10/20.
//

#ifndef GP_HW_02_TERMINALSTATE_H
#define GP_HW_02_TERMINALSTATE_H


class TerminalState {
private:
    int x;
    int y;
    int terminalValue;
    bool absorbing;

public:
    TerminalState(int x, int y, int terminalValue, bool absorbing);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getTerminalValue() const;

    void setTerminalValue(int terminalValue);

    bool isAbsorbing() const;

    void setAbsorbing(bool absorbing);
};


#endif //GP_HW_02_TERMINALSTATE_H
