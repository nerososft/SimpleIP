//
// Created by neroyang on 2017/10/19.
//

#include "Action.h"

Action::Action(int actionID, const std::string &actionName) : actionID(actionID), actionName(actionName) {}

int Action::getActionID() const {
    return actionID;
}

void Action::setActionID(int actionID) {
    Action::actionID = actionID;
}

const std::string &Action::getActionName() const {
    return actionName;
}

void Action::setActionName(const std::string &actionName) {
    Action::actionName = actionName;
}
