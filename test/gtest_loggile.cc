#include "gtest/gtest.h"
#include "../include/base/logfile.h"
#include "../include/base/logging.h"
#include <string>
#include <memory>

using namespace muduonet;

std::unique_ptr<LogFile> g_logfile;

void outputFunc(const char* msg, int len) {
    g_logfile->append(msg, len);
}

void flushFunc() {
    g_logfile->flush();
}

TEST(MUDUONET, logfile) {
    g_logfile.reset(new LogFile("chencong", /*rollsize*/ 200*1000));
    Logger::setOutput(outputFunc);
    Logger::setFlush(flushFunc);
    std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFJHIJKLMNOPQRSTUVWXYZ ";
    for (int i=0; i < 10; ++i) {
        LOG_INFO << line << i;
        usleep(1000);
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
