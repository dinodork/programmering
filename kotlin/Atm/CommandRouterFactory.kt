import dagger.Component

@Component(modules = HelloWorldModule)
interface CommandRouterFactory {
    val router: CommandRouter
}
