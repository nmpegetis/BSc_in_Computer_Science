"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* University/Faculty    : National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor    : Artificial Intelligence - Koumparakis Manolis
* File name             : problem1_1.py
* Name/Surname          : Nikolaos Mpegetis
* A.M                   : 1115200700281
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

from search import *                                    #aima-python code
import math, sys, time

"""
* classes and functions
"""

def finput(fname):
#returns the whole grid list, the initial position of the problem and the goal position of the problem

    file = open(fname, 'r')
    fileLines = []

    print("The game map is:\n")
    for fileColumns in file:
        tempLine = []
        #print(fileLines)
        for index in range(len(fileColumns)):
            #print(tempLine)
            #tempLine.append(fileColumns[index])
            if fileColumns[index] == '3':
                initialPos = (len(fileLines), len(tempLine))#if tempLine.append(fileColumns[index]) is situated above we need : len(tempLine)-1
            if fileColumns[index] == '4':
                goalPos = (len(fileLines), len(tempLine))
            tempLine.append(fileColumns[index])
        fileLines.append(tempLine)
        sys.stdout.write(fileColumns)

    print("\nThe initial and goal positions are :")
    print(tuple(reversed(initialPos)), tuple(reversed(goalPos)))

    return fileLines, initialPos, goalPos


class Game(Problem):

    def __init__(self,fname):
    #constructor
        self.grid, self.initialPos, self.goalPos = finput(fname)
        Problem.__init__(self, self.initialPos, self.goalPos)

    def actions(self,state):
    #returns the valid actions that can be achieved from every state position
        (x,y) = state
        allowableActions = []

        #ckecks if squares exist on grid and are not black squares
        if x-1 >= 0 and self.grid[x-1][y] != '1':
            allowableActions.append('up')
        if x+1 <= (len(self.grid)-1) and self.grid[x+1][y] != '1':
            allowableActions.append('down')
        if y+1 <= (len(self.grid)-1) and self.grid[x][y+1] != '1':
            allowableActions.append('right')
        if y-1 >= 0 and self.grid[x][y-1] != '1':
            allowableActions.append('left')
        return allowableActions

    def result(self, state, action):
    #returns the next state position depending on what the action is
        (x,y) = state
        if action == 'up':
            nextState = (x-1, y)
        elif action == 'down':
            nextState = (x+1, y)
        elif action == 'right':
            nextState = (x, y+1)
        elif action == 'left':
            nextState = (x, y-1)
        return nextState

    def path_cost(self, c, state1, action, state2):
    #returns the cost between the currentState and the nextState
        (x, y) = state2
        if self.grid[x][y] == '0':
            cost = c+1
        elif self.grid[x][y] == '2':
            cost = c+2
        elif self.grid[x][y] == '3':
            cost = c+1
        elif self.grid[x][y] == '4':
            cost = c+1
        return cost

    #heuristics taken from http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html

    def manhattan_simple(self, node):
    #heuristic manhattan_simple distance func without D cost
        (node_x, node_y) = node.state
        (goal_x, goal_y) = self.goalPos
        h_n = math.fabs(node_x-goal_x)+math.fabs(node_y-goal_y)
        return h_n

    def manhattan_improved(self, node):
    #heuristic manhatan
        (node_x, node_y) = node.state
        (goal_x, goal_y) = self.goalPos
        D = 0.05                                                        #equivalent to: 1/<expected maximum path lenght> for this exercise 0.05
        h_n = (1+D)*(math.fabs(node_x-goal_x)+math.fabs(node_y-goal_y))
        return h_n

    def euclidean(self, node):
    #euclidean heuristic func
        (node_x, node_y) = node.state
        (goal_x, goal_y) = self.goalPos
        D =0.05
        h_n = (1+D) * math.sqrt(math.pow((node_x-goal_x), 2) + math.pow((node_y-goal_y), 2));
        return h_n

    def euclidean_squared(self, node):
    #euclidean heuristic func without sqrt
        (node_x, node_y) = node.state
        (goal_x, goal_y) = self.goalPos
        D =0.05
        h_n = (1+D) * (math.pow((node_x-goal_x), 2) + math.pow((node_y-goal_y), 2));
        return h_n

    def diagonial(self, node):                                                 #Chebyshev distance
    #heuristic diagonial distance
        (node_x, node_y) = node.state
        (goal_x, goal_y) = self.goalPos
        D = 0.05
        D2 = 0.05
        h_diagonial_n = min(math.fabs(node_x-goal_x),math.fabs(node_y-goal_y)) #the num of steps you can take along a diagonial
        h_straight_n = math.fabs(node_x-goal_x)+math.fabs(node_y-goal_y)       #the manhattan distance
        h_n = (1+D2)*h_diagonial_n + (1+D)*(h_straight_n-2*h_diagonial_n)
        return h_n

#def heuristic(self):
#selection of the heurestic function
#    print('Switch from the following 5 heurestic functions :\n1. manhattan_simple\n2. manhattan_improved\n3. euclidean\n4. euclidean_squared\n5. diagonial\n')
#    h = input('type the heuristic function you want to use : ')
#    if h == 1:
#        return game.manhattan_simple
#    elif h == 2:
#        return game.manhattan_improved
#    elif h == 3:
#        return game.euclidean
#    elif h == 4:
#        return game.euclidean_squared
#    elif h == 5:
#        return game.diagonial


"""
* start of the main program
"""


game = Game(input('Type the name of the file with the grid(eg."input.txt") : '))

#search = astar_search(game,heuristic)
print('Switch from the following 3 heurestic functions :\n1. manhattan_simple\n2. manhattan_improved\n3. euclidean\n4. euclidean_squared\n5. diagonial\n')
h = input('Type the heuristic function you want to use : ')

start = time.clock()                               # starting time 
while True:
    if h == 1:
        print('Manhattan simple heurestic algorithm is selected\n')
        search = astar_search(game,game.manhattan_simple)
        break
    elif h == 2:
        print('Improved Manhattan heurestic algorithm is selected\n')
        search = astar_search(game,game.manhattan_improved)
        break
    elif h == 3:
        print('Euclidean heurestic algorithm is selected\n')
        search = astar_search(game,game.euclidean)
        break
    elif h == 4:
        print('Euclidean squared (without sqrt computation) heurestic algorithm is selected\n')
        search = astar_search(game,game.euclidean_squared)
        break
    elif h == 5:
        print('Diagonial heurestic algorithm is selected\n')
        search = astar_search(game,game.diagonial)
        break

search_result = search.solution()                  # Actions to be done from the initial position to current position
path = search.path()                               # Nodes to be followed to have a solution

end = time.clock()                                 # ending time

print "\nGame solution: \n{0}\n||No.\t|State\t\t|Action\t|Cost\t||\n||{1}||".format('='*42,'='*38)
for i in range(len(path)) :

    state = path[i].state
    action = " "
    cost = path[i].path_cost
    if i > 0 :
        action = search_result[i-1]

    print("|| {0}\t| {1}\t| {2}\t| {3}\t||".format(i, tuple(reversed(state)), action, cost))
print("{0}".format('='*42))
print('Execution time : %.3f seconds'%(end-start))

