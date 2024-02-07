# Import "get string" function from cs50 library
from cs50 import get_string

# Prompt user for their name
name = get_string("What is your name? ")

# Print greeting
print("Hello, " + name)
