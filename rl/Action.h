//
// Created by neroyang on 2017/10/19.
//

#ifndef GP_HW_02_ACTION_H
#define GP_HW_02_ACTION_H


#include <string>

class Action{
private:
    int actionID;
    std::string actionName;
public:

    int getActionID() const;

    void setActionID(int actionID);

    const std::string &getActionName() const;

    void setActionName(const std::string &actionName);

    Action(int actionID, const std::string &actionName);
};


#endif //GP_HW_02_ACTION_H
