"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* University/Faculty    : National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor    : Artificial Intelligence - Koumparakis Manolis
* File name             : problem1_5.py
* Name/Surname          : Nikolaos Mpegetis
* A.M                   : 1115200700281
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

from search import *                                    #aima-python code
import sys, time

"""
* classes and functions
"""

class Hanoi(Problem):

    def __init__(self, diskListRange):
    #constructor                
        first = []
        last = []
        for i in range(len(diskListRange)):
            first.append(1)
            last.append(3)
        self.initialPos, self.goalPos = tuple(first), tuple(last)
        Problem.__init__(self, self.initialPos, self.goalPos)
            
    def actions(self, state):
    #returns the valid actions that can be achieved from every state position
        peg1st = -1
        peg2nd = -1
        peg3rd = -1
        curState = list(state)
        allowableActions = []

        if 1 in curState:                                        #if 1 exists in the list of disks
            peg1st = curState.index(1)                           #assign the index of the first disk which is placed on 1st peg
        if 2 in curState:
            peg2nd = curState.index(2)
        if 3 in curState:
            peg3rd = curState.index(3)
        if peg1st != -1 and (peg2nd == -1 or peg1st < peg2nd):
            allowableActions.append((1, 2))
        if peg1st != -1 and (peg3rd == -1 or peg1st < peg3rd):
            allowableActions.append((1, 3))
        if peg2nd != -1 and (peg1st == -1 or peg2nd < peg1st):
            allowableActions.append((2, 1))
        if peg2nd != -1 and (peg3rd == -1 or peg2nd < peg3rd):
            allowableActions.append((2, 3))
        if peg3rd != -1 and (peg1st == -1 or peg3rd < peg1st):
            allowableActions.append((3, 1))
        if peg3rd != -1 and (peg2nd == -1 or peg3rd < peg2nd):
            allowableActions.append((3, 2))
        #print peg1st, peg2nd, peg3rd, curState, allowableActions#uncomment to see how it works
        return allowableActions
            
    def result(self, state, action):
    #returns the next state position depending on what the action is
        nextState = list(state)                             #converting the tuple into list to be mutable and elabotate its' elements.
                                                            #At first it is assigned with the current state
        if action == (1, 2):
            diskPeg = nextState.index(1)                         #Return the index in the list(of disks) of the first disk whose value is 1, a.k.a is placed on the 1st peg.
            nextState.pop(diskPeg)                               #then that index content of the list is poped out
            nextState.insert(diskPeg, 2)                         #and in its place 2 is inserted, a.k.a that disk is moved and placed on the 2nd peg
        elif action == (1, 3):
            diskPeg = nextState.index(1)
            nextState.pop(diskPeg)
            nextState.insert(diskPeg, 3)
        elif action == (2, 1):
            diskPeg = nextState.index(2)
            nextState.pop(diskPeg)
            nextState.insert(diskPeg, 1)
        elif action == (2, 3):
            diskPeg = nextState.index(2)
            nextState.pop(diskPeg)
            nextState.insert(diskPeg, 3)
        elif action == (3, 1):
            diskPeg = nextState.index(3)
            nextState.pop(diskPeg)
            nextState.insert(diskPeg, 1)
        elif action == (3, 2):
            diskPeg = nextState.index(3)
            nextState.pop(diskPeg)
            nextState.insert(diskPeg, 2)
        #print diskPeg, nextState                                #uncomment to see how it works
        return tuple(nextState)
            
    def path_cost(self, c, state1, action, state2):
    #returns the cost between the currentState and the nextState
        return c+1 
            
    def hanoi_heuristic(self, node):
    #1st proposed hanoi heuristic in a.i. exercise 1.5 
    #counting the number of disks(=cost of actions) that are different than the goal peg.
        h_n = 0
        for i in range(len(node.state)):
            if node.state[i] != 3:
                h_n += 1
        return h_n


"""
* initialPos of the main program
"""


hanoi = Hanoi(range(int(input('Type a small integer for hanoi disks (eg. 6) <integers bigger than 10 are going to detain> : '))))

start = time.clock()                               # starting time 

search = astar_search(hanoi, hanoi.hanoi_heuristic)
search_result = search.solution()                  # Actions to be done from the initial position to current position
path = search.path()                               # Nodes to be followed to have a solution

end = time.clock()                                 # ending time

print "\nGame solution: \n{0}\n||No.\t|State\t\t\t|Action\t|Cost\t||\n||{1}||".format('='*50,'='*46)
for i in range(len(path)) :

    state = path[i].state
    action = " "
    cost = path[i].path_cost
    if i > 0 :
        action = search_result[i-1]

    print("|| {0}\t| {1} \t| {2}| {3}\t||".format(i, state, action, cost))
print("{0}".format('='*50))
print('Execution time : %.3f seconds'%(end-start))

