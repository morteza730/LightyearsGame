#include <iostream>
#include "framework/application.hpp"

int main(){
	ly::Application *app = new ly::Application("light years",480,640);
	app->run();
	return 0;
}