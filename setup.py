
class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'

def blockText(s): 
    ret_str = ""
    check = True
    while check:
        if len(s) > 16:
            win = s[:16]
            for j in range(len(win)-1, -1, -1):
                if win[j] == " ": 
                    ret_str += win[:j] + "^"
                    s = s[j+1:]          
                    break
        else: 
            ret_str += s + "^"
            check = False
    return ret_str

