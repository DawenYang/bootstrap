//
// Created by Dawen on 1/4/23.
//

#ifndef BOOTSTRAP_HEX_FORMATTER_H
#define BOOTSTRAP_HEX_FORMATTER_H

namespace basecode {

    class hex_formatter {
    public:
        static std::string dump_to_string(const void* data, size_t size);
    };

} // basecode

#endif //BOOTSTRAP_HEX_FORMATTER_H
