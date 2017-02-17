/* usbreset -- send a USB port reset to a USB device */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>


int main(int argc, char **argv)
{
    const char *filename;
    int fd;
    int rc;

    if (argc == 2) 
    {
        if ( strncmp( "mouse", argv[1], strlen("mouse") ) == 0 )
        {
            printf("Reset mouse\n");
            filename = "/dev/bus/usb/003/001";
        }
        else
        {
            filename = argv[1];
        }
    }
    else 
    {
        fprintf(stderr, "Usage: usbreset device-filename\n");
        return 1;
    }

    fd = open(filename, O_WRONLY);
    if (fd < 0) {
        perror("Error opening output file");
        return 1;
    }

    printf("Resetting USB device %s\n", filename);
    rc = ioctl(fd, USBDEVFS_RESET, 0);
    if (rc < 0) {
        perror("Error in ioctl");
        return 1;
    }
    printf("Reset successful\n");

    close(fd);
    return 0;
}
