.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:

    # Prologue
    addi sp sp -16
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    
    # Termination 1, not enough element to use, exit with 36
    bge x0 a2 terminate_1
    
    # Termination 2, either stride is less than 1
    bge x0 a3,terminate_2
    bge x0 a4,terminate_2

    # Initialization
    li s0 0     # Store for the return result
    li s1 0     # Index for array a0
    li s2 0     # Index for array a1
    li s3 0     # Number of elements'pair that have been used to calculate dot product
    
loop_start:
    bge s3 a2 loop_end   # while loop ends, number of elements exceed
    
    # Calculate the offset and get the element
    # Array 0
    mv t1 s1
    slli t1 t1 2
    add t1 a0 t1
    lw t1 0(t1)
    
    # Array 1
    mv t2 s2
    slli t2 t2 2
    add t2 a1 t2
    lw t2 0(t2)
    
    # Calculate
    mul t0 t1 t2
    
    # Update for the next iteration
    add s0 s0 t0
    add s1 s1 a3        # Update stride for array 1
    add s2 s2 a4        # Update stride for array 2
    addi s3 s3 1        # Update the number used for calculation
    
    j loop_start
    
loop_end:
    
    mv a0 s0

    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    addi sp sp 16
    
    jr ra
    
terminate_1:
    li a0 36
    j exit
    
terminate_2:
    li a0 37
    j exit
