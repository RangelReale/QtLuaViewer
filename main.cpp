#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "LuaIntf/LuaIntf.h"

#include <iostream>

#include <QApplication>

#include "LuaStateWidget.h"

int main (int argc, char *argv[]) 
{
	LuaIntf::LuaContext L(true);

	try
	{
		QApplication app(argc, argv);

		LuaStateWidget w;
		w.show();

		w.update(L.globals());

		app.exec();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Press any key to continue..." << std::endl;
		std::cin.ignore();
	}

}
