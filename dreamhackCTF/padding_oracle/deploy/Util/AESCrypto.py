from Cryptodome import Random
from Cryptodome.Cipher import AES
from Cryptodome.Util.Padding import pad, unpad
import pathlib


class AESCrypto:
    def __init__(self, mode=AES.MODE_CBC):
        self._block_size = 16
        with open(pathlib.Path(__file__).parent.parent.joinpath("rand_key"), "rb") as f:
            key = f.read(16)
        iv = bytes([0x00] * 16)
        self.crypto = AES.new(key, mode, iv)

    def encrypt(self, plain_text):
        enc_text = self.crypto.encrypt(pad(plain_text, self._block_size))
        return enc_text

    def decrypt(self, enc_text):
        dec_data = self.crypto.decrypt(enc_text)
        dec_text = unpad(dec_data, self._block_size)
        return dec_text
