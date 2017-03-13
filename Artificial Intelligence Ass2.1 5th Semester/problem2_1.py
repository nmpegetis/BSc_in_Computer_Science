"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* University/Faculty    : National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor    : Artificial Intelligence - Koumparakis Manolis
* File name             : problem2_1.py
* Name/Surname          : Nikolaos Mpegetis
* A.M                   : 1115200700281
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

from input_puzzles import *
from csp_search import *              #adds imports from utils, csp, sys, math
import time

"""
* classes and functions
"""

def finput(puzzle):
#returns 1.Neighbors: Every neighour(horizontally and vertically) of each vacant box.
#        2.All_ums: Every horizontal and vertical sum with the boxes from which it comes of, of each list-box.
   neighbors = {}
   all_sums = []
   i = 0
   print("{0}".format('='*42))
   for puzzleLines in puzzle:                             #for every element-list in list with name puzzle
      j = 0
      for puzzleColumns in puzzleLines:                   #for every element in list with name puzzleLines

         #Finding neighbors of every vacant box
         if puzzleColumns == '_':                         #if it's a vacant box
            neighbors[(i,j)] = []
            currLine = i+1
            while currLine < (len(puzzle)):         #while currentLine counter is <= of puzzle list-elements counter
               if puzzle[currLine][j] == '_':       #checks if boxes in below lines vertically are vacant
                  neighbors[(i,j)].append((currLine,j))  #and adds them  boxes(tuples) in the neighbor list
               else:
                  break                             #breaks off the while when a * or a list is found
               currLine += 1

            currLine= i-1
            while currLine >= 0:                    #while currentLine counter is >= of the first puzzle list-elements counter( =0 )
               if puzzle[currLine][j] == '_':       #does the same as above. Here it checks vertically and above puzzle[currLine][j]
                  neighbors[(i,j)].append((currLine,j))
               else:
                  break
               currLine -= 1

            currColumn = j+1
            while currColumn < (len(puzzle[i])):    #while currentColumn counter is <= of puzzle list-elements'-elements counter
               if puzzle[i][currColumn] == '_':     #checks if boxes in right columns horizontally are vacant
                  neighbors[(i,j)].append((i,currColumn))   #and adds them  boxes(tuples) in the neighbor list with all the others
               else:
                  break
               currColumn += 1

            currColumn = j-1
            while currColumn >= 0:                  #while currentColumn counter is >= of the first puzzle list-elements'-element counter( =0 )
               if puzzle[i][currColumn] == '_':     #does the same as above. Here it checks horizontally and left of puzzle[i][currColumn]
                  neighbors[(i,j)].append((i,currColumn))
               else:
                  break
               currColumn -= 1

         #Finding horizontal and vertical sums of every vacant box
         if isinstance(puzzleColumns,list):         #if it's a list #isinstance returns true if puzzle[currLine][j] is a list
            if puzzleColumns[0] != '':              #if there exists a vertical sum
               vertical_sums = [puzzleColumns[0]]   #type first in list 'vertical_sums' the sum(number)
               current_sums = []
               currLine = i+1                       #check the below vertical boxes
               while currLine < (len(puzzle)):      #while currentLine counter is <= of puzzle list-elements counter
                  if puzzle[currLine][j] == '_':    #checks if boxes in below lines vertically are vacant
                     current_sums.append((currLine,j))   #and adds them  boxes(tuples) in the current_sums list with all the others
                  else:
                     break
                  currLine += 1
               vertical_sums.append(current_sums)   #adds in the list of verical_sums the discrit sum(number of puzzleColumns[0]) and the boxes(tuples) of whose content sums in puzzleColumns[0]
               all_sums.append(vertical_sums)       #all the sums vertical and horizontal gathered together in one variable

            if puzzleColumns[1] != '':              #also followed the same logic as above
               horizontal_sums = [puzzleColumns[1]]
               current_sums = []
               currColumn = j+1
               while currColumn < (len(puzzleLines)):
                  if puzzle[i][currColumn] == '_':
                     current_sums.append((i,currColumn))
                  else:
                     break
                  currColumn += 1
               horizontal_sums.append(current_sums)
               all_sums.append(horizontal_sums)     #all the sums vertical and horizontal gathered together in one variable

         #Puzzle printing
         if isinstance(puzzle[i][j],list):
            if j == (len(puzzle[i])-1):
               print("{0}||".format(puzzle[i][j]))
            elif j == 0:
               print("||{0}".format(puzzle[i][j])),
            else:
               print("{0} ".format(puzzle[i][j])),
         else:
            if j == (len(puzzle[i])-1):
               print("{0} \t||".format(puzzle[i][j]))
            elif j == 0:
               print("||  {0}\t".format(puzzle[i][j])),
            else:
               print("{0}\t".format(puzzle[i][j])),
         j = j + 1
      i = i + 1
   print("{0}".format('='*42))
   return neighbors , all_sums


