
import dagger.Component

@Component
interface CommandRouterFactory {
    val router: CommandRouter
}
