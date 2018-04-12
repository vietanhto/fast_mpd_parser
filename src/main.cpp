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

    fast_mpd_parser::Mpd* ptr_mpd = (fast_mpd_parser::Mpd*) calloc(100, sizeof(fast_mpd_parser::Mpd));

    memcpy(buffer, source, fsize + 1);
    fast_mpd_parser::parse(buffer, fsize, ptr_mpd);

    for (int i = 1; i < 100; i++) {
        memcpy(buffer, source, fsize + 1);
        fast_mpd_parser::parse(buffer, fsize, ptr_mpd + i);
    } 

    // std::cout << "Read. File size is " << fsize << std::endl;
    // std::cout << "Size of a mpd is " << sizeof(fast_mpd_parser::Mpd) << std::endl;
    // std::cout << "Size of a period is " << sizeof(fast_mpd_parser::Period) << std::endl;
    
    free(buffer);
    free(source);

    for (int i = 0; i < 100; i++) {
        fast_mpd_parser::free_mpd(ptr_mpd + i);
    } 
    free(ptr_mpd);

    return 0;
}