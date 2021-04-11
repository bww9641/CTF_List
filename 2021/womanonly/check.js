$(document).ready(function() {
  $("form").submit(function() {
      var usr = $("#cuser").val();
      var pswd = $("#cpass").val();
      var magic = "";

      var cmd = ["", "\x6C\x65\x6E\x67\x74\x68", "\x6D\x61\x78", "\x63\x68\x61\x72\x41\x74", "\x63\x68\x61\x72\x43\x6F\x64\x65\x41\x74", "\x66\x72\x6F\x6D\x43\x68\x61\x72\x43\x6F\x64\x65", "\x73\x68\x61\x6B\x74\x69"];

      function merge(str1, str2) {
          for (var i = 0, temp = cmd[0], maxlength = Math[cmd[2]](str1[cmd[1]], str2[cmd[1]]); i < maxlength; i++) {
              temp += str1[cmd[3]](i) || cmd[0];
              temp += str2[cmd[3]](i) || cmd[0]
          };
          return temp
      }

      function encryptXor(param) {
          var temp_enc = cmd[0];
          for (var i = 0, j = 1; i < param[cmd[1]]; i++, j++) {
              if (j == param[cmd[1]]) {
                  j = 0
              };
              temp_enc += String[cmd[5]](param[cmd[4]](i) ^ param[cmd[4]](j))
          };
          return temp_enc
      }
      if (usr[cmd[1]] == 5) {
          magic = btoa(encryptXor(merge(cmd[6], usr)))
      }

      if (usr) {
          $.redirect("/check.php", {
              p: pswd,
              u: usr
          }, "POST", "_blank");
      }
  });
});