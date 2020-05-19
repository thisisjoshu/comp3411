is_a_list([]).
is_a_list(.(_Head, Tail)) :-
    is_a_list(Tail).

% head_tail(List, Head, Tail) extract the Head and Tail from the List
%
head_tail(.(Head, Tail), Head, Tail).
