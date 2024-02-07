# Import cs50 library
from cs50 import get_int

# Prompt user for height
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# Print out the piramid

# Outer loop to print out a single hash
for i in range(height):

    # Inner loop 1 to print out blank spaces
    for k in reversed(range(height - i - 1)):
        print(" ", end="")

    # Inner loop 2 to print out increasing amount of hashes depending on height
    for j in range(i):
        print("#", end="")

    # Print out the single hash
    print("#")
