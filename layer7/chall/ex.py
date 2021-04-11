data = open('./flag.jpg', 'rb').read()
data = data[4:]
huffman_table = list()
for i in range(0x100):
    huffman_table.append((data[i * 2], data[i * 2 + 1]))
data = data[0x200+4:]

conversion_table = dict()
a = list(filter(lambda x: x[1] == 7, huffman_table))
for i in range(len(a)):
    conversion_table[bin(2 + i)[2:].rjust(7, '0')] = chr(a[i][0])
a = list(filter(lambda x: x[1] == 8, huffman_table))
for i in range(len(a)):
    conversion_table[(bin(20 + (i // 2))[2:] + str(i%2)).rjust(8, '0')] = chr(a[i][0])
a = list(filter(lambda x: x[1] == 9, huffman_table))
for i in range(len(a)):
    conversion_table[(bin(0xEB + (i // 2))[2:] + str(i % 2)).rjust(9, '0')] = chr(a[i][0])
conversion_table['000000'] = '\x00'
print(conversion_table)
bindata = str()
for i in data:
    bindata += bin(i)[2:].rjust(8, '0')
ptr = 0
f = open('decrypted.jpg', 'ab')
while bindata:
    if conversion_table.get(bindata[:ptr]) != None:
        f.write(bytes([ord(conversion_table.get(bindata[:ptr]))]))
        bindata = bindata[ptr:]
        ptr = 0
        print(len(bindata))
    ptr += 1
