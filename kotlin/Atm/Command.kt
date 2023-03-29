/** Logic to process some user input. */
interface Command {
    /**
     * String token that signifies this command should be selected (e.g.:
     * "deposit", "withdraw")
     */
    val key: String

    /** Process the rest of the command's words and do something. */
    fun handleInput(input: List<String>): Result

    /**
     * This wrapper class is introduced to make a future change easier
     * even though it looks unnecessary right now.
     */
    class Result constructor(val status: Status)

    enum class Status {
        INVALID,
        HANDLED,
    }

    companion object {
        fun invalid() = Result(Status.INVALID)
        fun handled() = Result(Status.HANDLED)
    }
}
