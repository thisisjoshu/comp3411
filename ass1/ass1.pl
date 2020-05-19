%
% Course: COMP3411
% Assignment 1: Prolog Programming
% Student Name: Joshua Zobule
% Student zID: z5196042
% Start date: 18/03/2019
% Finish date: 24/03/2019
%

%
% Question 1
%
% sumsq_even(Numbers, Sum) sums the squares of only the even numbers
% in a list of integers.
%

% base case
sumsq_even([], 0).

% even number case
sumsq_even([Item | Rest], Sum) :-
    0 is Item mod 2,
    Square is Item * Item,
    sumsq_even(Rest, NewSum),
    Sum is Square + NewSum.

% odd number case    
sumsq_even([Item | Rest], Sum) :-
    1 is Item mod 2,
    sumsq_even(Rest, Sum).

%
% Question 2
%
% same_name(Person1, Person2) that succeeds if Person1 and Person2
% have the same family name.
%

% case 1. Person1 and Person2 have the same father.
same_name(Person1, Person2) :- 
    parent(Parent, Person1),
    parent(Parent, Person2),
    male(Parent),
    Person1 \== Person2.

% case 2. Person1 is a male anscestor of Person2.
same_name(Person1, Person2) :-
    anscestor(Person1, Person2).
    
% case 3. Person2 is a male anscestor of Person1.
same_name(Person1, Person2) :-
    anscestor(Person2, Person1).
    
    
% anscestor base case    
anscestor(Anscestor, Person) :-
    male(Anscestor),
    parent(Anscestor, Person).

% anscestor recursive case    
anscestor(Anscestor, Person) :-
    male(Anscestor),
    parent(Parent, Person),
    anscestor(Anscestor, Parent).
   
%
% Question 3
%
% sqrt_list(NumberList, ResultList) binds ResultList to the list
% of pairs consisting of a number and its square root for each
% number in NumberList.
%

% base case
sqrt_list([], []).

% recursive case
sqrt_list([Item | Rest], ResultList) :-
    SquareRoot is sqrt(Item),
    ResultList = [[Item, SquareRoot] | ResultListTail],
    sqrt_list(Rest, ResultListTail).

%
% Question 4
%
% sign_runs(List, RunList) that converts a list of numbers into the
% corresponding list of sign runs.
%

% case 1 - empty List
sign_runs([],[]).

% case 2 - List only has 1 item
sign_runs([Item], [[Item]]).

% case 3 - List starts with positive number
sign_runs([Item | Rest], [Pos, Neg | Seq]) :-
    Item >= 0,
	positive([Item | Rest], Pos, Last),
	negative(Last, Neg, Last1),
	sign_runs(Last1, Seq).
	
% case 4 - List starts with negative number
sign_runs([Item | Rest], [Neg, Pos | Seq]) :-
    Item < 0,
	negative([Item | Rest], Neg, Last),
	positive(Last, Pos, Last1),
	sign_runs(Last1, Seq).


positive([Item | Rest], [], [Item | Rest]) :-
	Item < 0.
positive([Item | Rest], [Item| Tail], Last) :-
	Item >= 0,
	positive(Rest, Tail, Last).
positive([], [], []).


negative([Item | Rest], [], [Item | Rest]) :-
	Item >= 0.
negative([Item | Rest], [Item| Tail], Last) :-
	Item < 0,
	negative(Rest, Tail, Last).
negative([], [], []).

      
% 
% Question 5
%
% is_heap(Tree) succeeds if Tree satisfies the heap property.
%

% case 1 - empty Tree
is_heap(empty).

% case 2 - both child nodes empty
is_heap(tree(empty, _Data, empty)).

% case 3 - both child nodes are not empty
is_heap(tree(Left, Data, Right)) :-
	is_nonLeaf(Left, Data, Right),
	check_data(Left, Data, Right),
	is_heap(Left),
	is_heap(Right).
	
% case 4 - one child node is empty
is_heap(tree(Left, Data, Right)) :-
	is_nonLeaf2(Left, Data, Right),
	check_data2(Left, Data, Right),
	is_heap(Left),
	is_heap(Right).


is_nonLeaf(Left, _, Right) :-
	Left \== empty,
	Right \== empty.

is_nonLeaf(Left, _, _) :-
	Left \== empty.

is_nonLeaf(_, _, Right) :-
	Right \== empty.
	
	
is_nonLeaf2(Left, _, Right) :-
    Right = empty,
    Left \== empty.
   
is_nonLeaf2(Left, _, Right) :-
    Left = empty,
    Right \== empty. 


check_data(tree(_L1, Data1, _R1), Data, tree(_L2, Data2, _R2)) :-
	Data =< Data1,
	Data =< Data2.


check_data2(tree(_L1, Data1, _R1), Data, _) :-
	Data =< Data1.

check_data2(_, Data, tree(_L1, Data1, _R1)) :-
	Data =< Data1.
    
