"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
* University/Faculty    : National Kapodistrian University of Athens - Department of Informatics and Telecommunications
* Course - Professor    : Artificial Intelligence - Koumparakis Manolis
* File name             : problem2_2.py
* Name/Surname          : Nikolaos Mpegetis
* A.M                   : 1115200700281
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

from csp_search import *              #adds imports from utils, csp, sys, math
import time

"""
* classes and functions
"""


class MapColoring(CSP):
    """ 
    >>> backtracking_search(australia)
    {'WA': 'R', 'Q': 'R', 'T': 'R', 'V': 'R', 'SA': 'G', 'NT': 'B', 'NSW': 'B'}
    >>> backtracking_search(australia, select_unassigned_variable=mrv)
    {'WA': 'R', 'Q': 'R', 'T': 'R', 'V': 'R', 'SA': 'G', 'NT': 'B', 'NSW': 'B'}
    >>> backtracking_search(australia, inference=forward_checking)
    {'Q': 'R', 'T': 'R', 'WA': 'R', 'V': 'R', 'SA': 'G', 'NT': 'B', 'NSW': 'B'}
    >>> backtracking_search(australia, inference=mac)
    {'WA': 'R', 'Q': 'R', 'T': 'R', 'V': 'R', 'SA': 'G', 'NT': 'B', 'NSW': 'B'}
    >>> backtracking_search(usa, select_unassigned_variable=mrv, inference=mac)
    {'WA': 'R', 'DE': 'G', 'DC': 'R', 'WI': 'G', 'WV': 'B', 'HI': 'R', 'FL': 'B', 'WY': 'R', 'NH': 'G', 'NJ': 'B', 'NM': 'R', 'TX': 'G', 'LA': 'B', 'NC': 'R', 'ND': 'R', 'NE': 'B', 'TN': 'B', 'NY': 'G', 'PA': 'R', 'RI': 'G', 'NV': 'R', 'VA': 'G', 'CO': 'G', 'CA': 'G', 'AL': 'R', 'AR': 'R', 'VT': 'R', 'IL': 'B', 'GA': 'G', 'IN': 'G', 'IA': 'R', 'MA': 'B', 'AZ': 'B', 'ID': 'G', 'CT': 'R', 'ME': 'R', 'MD': 'Y', 'KA': 'R', 'OK': 'B', 'OH': 'Y', 'UT': 'Y', 'MO': 'G', 'MN': 'B', 'MI': 'R', 'AK': 'R', 'MT': 'B', 'MS': 'G', 'SC': 'B', 'KY': 'R', 'OR': 'B', 'SD': 'G'}
    >>> min_conflicts(usa, 100000)
    {'WA': 'R', 'DE': 'G', 'DC': 'R', 'WI': 'G', 'WV': 'B', 'HI': 'R', 'FL': 'B', 'WY': 'R', 'NH': 'G', 'NJ': 'B', 'NM': 'R', 'TX': 'G', 'LA': 'B', 'NC': 'R', 'ND': 'R', 'NE': 'B', 'TN': 'B', 'NY': 'G', 'PA': 'R', 'RI': 'G', 'NV': 'R', 'VA': 'G', 'CO': 'G', 'CA': 'G', 'AL': 'R', 'AR': 'R', 'VT': 'R', 'IL': 'B', 'GA': 'G', 'IN': 'G', 'IA': 'R', 'OK': 'B', 'AZ': 'B', 'ID': 'G', 'CT': 'R', 'ME': 'R', 'MD': 'Y', 'KA': 'R', 'MA': 'B', 'OH': 'Y', 'UT': 'Y', 'MO': 'G', 'MN': 'B', 'MI': 'R', 'AK': 'R', 'MT': 'B', 'MS': 'G', 'SC': 'B', 'KY': 'R', 'OR': 'B', 'SD': 'G'}
    """

    def __init__(self, colors, neighbors):
        """Make a CSP for the problem of coloring a map with different colors
        for any two adjacent regions.  Arguments are a list of colors, and a
        dict of {region: [neighbor,...]} entries.  This dict may also be
        specified as a string of the form defined by parse_neighbors."""
        if isinstance(neighbors, str):
            neighbors = parse_neighbors(neighbors)
        domain=dict()    
        for i in neighbors.keys():
            domain[i]=colors[:]
                 
        CSP.__init__(self, neighbors.keys(), domain, neighbors, self.has_conflict)        
                   
    def has_conflict(self, var, val, assignment):
        "A constraint saying two neighboring variables must differ in value."
        for neighbor in self.neighbors[var]:
            if neighbor in assignment:
                if assignment[neighbor] == val:
                    return True
        return False  

    def arc_conflict(self, A, a, B, b):
        "A constraint saying two neighboring variables must differ in value."
        if a != b :
            return False
        else:
            return True 
             
    def nconflicts(self, var, val, assignment):                             
        conflicts=0

        for neighbor in self.neighbors[var]:
            if neighbor in assignment:
                if assignment[neighbor] == val:
                    conflicts+=1 
        return conflicts  

		
def parse_neighbors(neighbors, vars=[]):
    """Convert a string of the form 'X: Y Z; Y: Z' into a dict mapping
    regions to neighbors.  The syntax is a region name followed by a ':'
    followed by zero or more region names, followed by ';', repeated for
    each region name.  If you say 'X: Y' you don't need 'Y: X'.
    >>> parse_neighbors('X: Y Z; Y: Z')
    {'Y': ['X', 'Z'], 'X': ['Y', 'Z'], 'Z': ['X', 'Y']}
    """
    dict = DefaultDict([])
    for var in vars:
        dict[var] = []
    specs = [spec.split(':') for spec in neighbors.split(';')]
    for (A, Aneighbors) in specs:
        A = A.strip()
        dict.setdefault(A, [])
        for B in Aneighbors.split():
            dict[A].append(B)
            dict[B].append(A)
    return dict

	
