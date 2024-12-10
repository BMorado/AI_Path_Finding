#pragma once
#include "Decision.h"


class IsHealthLow : public Decision {
public:
    IsHealthLow() : Decision()
    {
    }
    IsHealthLow(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_)
        : Decision(trueNode_, falseNode_, owner_) {
    }

    bool TestValue() override;
};