class Kakuro_puzzle(CSP):

   def __init__(self, puzzleSelection):
   #constructor
      self.neighbors, self.sums = finput(puzzleSelection) #Neighbors. A dict of {var:[var,...]} that for each variable, lists the other variables that participate in constraints.
      self.vars = self.neighbors.keys()                          #A list of variables; each is atomic. keys() return a copy of the dictionary’s list of keys.This allows the creation of (value, key) pairs
      self.domains = dict()                                      #A dict of {var:[possible_value, ...]} entries. dict() returns a new empty dictionary.
      for i in self.neighbors.keys():
         for j in self.neighbors[i]:
            self.domains[j] = range(1,10)
      CSP.__init__(self, self.vars, self.domains, self.neighbors, self.has_conflict)

   def has_conflict(self, var, val, assignment):
   #Returns true if there is a conflict with other variables.   (the super class has_confict is declared as abstract)
   #According to the constraint every neighboring variables must be different
      for neighbor in self.neighbors[var]:                       #checks if a neighbor has taken the value val
         if neighbor in assignment:
            if assignment[neighbor] == val:
               return True

      for sum in self.sums:
         temp_total_sum = 0
         assignement_boxes = 0
         if var in sum[1]:
            boxes_sum_number = sum[0]                            #the number of summation in the box 
            vacant_boxes = len(sum[1])                           #the vacant boxes that when their values added together result in the boxes_sum number
            for box_position in sum[1]:
               if box_position in assignment:                    #uncomment the following printings to see how it works
                  assignement_boxes += 1
                  #print ("The box in place {0} has box summation number {1} and {2} vacant boxes next to it".format(box_position,boxes_sum_number,vacant_boxes))
            if assignement_boxes != vacant_boxes:                #implemented when some but not all boxes have a value
               for box_position in sum[1]:
                  if box_position in assignment:
                     temp_total_sum += assignment[box_position]
                     #print ("-The box in place {0} has box summation number {1} and {2} vacant boxes next to it--temp_total_sum is: {3} after adding {4}".format(box_position,boxes_sum_number,vacant_boxes,temp_total_sum,assignment[box_position]))
               if var not in assignment:
                  temp_total_sum += val
                  #print ("---The box in place {0} has box summation number {1} and {2} vacant boxes next to it--temp_total_sum is: {3} after adding {4}".format(box_position,boxes_sum_number,vacant_boxes,temp_total_sum,val))
               if assignement_boxes == vacant_boxes-1:
                  if var not in assignment:
                     if temp_total_sum != boxes_sum_number:
                        return True
                  else:
                     if temp_total_sum > boxes_sum_number:
                        return True
               else:
                  if temp_total_sum > boxes_sum_number:
                     return True
            else:                                                #needed when using forward checking.. implemented when all boxes have a value
               for box_position in sum[1]:
                  temp_total_sum += assignment[box_position]
                  #print ("The box in place {0} has box summation number {1} and {2} vacant boxes next to it  -- temp_total_sum is: {3}".format(box_position,boxes_sum_number,vacant_boxes,temp_total_sum))
               if temp_total_sum != boxes_sum_number:
                  return True
      return False


"""
* start of the main program
"""
rows=[("asdf","asfd"),("1234","1234"),("1","2")]
print rows
#result=[("a","b"),]
#for i in rows:
#   result.append((i["a"],i["b"],),)
#   print result
   
puzzleSelection = input('Type the kakuro puzzle name from the input_puzzles.py that you want to find a solution(eg. type: puzzle0,...,puzzle6) : ')
puzzle = Kakuro_puzzle(puzzleSelection)

print 'Switch the algorithm you want to use for finding a solution :\n1. BT (simple backtracking search)\n2. BT+MRV (backtracking search with the heurestic mechanism MRV)\n3. FC (forward checking search)\n4. FC+MRV (forward checking search with the heurestic mechanism MRV)\n'
s = input('Type : ')
while s>4 or s<1:
    s = input('Type again (1-4) : ')
    if s>0 and s<5:
        break

if s == 1:
    print 'Simple backtracking search(BT) is selected\n'
    start = time.clock()                               # starting time
    solution_result,conflicts,assignments = backtracking_search(puzzle)
    end = time.clock()                                 # ending time
elif s == 2:
    print 'Backtracking search with the heurestic mechanism MRV(BT+MRV) is selected\n'
    start = time.clock()                               # starting time
    solution_result,conflicts,assignments = backtracking_search(puzzle, mrv)
    end = time.clock()                                 # ending time
elif s == 3:
    print 'Forward checking search(FC) is selected\n'
    start = time.clock()                               # starting time
    solution_result,conflicts,assignments = backtracking_search(puzzle,first_unassigned_variable,forward_checking)
    end = time.clock()                                 # ending time
elif s == 4:
    print 'Forward checking search with the heurestic mechanism MRV(FC+MRV) is selected\n'
    start = time.clock()                               # starting time
    solution_result,conflicts,assignments = backtracking_search(puzzle, mrv, forward_checking)
    end = time.clock()                                 # ending time

i = 0
print("\nPuzzle solution: \n{0}".format('='*42))

for puzzleLines in puzzleSelection:                    #for every element(list) in list with name puzzle
   j = 0
   for puzzleColumns in puzzleLines:                   #for every element in list with name puzzleLines
      if isinstance(puzzleSelection[i][j],list):
         if j == (len(puzzleSelection[i])-1):
            print("{0}||".format(puzzleSelection[i][j]))
         elif j == 0:
            print("||{0}".format(puzzleSelection[i][j])),
         else:
            print("{0} ".format(puzzleSelection[i][j])),
      elif puzzleSelection[i][j] == '_':               #if it's an vacant box replace it with a solution found
         if j == (len(puzzleSelection[i])-1):
            print("{0} \t||".format(solution_result[(i,j)]))
         elif j == 0:
            print("||  {0}\t".format(solution_result[(i,j)])),
         else:
            print("{0}\t".format(solution_result[(i,j)])),
      else:
         if j == (len(puzzleSelection[i])-1):
            print("{0} \t||".format(puzzleSelection[i][j]))
         elif j == 0:
            print("||  {0}\t".format(puzzleSelection[i][j])),
         else:
            print("{0}\t".format(puzzleSelection[i][j])),
      j += 1
   i += 1
print("{0}".format('='*42))

print "\nTotal puzzle conflicts: ", conflicts[0]
print "Total assignments: ", assignments[0]
print 'Execution time : %.3f seconds'%(end-start)
