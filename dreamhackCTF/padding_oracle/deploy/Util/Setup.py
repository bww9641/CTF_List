import os, pathlib, random, string


class Setup:
    def __init__(self):
        self._runInit()

    def _runInit(self):
        self._write_rand_file("rand_key", 16, "urandom")
        self._write_rand_file("admin_pw", 32, "urandom")
        self._write_rand_file("salt", 32, "urandom")

    def _write_rand_file(self, name, size, option="urandom"):
        if option == "urandom":
            value = os.urandom(size)
            mode = "wb"
        else:
            value = "".join(
                random.choice(string.ascii_letters + string.digits) for _ in range(size)
            )
            mode = "w"
        save_file = pathlib.Path(__file__).parent.parent.joinpath(name)
        f = open(save_file, mode)
        f.write(value)
        f.close()