"""
* start of the main program
"""

australia = MapColoring(list('RGB'), """SA: WA NT Q NSW V; NT: WA Q; NSW: Q V; T: """)
usa = MapColoring(list('RGBY'),
        """WA: OR ID; OR: ID NV CA; CA: NV AZ; NV: ID UT AZ; ID: MT WY UT;
        UT: WY CO AZ; MT: ND SD WY; WY: SD NE CO; CO: NE KA OK NM; NM: OK TX;
        ND: MN SD; SD: MN IA NE; NE: IA MO KA; KA: MO OK; OK: MO AR TX;
        TX: AR LA; MN: WI IA; IA: WI IL MO; MO: IL KY TN AR; AR: MS TN LA;
        LA: MS; WI: MI IL; IL: IN KY; IN: OH KY; MS: TN AL; AL: TN GA FL;
        MI: OH IN; OH: PA WV KY; KY: WV VA TN; TN: VA NC GA; GA: NC SC FL;
        PA: NY NJ DE MD WV; WV: MD VA; VA: MD DC NC; NC: SC; NY: VT MA CT NJ;
        NJ: DE; DE: MD; MD: DC; VT: NH MA; MA: NH RI CT; CT: RI; ME: NH;
        HI: ; AK: """)
france = MapColoring(list('RGBY'),
        """AL: LO FC; AQ: MP LI PC; AU: LI CE BO RA LR MP; BO: CE IF CA FC RA
        AU; BR: NB PL; CA: IF PI LO FC BO; CE: PL NB NH IF BO AU LI PC; FC: BO
        CA LO AL RA; IF: NH PI CA BO CE; LI: PC CE AU MP AQ; LO: CA AL FC; LR:
        MP AU RA PA; MP: AQ LI AU LR; NB: NH CE PL BR; NH: PI IF CE NB; NO:
        PI; PA: LR RA; PC: PL CE LI AQ; PI: NH NO CA IF; PL: BR NB CE PC; RA:
        AU BO FC PA LR""")

print 'Switch the algorithm you want to use for finding a solution for map coloring Australia, USA and France :\n1. FC+MRV (forward checking search with the heurestic mechanism MRV)\n2. MAC (maintaining arc consistency)\n3. Min-Conflicts (minimum conflicts)\n'
s = input('Type : ')
while s>3 or s<1:
    s = input('Type again (1-3) : ')
    if s>0 and s<4:
        break

if s == 1:
    print 'Forward checking search with the heurestic mechanism MRV(FC+MRV) is selected\n'
    start1 = time.clock()                               # starting time
    solution_result1,conflicts1,assignments1 = backtracking_search(australia, mrv , forward_checking)
    end1 = time.clock()                                 # ending time
    start2 = time.clock()                               # starting time
    solution_result2,conflicts2,assignments2 = backtracking_search(usa, mrv , forward_checking)
    end2 = time.clock()                                 # ending time
    start3 = time.clock()                               # starting time
    solution_result3,conflicts3,assignments3 = backtracking_search(france, mrv , forward_checking)
    end3 = time.clock()                                 # ending time
elif s == 2:
    print 'Maintaining arc consistency (MAC) is selected\n'
    start1 = time.clock()                               # starting time
    solution_result1,conflicts1,assignments1 = backtracking_search(australia,first_unassigned_variable,mac)
    end1 = time.clock()                                 # ending time
    start2 = time.clock()                               # starting time
    solution_result2,conflicts2,assignments2 = backtracking_search(usa,first_unassigned_variable,mac)
    end2 = time.clock()                                 # ending time
    start3 = time.clock()                               # starting time
    solution_result3,conflicts3,assignments3 = backtracking_search(france,first_unassigned_variable,mac)
    end3 = time.clock()                                 # ending time
elif s == 3:
    print 'Minimum conflicts (Min-Conflicts) is selected\n'
    start1 = time.clock()                               # starting time
    solution_result1,conflicts1,assignments1 = min_conflicts(australia,9999)
    end1 = time.clock()                                 # ending time
    start2 = time.clock()                               # starting time
    solution_result2,conflicts2,assignments2 = min_conflicts(usa,9999)
    end2 = time.clock()                                 # ending time
    start3 = time.clock()                               # starting time
    solution_result3,conflicts3,assignments3 = min_conflicts(france,9999)
    end3 = time.clock()                                 # ending time

print "\nMap Coloring solution: \n"

print "AUSTRALIA\n Map coloring result: ", solution_result1
print "\nTotal puzzle conflicts: ", conflicts1[0]
print "Total assignments: ", assignments1[0]
print 'Execution time of Austalia map coloring : %.3f seconds'%(end1-start1)

print "\n\nUSA\n Map coloring result: ", solution_result2
print "\nTotal puzzle conflicts: ", conflicts2[0]
print "Total assignments: ", assignments2[0]
print 'Execution time of USA map coloring : %.3f seconds'%(end2-start2)

print "\n\nFRANCE\n Map coloring result: ", solution_result3
print "\nTotal puzzle conflicts: ", conflicts3[0]
print "Total assignments: ", assignments3[0]
print 'Execution time of France map coloring : %.3f seconds'%(end3-start3)
