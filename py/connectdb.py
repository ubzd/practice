import MySQLdb

class people:
    def __init__(self, v1, v2):
        self.__data1 = v1
        self.__data2 = v2
    def prints(self):
        print self.__data1,
        print self.__data2

def connect():
    conn = MySQLdb.connect(host = 'localhost', user = 'root', passwd = '123', db = 'yjj')
    cur = conn.cursor()
    n = cur.execute('select * from yjj')
    for row in cur.fetchall():
        for r in row:
            print r, 
        print
    conn.close()

if __name__ == '__main__':
    a, b = map(int, raw_input("please input two numbers").split())
    x = people(a, b)
    x.prints()

    #mysql connection
    connect()
