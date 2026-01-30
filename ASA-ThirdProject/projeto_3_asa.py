from pulp import *

n, m = map(int, input().split())

current_points = {i: 0 for i in range(1, n+1)}

remaining_matches = {}
for i in range(1, n+1):
    for j in range(i+1, n+1):
        remaining_matches[(i, j)] = 2

for _ in range(m):
    i, j, result = map(int, input().split())
    
    if result == i:
        current_points[i] += 3
    elif result == j:
        current_points[j] += 3
    else:
        current_points[i] += 1
        current_points[j] += 1
    
    pair = (min(i, j), max(i, j))
    remaining_matches[pair] -= 1

remaining_matches = {pair: k for pair, k in remaining_matches.items() if k > 0}#otimizaçao 1

max_possible_points = {i: current_points[i] for i in range(1, n+1)}#otimização 2 e 3
for (i, j), k in remaining_matches.items():
    max_possible_points[i] += 3 * k
    max_possible_points[j] += 3 * k

for target_team in range(1, n+1):
    #otimização 2
    if any(current_points[i] > max_possible_points[target_team] for i in range(1, n+1) if i != target_team):
        print(-1)
        continue
    #otimização 3
    if all(current_points[target_team] >= current_points[i] for i in range(1, n+1) if i != target_team):
        print(0)
        continue
    
    prob = LpProblem(f"MinWins_Team{target_team}", LpMinimize)
    
    team_points_vars = {}
    for i in range(1, n+1):
        team_points_vars[i] = LpVariable(f"points_{i}_t{target_team}", 0, None, cat='Integer')
    
    match_vars = {}
    for (i, j), k in remaining_matches.items():

        match_vars[(i, j, 'win_i')] = LpVariable(f"w_{i}_{j}_t{target_team}", 0, k, cat='Integer')
        match_vars[(i, j, 'win_j')] = LpVariable(f"w_{j}_{i}_t{target_team}", 0, k, cat='Integer')
        match_vars[(i, j, 'draw')] = LpVariable(f"d_{i}_{j}_t{target_team}", 0, k, cat='Integer')
        
        prob += match_vars[(i, j, 'win_i')] + match_vars[(i, j, 'win_j')] + match_vars[(i, j, 'draw')] == k

    for team in range(1, n+1):
        wins = []
        draws = []
        
        for (i, j), k in remaining_matches.items():
        
            if i == team:
                wins.append(match_vars[(i, j, 'win_i')])
                draws.append(match_vars[(i, j, 'draw')])
            elif j == team:
                wins.append(match_vars[(i, j, 'win_j')])
                draws.append(match_vars[(i, j, 'draw')])
    
        if wins or draws:
            prob += team_points_vars[team] == 3 * lpSum(wins) + lpSum(draws)
        else:
            prob += team_points_vars[team] == 0
    
    target_wins = []
    for (i, j), k in remaining_matches.items():

        if i == target_team:
            target_wins.append(match_vars[(i, j, 'win_i')])
        elif j == target_team:
            target_wins.append(match_vars[(i, j, 'win_j')])


    prob.setObjective(lpSum(target_wins))
    
    
    for i in range(1, n+1):
        if i != target_team:
            prob += current_points[target_team] + team_points_vars[target_team] >= current_points[i] + team_points_vars[i]
    
    prob.solve(PULP_CBC_CMD(msg=0))
    
    if prob.status == 1:
        obj_value = value(prob.objective)
        print(int(obj_value))
    else:
        print(-1)