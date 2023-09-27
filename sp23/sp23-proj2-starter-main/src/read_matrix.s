.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

    # Prologue
    addi sp sp -28
    sw ra 0(sp) 
    sw s1 4(sp)    # Store pointer for file descriptor
    sw s2 8(sp)    # Store number of rows
    sw s3 12(sp)   # Store number of columns
    sw s4 16(sp)   # Store pointer for buffer
    sw a1 20(sp)   # Pointer for row
    sw a2 24(sp)   # Pointer for column
    
    
    # 1. Parameter for fopen
    # a0 is prepared by read_matrix()
    li a1 0
    jal ra fopen
    li t0 -1
    beq a0 t0 error_27 
    mv s1 a0
    
    # 2. Parameter for fread
    # a0 is prepared
    # Read for 4 bytes(should be an int) -> num_rows
    lw a1 20(sp)
    li a2 4
    jal ra fread
    li t0 4
    bne t0 a0 error_29
    lw t0 20(sp)
    lw s2 0(t0)
    
    # Read for 4 bytes(should be an int) -> num_columns
    mv a0 s1
    lw a1 24(sp)
    li a2 4
    jal ra fread
    li t0 4
    bne t0 a0 error_29
    lw t0 24(sp)               # Get the addresss that where fread() store the result
    lw s3 0(t0)                # Get the actual result at that address!

    # 3. Parameter for malloc
    mul a0 s2 s3     # Calculate the number of elements to malloc
    slli a0 a0 2     # Calculate the number of bytes to malloc
    jal ra malloc 
    beq a0 x0 error_26  # malloc error
    mv s4 a0
    
    # 4. Read the matrix
    mv a0 s1
    mv a1 s4
    mul a2 s2 s3              # Get the total number of elements
    slli a2 a2 2              # Get the total number of bytes
    jal ra fread
    mul t0 s2 s3
    slli t0 t0 2
    bne t0 a0 error_29
    
    # 5. Close the file
    mv a0 s1
    jal ra fclose
    bne x0 a0 error_28
    
    # Epilogue
    mv a0 s4
    lw a1 20(sp)
    lw a2 24(sp)
    
    lw ra 0(sp) 
    lw s1 4(sp)    # Store pointer for file descriptor
    lw s2 8(sp)    # Store pointer for rows
    lw s3 12(sp)   # Store pointer for columns
    lw s4 16(sp)   # Store pointer for buffer
    addi sp sp 28
    
    jr ra


error_26:
    li a0 26
    lw ra 0(sp) 
    lw s1 4(sp)   
    lw s2 8(sp)   
    lw s3 12(sp)   
    lw s4 16(sp)  
    j exit
    
error_27:
    li a0 27
    lw ra 0(sp) 
    lw s1 4(sp)  
    lw s2 8(sp)    
    lw s3 12(sp)   
    lw s4 16(sp)    
    j exit
    
error_28:
    li a0 28
    lw ra 0(sp) 
    lw s1 4(sp)  
    lw s2 8(sp)    
    lw s3 12(sp)   
    lw s4 16(sp)   
    j exit
   
error_29:
    li a0 29
    lw ra 0(sp) 
    lw s1 4(sp)  
    lw s2 8(sp)   
    lw s3 12(sp)    
    lw s4 16(sp)   
    j exit
    

