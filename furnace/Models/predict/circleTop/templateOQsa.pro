
:- style_check(-singleton).
:- style_check(-discontiguous).
:- initialization(main).
 
main:-
        class(X), 
        pops(X),
        halt.
 
pops([]):- nl.  
pops([H|T]):-   
        write(H),
pops(T).




%% Background KB
area(W, H, A):- A is W*H.
area(ID, A):- size(ID, W, H), area(W, H, A).

distance(X1, Y1, X2, Y2, D):- D is sqrt((X1-X2)**2 + (Y1-Y2)**2).
distance(ID1, ID2, D):-
	position(ID1, X1, Y1), position(ID2, X2, Y2),
	distance(X1, Y1, X2, Y2, D).
	
color_distance(R1, G1, B1, R2, G2, B2, D):- D is sqrt((R1-R2)**2 + (G1-G2)**2 + (B1-B2)**2).
color_distance(ID1, ID2, D):-
	color(ID1, R1, G1, B1), color(ID2, R2, G2, B2),
	color_distance(R1, G1, B1, R2, G2, B2, D).
	
mid(X1, Y1, X2, Y2, X, Y):- X is (X1 + X2)/2, Y is (Y1 + Y2)/2.
mid(ID1, ID2, X, Y):-
	position(ID1, X1, Y1), position(ID2, X2, Y2),
	mid(X1, Y1, X2, Y2, X, Y).
	
north(_X1, Y1, _X2, Y2):- Y1 < Y2.
north(ID1, ID2):- position(ID1, X1, Y1), position(ID2, X2, Y2), north(X1, Y1, X2, Y2).

south(_X1, Y1, _X2, Y2):- Y1 > Y2.
south(ID1, ID2):- position(ID1, X1, Y1), position(ID2, X2, Y2), south(X1, Y1, X2, Y2).

east(X1, _Y1, X2, _Y2):- X1 > X2.
east(ID1, ID2):- position(ID1, X1, Y1), position(ID2, X2, Y2), east(X1, Y1, X2, Y2).

west(X1, _Y1, X2, _Y2):- X1 < X2.
west(ID1, ID2):- position(ID1, X1, Y1), position(ID2, X2, Y2), west(X1, Y1, X2, Y2).

%% Learnt Model
class([1.49367088607595]).
% 79.0 examples.


