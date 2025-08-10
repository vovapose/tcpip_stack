#include "../include/syshead.h"
#include "../include/utils.h"

static int tun_fd;

static int set_if_route(char *dev, char *cidr)
{
    return run_cmd("ip address add %s dev %s ", cidr, dev);
}

// static int set_if_address(char *dev, char *cidr)
// {
//    return run_cmd("ip address add dev %s local %s", dev, cidr);

// }

static int set_if_up(char *dev)
{
    return run_cmd("ip link set dev %s up", dev);
}

/*
 * Taken from Kernel Documentation/networking/tuntap.txt
 */
static int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ) {
        print_error("Cannot open TUN/TAP dev");
        exit(1);
    }

    CLEAR(ifr);

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if( *dev ) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        print_error("ERR: Could not ioctl tun: %s\n", strerror(errno));
        close(fd);
        return err;
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}

int tun_read(char *buf, int len)
{
    return read(tun_fd, buf, len);
}

int tun_write(char *buf, int len)
{
    return write(tun_fd, buf, len);
}

void tun_init(char *dev)
{
    tun_fd = tun_alloc(dev);
    
    // run_cmd("ip tuntap add mode tap dev tap0");
    // run_cmd("ip addr add 10.0.0.4/24 dev tap");
    if (set_if_up(dev) != 0) {
        print_error("ERROR when setting up if\n");
    }

    if (set_if_route(dev, "10.0.0.0/24") != 0) {
        print_error("ERROR when setting route for if\n");
    }
    // if (set_if_address(dev, tapaddr) != 0) {
    //     print_error("ERROR when setting addr for if\n");
    // }
}