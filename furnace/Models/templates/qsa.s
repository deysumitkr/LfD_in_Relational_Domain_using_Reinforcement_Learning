use_package(query).
load(models).

heuristic(eucl).

talking(3).
tilde_mode(regression).
euclid(qsa(X), X).

output_options([c45e,lp,ldt_term,prolog,roc01,elaborate]).

%----------------------------------------------

typed_language(yes).
type(number = number).
type(number < number).
type(number > number).

type(objectID(object)).
type(shape(object, number)).
type(size(object, number, number)).
type(area(object, number)).
type(color(object, number, number, number)).
type(position(object, number, number)).

type( north(object, object) ).
type( south(object, object) ).
type( east(object, object) ).
type( west(object, object) ).

type(north(number, number, number, number)).
type(south(number, number, number, number)).
type(east(number, number, number, number)).
type(west(number, number, number, number)).

type( color_distance(object, object, number) ).
type( color_distance(number, number, number, number, number, number, number) ).

type( distance(object, object, number) ).
type( distance(number, number, number, number, number) ).

type( mid(object, object, number, number) ).
type( mid(number, number, number, number, number, number) ).

%------------------------------------------------

%rmode( #((C: member(C,[10, 50, 100, 500, 1000])), (nearx(-ID1, +-ID2, C), neary(-ID1, +-ID2, C))) ).
%rmode( #(C: member(C,[10, 50, 100, 500, 1000]), (neary(-ID1, +-ID2, C))) ).

rmode( (objectID(+-ID)) ).
rmode( (position(+-ID, +-X, +-Y), objectID(ID)) ).


rmode( (distance(+-ID1, +-ID2, D), D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) ).
%rmode( (distance(+X1, +Y1, +X2, +Y2, D), D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) ).


rmode( (color_distance(+-ID1, +-ID2, D), D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400]) ).
%rmode( (color_distance(+R1, +G1, +B1, +R2, +G2, +B2, D), D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400]) ).
/*
rmode( (position(+-ID1, X1, Y1), position(+-ID2, X2, Y2), north(X1, Y1, X2, Y2)) ).
rmode( (position(+-ID1, X1, Y1), position(+-ID2, X2, Y2), south(X1, Y1, X2, Y2)) ).
rmode( (position(+-ID1, X1, Y1), position(+-ID2, X2, Y2), east(X1, Y1, X2, Y2)) ).
rmode( (position(+-ID1, X1, Y1), position(+-ID2, X2, Y2), west(X1, Y1, X2, Y2)) ).

rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	color_distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400]
)).

rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).
*/

%% ---------- Only Direction --------------

rmode(( north(+ID1, +ID2) )).
rmode(( south(+ID1, +ID2) )).
rmode(( east(+ID1, +ID2) )).
rmode(( west(+ID1, +ID2) )).

rmode(( north(+ID1, +ID2), east(ID1, ID2) )).
rmode(( south(+ID1, +ID2), east(ID1, ID2) )).
rmode(( north(+ID1, +ID2), west(ID1, ID2) )).
rmode(( south(+ID1, +ID2), west(ID1, ID2) )).

rmode(( shape(+ID1, #), shape(+ID2, #), north(ID1, ID2) )).
rmode(( shape(+ID1, #), shape(+ID2, #), south(ID1, ID2) )).
rmode(( shape(+ID1, #), shape(+ID2, #), east(ID1, ID2) )).
rmode(( shape(+ID1, #), shape(+ID2, #), west(ID1, ID2) )).

rmode(( shape(+ID1, #), shape(+ID2, #), north(ID1, ID2), east(ID1, ID2) )).
rmode(( shape(+ID1, #), shape(+ID2, #), south(ID1, ID2), east(ID1, ID2) )).
rmode(( shape(+ID1, #), shape(+ID2, #), north(ID1, ID2), west(ID1, ID2) )).
rmode(( shape(+ID1, #), shape(+ID2, #), south(ID1, ID2), west(ID1, ID2) )).

%%--------------------------------------------

%% ----------------- direction, distance, shape ---------------
rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	north(ID1, ID2),
	distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).

rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	south(ID1, ID2),
	distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).

rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	east(ID1, ID2),
	distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).

rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	west(ID1, ID2),
	distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).
%%-----------------------------------------------------------------

rmode((
	objectID(+-ID1), objectID(+-ID2),
	shape(ID1, #), shape(ID2, #),
	color_distance(ID1, ID2, -DC),
	DC < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400],
	distance(ID1, ID2, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).

rmode((
	objectID(+-ID1), objectID(+-ID2), objectID(+-ID3),
	shape(ID1, #), shape(ID2, #), shape(ID3, #),
	mid(ID1, ID2, -X, -Y),
	position(ID3, -X3, -Y3),
	distance(X, Y, X3, Y3, -D),
	D < #[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
)).


