import os
import pymysql
import pysftp
from stat import  S_ISDIR, S_ISREG
from sys import argv
from os.path import getctime
from datetime import datetime as dt
try:
    adress=argv[1]
except:
    print("Введите адрес")
with open(adress, "r") as f:
    data = f.readlines()
settings = {}
for i in data:
    currentRoom = i.replace(' ', '').strip().split('=')
    settings[currentRoom[0]] = currentRoom[1]
host = settings['sftp_host']
port = settings['sftp_port']
password = settings['sftp_password']
username = settings['sftp_user']
file_path = settings['sftp_remote_dir']
local_path = settings['local_dir']
sql_user=settings['sql_user']
sql_password=settings['sql_password']
sql_database=settings['sql_database']

cnopts = pysftp.CnOpts()
cnopts.hostkeys = None
sftp=pysftp.Connection(host=host, username=username,password=password,port=int(port),cnopts=cnopts)

def get_r_portable(sftp, remotedir, localdir, preserve_mtime=False):
    for entry in sftp.listdir(remotedir):
        remotepath = remotedir + "/" + entry
        localpath = os.path.join(localdir, entry)
        mode = sftp.stat(remotepath).st_mode
        if S_ISDIR(mode):
            try:
                os.mkdir(localpath,mode=777)
            except OSError:
                pass
            get_r_portable(sftp, remotepath, localpath, preserve_mtime)
        elif S_ISREG(mode):
            sftp.get(remotepath, localpath, preserve_mtime=preserve_mtime)

get_r_portable(sftp, file_path, local_path, preserve_mtime=False)
sftp.close()
filesname=os.listdir(local_path)
changetime=[]

for file in filesname:
    os.chdir(local_path)
    time1=dt.fromtimestamp(getctime(file)).strftime('%Y-%m-%d %H:%M')
    changetime.append(time1)
try:
    connection = pymysql.connect(
        host='localhost',
        database=sql_database,
        user=sql_user,
        password=sql_password,
        cursorclass=pymysql.cursors.DictCursor
    )
    try:
        with connection.cursor() as cursor:
            i=len(filesname)
            myid = list(range(1,i+1))
            sql = "INSERT INTO files2 (id) VALUES (%s)"
            cursor.executemany(sql, myid)
            query = "UPDATE files2 SET name = %s WHERE id = %s;"
            for i, val in enumerate(filesname):
                cursor.execute(query, (val, i + 1))
            query2 = "UPDATE files2 SET data = %s WHERE id = %s;"
            for i, val in enumerate(changetime):
                cursor.execute(query2, (val, i + 1))
            connection.commit()
        with connection.cursor() as cursor:
            select_all_rows = "SELECT * FROM `files2`"
            cursor.execute(select_all_rows)
            rows = cursor.fetchall()
            for row in rows:
                print(row)

    except Exception as ex:
        print("error")
        print(ex)
except Exception as ex:
    print("Connection resused...")
    print(ex)
