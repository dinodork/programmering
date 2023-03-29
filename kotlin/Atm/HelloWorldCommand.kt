import javax.inject.Inject

class HelloWorldCommand @Inject constructor() : Command {
    override val key = "hello"

    override fun handleInput(input: List<String>): Command.Result {
        if (!input.isEmpty()) { return Command.invalid() }
        println("world")

        return Command.handled()
    }
}
