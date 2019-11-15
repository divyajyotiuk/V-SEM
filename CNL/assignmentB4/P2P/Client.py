import socket
import os
import threading


class Client:
	def create(self):
		#self.ip = input("Enter the ip: ")
		self.ip = "10.10.14.233"#change ip here
		self.port = 2506
		self.c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		print("Socket binded successfully")
		self.chatWindow()
	def chatWindow(self):
		#os.system("clear")
		print("Chat Window\n############################\n say bye to stop")
		threadS = threading.Thread(target = self.sender)
		threadR = threading.Thread(target = self.receiver)
		threadS.start()
		threadR.start()
		
	def sender(self):
		while True:
			#m=input()
			msg = bytes(input(), "utf-8")


			self.c.sendto(msg, (self.ip, self.port))
			#if m == "bye":
				
				#self.c.close()
				#exit()
				

	def receiver(self):
		while True:
			msg, addr = self.c.recvfrom(1024)
			#if str(msg.decode("utf-8")) == "bye":
				#self.c.close()
				#exit()

			print("Message from " + str(addr) + ": " + str(msg.decode("utf-8")))

	
if __name__=='__main__':
	client = Client()
	client.create()
	#client.chatWindow()
