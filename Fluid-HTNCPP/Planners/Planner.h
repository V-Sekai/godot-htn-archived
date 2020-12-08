#pragma once
#include "Tasks/Task.h"
#include "Tasks/PrimitiveTasks/PrimitiveTask.h"

namespace FluidHTN
{

class Planner
{
    std::shared_ptr<ITask> _currentTask;
    TaskQueueType          _plan;
    TaskStatus             _LastStatus;

public:
    TaskStatus LastStatus() { return _LastStatus; }

    /// <summary>
    ///		OnNewPlan(newPlan) is called when we found a new plan, and there is no
    ///		old plan to replace.
    /// </summary>
    std::function<void(TaskQueueType)> OnNewPlan;

    /// <summary>
    ///		OnReplacePlan(oldPlan, currentTask, newPlan) is called when we're about to replace the
    ///		current plan with a new plan.
    /// </summary>
    std::function<void(TaskQueueType, std::shared_ptr<ITask>&, TaskQueueType)> OnReplacePlan;

    /// <summary>
    ///		OnNewTask(task) is called after we popped a new task off the current plan.
    /// </summary>
    std::function<void(std::shared_ptr<ITask>&)> OnNewTask;

    /// <summary>
    ///		OnNewTaskConditionFailed(task, failedCondition) is called when we failed to
    ///		validate a condition on a new task.
    /// </summary>
    std::function<void(std::shared_ptr<ITask>&, std::shared_ptr<ICondition>&)> OnNewTaskConditionFailed;

    /// <summary>
    ///		OnStopCurrentTask(task) is called when the currently running task was stopped
    ///		forcefully.
    /// </summary>
    std::function<void(std::shared_ptr<PrimitiveTask>&)> OnStopCurrentTask;

    /// <summary>
    ///		OnCurrentTaskCompletedSuccessfully(task) is called when the currently running task
    ///		completes successfully, and before its effects are applied.
    /// </summary>
    std::function<void(std::shared_ptr<PrimitiveTask>&)> OnCurrentTaskCompletedSuccessfully;

    /// <summary>
    ///		OnApplyEffect(effect) is called for each effect of the type PlanAndExecute on a
    ///		completed task.
    /// </summary>
    std::function<void(std::shared_ptr<IEffect>&)> OnApplyEffect;

    /// <summary>
    ///		OnCurrentTaskFailed(task) is called when the currently running task fails to complete.
    /// </summary>
    std::function<void(std::shared_ptr<PrimitiveTask>&)> OnCurrentTaskFailed;

    /// <summary>
    ///		OnCurrentTaskContinues(task) is called every tick that a currently running task
    ///		needs to continue.
    /// </summary>
    std::function<void(std::shared_ptr<PrimitiveTask>&)> OnCurrentTaskContinues;

    /// <summary>
    ///		OnCurrentTaskExecutingConditionFailed(task, condition) is called if an Executing Condition
    ///		fails. The Executing Conditions are checked before every call to task.Operator.Update(...).
    /// </summary>
    std::function<void(std::shared_ptr<PrimitiveTask>&, std::shared_ptr<ICondition>&)> OnCurrentTaskExecutingConditionFailed;

    // ========================================================= TICK PLAN
    void Tick(class Domain& domain, IContext& ctx, bool allowImmediateReplan = true);
    void Reset(IContext& ctx)
    {
        _plan = TaskQueueType();
        if (_currentTask != nullptr)
        {
            if (_currentTask->IsTypeOf(ITaskDerivedClassName::PrimitiveTask) )
            {
				auto task = std::static_pointer_cast<PrimitiveTask>(_currentTask);
                task->Stop(ctx);
            }
            _currentTask = nullptr;
        }
    }
    const TaskQueueType&          GetPlan() { return _plan; }
    const std::shared_ptr<ITask>& GetCurrentTask() { return _currentTask; }
};
} // namespace FluidHTN
