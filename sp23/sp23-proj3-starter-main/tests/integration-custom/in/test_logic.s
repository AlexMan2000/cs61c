slli t0, t1, 12
xori t2, t0, 22
srli t0, t2, 10
srai t0, t2, 13
ori t0, t1, 12
andi t2, t2, 13
slti t2, t2, 15

xori t2, t0, -22
andi t2, t2, -13
slti t2, t2, -15