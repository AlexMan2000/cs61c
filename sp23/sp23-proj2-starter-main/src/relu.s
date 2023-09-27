.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue
    addi sp sp -4
    sw s1 0(sp)
    
    
    bge x0 a1 error
    li s1 0   # Counter for array index
    
loop_start:
    
    beq s1 a1 loop_end
    
    mv t0 s1
    slli t0 t0 2    # Calculating offset, 4-byte integer
    add t1 a0 t0   # Calculating the address of the current integer
    
    lw t2 0(t1)  # Get the current element of array
    
    slt t3 t2 x0
    beq t3 x0 loop_continue # If current element is bigger than 0, skip 
    
    sw x0 0(t1)
loop_continue:

    addi s1 s1 1
    j loop_start

loop_end:

    li a0 0
    

    # Epilogue
    lw s1 0(sp)
    addi sp sp 4
    

    jr ra

error:
    # Epilogue
    lw s1 0(sp)
    addi sp sp 4
    li a0 36
    j exit