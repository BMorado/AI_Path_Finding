#pragma once
#include <VMath.h>
#include "Character.h"
#include "Decision.h"

class IsPlayerCloseToHome : public Decision {
public:
    IsPlayerCloseToHome () : Decision()
    {
    }
    IsPlayerCloseToHome(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_)
        : Decision(trueNode_, falseNode_, owner_) {
    }

    bool TestValue() override;
};

