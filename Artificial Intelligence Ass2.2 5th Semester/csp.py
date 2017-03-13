"""CSP (Constraint Satisfaction Problems) problems and solvers. (Chapter 6)."""

from utils import *

class CSP:
    """This class describes finite-domain Constraint Satisfaction Problems.
    A CSP is specified by the following inputs:
        vars        A list of variables; each is atomic (e.g. int or string).
        domains     A dict of {var:[possible_value, ...]} entries.
        neighbors   A dict of {var:[var,...]} that for each variable lists
                    the other variables that participate in constraints.
        assignment  A dict of {var:val} entries

    The class supports data structures and methods that help you
    solve CSPs by calling a search function on the CSP.
    """

    def __init__(self, vars, domains, neighbors, has_conflict):
        "Construct a CSP problem." 
        update(self, vars=vars, domains=domains, neighbors=neighbors, has_conflict=has_conflict)

    def assign(self, var, val, assignment):
        "Add {var: val} to assignment; Discard the old value if any."
        assignment[var] = val

    def unassign(self, var, assignment):
        "Remove {var: val} from assignment."
        del assignment[var]

    def nconflicts(self, var, val, assignment):
        "Returns the number of conflicts var=val has with other variables."
        # Subclasses may implement this more efficiently
        abstract
        
    def has_conflict(self, var, val, assignment):
        "Returns true if there is a conflict with other variables."
        # Subclasses may implement this more efficiently
        abstract    

    def display(self, assignment):
        "Show a human-readable representation of the CSP."
        # Subclasses can print in a prettier way
        print 'CSP:', self, 'with assignment:', assignment

    def prune(self, var, value, removals):
        "Rule out var=value."
        self.domains[var].remove(value)
        removals.append((var, value))

    def suppose(self, var, value):
        "Keep removals and assume var=value."
        removals = [(var, a) for a in self.domains[var] if a != value]
        self.domains[var] = [value]
        return removals
        
    def restore(self, removals):
        "Undo a supposition and all inferences from it."
        for B, b in removals:
            self.domains[B].append(b)

    def conflicted_vars(self, current, nconflicts_counter):
        "Return a list of variables in current assignment that are in conflict"
        nconflicts_counter[0] += len(self.vars)                     #added this line to count conflicts
        return [var for var in self.vars
            if self.has_conflict(var, current[var], current) == True]
