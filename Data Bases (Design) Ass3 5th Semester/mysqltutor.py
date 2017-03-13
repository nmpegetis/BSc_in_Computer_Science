import pymysql as MySQLdb

# Create connection
con=MySQLdb.connect('127.0.0.1', 'user', 'test', 'DB-A2')

# Create a cursor on the connection
cur=con.cursor()

# Simple query
cur.execute('select 5')

# Retrieve simple query's result
print cur.fetchone()
# --OUTPUT
# (5L,)

# Bulk query
cur.execute('select * from hospital limit 3')

# Retrieve bulk query's results
for i in cur:
    print i

# --OUTPUT--
#(0L, 'AHEPA University', 'Thessaloniki')
#(1L, 'Agios Andreas', 'California')
#(2L, 'Agios Dimitrios', 'Chania')


# Parameterized statement

cur.execute('select * from hospital where hid=%s or hid=%s', [40,41])

for i in cur:
    print i

# --OUTPUT
#(40L, 'Lincoln', 'Athina')
#(41L, 'Jacobi', 'New York')
