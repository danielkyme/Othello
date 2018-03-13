
Contributions:
We spent much of our time for this project coding together, so many parts of the
assignment were done together. Daniel spent more time on building SimplePlayer
and designed the heuristics and Ankush spent more time on implementing the
minimax algorithm. We both spent time updating the heuristic together to prepare
it for tournament quality.

We started out with our random SimplePlayer algorithm and then implemented
Heuristics and minimax algorithm. At first, we realized that the depth was not
properly working (i.e. a depth of 10000 ran at the same rate as depth of 2). 
We realized what the problem was. We were not copying the board correctly in our
minimax algorithm, and so the board that was being used in minimax was not the 
correct board that should have been passed into the function. So,
we fixed that issue first off and minimax then appeared to work as it should. 
Also, the heuristic given penalizes "good" moves, which we fixed by altering the
heuristic a bit. We feel that our new minimax algorithm will be better able to 
win the tournament since the depth portion is working properly now. Also, we 
refined our Heuristic so that the point system is different based on how we 
intuitively play Othello, so we feel confident that we will fare well against 
most teams. 
