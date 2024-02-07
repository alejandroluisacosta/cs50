from cs50 import get_string

# Prompt user to input text
text = get_string("Text: ").lower()

# Count letters
letters = 0
for letter in text:
    # If the ascii value of the current character is between the appropiate ranges of the ASCII table
    if ord(letter) >= 97 and ord(letter) <= 122:
        letters += 1

# Count words
words = 1
for word in text:
    # If there's a whitespace, add a new word
    if ord(word) == 32:
        words += 1

# Count sentences
sentences = 0
for character in text:
    # If there's a comma, period, interrogation or exclamation mark
    if ord(character) == 33 or ord(character) == 46 or ord(character) == 63:
        sentences += 1

# Calculate the Coleman-Liau index of the text
L = 100 * letters / words
S = 100 * sentences / words
coleman_liau = round(0.0588 * L - 0.296 * S - 15.8)

# Print index
if coleman_liau < 1:
    print("Before Grade 1")
elif coleman_liau > 1 and coleman_liau <= 16:
    print(f"Grade {coleman_liau}")
elif coleman_liau > 16:
    print("Grade 16+")