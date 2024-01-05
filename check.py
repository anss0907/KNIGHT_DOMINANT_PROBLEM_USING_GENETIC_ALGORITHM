__BOARD_SIZE__ = 8
Possible_Positions = []
r = []
c = []
for i in range(__BOARD_SIZE__ * __BOARD_SIZE__):
    x = i // __BOARD_SIZE__
    y = i % __BOARD_SIZE__
    if (x and y and x < 7 and y < 7):
        Possible_Positions.append(i)
        if(x not in r):
            r.append(x)
        if(y not in c):
            c.append(y)
        
print(Possible_Positions)
print(r)
print(c)