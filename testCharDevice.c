/**
 * @brief  A Linux user space program that communicates with the ebbchar.c LKM. It passes a
 * string to the LKM and reads the response from the LKM. For this example to work the device
 * must be called /dev/ebbchar.
*/

 // Carlos Membreno, Kevin Santana, Taylor Knight
 // Program 2, LKM: A character Device

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define BUFFER_LENGTH 1024               ///< The buffer length (crude but fine)

int main()
{
   int ret, fd, cont = 0;
   char stringToSend[BUFFER_LENGTH];
   char * receiveBuffer;
   printf("Starting device test code example...\n");
   fd = open("/dev/ebbchar", O_RDWR);             // Open the device with read/write access
   if (fd < 0)
   {
      perror("Failed to open the device...");
      return errno;
   }
   while(1==1)
   {
	   printf("would you like to continue ?\n0)yes\n1)no\n");
	   scanf("%d",&cont);

	   if(cont) break;

	   printf("Type in a short string to send to the kernel module:\n");
	   scanf("%s", stringToSend);                // Read in a string (with spaces)
	   printf("Writing message to the device [%s].\n", stringToSend);
	   ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
	   if (ret < 0)
	   {
	      perror("Failed to write the message to the device.");
	      return errno;
	   }
           int lengthWanted = 0;
	   printf("type a length to read back from the device...\n");
	   scanf("%d", &lengthWanted);
    	   receiveBuffer = calloc(lengthWanted + 1, sizeof(char));
	   printf("Reading from the device...\n");
	   ret = read(fd, receiveBuffer , lengthWanted);        // Read the response from the LKM
	   if (ret < 0)
	   {
	      perror("Failed to read the message from the device.");
	      return errno;
	   }
	   printf("The received message is: [%s]\n",receiveBuffer);
  	   free(receiveBuffer);
   }
   printf("End of the program\n");
   return 0;
}
