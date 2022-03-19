def main():
    # Main func
    text = input("Text: ")

    # Vars
    letters = 0
    words = 1
    sent = 0

    # End of sent
    xx = [".", "!", "?"]

    # Looping
    for i in range(len(text)):
        # Ascii
        asc = ord(text[i])

        # Condition
        if (asc >= 65 and asc <= 90) or (asc >= 97 and asc <= 122):
            letters += 1

        if text[i] == " ":
            words += 1

        if text[i] in xx:
            sent += 1

    # Percent
    pletters = (letters / words) * 100
    psent = (sent / words) * 100

    # Final
    index = round((0.0588 * pletters) - (0.296 * psent) - 15.8)

    # Out
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()