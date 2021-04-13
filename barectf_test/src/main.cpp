#include <iostream>
#include <string>
#include <sstream>
#include "platforms/linux-fs/barectf-platform-linux-fs.h"
#include "barectf.h"

int main() {
    struct barectf_platform_linux_fs_ctx *platform_ctx =
            barectf_platform_linux_fs_init(512, "../barectf_test/gen/traces/test_ctf_traces", 0, 0, 0);

    if (!platform_ctx) {
        std::cerr << "Error: failed to initialize Linux FS platform.\n";
        return -1;
    }

    struct barectf_default_ctx *ctx =
            barectf_platform_linux_fs_get_barectf_ctx(platform_ctx);

    for (int i = 0; i < 10; i++) {
        std::stringstream ss;
        ss << "next number is " << i;
        barectf_trace_one_string(barectf_platform_linux_fs_get_barectf_ctx(platform_ctx), ss.str().c_str());
    }

    barectf_platform_linux_fs_fini(platform_ctx);
    return 0;
}
