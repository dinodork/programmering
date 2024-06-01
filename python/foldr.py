#
# Foldr a la SML.
# Signature: (a * b -> b) b -> a list b
#
def foldr(combinefn):
    def seedfn(seed):
        def foldfn(list):
            return seed + ''.join(list)
        return foldfn
    return seedfn

# A combine function to try it with
def concat(a, b):
    return ''.join([a, b])
