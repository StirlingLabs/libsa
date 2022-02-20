namespace StirlingLabs;

internal sealed class CleanUpAction
{
    private readonly Action _action;

    public CleanUpAction(Action action)
        => _action = action;

    ~CleanUpAction()
        => _action();
}
