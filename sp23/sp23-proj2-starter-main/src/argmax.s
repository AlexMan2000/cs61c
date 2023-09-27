.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    addi sp sp -12
    sw s0 0(sp)     # Index of the array
    sw s1 4(sp)     # Maximum counter, argmax
    sw s2 8(sp)     # Maximum value till now
        
    # If array_length < 1, return 36 and exit
    bge x0 a1 error 
    
    
    # Initialization
    li s0 0
    li s1 0
    lw s2 0(a0)     # Initialize to be the first element of the array
 
loop_start:

    # Traverse to the end of the array
    beq s0 a1 loop_end
    

    # Get the current offset
    addi t0 s0 0
    slli t0 t0 2
    add t1 a0 t0
    
    # Load the current element
    lw t2 0(t1)
    
    # Compare with the biggest element
    # If the current element is smaller or equal to the maximum till now, skip
    bge s2 t2  loop_continue
    
    # Update the max_value and argmax
    addi s2 t2 0
    addi s1 s0 0

loop_continue:
    
    # Update the index
    addi s0 s0 1
    j loop_start


loop_end:

    # Prepare for the return value
    addi a0 s1 0
    # Epilogue
    lw s0 0(sp)     # Index of the array
    lw s1 4(sp)     # Maximum counter, argmax
    lw s2 8(sp)     # Maximum value till now
    addi sp sp 12
    
   
    jr ra


error: 
    # Handle the case where the array length is less than 1
    li a0 36
    j exit