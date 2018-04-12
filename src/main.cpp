#include <iostream>

#include "fast_mpd_parser/Include.h"

int main() {
    FILE *f = fopen("data/lalaland.mpd", "rb");
    
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);

    fseek(f, 0, SEEK_SET);
    
    char *source = (char *)malloc(fsize + 1);
    fread(source, fsize, 1, f);
    source[fsize] = 0;
    
    fclose(f);

    char* buffer = (char*) malloc(fsize + 1);

    memcpy(buffer, source, fsize + 1);
    fast_mpd_parser::parse(buffer, fsize);

    for (int i = 0; i < 99; i++) {
        memcpy(buffer, source, fsize + 1);
        fast_mpd_parser::parse(buffer, fsize);
    } 

    // std::cout << "Read. File size is " << fsize << std::endl;
    // std::cout << "Size of a mpd is " << sizeof(fast_mpd_parser::Mpd) << std::endl;
    // std::cout << "Size of a period is " << sizeof(fast_mpd_parser::Period) << std::endl;

    return 0;
}