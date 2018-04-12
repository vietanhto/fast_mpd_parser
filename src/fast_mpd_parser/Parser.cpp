#include "fast_mpd_parser/Include.h"

namespace fast_mpd_parser {

    inline uint64_t fast_atoi( const char * str ) {
        uint64_t val = 0;
        while( *str ) {
            val = val*10 + (*str++ - '0');
        }
        return val;
    }

    void parse1(char* buffer, uint32_t size) {
        uint32_t pos = 0;
        goto STATE_START;

    STATE_START:
        FMP__SCAN_CHAR('<');

        goto STATE_READ_TAG;

    //go here if the current character is '<'
    STATE_READ_TAG:
        pos++;//skip '<'
        if (pos >= size) {
            goto STATE_END;
        }

        switch(buffer[pos]) {
            case '/':
                pos++;
                goto STATE_READ_TAG_CLOSE;
            case '?':
            case '!':
                //skip metadata tag
                while (pos < size && buffer[pos] != '>') {
                    pos++;
                }
                pos++; //skip '>'
                goto STATE_READ_CONTENT;
            default:
                goto STATE_READ_TAG_OPEN;
        }

    //go here if the previous character is '<' and current characterr is not '/' or '?'
    STATE_READ_TAG_OPEN:
        uint32_t tag_name_start, tag_name_end;
        char lower_case_char;
        tag_name_start = pos;
        while (pos < size && buffer[pos] != ' ') {
            pos++;
        }
        tag_name_end = pos;
        buffer[tag_name_end] = 0;


        goto STATE_READ_ATTRIBUTE;

    //go here if the previous character is '<' and current character is not '/'
    STATE_READ_TAG_CLOSE:
        FMP__SCAN_CHAR('>');
        pos++; //skip '>'
        goto STATE_READ_CONTENT;

    //go here if we are inside a tag and current character is white space
    STATE_READ_ATTRIBUTE:
        while (pos < size && buffer[pos] == ' ') {
            pos++;
        }

        uint32_t attr_name_start, attr_name_end, attr_value_start, attr_value_end;
        char quote;
        switch(buffer[pos]) {
            case '/':
                pos++;//skip '/'
                pos++;//skip '>'
                goto STATE_READ_CONTENT;
            case '>':
                pos++;//skip '>'
                goto STATE_READ_CONTENT;
            default:
                break;
        }
        
        attr_name_start = pos;
        while (pos < size && buffer[pos] != '=') {
            pos++;
        }
        attr_name_end = pos;
        buffer[attr_name_end] = 0;

        pos++;//skip '='
        quote = buffer[pos];
        pos++;//skip quote
        attr_value_start = pos;
        while (pos < size && buffer[pos] != quote) {
            pos++;
        }
        attr_value_end = pos;
        buffer[attr_value_end] = 0;

        if (0 == strncmp(buffer + attr_name_start, "d", 1)) {
            // std::cout << buffer + attr_name_start << std::endl;
            uint64_t test = std::atoi(buffer + attr_value_start);
        }

        if (0 == strncmp(buffer + attr_name_start, "mediaRange", 10)) {
            // std::cout << buffer + attr_name_start << std::endl;
            uint64_t start = std::atoi(buffer + attr_value_start) * 1000 / 200000;
            uint64_t end = std::atoi(buffer + attr_value_start) * 1000 / 200000;
        }

        pos++;//skip quote

        goto STATE_READ_ATTRIBUTE;

    //go here if the previous character is '>'
    STATE_READ_CONTENT:
        while (pos < size && buffer[pos] != '<') {
            pos++;
        }
        goto STATE_READ_TAG;

    STATE_END:
        // std::cout << "number of media_ranges is " << media_ranges.size() << std::endl;
        return;
    }

    void parse(char* buffer, uint32_t size) {
        Mpd* pMpd = (Mpd*) calloc(1, sizeof(Mpd));
        uint32_t pos = 0;

        FMP__SCAN_CHAR('<');
        pos++;
        // std::cout << "pos is " << pos <<", text is " << buffer + pos << std::endl;
        FMP__SCAN_CHAR('<');
        FMP__SCAN_CHAR_TYPE(ct_space);

        parse_mpd(buffer, size, &pos, pMpd);
        free_mpd(pMpd);
    }

    void parseTag(char* buffer, uint32_t size, uint32_t* pPos, void* elem) {
        uint32_t pos = *pPos;
        uint32_t tag_name_start, 
            tag_name_end, 
            tag_name_len;
        FMP__SCAN_CHAR('>');
        uint32_t prev_pos = pos - 1;
        bool found_close_tag = false;

        if (buffer[prev_pos] == '/' || buffer[prev_pos] == '-' || buffer[prev_pos]=='?') {
            pos++;
            goto CleanUp;
        }

        while (!found_close_tag) {
            FMP__SCAN_CHAR('<');
            pos++;
            if (buffer[pos] == '/') {
                found_close_tag = true;
                FMP__SCAN_CHAR('>');
                pos++;
                continue;
            }

            if (buffer[pos] == '!' || buffer[pos] == '?') {
                FMP__SCAN_CHAR('>');
                pos++;
                continue;
            }

            tag_name_start = pos;
            FMP__SCAN_CHAR_TYPE(ct_space | ct_parse_cdata);
            tag_name_end = pos;
            // printf("%.*s\n",tag_name_end - tag_name_start,buffer + tag_name_start);

            *pPos = pos;
            parseTag(buffer, size, pPos, NULL);
            pos = *pPos;
        }

    CleanUp:
        *pPos = pos;
    }
}