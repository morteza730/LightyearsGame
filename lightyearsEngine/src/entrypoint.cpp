#include "entrypoint.hpp"
#include "framework/application.hpp"

int main(){
    ly::Application *app = getApplication();
    app->run();
    delete app;
    return 0;
}