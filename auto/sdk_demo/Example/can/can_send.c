#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <net/if.h> 
#include <sys/ioctl.h> 
#include <sys/socket.h> 
#include <linux/can.h> 
#include <linux/can/raw.h>
#include <getopt.h>

char *program_name;

/**
 * @brief: print usage message 
 * @Param: stream: output device 
 * @Param: exit_code: error code which want to exit 
 */
void print_usage (FILE *stream, int exit_code)
{
    fprintf(stream, "Usage: %s [ dev... ] \n", program_name);
    fprintf(stream,
            "\t-h  --help     Display this usage information.\n"
            "\t-d  --device   The device can[0-1]\n"
	    	"\t-i  --id		  Set the can id that want to send\n");
    exit(exit_code);
}
/**
 * @brief: Hexadecimal number converted to decimal number 
 * @Param: pHex: the Hexadecimal number that formularize string format 
 */
int hex2dec(const char * phex)
{
    int dwhexnum=0;
        
    if ((phex[0] == '0') && (phex[1] == 'x' || phex[1] == 'X')) {
    	phex = phex + 2;
    }
    for (; *phex!=0 ; phex++) {    
		 dwhexnum *= 16;
		 if ((*phex>='0') && (*phex<='9'))
		 	dwhexnum += *phex-'0';
		 else if ((*phex>='a') && (*phex<='f'))
		 	dwhexnum += *phex-'a'+10;
		 else if ((*phex>='A') && (*phex<='F'))
		 	dwhexnum += *phex-'A'+10;
		 else {
		 	printf("hex format error!\n");
		 	exit(0);	
		 }		 
	}
     return dwhexnum;
}

/**
 * @brief: main function  
 * @Param: argc: number of parameters
 * @Param: argv: parameters list
 */ 
int main(int argc, char *argv[])  
{  
    int s, nbytes, i; 
    char *device;
    int id, next_option, device_flag=0, id_flag=0;   
	struct sockaddr_can addr;  
	struct ifreq ifr;  
	struct can_frame frame[1];
	const char *const short_options = "hd:i:";
	const struct option long_options[] = {
		{ "help",   0, NULL, 'h'},
		{ "device", 1, NULL, 'd'},
		{ "id", 1, NULL, 'i'},
		{ NULL,     0, NULL, 0  }
	};
	
	program_name = argv[0];
	while (1) {
		next_option = getopt_long (argc, argv, short_options, long_options, NULL);
		if (next_option < 0)
			break;
		switch (next_option) {
			case 'h':
				print_usage (stdout, 0);
				break;
			case 'd':
				device = optarg;
				device_flag = 1;
				break;
			case 'i':
				id = hex2dec(optarg);
				id_flag = 1;
				break;
			case '?':
				print_usage (stderr, 1);
				break;
			default:
				abort ();
		}
	}
	
	if (!device_flag || !id_flag) {
		print_usage (stdout, 0);
		exit(0);	
	}
	
	/* create a socket */  
	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);      
	strcpy(ifr.ifr_name, device );
	/* determine the interface index */  
	ioctl(s, SIOCGIFINDEX, &ifr);                     
	addr.can_family = AF_CAN;  
	addr.can_ifindex = ifr.ifr_ifindex;
	/* bind the socket to a CAN interface */  
	bind(s, (struct sockaddr *)&addr, sizeof(addr));              
	/* Set the filter rules */  
	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);  
	/* generate CAN frames */ 
	frame[0].can_id = id;  
	frame[0].can_dlc = argc - 5;
	for(i = 0; i < frame[0].can_dlc; i++) {
		frame[0].data[i] = hex2dec(argv[5 + i]);	
	}
	 
	/* send CAN frames */  
	while(1) {  
		nbytes = write(s, &frame[0], sizeof(frame[0]));    
		if (nbytes < 0) {
            perror("can raw socket write");
		        return 1;
		}

		/* paranoid check ... */
		if (nbytes < sizeof(struct can_frame)) {
		        fprintf(stderr, "read: incomplete CAN frame\n");
		        return 1;
		} 
		usleep(10000);
	}  
	close(s);  
	return 0;  
}  
