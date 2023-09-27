.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
       
    # Error Checks
    li t0 5
    bne a0 t0 error_31

    # Prologue
    # 
    addi sp sp -60
    sw ra 0(sp)
    sw a1 4(sp)
    sw a2 8(sp)
    
    # Nums of rows and cols, and buffer pointer for m0
    sw s0 12(sp)
    sw s1 16(sp)
    sw s2 20(sp)
    
    # Nums of rows and cols, and buffer pointer for m1
    sw s3 24(sp)
    sw s4 28(sp)
    sw s5 32(sp)
    
    # Nums of rows and cols, and buffer pointer for input
    sw s6 36(sp)
    sw s7 40(sp)
    sw s8 44(sp)
    
    # Nums of rows and cols, and buffer pointer for output
    sw s9 48(sp)
    sw s10 52(sp)
    sw s11 56(sp)

    # Read pretrained m0
    # Malloc space for arguments
    li a0 4
    jal ra malloc
    beq a0 x0 error_26_m0_a1
    mv t1 a0
    
    addi sp sp -4
    sw t1 0(sp)
    
    li a0 4
    jal ra malloc
    beq a0 x0 error_26_m0_a2
    mv t2 a0
    
    addi sp sp -4
    sw t2 0(sp)
    
    lw a1 4(sp)
    addi t0 a1 4
    lw a0 0(t0)
    lw a1 4(sp)
    lw a2 0(sp)
    jal ra read_matrix
    mv s2 a0
    lw t0 4(sp)
    lw s0 0(t0)
    lw t0 0(sp)
    lw s1 0(t0)
    
    
    # Read pretrained m1
    # Malloc space for arguments
    li a0 4
    jal ra malloc
    beq a0 x0 error_26_m1_a1
    mv t1 a0
    
    addi sp sp -4
    sw t1 0(sp)
    
    li a0 4
    jal ra malloc
    beq a0 x0 error_26_m1_a2
    mv t2 a0
    
    addi sp sp -4
    sw t2 0(sp)
    
    
    addi t0 a1 8
    lw a0 0(t0)
    lw a1 4(sp)
    lw a2 0(sp)
    jal ra read_matrix
    mv s5 a0
    lw t0 4(sp)
    lw s3 0(t0)
    lw t0 0(sp)
    lw s4 0(t0)
    

    # Read input matrix
    # Malloc space for arguments
    li a0 4
    jal ra malloc
    beq a0 x0 error_26_input_a1
    mv t1 a0
    
    addi sp sp -4
    sw t1 0(sp)
    
    li a0 4
    jal ra malloc
    beq a0 x0 error_26_input_a2
    mv t2 a0
    
    addi sp sp -4
    sw t2 0(sp)
    
    
    addi t0 a1 12
    lw a0 0(t0)
    
    lw a1 4(sp)
    lw a2 0(sp)
    jal ra read_matrix
    mv s8 a0
    lw t0 4(sp)
    lw s6 0(t0)
    lw t0 0(sp)
    lw s7 0(t0)


    # Compute h = matmul(m0, input)
    # Calculate size of h, used later for malloc
    mv s9 s0
    mv s10 s7
    mul t2 s0 s7
    slli t2 t2 2
    
    # Preparing arguments for malloc
    mv a0 t2
    jal ra malloc
    beq a0 x0 error_26_alloc_h
    mv s11 a0
    
    
    # Perform matmul
    mv a6 a0
    mv a0 s2
    mv a1 s0
    mv a2 s1
    mv a3 s8
    mv a4 s6
    mv a5 s7
    jal ra matmul
    
    # Compute h = relu(h)
    mv a0 s11
    jal ra relu
    
    # Free memory block for input
    mv a0 s8
    jal ra free
    
    
    # Free memory block for m0
    mv a0 s2
    jal ra free
    

    # Compute o = matmul(m1, h)
    # Calculate the size of o, used later for malloc
    mv s6 s3
    mv s7 s10
    mul t0 s6 s7
    slli t0 t0 2
    mv a0 t0
    jal ra malloc
    beq a0 x0 error_26_alloc_o
    mv s8 a0


    # Perform matmal
    mv a0 s5
    mv a1 s3
    mv a2 s4
    mv a3 s11
    mv a4 s9 
    mv a5 s10
    mv a6 s8
    jal ra matmul
    
    
    # Free memory block for m1
    mv a0 s5 
    jal ra free
    
    
    # Write output matrix o
    lw a0 4(sp)
    addi a0 a0 16   # Address to the filename for output 
    lw a0 0(a0)     # Filename for output 
    mv a1 s8
    mv a2 s6
    mv a3 s7
    jal ra write_matrix
    
    # Free memory block for h
    mv a0 s11
    jal ra free
    

    # Compute and return argmax(o)
    mv a0 s8
    mul a1 s6 s7
    jal ra argmax
    mv s11 a0  # Use s11 just to save the result

    # Free the output matrix
    mv a0 s8
    jal ra free

    # If enabled, print argmax(o) and newline
    lw t0 8(sp)
    beq x0 t0 print_section
    
    # Restore Stack
    lw ra 0(sp)
    lw a1 4(sp)
    lw a2 8(sp)
    
    # Nums of rows and cols, and buffer pointer for m0
    lw s0 12(sp)
    lw s1 16(sp)
    lw s2 20(sp)
    
    # Nums of rows and cols, and buffer pointer for m1
    lw s3 24(sp)
    lw s4 28(sp)
    lw s5 32(sp)
    
    # Nums of rows and cols, and buffer pointer for input
    lw s6 36(sp)
    lw s7 40(sp)
    lw s8 44(sp)
    
    
    # Nums of rows and cols, and buffer pointer for output
    lw s9 48(sp)
    lw s10 52(sp)
    lw s11 56(sp)
    
    addi sp sp 60

    jr ra


