import java.util.Scanner

class Atm(scanner: Scanner) {
    val scanner = scanner
    var commandRouter = CommandRouter()

    fun run() {
        while (scanner.hasNextLine()) {
            var unused = commandRouter.route(scanner.nextLine())
        }
    }
}
