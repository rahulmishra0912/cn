import socket 
from threading import Thread 
from SocketServer import ThreadingMixIn 
import datetime

import fileinput
import sys

def replaceAll(file,searchExp,replaceExp):
    for line in fileinput.input(file, inplace=1):
        if searchExp in line:
	    avl = line
            line = line.replace(avl,replaceExp)
        sys.stdout.write(line)

# Multithreaded Python server : TCP Server Socket Thread Pool
class ClientThread(Thread): 
 
    def __init__(self,ip,port): 
        Thread.__init__(self) 
        self.ip = ip 
        self.port = port 
        print "Connected with " + ip + ":" + str(port) 
 
    def run(self): 
        while True :
	    i = 0
	    n = 0 
	    print "CPU Utilisation by "+ ip
	    #f = open('avg.txt', 'a+')
            while True :
		now = datetime.datetime.now()
	        data = conn.recv(2048) 
		if data == None or data == "":
		    conn.close()
		    break
        	else :
		    i = i + float(data)
		    n = n + 1
		    print str(n) +". "+now.strftime("%Y-%m-%d %H:%M:%S")+" - ",data
		    avg = float(i/n)
	    av = "Average CPU Usage by "+ip+" ("+now.strftime("%Y-%m-%d %H:%M:%S") + ") : " + str(avg) +" %\n"
	    print av
	    replaceAll("avg.txt","127.0.0.1",av)
            break

# Multithreaded Python server : TCP Server Socket Program Stub
TCP_IP = '127.0.0.1' 
TCP_PORT = 2004

tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
tcpServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 
tcpServer.bind((TCP_IP, TCP_PORT)) 
threads = [] 
 
while True: 
    tcpServer.listen(4) 
    print "Server Started ...\n" 
    (conn, (ip,port)) = tcpServer.accept() 
    newthread = ClientThread(ip,port) 
    newthread.start() 
    threads.append(newthread) 
 
for t in threads: 
    t.join() 
