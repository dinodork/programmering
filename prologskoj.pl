woman(mia).
woman(jody).
woman(yolanda).

father(christoffer_Walken, butch).
father(benny, lolly).
father(dude, christoffer_Walken).

mother(lolly, butch).

grandfather(X, Z) :- father(Y, Z), father(X, Y).
grandfather(X, Z) :- mother(Y, Z), father(X, Y).

loves(mia, marsellus).
loves(X, Y) :- loves(Y, X), !.

first(X, [X|_]).
