.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

    # Prologue
    addi sp sp -20       # Grow the stack 
    sw ra 0(sp)          # Return register     
    sw a1 4(sp)          # Pointer to the start of matrix buffer
    sw a2 8(sp)          # Number of rows of matrix
    sw a3 12(sp)         # Number of cols of matrix
    sw s0 16(sp)         # Store the file descriptor
    
    # 1. Open the file
    # a0 is prepared already
    li a1 1
    jal ra fopen
    li t0 -1
    beq t0 a0 error_27
    mv s0 a0             # Save the file descriptor

    # 2. f_write
    # 2.1 Write number of rows
    # a0 is prepared
    addi a1 sp 8
    li a2 1
    li a3 4
    jal ra fwrite
    li t0 1
    bne a0 t0 error_30
    
    
    # 2.2 Write number of cols
    # Set a0, a1
    mv a0 s0
    addi a1 sp 12
    
    # Set a2, a3
    li a2 1
    li a3 4
    jal ra fwrite
    li t0 1
    bne a0 t0 error_30
    
    
    # 2.3 Write the matrix
    # Set a0, a1
    mv a0 s0
    lw a1 4(sp)
    
    # Set a2, a3
    lw t0 8(sp)
    lw t1 12(sp)
    mul a2 t0 t1      # Calculate the number of elements to write to the file
    li a3 4           # Integer Array, so hardcoded as 4, representing 4 bytes
    jal ra fwrite
    lw t0 8(sp)
    lw t1 12(sp)
    mul t0 t0 t1 
    bne t0 a0 error_30


    # 3. Close the file
    mv a0 s0
    jal ra fclose
    bne x0 a0 error_28


    # Epilogue
    lw ra 0(sp)          # Return register     
    lw a1 4(sp)          # Pointer to the start of matrix buffer
    lw a2 8(sp)          # Number of rows of matrix
    lw a3 12(sp)         # Number of cols of matrix
    lw s0 16(sp)         # Store the file descriptor
    addi sp sp 20       # Grow the stack 
    

    jr ra


error_27:
    li a0 27
    lw ra 0(sp)          # Return register     
    lw a1 4(sp)          # Pointer to the start of matrix buffer
    lw a2 8(sp)          # Number of rows of matrix
    lw a3 12(sp)         # Number of cols of matrix
    lw s0 16(sp)         # Store the file descriptor
    addi sp sp 20       # Grow the stack 
    j exit
    
error_28:
    li a0 28
    lw ra 0(sp)          # Return register     
    lw a1 4(sp)          # Pointer to the start of matrix buffer
    lw a2 8(sp)          # Number of rows of matrix
    lw a3 12(sp)         # Number of cols of matrix
    lw s0 16(sp)         # Store the file descriptor
    addi sp sp 20       # Grow the stack 
    j exit
    
error_30:
    li a0 30
    lw ra 0(sp)          # Return register     
    lw a1 4(sp)          # Pointer to the start of matrix buffer
    lw a2 8(sp)          # Number of rows of matrix
    lw a3 12(sp)         # Number of cols of matrix
    lw s0 16(sp)         # Store the file descriptor
    addi sp sp 20       # Grow the stack 
    j exit
    