import base64
import json

from flask import Flask, make_response, request, jsonify

from Util import AESCrypto, Setup, GuestBook

app = Flask(__name__)
gGuestBook = None
admin_password = None


@app.route("/")
@app.route("/index")
def index():
    return jsonify({"status": "success", "result": None})


@app.route("/login")
def login():
    AES_ENC = AESCrypto()
    user_id = request.args.get("id")
    user_pw = request.args.get("pw")
    accounts = gGuestBook.getAccounts()
    if user_id in accounts:
        if accounts[user_id] == user_pw:
            enc_data = json.dumps({"user_id": user_id, "group": "user"})
            enc_result = AES_ENC.encrypt(enc_data.encode("latin-1"))
            return jsonify(
                {
                    "status": "success",
                    "result": {"token": base64.b64encode(enc_result).decode("latin-1")},
                }
            )
    return jsonify({"status": "error", "result": {"message": "Login failed."}})


@app.route("/gb/")
def get_guest_books():
    return jsonify(
        {"status": "success", "result": {"articles": gGuestBook.getAllGuestBookList()}}
    )


@app.route("/gb/<idx>")
def get_guest_book(idx):
    article = gGuestBook.getGuestBook(idx)
    if article is not None:
        return jsonify({"status": "success", "result": {"article": article}})
    else:
        return jsonify(
            {"status": "error", "result": {"message": "article does not exists."}}
        )


@app.route("/secure/decrypt")
def secure_decrypt():
    e_data = request.args.get("e_data", None)
    token = request.args.get("token", None)
    sig = request.args.get("sig", None)

    if token is None or e_data is None or sig is None:
        return jsonify({"status": "error"})

    try:
        data = json.loads(
            AESCrypto()
            .decrypt(base64.b64decode(e_data))
            .decode("latin-1")
            .encode("latin-1")
        )
        article_user_id = data["author"]
        content = data["content"]

        data = json.loads(AESCrypto().decrypt(base64.b64decode(token)))
        user_id = data["user_id"]
        group = data["group"]

        if (
            user_id == article_user_id and gGuestBook.isValidSig(user_id, sig)
        ) or group == "admin":
            return jsonify({"status": "success", "result": {"content": content}})

        return jsonify(
            {"status": "error", "result": {"message": "you don't have a permission."}}
        )
    except json.decoder.JSONDecodeError as e:
        return jsonify({"status": "error", "result": {"message": "JSONDecodeError"}})
    except UnicodeDecodeError:
        return jsonify({"status": "error", "result": {"message": "UnicodeDecodeError"}})
    except ValueError as e:
        return jsonify({"status": "error", "result": {"message": "ValueError"}})


@app.route("/secure/secret")
def secure_secret():
    password = request.args.get("password", None)

    if password is None:
        return jsonify({"status": "error", "result": None})

    if password == admin_password:
        return jsonify(
            {
                "status": "success",
                "result": {"secret": gGuestBook.getFileContents("flag.txt", "r", 44)},
            }
        )

    return jsonify({"status": "error", "result": {"message": "password is incorrect"}})


if __name__ == "__main__":
    Setup()
    gGuestBook = GuestBook()
    admin_password = gGuestBook.getFileContents("password.txt", "r", 8)
    gGuestBook.saveGuestBook(
        "admin",
        "Admin Password",
        f"The password is: {admin_password}".encode("latin-1"),
    )
    gGuestBook.saveGuestBook("guest", "Hello", b"World")
    app.run(host="0.0.0.0", port=80)
