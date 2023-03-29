import javax.inject.Inject

class CommandRouter @Inject constructor() {
    val commands = mapOf<String, Command>()

    fun route(input: String): Command.Result {
        var splitInput = input.split("\\s".toRegex())
        if (splitInput.isEmpty()) {
            return invalidCommand(input)
        }

        var commandKey = splitInput.get(0)
        var command = commands.get(commandKey)
        if (command == null) {
            return invalidCommand(input)
        }

        var args = splitInput.subList(1, splitInput.size)
        var result = command.handleInput(args)

        return if (result.status.equals(Command.Status.INVALID)) {
            invalidCommand(input)
        } else {
            result
        }
    }

    fun invalidCommand(input: String): Command.Result {
        println(String.format("couldn't understand \"%s\". please try again.", input))
        return Command.invalid()
    }
}
