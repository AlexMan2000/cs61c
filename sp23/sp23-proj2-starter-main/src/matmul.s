.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

    # Error checks
    # Check for non-zero height and width
    bge x0 a1 error_1
    bge x0 a2 error_1
    bge x0 a4 error_1
    bge x0 a5 error_1
    
    # Check for shape mismatch between matrix
    bne a2, a4 error_1

    # Prologue
    # For matrix C
    addi sp sp -8
    sw s0 0(sp)
    sw s1 4(sp)
    
    # For inner function call
    addi sp sp -28
    sw s2 0(sp)
    sw s3 4(sp)
    sw s4 8(sp)
    sw s5 12(sp)
    sw s6 16(sp)
    sw s7 20(sp)
    sw s8 24(sp)
    
    addi sp sp -4
    sw ra 0(sp)
    
    # Function Body
    li s0 0         # row_index for output matrix
    li s1 0         # column index for output matrix
    

outer_loop_start:
    
    # for (int i = 0; i < row_num_A; i++)
    beq s0 a1 outer_loop_end
    
inner_loop_start:
    # for (int j = 0; j < col_num_B; j++)
    beq s1 a5 inner_loop_end
    
    
    # Ready to call function dot with stride
    # Store the volatile registers on to the saved registers
    mv s2 a0
    mv s3 a1
    mv s4 a2
    mv s5 a3
    mv s6 a4
    mv s7 a5
    mv s8 a6
    
    
    # Preparing for parameters
    # 1. Calculate the pointer to the first array
    mul t1 s0 a2
    slli t1 t1 2
    add a0 a0 t1
    # 2. Calculate the pointer to the second array
    mv t2 s1
    slli t2 t2 2
    add a1 a3 t2
    # 3. Number of elements' pair to use in the calculation(equal to number of columns in matrix A or number of rows in matrix B)
#     mv a2 a2
    # 4. The stride of the first array(should always be 1)
    addi a3 x0 1
    # 5. The stride of the second array(should be the number of columns of the matrix B)
    add a4 x0 a5
    
    # Call the function dot
    jal ra dot
    
    # Restore volatile registers
    mv a1 s3
    mv a2 s4
    mv a3 s5
    mv a4 s6
    mv a5 s7
    mv a6 s8
    
    # Calculate the address where the element should be updated
    mul t0 s0 a5
    add t0 t0 s1
    slli t0 t0 2
    add t3 a6 t0
    sw a0 0(t3)
    
    # Restore volatile registers
    mv a0 s2
    
    # Update for next inner loop
    addi s1 s1 1
    j inner_loop_start

inner_loop_end:
    
    # Update for next outer loop
    addi s0 s0 1
    li s1 0
    j outer_loop_start
    
outer_loop_end:


    # Epilogue
    lw ra 0(sp)
    addi sp sp 4
    
    lw s2 0(sp)
    lw s3 4(sp)
    lw s4 8(sp)
    lw s5 12(sp)
    lw s6 16(sp)
    lw s7 20(sp)
    lw s8 24(sp)
    addi sp sp 28
    lw s0 0(sp)
    lw s1 4(sp)
    addi sp sp 8
    
    jr ra
    
error_1:
    # Height or width < 1 || Mismatch
    li a0 38
    j exit
    