print_section:
    mv a0 s11
    jal ra print_int
    li t0 '\n'
    jal ra print_char
    
    j restore_stack

error_26_m0_a1:
    li a0 26
    j restore_stack

error_26_m0_a2:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    li a0 26
    j restore_stack

error_26_m1_a1:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    mv a0 s2
    jal ra free
    li a0 26
    j restore_stack

error_26_m1_a2:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    mv a0 s2
    jal ra free
    li a0 26
    j restore_stack
    

error_26_input_a1:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    mv a0 s2
    jal ra free
    mv a0 s5
    jal ra free
    li a0 26
    j restore_stack
       

error_26_input_a2:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    mv a0 s2
    jal ra free
    mv a0 s5
    jal ra free
    li a0 26
    j restore_stack

    
error_26_alloc_h:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    mv a0 s2
    jal ra free
    mv a0 s5
    jal ra free
    mv a0 s8
    jal ra free
    li a0 26
    j restore_stack
    
    
error_26_alloc_o:
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    sw a0 0(sp)
    addi sp sp 4
    jal ra free
    mv a0 s2
    jal ra free
    mv a0 s8
    jal ra free
    li a0 26
    j restore_stack

error_31:
    j restore_stack


restore_stack:
    lw ra 0(sp)
    lw a1 4(sp)
    lw a2 8(sp)
    
    # Nums of rows and cols, and buffer pointer for m0
    lw s0 12(sp)
    lw s1 16(sp)
    lw s2 20(sp)
    
    # Nums of rows and cols, and buffer pointer for m1
    lw s3 24(sp)
    lw s4 28(sp)
    lw s5 32(sp)
    
    # Nums of rows and cols, and buffer pointer for input
    lw s6 36(sp)
    lw s7 40(sp)
    lw s8 44(sp)
    
    
    # Nums of rows and cols, and buffer pointer for output
    lw s9 48(sp)
    lw s10 52(sp)
    lw s11 56(sp)
    
    addi sp sp 60
    j exit
    
    