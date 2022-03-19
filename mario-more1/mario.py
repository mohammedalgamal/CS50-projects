# height = int(input("height: "))
# while height < 0 or height > 8:
#    height = int(input("height: "))

def main():
    # Main func
    while True:
        try:
            height = int(input("height: "))
        except ValueError:
            print("That's not an integer!")
        else:
            if height > 0 and height <= 8:
                break

    # Call print
    pyramid(height)


def pyramid(n):
    # Func to print
    for i in range(1, n + 1):
        print(" " * (n-i), end="")
        print("#" * i, end="")
        print("  ", end="")
        print("#" * i, end="")
        print("")


if __name__ == "__main__":
    main()