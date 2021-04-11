import frida, sys

def on_message(message, data):
  print(message)

# Hooking 할 어플리케이션의 package 명
PACKAGE_NAME = "com.application.ezpz"

jscode = """
console.log("[+] Start Script");

Java.perform(function() {
	console.log("[+] Hooking System.exit");
	var MainActivity = Java.use("com.application.ezpz.MainActivity");
	var onClick = MainActivity.onClick;
  onClick.implementation = function(v) {
    onClick.call(this, v);
    console.log("[+] onclick hooked!");
  }
});
"""

process = frida.get_usb_device(1).attach(PACKAGE_NAME)
script = process.create_script(jscode)
script.on('message', on_message)
print('[+] Running Hook')
script.load()
sys.stdin.read()