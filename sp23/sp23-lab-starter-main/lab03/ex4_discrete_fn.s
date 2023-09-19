.globl f # this allows other files to find the function f

# f takes in two arguments:
# a0 is the value we want to evaluate f at
# a1 is the address of the "output" array (defined above).
# The return value should be stored in a0
f:
    # Your code here
    # Initialize the registers
    addi t0 x0 6
    addi t1 x0 61
    addi t2 x0 17
    addi t3 x0 -38
    addi t4 x0 19
    addi t5 x0 42
    addi t6 x0 5
    

    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra
