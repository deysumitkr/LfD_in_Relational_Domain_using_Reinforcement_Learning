
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
class([0.99]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,north(B,A),objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<40, !.
% 8.0 examples.
class([0.9604]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,north(B,A),objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<60, !.
% 4.0 examples.
class([0.937427232]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,north(B,A),objectID(A),objectID(I),objectID(C),shape(A,0),shape(I,0),shape(C,1),mid(A,I,J,K),position(C,L,M),distance(J,K,L,M,N),N<80, !.
% 5.0 examples.
class([0.92236816]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,north(B,A), !.
% 3.0 examples.
class([0.89045237692775]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,objectID(C),objectID(B),shape(C,1),shape(B,0),east(C,B),distance(C,B,I),I<70, !.
% 4.0 examples.
class([0.87264332938925]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,north(B,C),east(B,C), !.
% 4.0 examples.
class([0.834003008399625]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100,distance(C,B,I),I<90, !.
% 8.0 examples.
class([0.7927240372425]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<100, !.
% 2.0 examples.
class([0.654344826716333]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,1),shape(C,0),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<50,objectID(C),objectID(B),objectID(A),shape(C,0),shape(B,1),shape(A,0),mid(C,B,I,J),position(A,K,L),distance(I,J,K,L,M),M<500, !.
% 3.0 examples.
class([0.60974694590575]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,1),shape(C,0),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<50, !.
% 4.0 examples.
class([0.866214875671333]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),north(A,B),distance(A,B,C),C<300, !.
% 6.0 examples.
class([0.695229907092667]) :- objectID(A),objectID(B),shape(A,0),shape(B,0),north(A,B),distance(A,B,C),C<500,objectID(A),objectID(D),objectID(B),shape(A,0),shape(D,1),shape(B,0),mid(A,D,E,F),position(B,G,H),distance(E,F,G,H,I),I<80, !.
% 3.0 examples.
class([0.7613321653675]) :- objectID(A),objectID(B),shape(A,0),shape(B,0),north(A,B),distance(A,B,C),C<500,objectID(D),objectID(E),objectID(E),shape(D,0),shape(E,1),shape(E,1),mid(D,E,F,G),position(E,H,I),distance(F,G,H,I,J),J<70, !.
% 4.0 examples.
class([0.7311834116185]) :- objectID(A),objectID(B),shape(A,0),shape(B,0),north(A,B),distance(A,B,C),C<500, !.
% 4.0 examples.
class([0.817183973256]) :- objectID(A),objectID(B),shape(A,1),shape(B,0),east(A,B),distance(A,B,C),C<400, !.
% 3.0 examples.
class([0.7539495755414]).
% 5.0 examples.


%% State

objectID(1).
shape(1, 0).
color(1, 223, 76, 42).
size(1, 194, 50).
position(1, 1001, 95).
objectID(2).
shape(2, 0).
color(2, 58, 118, 215).
size(2, 194, 50).
position(2, 261, 503).
objectID(3).
shape(3, 1).
color(3, 35, 222, 127).
size(3, 80, 80).
objectID(4).
shape(4, 0).
color(4, 223, 185, 35).
size(4, 212, 50).
position(4, 200, 129).
objectID(5).
shape(5, 0).
color(5, 223, 120, 223).
size(5, 51, 50).
position(5, 1064, 464).
objectID(6).
shape(6, 0).
color(6, 32, 239, 35).
size(6, 215, 50).
position(6, 762, 638).
position(3, 1275, 705).


