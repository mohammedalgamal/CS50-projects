def main():
    # Main func

    while True:
        try:
            snum = input("Number: ")
            num = int(snum)
        except ValueError:
            continue
        else:
            break
    print(brand(check(num), num))


def check(n):
    # sum
    sum = 0

    # Each other digit double sum digits
    for i in range(2, len(str(n)) + 1, 2):
        try:
            sum += int(str(((n % (10 ** i)) // 10 ** (i-1)) * 2)[1])
            sum += int(str(((n % (10 ** i)) // 10 ** (i-1)) * 2)[0])
        except IndexError:
            sum += int(str(((n % (10 ** i)) // 10 ** (i-1)) * 2)[0])

    # sum of total
    if (len(str(n)) % 2) == 1:
        for i in range(0, len(str(n)), 2):
            sum += int(str(n)[i])
    else:
        for i in range(1, len(str(n)), 2):
            sum += int(str(n)[i])

    # Sum modulo 10
    check = sum % 10
    value = not check

    # return
    return value


def brand(cs, num):
    # func to print desired values
    snum = str(num)
    leng = len(snum)

    # cinditions
    if cs:
        if (leng == 15) and (snum[0] == '3') and ((snum[1] == '4') or (snum[1] == '7')):
            return "AMEX"
        elif (leng == 16) and (snum[0] == '5') and (int(snum[1]) >= 1) and (int(snum[1]) <= 5):
            return "MASTERCARD"
        elif ((leng == 16) or (leng == 13)) and (snum[0] == '4'):
            return "VISA"
    return "INVALID"


if __name__ == "__main__":
    main()