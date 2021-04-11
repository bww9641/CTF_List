import base64
import pathlib
import hashlib
import json

from Util import AESCrypto


class GuestBook:
    def __init__(self):
        self.articles = list()
        self._salt = self.getFileContents("salt", "rb", 32)
        self._accounts = {
            "guest": "guest",
            "admin": self.getFileContents("admin_pw", "rb", 32),
        }

    def getAccounts(self):
        return self._accounts

    def getAllGuestBookList(self):
        return list(
            map(
                lambda x: {"idx": x["idx"], "author": x["author"], "title": x["title"]},
                self.articles,
            )
        )

    def getGuestBook(self, idx):
        for article in self.articles:
            if article["idx"] == int(idx):
                return article
        return None

    def saveGuestBook(self, author, title, content):
        article = {
            "idx": len(self.articles) + 1,
            "author": author,
            "title": title,
            "enc_data": base64.b64encode(
                AESCrypto().encrypt(
                    json.dumps(
                        {"content": content.decode("latin-1"), "author": author}
                    ).encode("latin-1")
                )
            ).decode("latin-1"),
            "sig": hashlib.sha1(
                "{}_{}".format(author, self._salt).encode("latin-1")
            ).hexdigest(),
        }
        self.articles.append(article)

    def isValidSig(self, author, sig):
        return (
            True
            if hashlib.sha1(
                "{}_{}".format(author, self._salt).encode("latin-1")
            ).hexdigest()
            == sig
            else False
        )

    def getFileContents(self, file_name, mode, size):
        data = None
        with open(pathlib.Path(__file__).parent.parent.joinpath(file_name), mode) as f:
            data = f.read(size)
        assert len(data) == size
        return data
