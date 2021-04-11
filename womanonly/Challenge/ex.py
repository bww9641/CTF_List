s = 4
y = []
Z = []
k = []
Q = 'uh27bio:uY<xrA.'


def yes(inp):
    st = []
    for i in range(len(inp)):
        st.append(chr(ord(inp[i]) - i + 4))
    print(''.join(st) + '}')


def Checkin(inp):
    for i in range(len(inp)):
        if len(inp) <= 7:
            Z.append(chr(ord(inp[i]) - 1 + i))
        else:
            Z.append(chr(ord(inp[i]) + 4))
    return ''.join(Z)


def tryin(text, s):
    result = ''
    for i in range(len(text)):
        char = text[i]
        if char.isnumeric():
            result += chr(ord(char) - 1)
        elif char.isupper():
            result += chr((ord(char) + s - 65) % 26 + 65)
        else:
            result += chr(ord(char) ^ 1)
    return result


X = input('Enter input:  ')

k = Checkin(tryin(X, s))


if Q == k:
	print("wowwowowow")