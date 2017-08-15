
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
class([0.9743184]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<300,objectID(B),objectID(A),objectID(B),shape(B,1),shape(A,0),shape(B,1),mid(B,A,E,F),position(B,G,H),distance(E,F,G,H,I),I<90,objectID(B),objectID(A),shape(B,1),shape(A,0),north(B,A),distance(B,A,J),J<100, !.
% 10.0 examples.
class([0.876071696333666]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<300,objectID(B),objectID(A),objectID(B),shape(B,1),shape(A,0),shape(B,1),mid(B,A,E,F),position(B,G,H),distance(E,F,G,H,I),I<90,east(A,B), !.
% 12.0 examples.
class([0.9319702392]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<300,objectID(B),objectID(A),objectID(B),shape(B,1),shape(A,0),shape(B,1),mid(B,A,E,F),position(B,G,H),distance(E,F,G,H,I),I<90, !.
% 4.0 examples.
class([0.841432945513]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<300,north(B,A), !.
% 7.0 examples.
class([0.769650290763571]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<300, !.
% 7.0 examples.
class([0.7539495755414]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<500,objectID(B),objectID(A),shape(B,1),shape(A,0),north(B,A),distance(B,A,E),E<400, !.
% 5.0 examples.
class([0.659684366026867]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<500, !.
% 15.0 examples.
class([0.6160316959394]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<700,objectID(B),objectID(A),shape(B,1),shape(A,0),north(B,A),distance(B,A,E),E<600, !.
% 5.0 examples.
class([0.566198062778833]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<700, !.
% 6.0 examples.
class([0.5136150478908]) :- objectID(A),objectID(B),shape(A,1),shape(B,0),north(A,B),distance(A,B,C),C<800, !.
% 5.0 examples.
class([0.473613294059]).
% 3.0 examples.


