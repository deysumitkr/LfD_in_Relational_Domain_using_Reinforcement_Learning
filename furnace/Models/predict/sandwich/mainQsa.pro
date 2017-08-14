
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
class([0.99]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<200,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,N,O),position(C,P,Q),distance(N,O,P,Q,R),R<100,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,S,T),position(C,U,V),distance(S,T,U,V,W),W<40, !.
% 6.0 examples.
class([0.9604]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<200,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,N,O),position(C,P,Q),distance(N,O,P,Q,R),R<100,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,S,T),position(C,U,V),distance(S,T,U,V,W),W<60, !.
% 3.0 examples.
class([0.941192]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<200,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,N,O),position(C,P,Q),distance(N,O,P,Q,R),R<100,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,S,T),position(C,U,V),distance(S,T,U,V,W),W<80, !.
% 3.0 examples.
class([0.92236816]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<200,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,N,O),position(C,P,Q),distance(N,O,P,Q,R),R<100, !.
% 2.0 examples.
class([0.877290794472071]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<200,north(B,A), !.
% 14.0 examples.
class([0.817183973256]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(B),objectID(A),objectID(C),shape(B,0),shape(A,0),shape(C,1),mid(B,A,I,J),position(C,K,L),distance(I,J,K,L,M),M<200, !.
% 3.0 examples.
class([0.805541360696571]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,north(B,A),distance(C,B,I),I<300, !.
% 7.0 examples.
class([0.7691008609325]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,north(B,A), !.
% 4.0 examples.
class([0.7314818781903]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300,objectID(C),objectID(I),shape(C,1),shape(I,0),color_distance(C,I,J),J<300,distance(C,I,K),K<600, !.
% 10.0 examples.
class([0.674557934793]) :- objectID(A),objectID(B),objectID(C),shape(A,0),shape(B,0),shape(C,1),mid(A,B,D,E),position(C,F,G),distance(D,E,F,G,H),H<300, !.
% 4.0 examples.
class([0.709611308903]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<400,distance(A,B,D),D<500,objectID(A),objectID(B),shape(A,0),shape(B,1),north(A,B),distance(A,B,E),E<400,color_distance(B,A,F),F<10, !.
% 5.0 examples.
class([0.648065787175]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<400,distance(A,B,D),D<500,objectID(A),objectID(B),shape(A,0),shape(B,1),north(A,B),distance(A,B,E),E<400, !.
% 6.0 examples.
class([0.643483290087833]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<400,distance(A,B,D),D<500,objectID(B),objectID(E),shape(B,1),shape(E,0),color_distance(B,E,F),F<300,distance(B,E,G),G<800,objectID(B),objectID(H),shape(B,1),shape(H,0),north(B,H),distance(B,H,I),I<600,objectID(H),objectID(E),objectID(B),shape(H,0),shape(E,0),shape(B,1),mid(H,E,J,K),position(B,L,M),distance(J,K,L,M,N),N<500, !.
% 6.0 examples.
class([0.606605209495]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<400,distance(A,B,D),D<500,objectID(B),objectID(E),shape(B,1),shape(E,0),color_distance(B,E,F),F<300,distance(B,E,G),G<800,objectID(B),objectID(H),shape(B,1),shape(H,0),north(B,H),distance(B,H,I),I<600, !.
% 4.0 examples.
class([0.583747541600333]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<400,distance(A,B,D),D<500,objectID(B),objectID(E),shape(B,1),shape(E,0),color_distance(B,E,F),F<300,distance(B,E,G),G<800, !.
% 6.0 examples.
class([0.5568438614476]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<400,distance(A,B,D),D<500, !.
% 5.0 examples.
class([0.5682080218852]) :- objectID(A),objectID(B),shape(A,1),shape(B,0),east(A,B),distance(A,B,C),C<600,color_distance(B,A,D),D<10, !.
% 5.0 examples.
class([0.534647364237333]) :- objectID(A),objectID(B),shape(A,1),shape(B,0),east(A,B),distance(A,B,C),C<600, !.
% 3.0 examples.
class([0.506182009302273]) :- objectID(A),objectID(B),shape(A,0),shape(B,1),color_distance(A,B,C),C<300,distance(A,B,D),D<1000, !.
% 11.0 examples.
class([0.464141028177667]).
% 3.0 examples.


%% State


objectID(1).
shape(1, 1).
color(1, 223, 223, 223).
size(1, 80, 80).
position(1, 640, 360).
objectID(2).
shape(2, 0).
color(2, 223, 223, 223).
size(2, 150, 50).
position(2, 253, 407).
objectID(3).
shape(3, 0).
color(3, 223, 223, 223).
size(3, 150, 50).
position(3, 259, 171).


