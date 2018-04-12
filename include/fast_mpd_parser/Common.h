namespace fast_mpd_parser {
    enum Status {
        Success
    };

    inline uint64_t fast_atoi(const char* s) {
        uint64_t r = 0;
        while(*s) {
            r = r * 10 + (*s++ - '0');
        }
        return r;
    }

    #define FMP__SCAN_CHAR(c) while (pos < size && buffer[pos] != c) { pos++; }
    #define FMP__SKIP_CHAR(c) while (pos < size && buffer[pos] == c) { pos++; }

    #define FMP__LOC_NEXT_ATTR() \
        { \
            FMP__SKIP_CHAR(' '); \
            \
            attr_name_start = pos; \
            FMP__SCAN_CHAR('='); \
            attr_name_end = pos; \
            buffer[attr_name_end] = 0; \
            \
            pos++; \
            quote = buffer[pos]; \
            pos++; \
            \
            attr_value_start = pos; \
            FMP__SCAN_CHAR(quote); \
            attr_value_end = pos; \
            buffer[attr_value_end] = 0; \
            attr_name_len = attr_name_end - attr_name_start; \
            pos++; \
            \
            FMP__SKIP_CHAR(' '); \
        }

    #define FMP__LOC_NEXT_TAG() \
        { \
            FMP__SCAN_CHAR('<'); \
            pos++; \
            if (buffer[pos] == '/') { \
                found_close_tag = true; \
                FMP__SCAN_CHAR('>'); \
                pos++; \
                continue; \
            } \
            \
            if (buffer[pos] == '!' || buffer[pos] == '?') { \
                FMP__SCAN_CHAR('>'); \
                pos++; \
                continue; \
            } \
            \
            tag_name_start = pos; \
            FMP__SCAN_CHAR_TYPE(ct_space | ct_parse_cdata); \
            tag_name_end = pos; \
            tag_name_len = tag_name_end - tag_name_start; \
        }

    enum chartype_t {
        ct_parse_pcdata = 1,    // \0, &, \r, <
        ct_parse_attr = 2,      // \0, &, \r, ', "
        ct_parse_attr_ws = 4,   // \0, &, \r, ', ", \n, tab
        ct_space = 8,           // \r, \n, space, tab
        ct_parse_cdata = 16,    // \0, ], >, \r
        ct_parse_comment = 32,  // \0, -, >, \r
        ct_symbol = 64,         // Any symbol > 127, a-z, A-Z, 0-9, _, :, -, .
        ct_start_symbol = 128   // Any symbol > 127, a-z, A-Z, _, :
    };

    static const unsigned char chartype_table[256] = {
        55,  0,   0,   0,   0,   0,   0,   0,      0,   12,  12,  0,   0,   63,  0,   0,   // 0-15
        0,   0,   0,   0,   0,   0,   0,   0,      0,   0,   0,   0,   0,   0,   0,   0,   // 16-31
        8,   0,   6,   0,   0,   0,   7,   6,      0,   0,   0,   0,   0,   96,  64,  0,   // 32-47
        64,  64,  64,  64,  64,  64,  64,  64,     64,  64,  192, 0,   1,   0,   48,  0,   // 48-63
        0,   192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 64-79
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 0,   0,   16,  0,   192, // 80-95
        0,   192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 96-111
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 0, 0, 0, 0, 0,           // 112-127

        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 128+
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192
    };

    #define FMP__IS_CHAR_TYPE(c, ct) (chartype_table[static_cast<uint8_t>(c)] & (ct))
    #define FMP__SCAN_CHAR_TYPE(ct) while (pos < size && !FMP__IS_CHAR_TYPE(buffer[pos], ct)) { pos++; }
}