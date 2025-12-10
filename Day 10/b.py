# Reddit code

import sys
from z3 import *

def solve():
    total_presses = 0
    
    # Read all lines from input.txt
    with open("input.txt", "r") as f:
        lines = f.readlines()

    for line in lines:
        if not line.strip(): continue
        
        parts = line.strip().split()
        
        # Parse inputs
        # Skip parts[0] (indicator diagram)
        
        buttons = []
        target = []
        
        for p in parts[1:]:
            # Parse Target {3,5,4}
            if p.startswith('{'):
                nums = p[1:-1].split(',')
                target = [int(x) for x in nums]
            # Parse Button (0,1)
            elif p.startswith('('):
                nums = p[1:-1].split(',')
                buttons.append([int(x) for x in nums])

        # Z3 Solver Setup
        s = Optimize()
        
        # Create variables p0, p1... for each button
        presses = [Int(f'p{i}') for i in range(len(buttons))]
        
        # Constraint 1: Presses must be non-negative
        for p in presses:
            s.add(p >= 0)
            
        # Constraint 2: Sum of button effects must equal target for each row
        for r in range(len(target)):
            row_sum = 0
            for b_idx, btn_indices in enumerate(buttons):
                if r in btn_indices:
                    row_sum += presses[b_idx]
            s.add(row_sum == target[r])

        # Objective: Minimize total presses
        s.minimize(Sum(presses))

        if s.check() == sat:
            m = s.model()
            # Calculate sum of all press counts
            machine_total = sum(m[p].as_long() for p in presses)
            total_presses += machine_total

    print(f"Total Minimum Presses: {total_presses}")

if __name__ == "__main__":
    solve()