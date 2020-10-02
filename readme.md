# Sudoku Solver

    Sudoku is a very popular board game these days. It's being assessed
    as an NP-complete problem which has made a magnet out of it attracting
    programming talent. Many hugely efficient Sudoku Solvers have been
    constructed till date. Still there is always a room for optimization,
    variations and implementations.

#### Logical Solver

===============================================================================

    I am not going to go into the rules of Sudoku in this document. The
    assignment already lists those rules. It is assumed here that the
    reader is already familiar with the rules. Every Sudoku solver has to
    check validity of a number in a blank cell numerous times. The process
    involves checking if the number is already present in every row, column
    and the block where that cell resides. If the value is valid, it may be
    put there but we cannot be sure unless we make sure none of the other
    values can contend for the same cell. This means for every validation,
    solver has to check in 9*3=27 cells for each number. Or a whopping 243
    checks every cell which is a lot. So if this number can be reduced,
    overall speed of the solvers will increase proportionately.

    As it turns out, we can reduce the number of checks at the expense of
    some memory. We index the board using 3 2D arrays. The indexes are
    updated every time an assignment is made. There are separate indexes
    (or what we refer to as tags) for rows, columns and blocks on the board.

    Consider the cell (4, 5) that is row 4 and column 5. Say that number is 8.
    Now, the tagRow contains the state of the rows. This is the 4th row and
    the number 8 is present there. So we make tagRow[4][8] = True. Similarly
    tagCol[5][8] would be true and this cells falls in the 4th block so
    tagBlk[4][8] would also be true.

    Now suppose we want to check if the number 8 can be put at location (4, 1).
    Originally we would have had to check entire 4th row then the 1st column
    and finally 3rd block for the number 8. Now however, in the best case
    scenario where you check row first, all the code does is checks tagRow[4][8]
    (since it wants to know if the number 8 is already in 4th row). Since the
    value of the tag is true, the program does not have to check further.

    Now, the algorithm is very simple. All the tags are filled first with the
    values of the cells already filled in the problem. Then it goes on checking
    the numbers from 1 to 9 for all rows and columns. If it finds the value is
    valid, it sets a flag. Once it has checked for all the 9 values and has only
    found one valid value, the value is valid and we can assign it (also called
    a singles value or a singleton). If, however, multiple values can be true in
    any cell (after checking with the row, column and block tags), the algorithm
    skips it.

    It goes on recursively checking the values, if it finds the value to be valid,
    it sets the cell and assigns the tags and goes into next iteration. Now, if
    there is any iteration where no value is valid that means we have no more
    singletons present in the puzzle.

    At this point the logical solver can no longer solve the puzzle further. This
    is where the code breaks out of the loop and goes to the backtrack solver.

#### Backtrack Solver

===============================================================================

    Most puzzles with a single solution can be solved with the logical solver.
    Traditionally that means almost all the puzzles can be solved with this
    puzzle. However, nowadays to increase the complexity, the puzzles are
    designed in a way where they can have multiple solutions. This makes
    solving them more challenging.

    In the backtrack solver, we again make use of the same tags which were
    used for logical solving. The algorithm assumes the first valid value to
    be true. It assigns the tags and tries to solve the puzzle logically. If
    it cannot solve the puzzle that means our initial assumption was wrong.
    All the tags are reset and the next valid value for previous cell is used.
    If that also fails to solve the puzzle, we go one more step back and so on.

    The advantage here is again the tags. We are only checking 3 values in
    backtracking instead of 27 for each cell. This makes slight improvement in
    the code. The backtrack goes advancing column by column and then the next
    row. If it finally reaches the last row and column (final cell) and finds a
    valid value that means the puzzle is solved. If there is no valid value at
    the last position then the algorithm again backtracks.

#### Observations

===============================================================================

    As already mentioned above, the singleton logical solver is good enough
    to take care of almost all the easy and medium level puzzles and even
    some hard level puzzles. For others it can fill anywhere from 70% to 90%
    of the board at which point the remaining cells are filled by the
    backtrack algorithm.

    Backtrack algorithm fills the first value it finds to be valid. As we
    already mentioned, there were 2 puzzles in the set which have multiple
    solutions. In that case, this solver finds the first value it can come
    up with. If, instead of checking for valid numbers from 1 to 9, it checks
    them from 9 to 1 then it will give a different result. It can also be a
    constrained randomization algorithm which can do the same thing but at the
    end as long as the answer is correct, as per traditional Sudoku rules, the
    algorithm is working perfect.

#### Future Enhancements

===============================================================================

    As far as the algorithm is concerned, one point is already mentioned
    in the observations section – it cannot handle puzzles with multiple
    solutions. It will provide one correct solution and stop. One
    enhancement would be to store this result and then check for remaining
    numbers (in backtrack) and see if any other solution exists. If it
    does, also store that and keep on doing this till no other solution
    can be found.

    This would take significant amount of time and would considerably slow
    down the process so the algorithm needs to be improved to check that
    case. One thing that I can think of at this point is, after the logical
    solve, try to find the doublets (cells where 2 values are valid) and
    while backtracking, assume one value on this cell and then solve the
    puzzle. This would reduce the sample space from 9 values to 2 values.
    Once this step is done we can find the triplets and so on. This can be
    considered to be a random constrained backtrack implementation.

    This improvement would not speed up the solving time for most puzzles
    but the puzzles with multiple solutions and exotic grids (say 16x16)
    would benefit a lot from it.

#### Algorithm

===============================================================================

    Here is an overly simplified version of the algorithm.

        Reset all the tags
        Read the puzzle
        Logical Solve Loop
            Check validity in row – set flag if valid
            Check validity in column – set flag if valid
            Check validity in block – set flag if valid
            Set flag if all three flags are set
            Check other numbers to make sure it's a singleton
                If it is not a singleton then skip otherwise assign the value to cell
            Make sure we actually made an assignment if not break out and backtrack
        Backtrack Solve Loop
            Check for values serially column by column and then row
            If plausible number is found, assign it and set proper tags
            Call backtrack again
        If no error is found and this is the last cell – return true and exit
        If error is found (no further values and not the last cell) then go to last cell
        Reset the proper tags
        Continue in the backtrack with next value

    The puzzle should be solved at this time if it is not then the
    program exits otherwise it copies the result back to the original
    array which was passed to the puzzle.

===============================================================================
