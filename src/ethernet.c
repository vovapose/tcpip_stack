#include "../include/ethernet.h"
#include <arpa/inet.h>
struct eth_hdr* init_eth_hdr(char* buf)
{
    struct eth_hdr *hdr = (struct eth_hdr *) buf;

    hdr->ethertype = htons(hdr->ethertype);
    
    return hdr;
}
