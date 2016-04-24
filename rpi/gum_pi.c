#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

while(1 == 1){
    // put socket into listening mode
    printf("Starting to listen \n");
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        //printf("received [%s]\n", buf);
	/* This handles png/jpeg/gif, not xbm
	char strcmd [300] = "sudo python /home/pi/Desktop/ec535/PlatformWithOS/demo/ImageDemo.py ";
	strcat(strcmd, "/home/pi/Desktop/ec535/PlatformWithOS/demo/");//add absolute dir
	strcat(strcmd, buf);
	strcat(strcmd, ".*");
	printf("%s\n", strcmd); //for debug
	system(strcmd);
	*/
	char strcmd1 [300] = "/home/pi/Desktop/ec535/PlatformWithOS/driver-common/xbm2bin < ";
	strcat(strcmd1, "/home/pi/Desktop/ec535/PlatformWithOS/demo/"); //add directory
	strcat(strcmd1, buf);
	strcat(strcmd1, ".xbm > /dev/epd/display"); //add extension/rest of command

	system(strcmd1);
	system("echo U > /dev/epd/command");
    }

    // close connection
    close(client);
}
    close(s);
    return 0;
}
