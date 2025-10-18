#include "EntryPoint.h"

int main(int argc, char** argv) {
    auto app = CreateApplication();
    app->defaultOnInit();
    app->defaultRun();
    app->defaultOnExit();
    delete(app);
    return 0;
};