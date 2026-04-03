1.Compilation:
gcc -splitter.c -o split
gcc -combine.c -o combine
gcc -sender.c -o send
gcc -receive.c -o receive
 

2.Usage :
(send and receive can be used both for transfers locally and over a network | split and combine work locally only)

3. Commands:
./receive  // in the receiver's end
ip route | grep default 
 //example default via 192.168.1.254 dev wlp0s20f3 proto dhcp src 192.168.1.79 metric 600 (first one is the APs ip, second one is device ip)
./send <receiver's ip> <filename.format> // in the sender's end
./split <filename.format>
./combine <filename.format>

4. Example of Usage:
a linux machine connected to a phone's hotspot: (In this example, linux is taken as sender and phone as receiver of file)
receiver's end:
./receive
sender's end : ./send 192.168.1.254 traffic.mp4


