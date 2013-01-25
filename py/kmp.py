next = []
s = 'aaaaab'
t = 'aaaab'

def getnext():
    next.append(-1)
    i = 0; j = -1
    while i < len(t) - 1:
        if j == -1 or t[i] == t[j]:
            i += 1; j += 1
            if t[i] == t[j]: next.append(next[j])
            else: next.append(j) 
        else: j = next[j]

def KMP():
    i = 0; j = 0
    getnext()
    while i < len(s) and j < len(t):
        if j == -1 or s[i] == t[j]:
            i += 1; j += 1
        else: j = next[j]
    if j >= len(t):
        print 'i = ', i - len(t)
    
if __name__ == '__main__':
    KMP()
    print next[0:]
