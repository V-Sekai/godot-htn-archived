#pragma once

#include "Effects/EffectType.h"
#include "DebugInterfaces/DecompositionLogEntry.h"

namespace FluidHTN
{
class IEffect  : public std::enable_shared_from_this<IEffect>
{
protected:
    std::string _Name;
    EffectType  _Type;


public:
    const std::string& Name() { return _Name; }
    EffectType         Type() { return _Type; }
    virtual void       Apply(class IContext& ctx) = 0;
};

typedef IDecompositionLogEntry<IEffect>    DecomposedEffectEntry;
typedef std::function<void(IContext&, EffectType)> ActionType;

class ActionEffect : public IEffect
{
    ActionType _action;

public:
    ActionEffect() =delete;
    ActionEffect(const std::string name, EffectType type, ActionType action)
    {
        _Name = name;
        _Type = type;
        _action = action;
    }
    void Apply(IContext& ctx);
    
};
} // namespace FluidHTN
