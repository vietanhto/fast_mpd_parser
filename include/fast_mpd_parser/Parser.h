#ifndef FAST_MPD_PARSER_PARSER_H
#define FAST_MPD_PARSER_PARSER_H

namespace fast_mpd_parser {
    Status parse(char* buffer, uint32_t size, Mpd* ptr_mpd);

    Status parse_mpd(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);
    
    Status parse_period(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);
    
    Status parse_adaptation_set(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);
    
    Status parse_representation(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);
    
    Status parse_segment_list(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);
    
    Status parse_segment_url(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);
    
    /**
     * Requirement: pos is right after tag name
     * tag_name_
     *         ^
     *         |
     *        pos
     * After parsing, pos is right after close tag
     * </tag_name>_
     *            ^
     *            |
     *           pos
     */
    void parseTag(char* buffer, uint32_t size, uint32_t* ptr_pos, void* elem);

    void free_representation(Representation* ptr_representation);

    void free_adaptation_set(AdaptationSet* ptr_adaptation_set);

    void free_period(Period* ptr_period);

    void free_mpd(Mpd* ptr_mpd);
}

    

#endif //FAST_MPD_PARSER_PARSER_H