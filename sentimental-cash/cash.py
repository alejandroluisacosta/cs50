# Import cs50 library
from cs50 import get_float

# Prompt user for dollars owed
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

# Convert change into cents
change = change * 100

# Calculate minimun coins for change
count = 0

while change > 0:

    # Quarters
    if change >= 25:
        count += 1
        change -= 25

    # Dimes
    elif change >= 10:
        count += 1
        change -= 10

    # Nickels
    elif change >= 5:
        count += 1
        change -= 5

    # Pennies
    elif change >= 1:
        count += 1
        change -= 1
        
# Print out the amount of coins needed
print(count)