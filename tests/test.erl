-module(sudoku).
-author(vmiklos@frugalware.org).
-vsn('2009-11-10').
-compile(export_all).

% Return the value of Fun or an empty list based on the value of If.
% @spec fun_or_empty(If::bool(), Fun::fun() -> [any()]) -> Ret::[any()]
% Ret = Fun() if If is true, [] otherwise.
fun_or_empty(If, Fun) ->
	case If of
		true -> Fun();
		_ -> []
	end.

% Return a cell from a field.
% @spec field(I::integer(), J::integer(), Table::[any()], M::integer()) ->
% 	Ret::any()
% Table is a flatten list of lists, M is the length of a row,
% representing a matrix, Ret is the cell in the Ith row and Jth column.
field(I, J, Table, M) ->
	P = (I-1)*M+J,
	case P > length(Table) of
		true -> 0;
		_ -> lists:nth((I-1)*M+J, Table)
	end.

% Return a cell from a field.
% @spec field(I::integer(), J::integer(), Table::[[any()]]) ->
% 	Ret::any()
% Ret is the cell in the Ith row and Jth column of Table.
field(I, J, Table) ->
	lists:nth(J, lists:nth(I, Table)).


% Round up.
% @spec ceil(X::float()) -> Ret::integer().
% Ret is the value of X, rounded up to an integer.
ceil(X) ->
	T = trunc(X),
	case X - T == 0 of
		true -> T;
		false -> T + 1
	end.

% This is the same as lists:seq(), but it returns an empty list if the
% second argument is true to make the program work with Erlang-R12, not
% just with R13.
% @spec seq(N::integer(), M::integer()) -> Ret::[integer()].
seq(_, 0) -> [];
seq(N, M) -> lists:seq(N, M).

% Finds possible values for a cell.
% @spec possible({N::integer(), Rules::[[s | w | integer()]],
% 	M::integer(), K::integer()}, L::[integer()]) -> Ret::[integer()].
% N is the distance of cells required when the s/w info is available.
% Rules is a list of lists, containing s/w/integer infos.
% M = K*K is the length of a row.
% L is a partial solution.
% Ret is a list of possible values for the next cell if the list of
% already filled ones is L.
possible(_P = {N, Rules, M, K}, L) ->
	X = (length(L) rem M)+1,
	Y = (length(L) div M)+1,
	Ok = lists:seq(1, M),
	R = field(Y, X, Rules),
	Integers = [I || I <- R, is_integer(I)],
	% first exclude values based on the s, w and integer info rules
	% and the values of both the already filled list and the
	% Rules matrix
	Swdeny = lists:append([
		fun_or_empty(X > 1 andalso lists:member(w, R),
			fun() -> X1 = field(Y, X-1, L, M), Ok -- [X1+N, X1-N] end),
		fun_or_empty(X > 1 andalso not lists:member(w, R),
			fun() -> X1 = field(Y, X-1, L, M), [X1+N, X1-N] end),
		fun_or_empty(Y > 1 andalso lists:member(s, field(Y-1, X, Rules)),
			fun() -> Y1 = field(Y-1, X, L, M), Ok -- [Y1+N, Y1-N] end),
		fun_or_empty(Y > 1 andalso not lists:member(s, field(Y-1, X, Rules)),
			fun() -> Y1 = field(Y-1, X, L, M), [Y1+N, Y1-N] end),
		fun_or_empty(length(Integers) > 0, fun() -> Ok -- Integers end)
	]),
	% these exclude values based on row / column rules and the
	% values of the Rules matrix
	Rulesdeny = case [I || I <- R, is_integer(I)] =:= [] of
		true -> lists:append(
				lists:nth(Y, Rules) ++ % row
				[lists:nth(X, I) || I <- Rules] ++ % column
				[field(I, J, Rules) || % subcell
					J <- lists:seq((ceil(X / K) - 1)* K + 1, (ceil(X / K) - 1)* K + K),
					I <- lists:seq((ceil(Y / K) - 1)* K + 1, (ceil(Y / K) - 1)* K + K)]
			);
		_ -> []
	end,
	% these exclude values based on row, column and subcell rules,
	% based on the already filled values
	Rowdeny = lists:nthtail((length(L) div M)*M, L),
	Coldeny = [lists:nth(M*(I-1)+X, L) || I <- seq(1, Y-1)],
	Subdeny = [lists:nth((I-1)*M+J, L) ||
		J <- lists:seq((ceil(X / K) - 1)* K + 1, (ceil(X / K) - 1)* K + K),
		I <- lists:seq((ceil(Y / K) - 1)* K + 1, (ceil(Y / K) - 1)* K + K),
		(I-1)*M+J < length(L)+1],
	Ok -- lists:append([Swdeny, Rulesdeny, Rowdeny, Coldeny, Subdeny]).
