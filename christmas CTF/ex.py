import base64
from Crypto.Cipher import Blowfish

K1 = "9e919bb33aef"
K2 = "f6ea6d937f22"
tmp = ""

def decrypt_key(cipher, salt_key):
    try:
        crypt_obj = Blowfish.new(salt_key, Blowfish.MODE_ECB)
        decrypted_key = crypt_obj.decrypt(cipher)
        # return decrypted_key
        # print(decrypted_key)
        padding_size = ord(decrypted_key[-1])

        text = decrypted_key[:-padding_size]

        # print "Decrypt key was made successfully"
        return str(text)

    except Exception as ERROR:
        return "ERROR"
        # print "error"


def encrypt_key(text, salt_key):
    try:
        bs = 8
        extra_bytes = len(text) % bs
        padding_size = bs - extra_bytes
        padding = chr(padding_size) * padding_size
        padded_text = text + padding

        crypt_obj = Blowfish.new(salt_key, Blowfish.MODE_ECB)

        cipher = crypt_obj.encrypt(padded_text)

        return cipher
    except Exception as ERROR:
        return "ERROR"
        # log.error(ERROR)

enc = 'm6US+8OA+WK1Dl2kLc60Kxp2o3ydWPuXbZK2vBOrQEPTSzH6Od6Qn137Ctn7oLqm7Nb2uvb2wHU='
enc = enc.decode('base64')
k1 = '9e919bb33aef!@'
k2 = '!@f6ea6d937f22'

for i in range(0,256):
    print(i)
    for j in range(256):
        K1 = "9e919bb33aef"
        a = hex(i)[2:]
        if len(a) == 1 : a = '0' + a
        b = hex(j)[2:]
        if len(b) == 1 : b = '0' + b
        K1 += a + b
        c1 = encrypt_key(base64.b64decode("QUJDREVGR0g="), K1.decode('hex'))
        if c1 != 'ERROR':
            for k in range(256):
                for l in range(256):
                    k2 = 'f6ea6d937f22'
                    c = hex(k)[2:]
                    if len(c) == 1 : c = '0' + c
                    d = hex(l)[2:]
                    if len(d) == 1 : d = '0' + d
                    k2 = c + d + k2
                    c2 = encrypt_key(c1, k2.decode('hex'))
                    if base64.b64encode(c2) == "J8LFHyoEuoo=":
                        print 'K1 : ' + K1
                        print 'K2 : ' + K2
