# Python TCP Client A
import socket 
import os
import time
from threading import Timer
starttime=time.time()

class RepeatedTimer(object):
    def __init__(self, interval, function, *args, **kwargs):
        self._timer     = None
        self.interval   = interval
        self.function   = function
        self.args       = args
        self.kwargs     = kwargs
        self.is_running = False
        self.start()

    def _run(self):
        self.is_running = False
        self.start()
        self.function(*self.args, **self.kwargs)

    def start(self):
        if not self.is_running:
            self._timer = Timer(self.interval, self._run)
            self._timer.start()
            self.is_running = True

    def stop(self):
        self._timer.cancel()
        self.is_running = False

host = '127.0.0.1'
port = 2004
#EXIT = '100000'
 
tcpClientA = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
tcpClientA.connect((host, port))

from time import sleep

def hello():
    os.system("ps -eo %cpu --sort=-%cpu > my.csv")
    cpu = os.popen("awk '{sum+=$1} END {print sum}' my.csv").read()
    print cpu
    tcpClientA.send(cpu)
rt = RepeatedTimer(1, hello)
try:
    sleep(5)
finally:
    rt.stop()
#tcpClientA.send(EXIT)     
tcpClientA.close() 
