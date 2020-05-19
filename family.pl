% Program:  family.pl
% Source:   Prolog
%
% Purpose:  This is the sample program for the Prolog Lab in COMP9414/9814/3411.
%           It is a simple Prolog program to demonstrate how prolog works.
%           See lab.html for a full description.
%
% History:  Original code by Barry Drake


% parent(Parent, Child)
%
parent(albert, jim).
parent(albert, peter).
parent(jim, brian).
parent(john, darren).
parent(peter, lee).
parent(peter, sandra).
parent(peter, james).
parent(peter, kate).
parent(peter, kyle).
parent(brian, jenny).
parent(irene, jim).
parent(irene, peter).
parent(pat, brian).
parent(pat, darren).
parent(amanda, jenny).


% female(Person)
%
female(irene).
female(pat).
female(lee).
female(sandra).
female(jenny).
female(amanda).
female(kate).

% male(Person)
%
male(albert).
male(jim).
male(peter).
male(brian).
male(john).
male(darren).
male(james).
male(kyle).


% yearOfBirth(Person, Year).
%
yearOfBirth(irene, 1923).
yearOfBirth(pat, 1954).
yearOfBirth(lee, 1970).
yearOfBirth(sandra, 1973).
yearOfBirth(jenny, 2004).
yearOfBirth(amanda, 1979).
yearOfBirth(albert, 1926).
yearOfBirth(jim, 1949).
yearOfBirth(peter, 1945).
yearOfBirth(brian, 1974).
yearOfBirth(john, 1955).
yearOfBirth(darren, 1976).
yearOfBirth(james, 1969).
yearOfBirth(kate, 1975).
yearOfBirth(kyle, 1976).


% grandParent(Grandparent, Grandchild).
%
grandParent(Grandparent, Grandchild) :-
    parent(Grandparent, Child),
    parent(Child, Grandchild).


% olderperson(Person1, Person2). Person1 is older than Person2
%
olderperson(Person1, Person2) :-
    yearOfBirth(Person1, Year1), 
    yearOfBirth(Person2, Year2),
    Year2 > Year1.
    
    
% siblings(Person1, Person2). 
%
siblings(Person1, Person2) :-
    parent(X, Person1),
    parent(X, Person2),
    Person1 \= Person2.
    
    
% olderBrother(Brother, Person).
%
olderBrother(Brother, Person) :-
    male(Brother),
    siblings(Brother, Person),
    olderperson(Brother, Person).


% descendant(Person, Descendant) :-
%
descendant(Person, Descendant) :-
    parent(Person, Descendant).
    
descendant(Person, Descendant) :-
    parent(Person, Child),
    descendant(Child, Descendant).

% anscestor(Person, Anscestor) :-
%
anscestor(Person, Anscestor) :-
    parent(Anscestor, Person).
    
anscestor(Person, Anscestor) :-
    parent(Parent, Person),
    anscestor(Parent, Anscestor).
    
