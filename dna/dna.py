import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py sequences databases")
        sys.exit(1)

    # Read database file into a variable
    csvfile = open(sys.argv[1], "r")
    database = csv.DictReader(csvfile)

    # Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2])
    sequence = sequence_file.read().rstrip()

    # Find longest match of each STR in DNA sequence

    # Dict to store each STR max repetitions
    coincidences = {}
    # List for STRs to check in DNA sequence
    keys = list(database.fieldnames[1:])
    # Apply longest_match func to each STR
    for key in keys:
        longest = str(longest_match(sequence, key))
        coincidences[key] = longest

    # Boolean value to see if any matches were found
    found = False

    # Check database for matching profiles
    for row in database:
        # If all the STR max counts matches any person
        if(list(row.values())[1:] == list(coincidences.values())):
            found = True
            print(row['name'])
    if not found:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
