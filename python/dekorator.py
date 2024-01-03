class Dekorator:
    def __init__(self, func):
        self.func = func
        print("Dekorator()")
        print("  self = " + str(self))
        print("  func = " + str(func))

    def __call__(self, *args, **kwargs):
        print(">Dekorator(args)")
        print("  ", end="")
        self.func(*args, **kwargs)
        print("<Dekorator(args)")

    def __get__(self, instance, owner):
        print("Dekorator.__get__()")
        print("  instance = " + str(instance))
        print("  owner = " + str(owner))
        return Wrapper(self, instance)


class Wrapper:
    def __init__(self, desc, subj):
        print("Wrapper()")
        print("  desc = " + str(desc))
        print("  subj = " + str(subj))
        self.desc = desc
        self.subj = subj

    def __call__(self, *args, **kwargs):
        print("Wrapper.__call__()")
        return self.desc(self.subj, *args, **kwargs)


class Klas:
    @Dekorator
    def foo(self):
        print("Klas.foo()")


klas = Klas()
klas.foo()
