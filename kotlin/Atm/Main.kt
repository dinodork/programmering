
import java.util.Scanner

fun main(args: Array<String>) {
    println("Hello, World!")
    var scanner = Scanner(System.`in`)
    var commandRouter = CommandRouter()

    while (scanner.hasNextLine()) {
        var unused = commandRouter.route(scanner.nextLine())
    }
}
